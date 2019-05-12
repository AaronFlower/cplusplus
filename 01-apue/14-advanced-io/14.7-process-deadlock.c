#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // fork, wirte, read
#include <fcntl.h>      // creat, fcntl
#include <signal.h>     // about signal function
#include <errno.h>

/*
 * Default file access permissions for new files.
 */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


// 填充 flock 结构体的帮助函数。
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len) {
    struct flock lock;
    lock.l_type = type;         // F_RDLCK, F_WRLCK, F_UNLCK
    lock.l_start = offset;      // byte offset, relative to l_whence
    lock.l_whence = whence;     // SEEK_SET, SEEK_CUR, SEEK_END
    lock.l_len = len;           // #bytes (0 means to EOF);

    return fcntl(fd, cmd, &lock);
}

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    (void)signo;
    sigflag = 1;
}

// 初始化进程信号集
void TELL_WAIT(void) {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        perror("[-] Error signal SIGUSR1");
        exit(1);
    }

    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        perror("[-] Error signal SIGUSR2");
        exit(1);
    }

    sigemptyset(&newmask);
    sigemptyset(&zeromask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        perror("[-] Error SIG_BLOCK");
        exit(1);
    }
}

void TELL_PARENT(pid_t pid) {
    kill(pid, SIGUSR2);
}

void WAIT_PARENT(void) {
    while (sigflag == 0) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("[-] Error SIG_SETMASK ");
        exit(1);
    }
}

void TELL_CHILD(pid_t pid) {
    kill(pid, SIGUSR1);
}

void WAIT_CHILD(void) {
    while(sigflag == 0) {
        sigsuspend(&zeromask);
    }
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        perror("[-] Error SIG_SETMASK");
        exit(1);
    }
}

static void lockabyte(const char *name, int fd, off_t offset) {
    // F_SETLKW 命令多了一个 W
    // This command is the same as F_SETLK except that if a shared or exclusive
    // lock is blocked by other locks, the process waits until the request can be
    // satisfied.
    int ret = lock_reg(fd, F_SETLKW, F_WRLCK, offset, SEEK_SET, 1);
    if (ret < 0 ) {
       perror("[-] Error writew_lock error ");
       exit(1);
    }
    printf("%s: got the lock byte %lld \n", name, (long long)offset);
}

int main(void)
{
    int fd;
    pid_t pid;

    /**
     * create a file and write two bytes to it.
     * creat() is obselete, you can instead use open.
     */
    if ((fd = creat("templock", FILE_MODE)) < 0) {
        perror("[-] Error create");
        exit(1);
    }

    if (write(fd, "ab", 2) != 2) {
        perror("[-] Error write");
        exit(1);
    }

    TELL_WAIT();

    if ((pid = fork()) < 0) {
        perror("[-] Error fork");
        exit(1);
    } else if (pid == 0) {
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else {
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }

    return 0;
}
