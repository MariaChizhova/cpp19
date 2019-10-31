#ifndef CLIST_H_
#define CLIST_H_
#include <stddef.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

struct intrusive_node {
    struct intrusive_node *next;
    struct intrusive_node *prev;
};

struct intrusive_list {
    struct intrusive_node *head;
    int size;
};

void init_list(struct intrusive_list *list);
void add_node(struct intrusive_list *list, struct intrusive_node *node);
void remove_node(struct intrusive_list *list, struct intrusive_node *node);
int get_length(struct intrusive_list *node);

#endif
