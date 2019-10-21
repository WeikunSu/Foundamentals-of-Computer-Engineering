#include <iostream>
#include <windows.h>

void insertion_sort(int v[], int n)
{
    int value;
    int i, j;
    for (i = 1; i < n; i++)
    {
        value = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > value)
        {
            v[j + 1] = v[j];
            j--;

        }
        v[j + 1] = value;
    }
}

void merge(int v[], int l, int m, int h)
{
    int i, j, k;
    int temp[h - l + 1];
    i = l;
    j = m + 1;
    k = 0;
    while (i <= m && j <= h)
    {
        if (v[i] < v[j])
        {
            temp[k] = v[i];
            i++;
            k++;
        }
        else
        {
            temp[k] = v[j];
            j++;
            k++;
        }
    }
    while (i <= m)
    {
        temp[k] = v[i];
        i++;
        k++;
    }
    while (j <= h)
    {
        temp[k] = v[j];
        j++;
        k++;
    }
    for (i = l; i <= h; i++)
    {
        v[i] = temp[i - l];
    }
}

void merge_sort(int v[], int l, int h)
{
    int m;
    if (l < h)
    {
        m = (l + h) / 2;
        merge_sort(v, l, m);
        merge_sort(v, m+1, h);
        merge(v, l, m, h);
    }
}
int main()
{
    int n;
    int i;
    n = 50; //input size n
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    double t_1;
    double t_2;
    int v_1[n];
    int v_2[n];
    for (i = 0; i < n; i++)
    {
        v_1[i] = n - i - 1;
    }
    for (i = 0; i < n; i++)
    {
        v_2[i] = n - i - 1;
    }
    QueryPerformanceFrequency(&nFreq); 
    QueryPerformanceCounter(&nBeginTime); //begin time of insertion sort
    insertion_sort(v_1, n);
    QueryPerformanceCounter(&nEndTime); //end time of insertion sort
    t_1 = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; //running time of insertion sort
    QueryPerformanceCounter(&nBeginTime); //begin time of merge sort 
    merge_sort(v_2, 0, n-1);
    QueryPerformanceCounter(&nEndTime); //end time of merge sort
    t_2 = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; //running time of merge sort 
    std::cout << "running time of insertion sort:" << t_1 << "s" << std::endl ;
    std::cout << "running time of merge sort:" << t_2 << "s" << std::endl ;
    return 0;
}