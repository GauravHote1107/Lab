#include <stdio.h>

int Time(int t, int p)
{
    int ans = 2 * (t + p);
    return ans;
}

int main()
{

    int t, p, n;

    printf("Enter transmission time (Tt): \n");
    scanf("%d", &t);
    printf("Enter propagation time (Tt): \n");
    scanf("%d", &p);

    printf("Enter number of packets to send: \n");
    scanf("%d", &n);

    int totalTime = n * Time(t, p);

    printf("Time for 1 packet to transfer is %d \n", Time(t, p));
    printf("Time for n packets to transfer is %d ", totalTime);

    return 0;
}


/*
Enter transmission time (Tt): 
1 
Enter propagation time (Tt): 
5
Enter number of packets to send: 
10
Time for 1 packet to transfer is 12 
Time for n packets to transfer is 120 
*/


/*
gcc Noiselecc.c
./a.out
*/