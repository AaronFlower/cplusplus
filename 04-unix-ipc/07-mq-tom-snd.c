#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


typedef struct my_msgbuf {
    long mtype;
    char mtext[200];
} msgbuf;

int main(void)
{
    msgbuf buf;
    int msqid;
    key_t key;

    if ((key = ftok("07-mq-tom-snd.c", 'A')) == -1) {
        perror("[-] Error ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("[-] Error msgget");
        exit(1);
    }

    printf("Enter lines of text, ^D to quit: \n");
    buf.mtype = 1; // we don't really care in this case.

    while (fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        int len = strlen(buf.mtext);

        // ditch newline at end, if it exists.
        if (buf.mtext[len - 1] == '\n') {
            buf.mtext[len - 1] = '\0';
        }
        if (msgsnd(msqid, &buf, len + 1, 0) == -1) { // +1 for '\0'
            perror("[-] Error msgsnd");
            exit(1);
        }
    }

    // destroy the queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("[-] Error msgctl");
        exit(1);
    }

    return 0;
}
