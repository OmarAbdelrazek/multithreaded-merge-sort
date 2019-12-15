#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>


typedef struct my_threads
{
    int low;
    int high;

} TH;
void getInput();
void merge(int low, int mid, int high);
void *mergeSort(TH *info);
void start();
void printArray();
int getSize();
FILE *input;
int size;
int inputArray[];

int main()
{
    start();
    printArray();

    return 0;
}
void printArray()
{
    printf("Sorted Array: ");
    for(int i=0; i<size; i++)
    {
        printf("%d  ",inputArray[i]);
    }
}
void getInput()
{
    getSize();
    int value;
    for(int i=0; i<size; i++)
    {
        fscanf(input,"%d",&value);
        inputArray[i] = value;
    }
}
int getSize()
{
    fscanf(input,"%d",&size);
    inputArray[size];
}

// merge function for merging two parts
void merge(int low, int mid, int high)
{

    int i, j;
    int left = mid - low + 1;
    int right =  high - mid;

    /* create temp arrays */
    int L[left], R[right];
    // storing values in left part
    for (i = 0; i < left; i++)
        L[i] = inputArray[low + i];
    // storing values in right part
    for (j = 0; j < right; j++)
        R[j] = inputArray[mid + 1+ j];

    i = 0;
    j = 0;
    int k = low;

    while (i < left && j < right)
    {
        if (L[i] <= R[j])
        {
            inputArray[k] = L[i];
            i++;
        }
        else
        {
            inputArray[k] = R[j];
            j++;
        }
        k++;
    }


    while (i < left)
    {
        inputArray[k] = L[i];
        i++;
        k++;
    }


    while (j < right)
    {
        inputArray[k] = R[j];
        j++;
        k++;
    }
}
void *mergeSort(TH *t)
{

    TH th1, th2;
    pthread_t thread_id[2];
    if ((t->high) < (t->low))
    {
        int mid = ((t->high)+((t->low)))/2;
        th1.high = mid+1;
        th1.low = t->low;
        pthread_create(&thread_id[1], NULL, mergeSort, &th1);        //mergeSort(inputArray, mid+1, high);
        th2.high = t->high;
        th2.low = mid;
        pthread_create(&thread_id[0], NULL, mergeSort, &th2);        //mergeSort(inputArray, low, mid);
        pthread_join(thread_id[0], NULL);
        pthread_join(thread_id[1], NULL);
        merge(t->high, mid, t->low);
    }
}


void start()
{
    input = fopen("inputmerge.txt","r");
    getInput();
    fclose(input);


    clock_t start, low;
    float calculatedTime;
    start = clock();
    TH t;
    t.high = 0;
    t.low = size - 1;
    pthread_t tid;
    pthread_create(&tid, NULL, mergeSort, &t);
    pthread_join(tid, NULL);
    low = clock();
    calculatedTime = ((float) (low - start)) / CLOCKS_PER_SEC;
    printf("\nTime = ---%f sec---\n",calculatedTime);
}
