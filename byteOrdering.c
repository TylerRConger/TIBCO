#include <stdio.h>
#include <stdlib.h>

// Stack overflow post related to the question
//https://stackoverflow.com/questions/19275955/convert-little-endian-to-big-endian
unsigned short my_ntohs(unsigned short in) {
    // Do bitwise manipulation to convert the short from big to little or little to big endian
    // Extract the top byte and shift it, then extract bottom byte and shift, then combine the two
    return ((in & 0xff00) >> 8u) | ((in & 0x00ff) << 8u);
}

unsigned int my_ntohl(unsigned int in) {
    // Do bitwise manipulation to convert the int from big to little or little to big endian
    // Shift each byte then combine them back together
    return ((in & 0xff000000) >> 24u) | ((in & 0x00ff0000) >> 8u) |
           ((in & 0x0000ff00) << 8u) | ((in & 0x000000ff) << 24u);
}

int main(int argc, char** argv)
{
    printf("\n\n\n");
    printf("Testing ntohs:\n");

    unsigned short expectedOne[] = {0x0102, 0xf00f, 0x9988, 0x01ff, 0x1234};
    unsigned short testsOne[] = {0x0201, 0x0ff0, 0x8899, 0xff01, 0x3412};

    for (int i = 0; i < sizeof(testsOne) / sizeof(testsOne[0]); i++) {
        unsigned short result = my_ntohs(testsOne[i]);
        if (result == expectedOne[i]) {
            printf("Test case %d: PASSED\n", i + 1);
        } else {
            printf("Test case %d: FAILED (Expected: 0x%04X, Actual: 0x%04X)\n", i + 1, expectedOne[i], result);
        }
    }

    printf("Testing ntohl:\n");

    unsigned int expectedTwo[] = {0x99887766, 0x01ff01ff, 0xfedcba98, 0x11223344, 0x00ff00ff};
    unsigned int testsTwo[] = {0x66778899, 0xff01ff01, 0x98badcfe, 0x44332211, 0xff00ff00};

    for (int i = 0; i < sizeof(testsTwo) / sizeof(testsTwo[0]); i++) {
        unsigned int resultTwo = my_ntohl(testsTwo[i]);
        if (resultTwo == expectedTwo[i]) {
            printf("Test case %d: PASSED\n", i + 1);
        } else {
            printf("Test case %d: FAILED (Expected: 0x%08X, Actual: 0x%08X)\n", i + 1, expectedTwo[i], resultTwo);
        }
    }
    return 0;

}