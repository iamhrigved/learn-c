#include <stdio.h>
#include <string.h>
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

void get_line(char *linesptr[]);
void sort(char *linesptr[]);

int len_line(char line[]);
int len_linesptr(char *linesptr[]);

char *alloc(int n);
void free_alloc(int n);

int main(int argc, char *argv[]) {
    char *linesptr[100];
    get_line(linesptr);
    sort(linesptr);

    printf("Sorted by length:\n");
    for (int i = 0; i < len_linesptr(linesptr); i++) {
        printf("%s\n", linesptr[i]);
    }
    free_alloc(10000);

    return 0;
}

void get_line(char *linesptr[]) {
    int i, j;
    char c, *line = alloc(400);

    for (i = 0;;) {
        for (j = 0; (c = getchar()) != '\t'; j++) {
            if (c == '\n')
                break;
            line[j] = c;
        }

        free_alloc(400 - j - 2); /* To free up extra space */
        printf("%ld", strlen(line));

        linesptr[i] = line;
        i++;

        line = alloc(400); /* Reallocating new space */

        if (c == '\t')
            break;
    }
}

void sort(char *linesptr[]) {
    int total_len = len_linesptr(linesptr);
    char *temp;

    for (int i = 0; i < total_len; i++) {
        for (int j = 0; j < (total_len - 1 - i); j++) {
            if (len_line(linesptr[j]) > len_line(linesptr[j + 1])) {
                temp = linesptr[j];
                linesptr[j] = linesptr[j + 1];
                linesptr[j + 1] = temp;
            }
        }
    }
}

int len_line(char line[]) {
    int i;
    for (i = 0; line[i] != '\0'; i++)
        ;
    return i;
}

int len_linesptr(char *linesptr[]) {
    int i;
    for (i = 0; linesptr[i] != (void *)0; i++) /* Comparing to NULL pointer */
        ;
    return i;
}

char *alloc(int n) {
    if (allocp + n > allocbuf + ALLOCSIZE)
        return 0;
    else {
        allocp += n;
        return allocp - n;
    }
}

void free_alloc(int n) {
    char *p = allocp;

    if (allocp - n < allocbuf)
        n = allocp - allocbuf;

    for (; allocp >= p - n; allocp--)
        *allocp = '\0';
}
