#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include <sys/fs.h>
#include <sys/process.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/synchronization.h>

#include <cell/sysmodule.h>
#include <cell/cell_fs.h>

#include "ntfs.h"

#define PATH_MAX 255

SYS_PROCESS_PARAM(1001, 0x10000)
int max_list = 0;
static char buff[4096];

int LOG;

void log_printf(const char *format, ...);
void list(const char *path, int depth);
int NTFS_Event_Mount(int id);
int NTFS_UnMount(int id);
void NTFS_UnMountAll(void);
int NTFS_Test_Device(const char *name);

void log_printf(const char *format, ...)
{
	char *str = (char *) buff;
	va_list	opt;
	
	va_start(opt, format);
	vsprintf( (void *) buff, format, opt);
	va_end(opt);
	
	uint64_t sw;
	cellFsWrite(LOG, (const void *) str, (uint64_t)strlen(str), &sw);
}

void list(const char *path, int depth)
{
	DIR_ITER *pdir;
	struct stat st;
	char indent[PATH_MAX] = {0};
	char new_path[PATH_MAX] = {0};
	char filename[PATH_MAX] = {0};
	

	// Open the directory
	pdir = ps3ntfs_diropen(path);

	if (pdir) {

		// Build a directory indent (for better readability)
		memset(indent, ' ', depth * 2);
		indent[depth * 2] = 0;

		// List the contents of the directory
		while (ps3ntfs_dirnext(pdir, filename, &st) == 0) {
		  
			if ((strcmp(filename, ".") == 0) || (strcmp(filename, "..") == 0))
				continue;

			max_list++;
			if(max_list > 10) break;

			
			sprintf(new_path, "%s/%s", path, filename);
			//ps3ntfs_stat(new_path, &st);
			// List the entry
			if (S_ISDIR(st.st_mode)) {
				log_printf(" D %s%s/\n", indent, filename);

				// List the directories contents
				
				//list(new_path, depth + 1); // recursive list
			   
			} else if (S_ISREG(st.st_mode)) {
				log_printf(" F %s%s (%lu)\n", indent, filename, (unsigned long int)st.st_size);
			} else {
				log_printf(" ? %s%s\n", indent, filename);
			}

		}

		// Close the directory
		ps3ntfs_dirclose(pdir);

	} else {
		log_printf("opendir(%s) failure.\n", path);
	}

	return;
}

const DISC_INTERFACE *disc_ntfs[8]= {
	&__io_ntfs_usb000,
	&__io_ntfs_usb001,
	&__io_ntfs_usb002,
	&__io_ntfs_usb003,
	&__io_ntfs_usb004,
	&__io_ntfs_usb005,
	&__io_ntfs_usb006,
	&__io_ntfs_usb007
};

// mounts from /dev_usb000 to 007
ntfs_md *mounts[8] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
int mountCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int automountCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};

u32 ports_cnt = 0, old_ports_cnt = 0;

// NOTE: NTFS_Event_Mount() must be in the main loop. Automount count is 300 because 300 / 60 fps = 5 seconds
// to wait system operations before to mount the device

int NTFS_Event_Mount(int id) 
{
	int r = 0;

	ports_cnt &= ~(1<<id);
	if(PS3_NTFS_IsInserted(id)) ports_cnt |= 1<<id;

	if( ((ports_cnt>>id) & 1) && !((old_ports_cnt>>id) & 1)) automountCount[id] = 300; // enable delay event

	if(automountCount[id]>0) { // if delay counter ticks...
		automountCount[id]--; if(automountCount[id]==0) r = 1; // mount device
	}

	if( !((ports_cnt>>id) & 1) && ((old_ports_cnt>>id) & 1)) { // unmount device
		automountCount[id]=0; r = -1; 
	}

	old_ports_cnt = ports_cnt;

	return r;
}

int NTFS_UnMount(int id)
{
	int ret = 0;

	if (mounts[id]) {
		int k;
		for (k = 0; k < mountCount[id]; k++)
			if((mounts[id]+k)->name[0]) 
				{ret = 1; ntfsUnmount((mounts[id]+k)->name, true); (mounts[id]+k)->name[0] = 0;}

		free(mounts[id]); 
		mounts[id]= NULL;
		mountCount[id] = 0;
	}
	
	PS3_NTFS_Shutdown(id);

	return ret;
}

void NTFS_UnMountAll(void)
{ 
	int i;

	for(i = 0; i < 8; i++) {
		NTFS_UnMount(i);
	}
}

