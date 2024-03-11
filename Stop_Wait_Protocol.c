#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TIMEOUT_SEC 1 

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
 
    clock_t start_time = clock();
 
    while (clock() < start_time + milli_seconds);
}

int main(){
    int data[50], ts, tp, n, tt, i, j, choice;
    printf("Enter number of bits: ");
    scanf("%d", &n);
    printf("Enter transmission time: ");
    scanf("%d", &ts);
    printf("Enter propagation time: ");
    scanf("%d", &tp);

    printf("Enter Data: ");
    for(i=0; i<n; i++){
        scanf("%d", &data[i]);
    }

    printf("Choose scenario:\n1. Acknowledged \n2. No acknowledgement for a bit\n");
    scanf("%d", &choice);

    bool ack_received = false;
    int ctr=0;
    for(j=1; j<=n;){
        printf("Sending bit no. %d = %d\n", j, data[j-1]);
        delay(tp); 
        printf("Bit %d sent\n", j);
        delay(ts); 
        printf("Waiting for ACK...\n");
        time_t start_time = time(NULL);
        while (!ack_received) {
            time_t current_time = time(NULL);
                if (choice == 2 && j == 4 && ctr==0) {
                    printf("Timeout occurred. Retrying...\n");
                    ack_received=false;
                    break;
                } 
            else if (rand() % 10 == 0) { 
                ack_received = true;
                printf("ACK received for bit %d\n", j);
            }
        }

        if (ack_received) {
            j++; 
            ack_received = false; 
        } else {
            ctr=1;
            printf("Resending bit %d...\n", j);
        }
    }

    tt = ts + n * (ts + tp) + (ctr)* (ts + tp); 

    printf("Total time for transmission: %d\n", tt);
}
