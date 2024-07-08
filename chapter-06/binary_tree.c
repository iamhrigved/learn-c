#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORDSIZE 50

struct tree_node {
    char *word;
    int word_count;
    struct tree_node *left_child;
    struct tree_node *right_child;
};

char **get_word();
struct tree_node *add_word_to_tree(struct tree_node *search_node, char *word);
struct tree_node *search_and_insert(struct tree_node *tree_root,
                                    char *search_word);
void print_tree(struct tree_node *tree_root);

int main() {
    char **data; /* The word and and the exit code */
    struct tree_node *cur_node,
        *starting_node = (struct tree_node *)malloc(sizeof(struct tree_node));
    starting_node->word = "start";
    starting_node->word_count = 0;
    cur_node = starting_node;

    while (1) {
        data = get_word();
        search_and_insert(starting_node, *data); /* giving the word */
        if (data[1] == NULL)
            break;
    }
    printf("\nAll the words you typed: \n\n");
    print_tree(starting_node);
}

/* Returns the word and the exit code (if user presses ESC) */
char **get_word() {
    int i;
    char c;
    char *word = malloc(MAXWORDSIZE);
    char **data =
        malloc(sizeof(word) + 3); /* Stores the word and the exit code */
    *data = word;
    data[1] = "OK";

    for (i = 0; (c = getchar()) != ' '; i++) {
        if (c == 27) {
            data[1] = NULL;
            return data;
        }
        if (c == '\n') /* Handling the last word of a line */
            break;
        word[i] = c;
    }

    return data;
}

struct tree_node *create_new_node(struct tree_node *prev_node, char *word) {
    struct tree_node *new_node = malloc(sizeof(struct tree_node));
    new_node->word = word;
    new_node->word_count = 1;
    new_node->right_child = new_node->left_child = NULL;
    if (strcmp(word, prev_node->word) > 0)
        prev_node->right_child = new_node;
    else
        prev_node->left_child = new_node;

    return new_node;
}

struct tree_node *search_and_insert(struct tree_node *tree_root,
                                    char *search_word) {
    struct tree_node *result;

    if (tree_root == NULL) { /* For extra safety */
        return NULL;
    }

    if (strcmp(search_word, tree_root->word) > 0) {
        result = tree_root->right_child != NULL
                     ? search_and_insert(tree_root->right_child, search_word)
                     : tree_root;
    }

    else if (strcmp(search_word, tree_root->word) < 0) {
        result = tree_root->left_child != NULL
                     ? search_and_insert(tree_root->left_child, search_word)
                     : tree_root;
    }

    else {
        tree_root->word_count += 1;
        return NULL; /* Word found */
    }

    if (result == NULL)
        return NULL;
    else {
        create_new_node(result,
                        search_word); /* Only returns a valid pointer, when we
                                         have to create a new node */
        return NULL;
    }
}

void print_tree(struct tree_node *tree_root) {
    if (tree_root == NULL) {
        return;
    }
    print_tree(tree_root->left_child);

    if (strcmp(tree_root->word, "start") != 0)
        printf("%s x%d\n", tree_root->word, tree_root->word_count);

    print_tree(tree_root->right_child);
    return;
}
