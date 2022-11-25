#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <ctime>
#include <omp.h>
#define size 100
int** scan_dat(const char* name)
{
    int i, j;
    FILE* fp;
    int** arr = (int**)malloc(size * sizeof(int));
    fp = fopen(name, "r");

    for (i = 0; i < size; i++)
    {
        arr[i] = (int*)malloc(size * sizeof(int));
    }


    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            fscanf(fp, "%d", &arr[i][j]);
    }
    return arr;
}

int** write_dat()
{
    int** arr = (int**)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        arr[i] = (int*)malloc(size * sizeof(int));
    }
    int i, j;
    srand(time(NULL));
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            arr[i][j] = rand();
        }
    }
    return arr;
}


int** mul(int** arr1, int** arr2)
{
    FILE* fp;
    int i, j, k;
    if ((fp = fopen("result.txt", "w+")) == NULL)
    {
        printf("Open are failed");
        getchar();
        return 0;
    }

    int** arr = (int**)malloc(size * sizeof(int));
    for (int i = 0; i < size; ++i)
    {
        arr[i] = (int*)malloc(size * sizeof(int));
    }
    srand(time(0));
    int threads;
    int value = 0;

#pragma omp parallel
    {
#pragma omp for
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                arr[i][j] = 0;
                for (int k = 0; k < size; k++) {
                    arr[i][j] += arr1[i][k] * arr2[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            fprintf(fp, "%d ", arr[i][j]);
        }
        fprintf(fp, "\n");
    }
       printf("%lf ", clock() / 1000.0);
       printf("%d*%d", size, size);
    fclose(fp);
    return arr;
}

int main() {
    const char name1[] = "data1.txt";
    const char name2[] = "data2.txt";
    int** arr1=write_dat();
    int** arr2 =write_dat();
    /*int** arr1 = scan_dat(name1);
    int** arr2 = scan_dat(name2);*/
    int** arr = mul(arr1, arr2);
    return 0;
}