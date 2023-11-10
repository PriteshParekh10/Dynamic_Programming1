//Pritesh Parekh
//1002173280


#include <stdio.h>
#include <stdlib.h>
#define TABSIZE (100)

// creates struct to represent activities
struct Activity
{
    int start;
    int end;
    int weight;
};

// Function to return max from int compare
int max(int x, int y)
{
    if(x>y)
        return x;
    return y;
}

// Binary Search function intialization
int binarySearch(struct Activity a[], int n, int key);

int n;
struct Activity activities[TABSIZE];
int p[TABSIZE];
int M[TABSIZE][TABSIZE]; 
int room1[TABSIZE], room2[TABSIZE];

int main()
{
    int i, j, sum = 0, room1Counter = 0, room2Counter = 0;

    scanf("%d", &n);

    activities[0].end = -999999; // end time for first activity


    for (i = 1; i <= n; i++)
        scanf("%d %d %d", &activities[i].start, &activities[i].end, &activities[i].weight);
    if (i <= n) 
    {
        printf("Intervals not ordered by finish time %d\n", __LINE__);
        exit(0);
    }

    // Calculate the position of activities
    for(i = 1; i <= n; i++)
    {
        p[i] = binarySearch(activities, n + 1, activities[i].start);
    }

    printf("%d\n", n);

    for(i = 1; i <= n; i++)
     {
        printf("%d %d %d\n", activities[i].start, activities[i].end, activities[i].weight);
     }

    // Dynamic programming Calculations
    for (i = 0; i <= n; i++) 
    {
        for (j = 0; j <= n; j++) 
        {
            if (i == j) 
            {
                if (i == 0) 
                {
                    M[i][j] = 0;
                } 
                else 
                {
                    M[i][j] = M[i][i - 1];
                }
            } 
            else if (i > j) 
            {
                M[i][j] = max(M[p[i]][j] + activities[i].weight, M[i - 1][j]);
            } 
            else 
            {
                M[i][j] = max(M[i][p[j]] + activities[j].weight, M[i][j - 1]);
            }
        }
    }

    //Display DP table
   for (i = 0; i <= n; i++) 
   {
        for (j = 0; j <= n; j++)
            printf(" %2d", M[i][j]);
        printf("\n");
    }
    
// traceback
    i = j = n;
    while (1) 
    {
        if (i == j)
            if (i == 0)
                break;
            else
                j--;
        else if (i > j)
            if (M[i][j] == M[p[i]][j] + activities[i].weight) {
                room1[room1Counter++] = i;
                sum += activities[i].weight;
                i = p[i];
            } 
            else
                i--;
        else
            if (M[i][j] == M[i][p[j]] + activities[j].weight) {
                room2[room2Counter++] = j;
                sum += activities[j].weight;
                j = p[j];
            } 
            else
                j--;
    }

    // Display room results
    printf("%d\n", room1Counter);
    for (i = room1Counter - 1; i >= 0; i--)
        printf("%d %d %d\n", activities[room1[i]].start, activities[room1[i]].end, activities[room1[i]].weight);

    printf("%d\n", room2Counter);

    for (i = room2Counter - 1; i >= 0; i--)
        printf("%d %d %d\n", activities[room2[i]].start, activities[room2[i]].end, activities[room2[i]].weight);

    printf("%d\n", sum);
    return 0;

} // end of main

int binarySearch(struct Activity a[], int n, int key)
{
    int low = 0;
    int high = n-1;

    while(low <= high)
    {
        int mid = (low + high) /2;
        
        if(a[mid].end <= key)
        {
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
    return high;
} // end of binarySearch Method


