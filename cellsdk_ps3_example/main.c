#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/fs.h>
#include <dirent.h>

#include <sys/process.h>
#include <cell/cell_fs.h>
#include <sys/syscall.h>
#include <sys/synchronization.h>

#include "ntfs.h"

int main()
{
	NTFS_init_system_io();

	//ps3ntfs_open("ntfs0:/text.txt", O_RDONLY, 0);

	return 0;
}
