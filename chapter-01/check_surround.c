#include <stdbool.h>
#include <stdio.h>

char pair(char s);
bool check_surround(char surround[]);
bool get_text(char str[], int lim);

int main() {
    int lim = 10000;
    char str[lim];

    bool check = get_text(str, lim);

    if (check)
        printf("\n\nSUCCESS! No error!");
    else
        printf("\n\nERROR! There is an error");

    return 0;
}

bool get_text(char str[], int lim) {
    int c, i = 0;
    char surround[1000];
    int cur_sur_index = 0;

    for (i = 0; (c = getchar()) != EOF || i < (lim - 1); i++) {
        if (c == '\'' || c == '\"' || c == '(' || c == ')' || c == '{' ||
            c == '}' || c == '[' || c == ']' || c == '\\' || c == '/' ||
            c == '*') {
            surround[cur_sur_index] = c;
            cur_sur_index++;
        }
        str[i] = c;
    }

    str[i + 1] = '\0';

    return check_surround(surround);
}

bool check_surround(char surround[]) {
    int len = 0;
    while (surround[len] != '\0')
        len++;

    int cur_pos_in_stack = 0;
    char sur_stack[200];
    bool comment = false;
    for (int i = 0; i < len; i++) {

        if (surround[i] == '/' && surround[i - 1] == '*')
            comment = false;

        if (surround[i] == '*' && surround[i - 1] == '/')
            comment = true;

        if (comment)
            continue;

        if (surround[i] == '(' || surround[i] == '{' || surround[i] == '[') {
            sur_stack[cur_pos_in_stack] = surround[i];
            cur_pos_in_stack++;
        }

        if (surround[i] == ')' || surround[i] == '}' || surround[i] == ']') {
            if (sur_stack[cur_pos_in_stack - 1] == pair(surround[i])) {
                cur_pos_in_stack--;
                sur_stack[cur_pos_in_stack] = '\0';
            } else
                return false;
        }

        if (surround[i] == '\'' || surround[i] == '\"') {
            if (surround[i - 1] == '\\')
                continue;
            if (sur_stack[cur_pos_in_stack - 1] == surround[i]) {
                cur_pos_in_stack--;
                sur_stack[cur_pos_in_stack] = '\0';
            } else {
                sur_stack[cur_pos_in_stack] = surround[i];
                cur_pos_in_stack++;
            }
        }
    }
    if (comment == true)
        return false;
    return true;
}

char pair(char s) {
    if (s == ')')
        return '(';
    if (s == '}')
        return '{';
    if (s == ']')
        return '[';
    return 0;
}
