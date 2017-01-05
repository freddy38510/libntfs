#ifndef _PS3_DEFINES_H
#define _PS3_DEFINES_H

// *** sys/stat.h *** //

#define	S_IFCHR	0020000	/* character special */
#define	S_IFBLK	0060000	/* block special */
#define	S_IFSOCK 0140000 /* socket */
#define	S_IFIFO	0010000	/* fifo */

#define	S_ISBLK(m)	(((m)&S_IFMT) == S_IFBLK)
#define	S_ISCHR(m)	(((m)&S_IFMT) == S_IFCHR)
#define	S_ISDIR(m)	(((m)&S_IFMT) == S_IFDIR)
#define	S_ISFIFO(m)	(((m)&S_IFMT) == S_IFIFO)
#define	S_ISREG(m)	(((m)&S_IFMT) == S_IFREG)
#define	S_ISLNK(m)	(((m)&S_IFMT) == S_IFLNK)
#define	S_ISSOCK(m)	(((m)&S_IFMT) == S_IFSOCK)

#define	S_ISVTX 0001000
#define S_ISGID 0002000
#define	S_ISUID	0004000

#define S_IEXEC S_IXUSR
#define S_IWRITE S_IWUSR
#define S_IREAD S_IRUSR

// *** errno.h *** //

#define EOPNOTSUPP ENOTSUP
#define ELOOP EMLINK
#define EADDRNOTAVAIL EAGAIN
#define EADDRINUSE EBUSY

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

// *** sys/fs_external.h *** //

//#define FS_S_IFMT CELL_FS_S_IFMT

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
