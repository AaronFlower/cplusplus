#include "test.h"
#include <arpa/inet.h>

#define UNKNOWN_ENDIAN -1;

typedef union {
    short val;
    char c[sizeof(short)];
} un_short;

typedef union {
    int val;
    char c[sizeof(int)];
} un_int;

/**
 * static 函数的意思是指，该函数只作用于编译单元中，如果没有调用能被发现的, 编译时会报 [-Wunused-function] 。
 */
static void test_endian() {
    union {
        short s;
        char c[sizeof(short)];
    } un;

    un.s = 0x0102;
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2) {
            printf("big-endian\n");
        } else if (un.c[0] == 2 && un.c[1] == 1) {
            printf("little-endian\n");
        } else {
            printf("Unkown \n");
        }
    } else {
        fprintf(stdout, "sizeof(short) = %lu\n", sizeof(short));
    }
}

static int get_byte_order() {
    un_short un;
    un.val = 0x0102;

    if (sizeof(short) == 2) {
        if (un.c[0] == 0x01 && un.c[1] == 0x02) {
            return BIG_ENDIAN;
        } else if (un.c[0] == 0x02 && un.c[1] == 0x01) {
            return LITTLE_ENDIAN;
        } else {
            return UNKNOWN_ENDIAN;
        }
    } else {
        printf("sizeof(short) = %lu\n", sizeof(short));
        return UNKNOWN_ENDIAN;
    }
}

static void test_order () {
    un_short us;
    us.val = 0x1234;
    un_int ui;
    ui.val = 0x12345678;
    int order = get_byte_order();
    switch (order) {
        case BIG_ENDIAN:
            EXPECT_EQ_HEX(us.c[0], 0x12);
            EXPECT_EQ_HEX(us.c[1], 0x34);
            break;
        case LITTLE_ENDIAN:
            EXPECT_EQ_HEX(us.c[0], 0x34);
            EXPECT_EQ_HEX(us.c[1], 0x12);

            EXPECT_EQ_HEX(ui.c[0], 0x78);
            EXPECT_EQ_HEX(ui.c[1], 0x56);
            EXPECT_EQ_HEX(ui.c[2], 0x34);
            EXPECT_EQ_HEX(ui.c[3], 0x12);
            break;
        default:
            break;
    }
}

static void test_aton() {
    const char* addr[] = {"1.0.0.0", "127.0.0.1", "244.0.0.1", "255.255.255.255"};
    size_t len = sizeof(addr) / sizeof(addr[0]);

    struct in_addr in_val;
    for (size_t i = 0; i < len; ++i) {
        inet_aton(addr[i], &in_val);
        printf("%15s : %12d 0x%8x \n", addr[i], in_val.s_addr, in_val.s_addr);
        printf("%15s : %12d 0x%8x \n", addr[i], htonl(in_val.s_addr), htonl(in_val.s_addr));
    }
}

static void test_ntoa() {
    struct in_addr in_val;
    in_val.s_addr = 0x1;
    printf("%s\n", inet_ntoa(in_val));
    in_val.s_addr = htonl(0x1);
    printf("%s\n", inet_ntoa(in_val));
    in_val.s_addr = 0x7f000001;
    printf("%s\n", inet_ntoa(in_val));
    in_val.s_addr = htonl(0x7f000001);
    printf("%s\n", inet_ntoa(in_val));
}

int main()
{
    printf("The os byte order is: %d\n", get_byte_order());
    test_order();
    test_aton();
    test_ntoa();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return 0;
}
