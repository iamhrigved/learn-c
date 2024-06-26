#include <stdio.h>

/* converts uppercase characters to lowercase */
char lower(char c) {
    if (c < 65 || c >= 91)
        return c;

    return c + 32;
}

int power(int base, int pow) {
    int result = 1;

    for (int i = 0; i < pow; i++)
        result *= base;

    return result;
}

/* get input of a line and returns its length */
int get_line(char str[], int lim) {
    int len, c;

    for (len = 0; (c = getchar()) != EOF && c != '\n'; len++)
        str[len] = c;

    if (c == EOF)
        str[len + 1] = '0'; /* to tell main() that the user has quit */

    str[len] = '\0';
    return len;
}

int main() {
    int num = power(5, 4);
    printf("%d", num);

    char c = lower('B');
    printf("\n%c\n", c);

    int len = 0, highest = 0;
    while (1) {
        char str[1000]; /* each time a new string of length 1000 is defined
                           after a new line */

        len = get_line(str, 1000);

        if (len > highest)
            highest = len;

        if (str[len + 1] == '0') /* checking if the user has quit */
            break;
    }
    printf("\n\nThe lenght of the longest line you wrote = %d", highest);

    return 0;
}
