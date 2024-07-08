#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXHASHNUM 100

static struct hash_item *hash_table[MAXHASHNUM];

struct hash_item {
    char *key;
    char *value;
    struct hash_item *next_item;
};

struct hash_item *create_new_item(char *key, char *value);
char *lookup_table(char *key);

int main(int argc, char **argv) {
    create_new_item("1", "HRIGVED");
    create_new_item("2", "CHESS");
    create_new_item("3", "PLAY");

    /* for (int i = 0; hash_table[i] != 0; i++) { */
    /*     printf("key: %s, value: %s\n", hash_table[i]->key, */
    /*            hash_table[i]->value); */
    /* } */

    printf("%s", lookup_table("2"));
}

struct hash_item *create_new_item(char *key, char *value) {
    int last_index = 0;
    struct hash_item *new_item = malloc(sizeof(struct hash_item));

    new_item->key = key;
    new_item->value = value;
    new_item->next_item = NULL;

    for (; hash_table[last_index] != 0; last_index++)
        ;

    if (last_index >= MAXHASHNUM)
        return 0;

    hash_table[last_index] = new_item;

    if (last_index >= 1) { /* not if we are creating the first item */
        hash_table[last_index - 1]->next_item = new_item;
    }

    return new_item;
}

char *lookup_table(char *key) {
    struct hash_item *search = hash_table[0];

    for (; search != 0; search = search->next_item) {
        if (strcmp(search->key, key) == 0) {
            return search->value;
        }
    }

    return 0;
}
