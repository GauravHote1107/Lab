#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50

void sender(int *dataPackets, int packets)
{
    int *frequencies = (int *)malloc(sizeof(int) * packets);
    srand(time(NULL));
    for (int i = 0; i < packets; i++)
    {
        frequencies[i] = rand() % 100;
    }
    printf("\nPackets to transmit are:%d\n\n", packets);
    for (int i = 0; i < packets; i++)
    {
        printf("Data packet %d sent with frequency:%d\n", i + 1, frequencies[i]);
        printf("Data:%d\n", dataPackets[i]);
    }
    free(frequencies);
}

void receiver(int *dataPackets, int packets)
{
    printf("\nData received:\n");
    for (int i = 0; i < packets; i++)
    {
        printf("Data packet%d:%d\n", i + 1, dataPackets[i]);
    }
}

int main()
{
    int packets;
    printf("Enter number of packets to send:");
    scanf("%d", &packets);
    if (packets > SIZE)
    {
        printf("Error: Number of packets exceeds the maximum limit of %d.\n", SIZE);
        return 1;
    }
    int *dataPackets = (int *)malloc(sizeof(int) * packets);
    if (dataPackets == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }
    for (int i = 0; i < packets; i++)
    {
        printf("Enter data packet %d: ", i + 1);
        scanf("%d", &dataPackets[i]);
    }
    sender(dataPackets, packets);
    receiver(dataPackets, packets);
    free(dataPackets);
    return 0;
}

/*
Input
3
10
20
30
*/

/*
gcc fhss.c
./a.out
*/
