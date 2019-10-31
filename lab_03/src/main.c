#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "clist.h"
 
struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list *l, int x, int y) {
    struct point *pt =  malloc(sizeof(struct point));
    pt->x = x;
    pt->y = y; 
    add_node(l, &pt->node);
}

void remove_point(struct intrusive_list *l, int x, int y) { 
    struct intrusive_node *item = l->head;
    while (item) {
        struct point *pt = container_of(item, struct point, node);
        item = item->next;
        if (pt->x == x && pt->y == y) {
            remove_node(l, &pt->node);
            free(pt);
        }
    }
}

void show_all_points(struct intrusive_list *l) {
    for (struct intrusive_node *item = l->head; item; item = item->next) {
        struct point *pt = container_of(item, struct point, node);
        printf("(%d %d)", pt->x, pt->y);
        if (item->next) {
            printf(" ");
        }
    }
    printf("\n");
}

void remove_all_points(struct intrusive_list *l) {
    struct intrusive_node *item = l->head;
    while (item) {
        struct point *pt = container_of(item, struct point, node);
        item = item->next;
        remove_node(l, &pt->node);
        free(pt);
    }
}

int main() {
    struct intrusive_list l;
    init_list(&l);
    while (1) {
        char command[7];
        scanf("%6s", command);
        if (!strcmp("add", command)) {
            int x, y;
            scanf("%d", &x);
            scanf("%d", &y);
            add_point(&l, x, y);
        }
        else if (!strcmp("rm", command)) {
            int x, y;
            scanf("%d", &x);
            scanf("%d", &y);
            remove_point(&l, x, y);
        }
        else if (!strcmp("print", command)) {
            show_all_points(&l);
        }
        else if (!strcmp("rma", command)) {
            remove_all_points(&l);
        }
        else if (!strcmp("len", command)) {
            printf("%d\n", get_length(&l)); 
        }
        else if (!strcmp("exit", command)) {
            remove_all_points(&l);
            break;
        }
        else {
            scanf("%*[^\n]");
            printf("Unknown command\n");
        }
    }
    return 0;
}
