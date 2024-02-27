include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 28


char frame[size];
char crc[size];
char data[size];
char check_value[size];
int data_length;
int crc_size;
int bit;

void crcfun()
{
    int i, j;
    for (i = 0; i < crc_size; i++)
    {
        check_value[i] = data[i];
    }
    int step = 1;
    do
    {
        if (check_value[0] == '1')
        {
            for (j = 1; j < crc_size; j++)
            {
                if (check_value[j] == crc[j])
                {
                    check_value[j] = '0';
                }
                else
                {
                    check_value[j] = '1';
                }
            }
        }
        for (j = 0; j < crc_size - 1; j++)
        {
            check_value[j] = check_value[j + 1];
        }
        check_value[j] = data[i++];
        printf("XOR operation %d: %s\n", step++, check_value);
    } while (i <= (data_length + crc_size - 1));
}

void sender()
{
    crcfun();
    printf("CRC value: %s\n", check_value);
    int i, j;
    for (int i = 0; i < data_length; i++)
    {
        data[i] = frame[i];
    }
    for (i = 0; i < (crc_size - 1); i++)
    {
        data[i + data_length] = check_value[i];
    }
    printf("Data sent: %s\n", data);
}

void addError()
{
    if (bit <= (data_length + crc_size - 1))
    {
        if (data[bit - 1] == '0')
        {
            data[bit - 1] = '1';
        }
        else
        {
            data[bit - 1] = '0';
        }
    }
}

void receiver()
{
    printf("Data received %s\n", data);
    crcfun();
    int flag = 0;
    for (int i = 0; i < crc_size - 1; i++)
    {
        if (check_value[i] == '0')
        {
            flag = 0;
        }
        else
        {
            flag++;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No error detected\n");
    }
    else
    {
        printf("Error detected\n");
    }
}

void dataSend()
{
    for (int i = 0; i < data_length; i++)
        data[i] = frame[i];
    for (int i = data_length; i < (data_length + crc_size - 1);
         i++)
        data[i] = '0';
    printf("Data after appending zero's: %s\n\n", data);
}

int main()
{
    printf("Enter frame\n");
    scanf("%s", frame);
    data_length = strlen(frame);
    printf("Enter crc key\n");
    scanf("%s", crc);
    crc_size = strlen(crc);
    printf("\nData: %s\n", frame);
    printf("CRC key: %s\n", crc);
    int choice;
    while (1)
    {
        printf("1. Transmit data without error\n");
        printf("2. Transmit data with error\n");
        printf("3. Exit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            dataSend();
            sender();
            receiver();
            break;
        case 2:
            dataSend();
            sender();
            printf("Enter bit number to manipulate\n");
            scanf("%d", &bit);
            addError();
            receiver();
            break;
        case 3:
            printf("Exiting the system\n");
            exit(0);
            break;
        default:
            printf("Invalid option\n");
            break;
        }
        return 0;
    }
}