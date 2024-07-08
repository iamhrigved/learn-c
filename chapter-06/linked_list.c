#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELEN 1000

struct linked_item {
    char *text;
    struct linked_item *prev_item;
    struct linked_item *next_item;
};

struct linked_item *append_item(struct linked_item *last_item, char *value);

int main(int argc, char **argv) {
    int num_lines = 0;
    char line[MAXLINELEN];
    struct linked_item *prev = NULL, *next = NULL, *start;

    while (fgets(line, MAXLINELEN, stdin) != NULL) {
        char *save_line = (char *)malloc(
            strlen(line) + 1); /* Accounting for the last null character */

        if (strcmp(line, "\n") == 0) /* Not recording empty lines */
            continue;

        strcpy(save_line, line);

        prev = append_item(prev, save_line);
        num_lines++;

        if (num_lines == 1) /* To get the first item of the linked_list */
            start = prev;
    }
    printf("\nLINKED LIST:\n");
    for (struct linked_item *cur_item = start; cur_item != NULL;
         cur_item = cur_item->next_item) {
        printf("%s", cur_item->text);
    }
}

/* Returns the new item appended */
struct linked_item *append_item(struct linked_item *last_item, char *value) {

    struct linked_item *new_item =
        (struct linked_item *)malloc(sizeof(struct linked_item));

    new_item->text = value;
    new_item->prev_item = last_item; /* Implementing prev_item */
    new_item->next_item = NULL;
    if (last_item != NULL)
        last_item->next_item = new_item; /* Implementing next_item */

    return new_item;
}
