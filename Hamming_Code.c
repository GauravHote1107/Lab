#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int messageSize, parityBit = 0;
    
    // Prompt for message size
    printf("Enter message size: ");
    scanf("%d", &messageSize);
    
    // Calculate number of parity bits needed
    while ((messageSize + parityBit + 1) > pow(2, parityBit))
        parityBit++;

    int msg[messageSize + parityBit + 1]; // Array to store message and parity bits
    int data[messageSize + parityBit + 1]; // Array to store Hamming code

    // Prompt for message bits
    printf("Enter message bits (space separated): ");
    for (int i = 1; i <= messageSize; i++)
        scanf("%d", &msg[i]);

    // Initialize Hamming code with 0
    for (int i = 1; i <= (messageSize + parityBit); i++)
        data[i] = 0;

    // Insert message bits into Hamming code
    int j = 1;
    for (int i = 1; i <= (messageSize + parityBit); i++) {
        if ((i & (i - 1)) == 0) // Check if i is a power of 2
            continue; // Skip parity bits
        data[i] = msg[j];
        j++;
    }

    // Calculate parity bits
    for (int i = 0; i < parityBit; i++) {
        int parityPosition = (int)pow(2, i);
        int count = 0;
        for (int j = parityPosition; j <= (messageSize + parityBit); j += (2 * parityPosition)) {
            for (int k = 0; k < parityPosition && (j + k) <= (messageSize + parityBit); k++) {
                if (data[j + k] == 1)
                    count++;
            }
        }
        if (count % 2 != 0)
            data[parityPosition] = 1;
    }

    // Display generated Hamming code
    printf("Generated Hamming code: ");
    for (int i = (messageSize + parityBit); i >= 1; i--)
        printf("%d ", data[i]);

    printf("\n");

    // Error correction
    printf("Enter the received code (space separated): ");
    for (int i = (messageSize + parityBit); i >= 1; i--)
        scanf("%d", &data[i]);

    int errorPosition = 0;
    for (int i = 0; i < parityBit; i++) {
        int parityPosition = (int)pow(2, i);
        int count = 0;
        for (int j = parityPosition; j <= (messageSize + parityBit); j += (2 * parityPosition)) {
            for (int k = 0; k < parityPosition && (j + k) <= (messageSize + parityBit); k++) {
                if (data[j + k] == 1)
                    count++;
            }
        }
        if (count % 2 != 0)
            errorPosition += parityPosition;
    }

    if (errorPosition == 0)
        printf("No error in data.\n");
    else {
        printf("Error at position: %d\n", errorPosition);
        data[errorPosition] = (data[errorPosition] == 0) ? 1 : 0;
        printf("Code after error correction: ");
        for (int i = (messageSize + parityBit); i >= 1; i--)
            printf("%d", data[i]);
        printf("\n");
    }

    return 0;
}
