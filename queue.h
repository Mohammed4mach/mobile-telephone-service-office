#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queuenode
{
    struct queuenode * next;
    void * entry;
    int eSize;
} QueueNode;

typedef struct queue
{
    QueueNode * front;
    QueueNode * rear;
    QueueNode * voiceP; // pointing to the least prior voice call among its type.
    QueueNode * emergP; // pointing to the least prior emergency call among its type.
    int size;
} Queue;

void initQueue(Queue*);
void append(const void*, Queue*, int);
int serveSize(Queue*);
void serve(void*, Queue*);
int queueFull(const Queue*);
int queueEmpty(const Queue*);
int queueSize(const Queue*);
void clearQueue(Queue*);
void queueFront(void*, const Queue*);
void traverseQueue(Queue*, void (*pf) (void*));
void dismissDCalls(Queue*);

#endif // QUEUE_H_INCLUDED
