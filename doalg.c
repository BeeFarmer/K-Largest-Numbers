#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define G 10

// --------Print list for debugging --------
void print_list(int a[], int s)
{
    for (int i=0; i<s; ++i)
        printf("%d --> %d\n", i, a[i]);    
}

//-------- Quicksort and Helper Functions --------
void swap(int * x, int * y) 
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int par(int ar[], int left, int right)
{
    int pivot = ar[right];
    int i = left - 1;
    for (int j=left; j<=right-1; ++j)
    {
        if (COMPARE(pivot, ar[j])==1)
        {
            i++;
            swap(&ar[i], &ar[j]);
        }
    }
    swap(&ar[i+1], &ar[right]);
    return (i+1);
}

void qs(int ar[], int left, int right)
{
    if (left < right)
    {
        int p = par(ar, left, right);
        qs(ar, left, p-1);
        qs(ar, p+1, right);
    }
}
//-------------------------------------------
//
//-------- Delete element from array; Select Function ---------
void delete(int index, int a[], int *c)
{
    for (int i=index; i<(*c)-1; ++i)
        a[i] = a[i+1];
    (*c)--;
}

void Select(int ar[], int *siz, int can[], int *coun)
{
    if (*siz!=0)
    {
        int temp_max = ar[0];
        for (int j=1; j<*siz; ++j)
        {
            if (COMPARE(temp_max, ar[j])==2)
            {
                can[(*coun)++] = ar[j];
                delete(j ,ar, &(*siz));
            }
        }
        if (*coun == 0)
        {
            can[(*coun)++] = temp_max;
            delete(0, ar, &(*siz));
        } 
        else 
            qs(can, 0, (*coun)-1);
    }
}
//-------------------------------------------------------------
//
// Constant G is the number of groups divided 
int doalg(int n, int k, int Best[])
{

    int arr[G][n/G], cand[G][n/G];
    int size[G], count[G];
    // Initiation
    for (int i=0; i<G; ++i)
    {
        count[i] = 0;
        size[i] = n/G;
    }
    for (int i=0; i<G; ++i)
        for (int j=0; j<n/G; ++j)
            arr[i][j] = i*(n/G)+j+1;



    for (int i=0; i<G; ++i)
    {
        Select(arr[i], &size[i], cand[i], &count[i]);
    }


    for (int i=0; i<k; ++i)
    {
        int temp_max = cand[0][count[0]-1]; int max_count = 0;
        for (int j=1; j<G; j++)
        {
            if (count[j]==0)
            {
                Select(arr[j], &size[j], cand[j], &count[j]);
            }
            if (count[j]!=0)
            {
                if (COMPARE(temp_max, cand[j][count[j]-1])==2)
                {
                    temp_max = cand[j][count[j]-1];
                    max_count = j;
                }
            }
        }
        Best[i] = temp_max;
        count[max_count]--;
    }

    return (1);
}
