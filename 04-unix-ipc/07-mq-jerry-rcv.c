#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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

    if ((msqid = msgget(key, 0644)) == -1) { // connect to the queue
        perror("[-] Error msgget");
        exit(1);
    }

    printf("Jerry: ready to receive messages, Tom. \n");
    for (;;) {
        if (msgrcv(msqid, &buf, sizeof buf.mtext, 0, 0) == -1) {
            perror("[-] Error msgrcv");
            exit(1);
        }
        printf("Jerry: \"%s\" \n", buf.mtext);
    }
    return 0;
}
