#include <stdbool.h>
#include <stdio.h>

int main() {
    int nc = 0, nw = 0, nl = 1;
    int c;
    bool inword = true;

    while ((c = getchar()) != EOF) {

        if (c == '\n') {
            nl++;
            inword = false;
        }

        if (c == ' ' || c == '\n' || c == '\t') {
            nw++;
        }

        if (c != '\n') {
            nc++;
            inword = true;
        }
    }

    if (inword)
        nw++;

    printf("\nCharacters: %d, Words: %d, Lines: %d", nc, nw, nl);

    return 0;
}
