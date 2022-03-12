#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void initQueue(Queue * pq)
{
    pq -> front = NULL;
    pq -> rear = NULL;
    pq -> voiceP = NULL;
    pq -> emergP = NULL;
    pq -> size = 0;
}

void append(const void * pe, Queue * pq, int eSize)
{
    void * pe2;
    QueueNode * pn;

    do
    {
        pe2 = malloc(sizeof eSize);
        pn = (QueueNode*) malloc(sizeof(QueueNode));
    } while(!pn && !pe2);

    memcpy(pe2, pe, eSize);
    pn -> entry = pe2;
    pn -> eSize = eSize;

    if(eSize == 41)
    {
        if(pq -> front)
        {
            if(pq -> emergP)
            {
                pn -> next = pq -> emergP -> next;
                pq -> emergP -> next = pn;
            }
            else
            {
                pn -> next = pq -> front;
                pq -> front = pn;
            }
        }

        pq -> emergP = pn;
    }
    else if(eSize == 52)
    {
        if(pq -> front)
        {
            if(pq -> voiceP)
            {
                pn -> next = pq -> voiceP -> next;
                pq -> voiceP -> next = pn;
            }
            else
            {
                if(pq -> emergP)
                {
                    pn -> next = pq -> emergP -> next;
                    pq -> emergP -> next = pn;
                }
                else
                {
                    pn -> next = pq -> front;
                    pq -> front = pn;
                }
            }
        }

        pq -> voiceP = pn;
    }
    else
    {
        pn -> next = NULL;
        if(pq -> front) pq -> rear -> next = pn;
        pq -> rear = pn;
    }

    if(!pq -> front)
    {
        pq -> front = pn;
        pq -> rear = pn;
        pn -> next = NULL;
    }

    pq -> size++;
}

int serveSize(Queue * pq)
{
    return pq -> front -> eSize;
}

void serve(void * pe, Queue * pq)
{
    QueueNode * pn = pq -> front;
    memcpy(pe, pn -> entry, pn -> eSize);
    pq -> front = pn -> next;

    if(pn == pq -> emergP)
        pq -> emergP = NULL;
    else if(pn == pq -> voiceP)
        pq -> voiceP = NULL;

    if(!pq -> front)
        pq -> rear = NULL;

    free(pn -> entry);
    free(pn);
    pq -> size--;
}

int queueFull(const Queue * pq)
{
    return 0;
}

int queueEmpty(const Queue * pq)
{
    return !pq -> front;
}

int queueSize(const Queue * pq)
{
    return pq -> size;
}

void clearQueue(Queue * pq)
{
    while(pq -> front)
    {
        pq -> rear = pq -> front -> next;
        free(pq -> front -> entry);
        free(pq -> front);
        pq -> front = pq -> rear;
    }

    pq -> size = 0;
}

void queueFront(void * pe, const Queue * pq)
{
    memcpy(pe, pq -> front -> entry, pq -> front -> eSize);
}

void traverseQueue(Queue * pq, void (*pf) (void*))
{
    QueueNode * pn;
    for(pn = pq -> front; pn; pn = pn -> next)
        (*pf)(pn -> entry);
}

void dismissDCalls(Queue * pq)
{
    QueueNode * pn;
    QueueNode * pndc;
    if(pq -> voiceP)
        pn = pq -> voiceP;
    else if(pq -> emergP)
        pn = pq -> emergP;
    else
        pn = pq -> front;

    while(pn)
    {
        if(pn -> next)
        {
            if(pn -> next -> eSize == 48)
            {
                pndc = pn -> next;
                pn -> next = pndc -> next;
            }
            else
                pn = pn -> next;
        }
        else
            pn = pn -> next;
    }
}
