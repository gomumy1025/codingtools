/*
C언어에서 사용할 수 있는 스택

만든 사람: GomU
*/

#ifndef GomU_Stack_h
#define GomU_Stack_h

#define MAX 100000

typedef struct STACK {
    int t;
    int as[MAX];
} stack;

void Initialize(stack* st) {
    st->t = -1;
}

void push(stack* st, int k) {
    st->t++;
    st->as[st->t] = k;
}

void pop(stack* st) {
    if (st->t == -1) return;  // 비어있는 스택에 대해 -1을 반환
    st->t--;
}

int top(stack* st) {
    if (st->t == -1) return -1;  // 비어있는 스택에 대해 -1을 반환
    return st->as[st->t];
}

int empty(stack* st) {
    return st->t == -1;  // 비어있는 경우 1을 반환
}

int size(stack* st) {
    return st->t + 1;  // 스택의 크기
}

#endif
