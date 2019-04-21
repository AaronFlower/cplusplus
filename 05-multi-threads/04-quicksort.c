#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 64

int *initData() {
   int *p = (int *)malloc(sizeof(int) * INIT_SIZE);
   if (p == NULL) {
       perror("[-] Error malloc");
       exit(1);
   }
   return p;
}


int *reMalloc(int *data, size_t cap) {
    data = (int *)realloc(data, cap *2);
    if (data == NULL) {
        perror("[-] Error realloc");
        exit(1);
    }
    return data;
}

int partition(int *data, int begin, int end) {
    int i = begin - 1;
    int j = begin;
    int pivot  = data[end - 1];
    int tmp;

    for (; j < end; ++j) {
        if (data[j] < pivot) {
            ++i;
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
        }
    }
    ++i;
    tmp = data[i];
    data[i] = data[j - 1];
    data[j - 1] = tmp;
    return i;
}

void quickSort(int *data, int begin, int end) {
    if (begin < end) {
        int i = partition(data, begin, end);
        quickSort(data, begin, i);
        quickSort(data, i + 1, end);
    }
}

int main(void)
{
    int num;
    size_t cap = INIT_SIZE, len = 0;
    int *data = initData();
    FILE *fdIn, *fdOut;
    if ((fdIn = fopen("data.in", "r")) == NULL) {
        perror("[-] Error fopen data.in");
        exit(1);
    }


    while(fscanf(fdIn, "%d\n", &num) != EOF) {
        if (++len > cap) {
            data = reMalloc(data, cap);
        }
        data[len - 1] = num;
    }
    fclose(fdIn);

    quickSort(data, 0, len);

    if ((fdOut = fopen("data.out", "w")) == NULL) {
        perror("[-] Error fopen data.out");
        exit(1);
    }

    for (size_t i = 0; i < len; ++i) {
        fprintf(fdOut, "%d ", data[i]);
    }
    fclose(fdOut);

    free(data); // todo why free the data is error

    return 0;
}
