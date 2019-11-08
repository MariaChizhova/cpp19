#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "point_list.h"

int text(int x) {
    return (x & (1 << 23) ? (x ^ (1 << 23)) - (1 << 23) : x);
}

int binary(int x) {
    return (x < 0 ? x & ((1 << 24) - 1) : x);
}

void loadtext(char *file_name, intrusive_list *list) {
    FILE *fin = fopen(file_name, "r");
    int x, y;
    while (fscanf(fin, "%d %d", &x, &y) == 2)
        add_point(list, x, y);
    fclose(fin);
}

void savetext(char *file_name, intrusive_list *list) {
    FILE *fout = fopen(file_name, "w");
    for (intrusive_node *item = list->head.next; item != &list->head; item = item->next) {
        fprintf(fout, "%d %d\n", get_point(item)->x, get_point(item)->y);
    }
    fclose(fout);
}

void loadbin(char *file_name, intrusive_list *list) {
    FILE *fin = fopen(file_name, "rb");
    int x = 0, y = 0;
    while (fread(&x, 3, 1, fin) == 1) {
        assert(fread(&y, 3, 1, fin) == 1);
        add_point(list, text(x), text(y));
    }
    fclose(fin);
}

void savebin(char *file_name, intrusive_list *list) {
    FILE *fout = fopen(file_name, "wb");
    for (intrusive_node *item = list->head.next; item != &list->head; item = item->next) {
        point_node *pnode = get_point(item);
        int x = binary(pnode->x), y = binary(pnode->y);
        fwrite(&x, 3, 1, fout);
        fwrite(&y, 3, 1, fout);
    }
    fclose(fout);
}

void print(intrusive_node *node, void *data) {
    printf((char *) data, get_point(node)->x, get_point(node)->y);
}

void count_nodes(intrusive_node *node, void *data) {
    assert(node != NULL);
    assert(data != NULL);
    (*(int *) data)++;
}

int main(int argc, char *argv[]) {
    intrusive_list list;
    intrusive_list *l = &list;
    init_list(l);

    assert(argc >= 4 && argc <= 5);

    if (!strcmp(argv[1], "loadtext")) {
        loadtext(argv[2], l);
    } else if (!strcmp(argv[1], "loadbin")) {
        loadbin(argv[2], l);
    } else {
        assert(!"Unknown command");
    }

    if (!strcmp(argv[3], "print")) {
        apply(l, print, argv[4]);
        printf("\n");
    } else if (!strcmp(argv[3], "savetext")) {
        savetext(argv[4], l);
    } else if (!strcmp(argv[3], "savebin")) {
        savebin(argv[4], l);
    } else if (!strcmp(argv[3], "count")) {
        int cnt = 0;
        apply(l, count_nodes, &cnt);
        printf("%d\n", cnt);
    } else {
        assert(!"Unknown command");
    }

    remove_all_points(l);
    return 0;
}

