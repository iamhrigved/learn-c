#include <stdbool.h>
#include <stdio.h>

#define ALLOCSIZE 10000
#define ERRORNUM -1111

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

/* Printing help */
void print_help();

/* Main functions */
int get_line(char *linesptr[]);
int sort(char *linesptr[], int num_of_line, int (*sort_func)(char *, char *));
/* ^^ Takes a pointer to the comparision function to use */

/* Utility functions */
int len_line(char line[]);
int len_line_diff(char *s, char *t);
int difference(char *s, char *t);
int str_cmp(char *s, char *t);
long to_num(char *s);

/* Alloc functions */
char *alloc(int n);
void free_alloc(int n);

int main(int argc, char **argv) {
    char *linesptr[100];
    bool copy_mode = 0;
    int num_of_lines, result = 0;

    /* Handling command-line arguments */
    for (int i = 1; i < argc; i++) {

        if (str_cmp(argv[i], "--copy") == 0 || str_cmp(argv[i], "-c") == 0) {
            copy_mode = 1;
            continue;
        }

        if (result != 0) /* Already sorted */
            continue;

        if (str_cmp(argv[i], "--help") == 0 || str_cmp(argv[i], "-h") == 0) {
            print_help();
            return 1;
        }

        if (str_cmp(argv[i], "--length") == 0 || str_cmp(argv[i], "-l") == 0) {
            num_of_lines = get_line(linesptr);
            result = sort(linesptr, num_of_lines, len_line_diff);
            if (result == ERRORNUM)
                return 1;
            printf("\nSorted by Length:\n");
        }

        else if (str_cmp(argv[i], "--number") == 0 ||
                 str_cmp(argv[i], "-n") == 0) {
            num_of_lines = get_line(linesptr);
            result = sort(linesptr, num_of_lines, difference);
            if (result == ERRORNUM)
                return 1;
            printf("\nSorted Numerically:\n");
        }

        else if (str_cmp(argv[i], "--alphabetical") == 0 ||
                 str_cmp(argv[i], "-a") == 0) {
            num_of_lines = get_line(linesptr);
            result = sort(linesptr, num_of_lines, str_cmp);
            if (result == ERRORNUM)
                return 1;
            printf("\nSorted Alphabetically:\n");
        }

        /* Sorting by length (default) */
        else {
            num_of_lines = get_line(linesptr);
            result = sort(linesptr, num_of_lines, len_line_diff);
            printf("\nPlease do `%s --help` or `%s -h` to see help.", argv[0],
                   argv[0]);
            if (result == ERRORNUM)
                return 1;
            printf("\nSorted by Length: (default)\n");
        }
    }

    if (argc == 1) { /* When previous loop did not run */
        num_of_lines = get_line(linesptr);
        result = sort(linesptr, num_of_lines, len_line_diff);
        printf("\nSorted by Length: (default)\n");
    }

    /* Printing the sorted list */
    for (int i = 0; i < num_of_lines; i++) {
        if (copy_mode)
            printf("\n%s", linesptr[i]);
        else
            printf("\n%2.0d: %s", i + 1, linesptr[i]);
    }

    return 0;
}

/* clang-format off */
void print_help() {
    printf("my_sort utility: --help\n\n");
    printf("Usage: my_sort [OPTIONS]\n\n");
    printf("Sorting options:\n\n");
    printf("  -l, --length        (default) Order the lines by their Length\n");
    printf("  -a, --alphabetical  Order the lines Alphabetically\n");
    printf("  -n, --number        Order Numbers\n");
    printf("  -c, --copy          Enable copy_mode which ommits the line numbers in the output\n");
    printf("  -h, --help          Show help message\n");
}
/* clang-format on */

int get_line(char *linesptr[]) {
    int i, j;
    char c, *line = alloc(400);

    printf("Enter your list: (Press `ESC` then `ENTER` to exit)\n\n");
    for (i = 0;;) {
        for (j = 0; (c = getchar()) != 27; j++) {
            if (c == '\n')
                break;
            line[j] = c;
        }

        if (len_line(line) != 0) {
            /* if line is not empty and previous character is not <escape> */
            linesptr[i] = line;
            i++;
            free_alloc(400 - j - 2); /* To free up extra space */
            line = alloc(400);       /* Reallocating new space */
        }

        if (c == 27)
            break;
    }

    free_alloc(399);
    return i; /* Returning the length of the array, `linesptr` */
}

int sort(char *linesptr[], int num_of_line, int (*sort_func)(char *, char *)) {
    char *temp = 0;

    for (int i = 0; i < num_of_line; i++) {
        for (int j = 0; j < (num_of_line - 1 - i); j++) {

            int comp = sort_func(linesptr[j], linesptr[j + 1]);

            if (comp == ERRORNUM)
                return comp;

            if (comp > 0) {
                temp = linesptr[j];
                linesptr[j] = linesptr[j + 1];
                linesptr[j + 1] = temp;
            }
        }
    }
    return 1; /* If sorting successful */
}

long to_num(char *s) {
    long final_num = 0;
    int sign = 1, i, start;

    if (s[0] == '-') {
        start = 1;
        sign = -1;
    }

    else if (s[0] == '+')
        start = 1;

    for (i = len_line(s) - 1; i >= start; i--) {
        if (s[i] <= '0' || s[i] > '9') {
            printf("\n%s <- Invalid Number!", s);
            return ERRORNUM;
        }
        final_num = final_num * 10 + s[i] - '0';
    }
    return sign * final_num;
}

int difference(char *s, char *t) {
    long first_num;
    long second_num;

    if ((first_num = to_num(s)) == ERRORNUM ||
        (second_num = to_num(t)) == ERRORNUM)
        return ERRORNUM;

    return first_num - second_num;
}

int str_cmp(char *s, char *t) {
    for (; *s == *t && *s != '\0'; s++, t++)
        ;
    return *s - *t;
}

int len_line(char line[]) {
    int i;
    for (i = 0; line[i] != '\0'; i++)
        ;
    return i;
}

int len_line_diff(char *s, char *t) {
    return len_line(s) - len_line(t);
} /* difference between lengths of lines */

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
        ;
}
