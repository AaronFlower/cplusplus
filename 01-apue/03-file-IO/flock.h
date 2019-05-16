#ifndef FILE_LOCK_HELPER__
#define FILE_LOCK_HELPER__

/* 关于文件记录锁的一些帮助函数 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int
lock_reg(int fd,
        int cmd,
        int type,
        off_t offset,
        int whence,
        off_t len) {
    struct flock lock;

    lock.l_type = type;
    lock.l_whence = whence;
    lock.l_start = offset;
    lock.l_len = len;

    return fcntl(fd, cmd, &lock);
}


#define read_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))

#define readw_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))

#define write_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))

#define writew_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))

#define un_lock(fd, offset, whence, len) \
    lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))

// 检测是否有锁
pid_t lock_test(int fd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;

    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;

    if (fcntl(fd, F_GETLK, &lock) < 0) {
        perror("[-] Error fntl");
        exit(1);
    }

    if (lock.l_type == F_UNLCK) {
        return 0;
    }
    return lock.l_pid;
}

#define is_read_lockable(fd, offset, whence, len) \
    (lock_test((fd), F_RDLCK, (offset), (whence), (len)) == 0)

#define is_write_lockabel(fd, offset, whence, len) \
    (lock_test((fd), F_WRLCK, (offset), (whence), (len)) == 0)

#endif /* ifndef FILE_LOCK_HELPER__ */
