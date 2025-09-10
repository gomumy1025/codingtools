/*
  Double Linked List (made by GomU, fixed by ChatGPT)
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node* prev;  // previous address
    struct node* next;  // next address
    int data;           // data (integer)
} node;

typedef struct list {
    node* head;
    node* tail;
    int size;
} list;

void init(list* l) {
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

void push_front(list* l, int dt) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) return;  // if malloc fails, process safely

    newNode->data = dt;
    newNode->prev = NULL;

    if (l->size == 0) {  // if empty list-> head, tail: all newNode
        newNode->next = NULL;
        l->head = newNode;
        l->tail = newNode;
    } else {             // insert in front of previous 'head'
        newNode->next = l->head;
        l->head->prev = newNode;
        l->head = newNode;
    }

    ++l->size;
}

void push_back(list* l, int dt) {
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) return;

    newNode->data = dt;
    newNode->next = NULL;

    if (l->size == 0) {  // empty list?
        newNode->prev = NULL;
        l->head = newNode;
        l->tail = newNode;
    } else {
        l->tail->next = newNode;
        newNode->prev = l->tail;
        l->tail = newNode;
    }

    ++l->size;
}

void pop_front(list* l) {
    if (l->size == 0) return;

    node* t = l->head;

    if (l->size == 1) {
        l->head = NULL;
        l->tail = NULL;
    } else {
        l->head = l->head->next;
        l->head->prev = NULL;
    }

    free(t);
    --l->size;
}

void pop_back(list* l) {
    if (l->size == 0) return;

    node* t = l->tail;

    if (l->size == 1) {
        l->head = NULL;
        l->tail = NULL;
    } else {
        l->tail = l->tail->prev;
        l->tail->next = NULL;
    }

    free(t);
    --l->size;
}

node* find(list* l, node* tg) {  // 'tg' stands for 'target'
    node* cur = l->head;
    while (cur != NULL) {
        if (cur == tg) return cur;
        cur = cur->next;
    }
    return NULL;  // not found
}

void push_mid(list* l, node* tg, int dt) {
    if (l->size == 0 || !find(l, tg)) return;

    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) return;

    newNode->data = dt;
    newNode->next = tg;
    newNode->prev = tg->prev;

    if (tg->prev != NULL) {
        tg->prev->next = newNode;
    }
    tg->prev = newNode;

    if (tg == l->head) {
        l->head = newNode;
    }

    ++l->size;
}

node* pop_mid(list* l, node* tg) {
    if (l->size == 0 || !find(l, tg)) return NULL;

    node* nt = tg->next;  // saving properly :)

    if (l->size == 1) {
        pop_front(l);
    } else if (tg == l->head) {
        pop_front(l);
    } else if (tg == l->tail) {
        pop_back(l);
    } else {
        tg->prev->next = tg->next;
        tg->next->prev = tg->prev;
        free(tg);
        --l->size;
    }

    return nt;  // return next node
}

void all_clear(list* l) {
    node* cur = l->head;
    node* nt;

    while (cur != NULL) {
        nt = cur->next;
        free(cur);
        cur = nt;
    }

    init(l);
}

void print_list(list* my_list) {
    node* cur = my_list->head;

    printf("[size:%d] ", my_list->size);
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main()
{
	// type any codes :)

	return 0;
}
