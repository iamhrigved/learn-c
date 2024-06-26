#include <stdio.h>

int main() {
    int nwhite, nc, c;
    int ndigit[10];
    nwhite = nc = 0;

    for (int i = 0; i < 10; i++)
        ndigit[i] = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n' || c == '\t') {
            nwhite++;
            nc--;
        }

        if (c >= '0' && c <= '9') {
            ndigit[c - '0']++;
            nc--;
        }

        nc++;
    }

    printf("\n\nCharacters: %d, Whitespace: %d", nc, nwhite);
    for (int i = 0; i < 10; i++)
        printf("\nNumber of %d's: %d", i, ndigit[i]);

    return 0;
}
