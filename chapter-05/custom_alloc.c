#include <stdio.h>
#define ALLOCSIZE 100

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n);
void free_alloc(int n);

int main() {

    char *ps = alloc(10);
    for (int i = 0; i < 10; i++)
        ps[i] = 'H';

    printf("%s", ps);
    free_alloc(10);
    printf("\n%s", ps);

    return 0;
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

    for (; allocp >= p - n; allocp--) {
        *allocp = '\0';
    }
}
