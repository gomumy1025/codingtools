/*
C언어에서 사용할 수 있는 큐(원형 ver.)

만든 사람: GomU
*/

#ifndef GomU_Queue_h
#define GomU_Queue_h

#define MAX_SIZE 100000

typedef struct QUEUE {
    int data[MAX_SIZE];
    int front;
    int rear;
    int max;
} queue;

void init(queue* q, int sz) {
    q->front = 0;
    q->rear = 0;
    q->max = sz;
}

int empty(queue* q) {
    return q->front == q->rear;
}

void push(queue* q, int value) {
    if ((q->rear + 1) % q->max == q->front) {
        return;  // 큐가 가득 찼을 때는 원소를 추가하지 않음
    }
    q->rear = (q->rear + 1) % q->max;
    q->data[q->rear] = value;
}

int front(queue* q) {
    if (empty(q)) {
        return -1;  // 큐가 비었을 때는 -1을 반환
    }
    return q->data[(q->front + 1) % q->max];  // 큐의 앞 원소 반환
}

int back(queue* q) {
    if (empty(q)) {
        return -1;  // 큐가 비었을 때는 -1을 반환
    }
    return q->data[q->rear];  // 큐의 뒷 원소 반환
}

void pop(queue* q) {
    if (empty(q)) {
        return;  // 큐가 비었을 때는 아무 작업도 하지 않음
    }
    q->front = (q->front + 1) % q->max;  // 큐의 front를 하나 증가시킴
}

int size(queue* q) {
    int res = q->rear - q->front;
    if (res < 0)res *= -1;

    return res % (q->max);
}


#endif
