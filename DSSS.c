#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char data[16] = {0};
char key[16] = {0};
char receiver[16] = {0};
char temp[128] = {0};
int keyLength, dataLength;
char xnor(char a, char b)
{
    return (a == b) + '0';
}
int checkBit(char bit[], int length)
{
    char start = bit[0];
    for (int i = 0; i < length; i++)
        if (bit[i] != start)
            return 0;
    return 1;
}
void calculateResultForBit(int position, char bit)
{
    printf("Performing XNOR for bit %c:", bit);
    int keyIndex = 0;
    for (int i = position * keyLength; i < (position + 1) * keyLength;
         i++)
    {
        temp[i] = xnor(bit, key[keyIndex++]);
        printf("%c", temp[i]);
    }
    printf("\n");
}
char calculateBitForResult(int start, int end)
{
    if (end < start)
        return 0;
    printf("Performing reverse operation for ");
    for (int i = start; i < end; i++)
        printf("%c", temp[i]);
    printf(":");
    char bit[end - start];
    int keyIndex = 0;
    for (int i = start; i < end; i++)
    {
        bit[keyIndex] = xnor(temp[i], key[keyIndex]);
        printf("%c", bit[keyIndex++]);
    }
    if (!checkBit(bit, keyIndex))
    {
        printf("Error occured while calculating data.\n");
        return 0;
    }
    printf("\n");
    return bit[0];
}
int main()
{
    printf("Enter the data to send:");
    scanf("%s", data);
    printf("Enter the key:");
    scanf("%s", key);
    dataLength = strlen(data);
    keyLength = strlen(key);
    printf("\n");
    for (int i = 0; i < dataLength; i++)
        calculateResultForBit(i, data[i]);
    printf("\nFinal string to send:%s\n\n", temp);
    for (int i = 0; i < dataLength; i++)
        receiver[i] = calculateBitForResult(i * keyLength, (i + 1) * keyLength);
    printf("\nFinal string received:%s\n", receiver);
    return 0;
}

/*
Input
Enter the data to send:0110110
Enter the key:101
*/

/*
gcc dsss.c
./a.out
*/
