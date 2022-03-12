#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct datacall // 48 byte
{
    char tag;
    char caller[20];
    char called[20];
    int packets;
} DataCall;

typedef struct voicecall // 52 byte
{
    char tag;
    char caller[20];
    char called[20];
    int showID;
    int isRoaming;
} VoiceCall;

typedef struct emergencycall // 41 byte
{
    char tag;
    char caller[20];
    char called[20];
} EmergencyCall;

void displayQueue(void * pe)
{
    EmergencyCall * pec = pe;
    printf("%c  ", pec -> tag);
}


int main()
{
    int choice, exit = 0, lastSize;
    Queue callQueue;initQueue(&callQueue);
    DataCall dc;
    dc.tag = 'D';
    VoiceCall vc;
    vc.tag = 'V';
    EmergencyCall ec;
    ec.tag = 'E';

    while(!exit)
    {
        printf("1. Data Call coming.\n2. Voice Call coming.\n3. Emergency Call coming.\n4. Serve a call.\n5. Dismiss calls with least priority.\n6. Exit.\n");
        printf("Your Choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch(choice)
        {
            case 1:
                printf("Data call coming:\nCalling number: ");
                scanf("%s", &dc.caller);
                printf("Called number: ");
                scanf("%s", &dc.called);
                printf("Number of Packets: ");
                scanf("%d", &dc.packets);
                append(&dc, &callQueue, sizeof dc);
                printf("\n\n");
                break;
            case 2:
                printf("Voice call coming:\nCalling number: ");
                scanf("%s", &vc.caller);
                printf("Called number: ");
                scanf("%s", &vc.called);
                printf("Showing caller ID: ");
                scanf("%d", &vc.showID);
                printf("Roaming: ");
                scanf("%d", &vc.isRoaming);
                append(&vc, &callQueue, sizeof vc);
                printf("\n\n");
                break;
            case 3:
                printf("Emergency call coming:\nCalling number: ");
                scanf("%s", &ec.caller);
                printf("Called number: ");
                scanf("%s", &ec.called);
                append(&ec, &callQueue, sizeof ec);
                printf("\n\n");
                break;
            case 4:
                printf("Serve a call: \n");
                lastSize = serveSize(&callQueue);
                if(lastSize == 48)
                {
                    serve(&dc, &callQueue);
                    printf("Tag: %c\nCalling number: %s ---> Called number: %s\nPackets: %d\n\n", dc.tag, dc.caller, dc.called, dc.packets);
                }
                else if(lastSize == 52)
                {
                    serve(&vc, &callQueue);
                    printf("Tag: %c,\nCalling number: %s ---> Called number: %s\nShow caller ID: %d\nRoaming: %d\n\n", vc.tag, vc.caller, vc.called, vc.showID, vc.isRoaming);
                }
                else
                {
                    serve(&ec, &callQueue);
                    printf("Tag: %c,\nCalling number: %s ---> Called number: %s\n\n", ec.tag, ec.caller, ec.called);
                }
                break;
            case 5:
                printf("Dismiss Data Calls: \nData Calls Dismissed.");
                dismissDCalls(&callQueue);
                break;
            case 6:
                exit = 1;
                break;
        }
        printf("\n_______________\nQueue:\n");
        traverseQueue(&callQueue, &displayQueue);
        printf("\n_______________\n");
    }

    return 0;
}