int NTFS_Test_Device(const char *name)
{
	int k, i;

	for(k = 0; k < 8; k++) {
		for (i = 0; i < mountCount[k]; i++)
		if(!strncmp((mounts[k]+i)->name, name, 5 - 1 *( name[0] == 'e'))) 
			return ((mounts[k] + i)->interface->ioType & 0xff) - '0';
	}

	return -1;
	
}

char message[] ="This is a NTFS file test writing";
char buffer[1024];

int main(void)
{
	int ret;
	
	ret = cellSysmoduleLoadModule(CELL_SYSMODULE_FS);
	if (ret != CELL_OK) return ret;
	
	ret = cellFsOpen("/dev_hdd0/libntfs_sample_log.txt",
                     CELL_FS_O_RDWR|CELL_FS_O_CREAT, &LOG, NULL, 0);
	if(ret) return ret;
	
	const char *cur_device = "/ntfs0:";
	char path[1024];
	int i, k, r;
	
	for(k = 0; k < 8; k++) {
		for (i = 0; i < mountCount[k]; i++)
		log_printf("%i - %s:/ (%s) (from usb00%i)\n", i + 1, 
		(mounts[k]+i)->name, ntfsGetVolumeName((mounts[k] + i)->name), 
			((mounts[k] + i)->interface->ioType & 0xff) - '0');
	}

	cur_device = NULL;
	r = NTFS_Test_Device("ext0"); log_printf("\nTest ext0 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ext0:";

	r = NTFS_Test_Device("ext1"); log_printf("Test ext1 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ext1:";

	r = NTFS_Test_Device("ext2"); log_printf("Test ext2 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ext2:";

	r = NTFS_Test_Device("ext3"); log_printf("Test ext3 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ext3:";

	r = NTFS_Test_Device("ntfs0"); log_printf("Test ntfs0 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ntfs0:";

	r = NTFS_Test_Device("ntfs1"); log_printf("Test ntfs1 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ntfs1:";

	r = NTFS_Test_Device("ntfs2"); log_printf("Test ntfs2 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ntfs2:";

	r = NTFS_Test_Device("ntfs3"); log_printf("Test ntfs3 %i\n" , r);
	if(r>=0 && !cur_device) cur_device = "/ntfs3:";

	if(!cur_device) cur_device = "/ntfs0:"; // by default

	for(i = 0; i < 8 ; i++) {
		r = NTFS_Event_Mount(i);

		if(r == 1) { // mount device

			NTFS_UnMount(i);

			mounts[i] = NULL;
			mountCount[i] = 0;

			mountCount[i] = ntfsMountDevice (disc_ntfs[i], &mounts[i], NTFS_DEFAULT | NTFS_RECOVER);
			
		} else if(r == -1) { // unmount device
			NTFS_UnMount(i);
		}
	}


	max_list = 0;

	log_printf("Listing 10 entries from %s (5 seconds)\n", cur_device);

	sprintf(path, "%s", cur_device);

	list(path, 0);

	log_printf("\n\nWriting / Reading a file from %s\n", cur_device);

	sprintf(path, "%s/0text", cur_device);

	ps3ntfs_mkdir(path, 0777);

	sprintf(path, "%s/0text/test.txt", cur_device);

	int fd= ps3ntfs_open(path, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		
	if(fd > 0) {
		i = ps3ntfs_write(fd, message, strlen(message));

		if(i != (int) strlen(message)) log_printf("Error writing the file!\n");

		ps3ntfs_close(fd);


	} else log_printf("Error creating the file!\n");

	memset(buffer, 0, 1024);

	sprintf(path, "%s/0text/test.txt", cur_device);

	fd= ps3ntfs_open(path, O_RDONLY, 0);
		   
	if(fd > 0) {

		int size = ps3ntfs_seek(fd, 0, SEEK_END);

		log_printf ("Size of file %i\n", size);

		ps3ntfs_seek(fd, 0, SEEK_SET);
		
		i = ps3ntfs_read(fd, buffer, size);

		if(i != size) log_printf("Error reading the file!\n");

		ps3ntfs_close(fd);

	} else log_printf("Error Reading the file!\n");

	log_printf("Readed From file: %s\n\n", buffer);
	
	log_printf("Umounting...");
 
	NTFS_UnMountAll();
	
	log_printf("OK\n");
	
	cellFsClose(LOG);
	
	return 0;
}