#include <stdio.h>
#include <string.h>

int main() {

    char str[] = "This is a string";
    char temp;
    int n = strlen(str);

    for (int i = 0; i < (n) / 2; i++) {
        temp = str[i];
        str[i] = str[n - 1 - i];
        str[n - 1 - i] = temp;
    }
    // comment

    printf("%s", str);
}
