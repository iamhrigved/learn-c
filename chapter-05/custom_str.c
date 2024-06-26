#include <stdio.h>

void str_cpy(char *s, char *t);
void str_cat(char *s, char *t);
int str_cmp(char *s, char *t);

int main() {
    char s[100] = "Hrigved";
    char *c = s;
    char t[] = "Chess";

    printf("s: %s, t: %s\n", s, t);

    printf("\nComparing s and t: ");
    printf("%d\n", str_cmp(s, t));

    str_cpy(s, t);
    printf("\nAfter copying:\n");
    printf("s: %s, t: %s\n", s, t);

    printf("\nComparing s and t: ");
    printf("%d\n", str_cmp(s, t));

    str_cat(s, t);
    printf("\nAfter concating:\n");
    printf("s: %s, t: %s\n", s, t);

    printf("\nComparing s and t: ");
    printf("%d", str_cmp(s, t));

    return 0;
}

void str_cpy(char *s, char *t) {
    for (; (*s = *t) != '\0'; s++, t++)
        ;
}

void str_cat(char *s, char *t) {
    for (; *s != '\0'; s++)
        ;
    for (; (*s = *t) != '\0'; s++, t++)
        ;
}

int str_cmp(char *s, char *t) {
    for (; *s == *t && *s != '\0'; s++, t++)
        ;
    return *s - *t;
}
