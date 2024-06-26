#include <stdbool.h>
#include <stdio.h>

double to_double(char num_str[]);
void trim(char str[]);
bool check_str(char num_str[], bool has_sign, bool is_scientific);
bool is_scientific(char num_str[]);

int main() {
    char num_str[100], c;

    /* Try to break this program :) */

    printf("Enter a number to convert to double: ");

    for (int i = 0; (c = getchar()) != '\n'; i++)
        num_str[i] = c;

    double num_double = to_double(num_str);

    if (num_double == -1)
        return 1;

    printf("Double: %lf", num_double);

    return 0;
}

double to_double(char num_str[]) {
    trim(num_str);

    double num_double = 0, power_10 = 1;
    int sign = 1, i = 0, end, len;
    bool after_dot = false, has_sign = false, scientific = false;

    /* Checking it the string is in scientific notation */
    for (len = 0; num_str[len] != '\0'; len++)
        ;

    end = len;

    if ((scientific = is_scientific(num_str)))
        end = len - 3;

    /* Checking the sign of the string */
    if (num_str[0] == '+' || num_str[0] == '-') {
        if (num_str[0] == '-')
            sign = -1;
        has_sign = true;
    }

    if (has_sign)
        i++;

    /* Passing all this info in the check_str funtion */
    if (!check_str(num_str, has_sign, scientific))
        return -1;

    for (; i < end; i++) {
        if (num_str[i] == '.') {
            after_dot = true;
            continue;
        }
        if (after_dot) {
            power_10 *= 10;
        }
        num_double = num_double * 10 + (num_str[i] - '0');
    }

    /* Additional computation if the string is scientific */
    if (scientific) {
        if (num_str[len - 2] == '+')
            for (int i = 0; i < num_str[len - 1] - '0'; power_10 /= 10, i++)
                ;
        else
            for (int i = 0; i < num_str[len - 1] - '0'; power_10 *= 10, i++)
                ;
    }

    return (sign * num_double) / power_10;
}

void trim(char str[]) {
    int cur_index = 0;
    char temp_num_str[100];

    for (int i = 0; str[i] != '\0'; i++) {

        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
            continue;
        }

        temp_num_str[cur_index] = str[i];
        cur_index++;
    }

    for (int i = 0; i < cur_index; i++) {
        str[i] = temp_num_str[i];
    }

    str[cur_index] = '\0';
}

bool check_str(char num_str[], bool has_sign, bool is_scientific) {
    int i = 0, end, num_dot = 0, len;

    for (len = 0; num_str[len] != '\0'; len++)
        ;

    end = len;

    if (is_scientific)
        end = len - 3;

    if (has_sign)
        i++;

    for (; i < end; i++) {
        if (num_str[i] == '.') {
            num_dot++;
        }

        if (num_dot > 1) {
            printf("ERROR: Please enter a valid number!");
            return false;
        }

        if (!(num_str[i] >= '0' && num_str[i] <= '9') && num_str[i] != '.') {
            printf("ERROR: Please enter a valid number!");
            return false;
        }
    }
    return true;
}

bool is_scientific(char num_str[]) {
    int len;

    for (len = 0; num_str[len] != '\0'; len++)
        ;

    if (!(num_str[len - 3] == 'e' || num_str[len - 3] == 'E')) {
        return false;
    }

    if (!(num_str[len - 2] == '+' || num_str[len - 2] == '-')) {
        return false;
    }

    if (!(num_str[len - 1] >= '0' || num_str[len - 1] <= '9'))
        return false;

    return true;
}
