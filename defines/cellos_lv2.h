#ifndef _PS3_DEFINES_H
#define _PS3_DEFINES_H

// *** sys/stat.h *** //

#define	_IFCHR	0020000	/* character special */
#define	_IFBLK	0060000	/* block special */
#define	_IFSOCK	0140000	/* socket */
#define	_IFIFO	0010000	/* fifo */

#define _IFMT 0170000	/* type of file */
#define _IFDIR 0040000	/* directory */
#define _IFREG 0100000	/* regular */
#define _IFLNK 0120000	/* symbolic link */
#define _IFWHT 0160000	/* unknown */
#define _IRWXU 0000700	/* RWX mask for owner */
#define _IRUSR 0000400	/* R for owner */
#define _IWUSR 0000200	/* W for owner */
#define _IXUSR 0000100	/* X for owner */
#define _IRWXG 0000070	/* RWX mask for group */
#define _IRGRP 0000040	/* R for group */
#define _IWGRP 0000020	/* W for group */
#define _IXGRP 0000010	/* X for group */
#define _IRWXO 0000007	/* RWX mask for other */
#define _IROTH 0000004	/* R for other */
#define _IWOTH 0000002	/* W for other */
#define _IXOTH 0000001	/* X for other */

#define	S_IFCHR	0020000	/* character special */
#define	S_IFBLK	0060000	/* block special */
#define	S_IFSOCK	0140000	/* socket */
#define	S_IFIFO	0010000	/* fifo */

#define	S_ISBLK(m)	(((m)&_IFMT) == _IFBLK)
#define	S_ISCHR(m)	(((m)&_IFMT) == _IFCHR)
#define	S_ISDIR(m)	(((m)&_IFMT) == _IFDIR)
#define	S_ISFIFO(m)	(((m)&_IFMT) == _IFIFO)
#define	S_ISREG(m)	(((m)&_IFMT) == _IFREG)
#define	S_ISLNK(m)	(((m)&_IFMT) == _IFLNK)
#define	S_ISSOCK(m)	(((m)&_IFMT) == _IFSOCK)

#define S_IEXEC		S_IXUSR
#define	S_ISVTX		0001000	/* save swapped text even after use */
#define	S_IREAD		0000400	/* read permission, owner */
#define	S_IWRITE 	0000200	/* write permission, owner */
#define	S_ISGID		0002000	/* set group id on execution */
#define	S_ISUID		0004000	/* set user id on execution */

// *** errno.h *** //

#define EOPNOTSUPP ENOTSUP
#define ELOOP EMLINK

// *** sys/synchronization.h *** //

#define sys_mutex_attr_t sys_mutex_attribute_t
#define sys_lwmutex_attr_t sys_lwmutex_attribute_t
#define sysLwMutexCreate sys_lwmutex_create
#define sysLwMutexDestroy sys_lwmutex_destroy
#define sysLwMutexLock sys_lwmutex_lock
#define sysLwMutexTryLock sys_lwmutex_trylock
#define sysLwMutexUnlock sys_lwmutex_unlock

#define SYS_LWMUTEX_ATTR_RECURSIVE SYS_SYNC_RECURSIVE
#define SYS_LWMUTEX_ATTR_PROTOCOL SYS_SYNC_PRIORITY

// -------------------------------- //

// *** sys/syscall.h *** //

#define lv2syscall1 system_call_1
#define lv2syscall2 system_call_2
#define lv2syscall3 system_call_3
#define lv2syscall4 system_call_4
#define lv2syscall5 system_call_5
#define lv2syscall6 system_call_6
#define lv2syscall7 system_call_7
#define lv2syscall8 system_call_8

// *** cell/fs/cell_fs_file_api.h *** //

#define sysFSStat CellFsStat
#define sysFSDirent CellFsDirent

#define sysLv2FsFStat cellFsFstat
#define sysLv2FsStat cellFsStat
#define sysLv2FsOpenDir cellFsOpendir
#define sysLv2FsOpen cellFsOpen
#define sysLv2FsChmod cellFsChmod
#define sysLv2FsClose cellFsClose
#define sysLv2FsRmdir cellFsRmdir
#define sysLv2FsUnlink cellFsUnlink
#define sysLv2FsRename cellFsRename
#define sysLv2FsMkdir cellFsMkdir
#define sysLv2FsCloseDir cellFsClosedir
#define sysLv2FsReadDir cellFsReaddir
#define sysLv2FsFtruncate cellFsFtruncate
#define sysLv2FsFsync cellFsFsync
#define sysLv2FsWrite cellFsWrite
#define sysLv2FsRead cellFsRead
#define sysLv2FsLSeek64 cellFsLseek

// *** sys/fs_external.h *** //

#define SYS_O_MSELF CELL_FS_O_MSELF
#define SYS_O_CREAT CELL_FS_O_CREAT
#define SYS_O_EXCL CELL_FS_O_EXCL
#define SYS_O_TRUNC CELL_FS_O_TRUNC
#define SYS_O_APPEND CELL_FS_O_APPEND

// ** miscellaneous *** //

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define usleep sys_timer_usleep

#define _exit _Exit

#endif //_PS3_DEFINES_H
