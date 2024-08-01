#include <stdio.h>
#include <stdlib.h>
#include "Platform_Types.h"
#include "Ch_6_Queue.h"

uint32 Queue1MaxElem = 0;
Queue_t *Queue1;
void *QueueRetVal;

uint8 *Name1[] = {"alice"};
uint8 *Name2[] = {"bob"};
uint8 *Name3[] = {"claire"};
uint8 *Name4[] = {"peggy"};
uint8 *Name5[] = {"thom"};
uint32 QueueCount;

int main()
{
    QueueStatus_t ReturnQueueStatus = QUEUE_NOK;

    printf("Please enter number of elements in Queue1 : ");
    scanf("%i", &Queue1MaxElem);

    Queue1 = CreateQueue(Queue1MaxElem, &ReturnQueueStatus);
    printf("0x%X \n", Queue1);

    ReturnQueueStatus = EnqueueElement(Queue1, Name1); printf("=> %i \n", ReturnQueueStatus);
    ReturnQueueStatus = EnqueueElement(Queue1, Name2); printf("=> %i \n", ReturnQueueStatus);
    ReturnQueueStatus = EnqueueElement(Queue1, Name3); printf("=> %i \n", ReturnQueueStatus);

    ReturnQueueStatus = GetQueueCount(Queue1, &QueueCount); printf("=> %i \n", ReturnQueueStatus);
    printf("Count = %i \n", QueueCount);

    QueueRetVal = QueueRear(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    printf("QueueRear = %s \n", *((uint32 *)QueueRetVal));

    ReturnQueueStatus = EnqueueElement(Queue1, Name4); printf("=> %i \n", ReturnQueueStatus);
    QueueRetVal = QueueRear(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    printf("QueueRear = %s \n", *((uint32 *)QueueRetVal));

    ReturnQueueStatus = EnqueueElement(Queue1, Name5); printf("=> %i \n", ReturnQueueStatus);

    ReturnQueueStatus = GetQueueCount(Queue1, &QueueCount); printf("=> %i \n", ReturnQueueStatus);
    printf("Count = %i \n", QueueCount);

    QueueRetVal = DequeueElement(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    QueueRetVal = DequeueElement(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    QueueRetVal = QueueFront(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    QueueRetVal = DequeueElement(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    QueueRetVal = DequeueElement(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    QueueRetVal = DequeueElement(Queue1, &ReturnQueueStatus); printf("=> %i \n", ReturnQueueStatus);
    if(!QueueRetVal){
        printf("Value = %s \n", *((uint8 *)QueueRetVal));
    }

    ReturnQueueStatus = DestroyQueue(Queue1);

    return 0;
}
