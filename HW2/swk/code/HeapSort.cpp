//Heap Sort
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void randperm(int a[], int N){
    int i, j;
    for (i=0; i<N; i++){
        j = rand() % (N-i) + i;
        std::swap(a[i], a[j]);
    }
}
void max_heapify(int a[], int N, int i){
    int left, right, largest;
    left = 2*i + 1;
    right = 2*i + 2;
    if (left < N && a[left] > a[i]){
        largest = left;
    }
    else
    {
        largest = i;
    }
    if (right < N && a[right] > a[largest]){
        largest = right;
    }
    if (largest != i){
        std::swap(a[i], a[largest]);
        max_heapify(a, N, largest);
    }
}
void build_max_heap(int a[], int N){
    int i;
    for (i = N/2 - 1; i >= 0; i--){
        max_heapify(a, N, i);
    }
}
void heap_sort(int a[], int N){
    build_max_heap(a, N);
    int i;
    for (i = N - 1; i >= 0; i--){
        std::swap(a[i], a[0]);
        max_heapify(a, i, 0);
    }
}
int main(){
    int i;
    int N = 100;
    int v[N];
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq); // get the frequency of the counter
    double t;
    srand(time(NULL));
    for (i=0; i<N; i++){
        v[i] = i+1;
    }
    randperm(v, N);
    std::cout << "Original array:" << std::endl;
    for (i=0; i<N; i++){
        std::cout << v[i] << '\t' ;
    }
    std::cout << std::endl;
    QueryPerformanceCounter(&nBeginTime);
    heap_sort(v, N);
    QueryPerformanceCounter(&nEndTime);
    t = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    std::cout << "Sorted array:" << std::endl;
    for (i=0; i<N; i++){
        std::cout << v[i] << '\t' ;
    }
    std::cout << std::endl;
    std::cout << "The running time is: " << t << " seconds" << std::endl;
    return 0;
}