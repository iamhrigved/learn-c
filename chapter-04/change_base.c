#include <stdio.h>

void convert(long base10num, int base);

int main() {
    long num = 23234234;
    convert(num, 16);
}

void convert(long base10num, int base) { // convert any base10num to any base
    int next_num = base10num;
    int remainder, i = 0;
    char max_base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // max base is 36
    char new_base_num[100];

    for (i = 0; next_num > 0; i++) { // making an array (in reverse order)
        remainder = next_num % base;
        new_base_num[i] = max_base[remainder];
        next_num = next_num / base;
    }

    new_base_num[i] = '\0'; // ending

    for (int j = 0; j < i / 2; j++) { // reversing the array
        char temp = new_base_num[j];
        new_base_num[j] = new_base_num[i - j - 1];
        new_base_num[i - j - 1] = temp;
    }
    printf("%ld in base %d is %s", base10num, base, new_base_num);
}
