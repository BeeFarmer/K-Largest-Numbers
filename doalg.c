#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

#define G 50

// --------Print list for debugging --------
void print_list(int a[], int s)
{
    for (int i=0; i<s; ++i)
        printf("%d ", a[i]);
    printf("\n");    
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
        if (COMPARE(pivot, ar[j])!=2)
        //if (pivot > ar[j])
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
    a[index] = -1; (*c)--;
}

void Select(int ar[], int *siz, int can[], int *coun, int s, int h)
{
    if (*siz!=0)
    {
        int j=0;
        while (ar[j] == -1)
            j++;
        
        int del_j = j;
        int temp_max = ar[j++];
        
        int hcount = 1; 
        while (hcount < h)
        {
            while (ar[j] == -1)
                j++;
            if (COMPARE(temp_max, ar[j]) == 2){
                temp_max = ar[j];
                del_j = j;
            }
            hcount++; j++;
        }

        can[(*coun)++] = temp_max;
        delete(del_j, ar, &(*siz));
        for ( int x=j; x<s; ++x)
        {
            if (ar[x] != -1){
                if (COMPARE(temp_max, ar[x])==2)
                //if (temp_max < ar[j])
                {
                    can[(*coun)++] = ar[x];
                    delete(x ,ar, &(*siz));
                }
            }
        }
        //printf("qs\n");
        //print_list(can, *coun);
    }
}

void Select2(int can[], int high[], int low[], int hsize[], int lsize[], int* count, int g)
{
    //copy ?
    int temp_max = can[0]; int i = 1;

    for ( ; i < 5; i++){
        if (COMPARE(temp_max,can[i])==2)
            temp_max = can[i];
    }
    for ( ; i < *count; ++i)
    {
        if (COMPARE(temp_max, can[i])==2)
            high[hsize[g]++] = can[i];
        else
            low[lsize[g]++] = can[i];
    }
}
//-------------------------------------------------------------
//
// Constant G is the number of groups divided 
int doalg(int n, int k, int Best[])
{
    //float H = ceil(n/G*0.01);
    int H = (n==100) ? 1 : 10;
    int arr[G][n/G], cand[G][n/G];
    int size[G], count[G];
    int high[G][n/G], low[G][n/G];
    int hsize[G], lsize[G];
    bool flag[G];
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
        hsize[i] = 0; lsize[i] = 0; flag[i] = false;
    }


    for (int i=0; i<G; ++i)
    {
        Select(arr[i], &size[i], cand[i], &count[i], n/G, H);
        //if (count[i]<40)
        qs(cand[i], 1, count[i]-1);
        /*else {
            Select2(high[i], count[i], i);
            qs(high[i], 1, hsize[i]-1);
            flag[i] = true;
        }*/
    }

    /* 
    printf("CAND\n");
    for (int i=0; i<G; ++i)
    {
        for (int j=0; j<count[i]; j++){
            //printf("%d ", COMPARE(cand[i][count[i]-1], cand[i][j]));
            printf("%d ", cand[i][j]);
        }
        printf("COUNT: %d\n", count[i]);
        printf("\n");}*/


    for (int i=0; i<k; ++i)
    {
        int t = 0;
        while (count[t]==0)
            t++;
        int temp_max = cand[t][count[t]-1]; int mc = t;
        for (int j=0; j<G; j++)
        {
            if (j != t)
            {
                //printf("Current-> %d\n", temp_max);
                if (count[j]!=0)
                {
                    if (COMPARE(temp_max, cand[j][count[j]-1])==2)
                    //if (temp_max < cand[j][count[j]-1])
                    {
                        temp_max = cand[j][count[j]-1];
                        mc = j;
                    }
                }
            }
        }
        Best[i] = temp_max;
        count[mc]--;
        if (i!=k-1 && count[mc]==0){
                Select(arr[mc], &size[mc], cand[mc], &count[mc], n/G, H);
                qs(cand[mc], 1, count[mc]-1);
        }
    }

    /* 
    printf("BEST\n");
    for (int i=0; i<k; ++i)
        printf("%d ", Best[i]);
        //printf("%d ", COMPARE(Best[8], Best[i]));

    //printf("DONE!!!\n");*/
    return (1);
}
