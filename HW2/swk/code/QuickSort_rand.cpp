//Quick Sort
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int partition(int v[], int p, int q){
    int pivot = v[p];
    int i  = p;
    int j;
    for (j = p+1; j <= q; j++){
        if (v[j] < pivot){
            i++;
            std::swap(v[j], v[i]);
        }
    }
    std::swap(v[i],v[p]);
    return i;
}
int partition_rand(int v[], int p, int q){
    int pivot_ind;
    pivot_ind = rand() % (q-p+1) + p;
    std::swap(v[p],v[pivot_ind]);
    return partition(v, p, q);
}
void quickSort_rand(int v[],int p,int q){
    int r;
    if (p < q){
        r = partition_rand(v, p, q);
        quickSort_rand(v, p, r-1);
        quickSort_rand(v, r+1, q);
    }
}

int main(){
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq); // get the frequency of the counter
    double t;
    int j;
    int N = 100;
    int v[N];
    int i;
    srand(time(NULL));
    for (i=0; i<N; i++){
        v[i] = i+1;
    }
    std::cout << "The original array is:" << std::endl; // print original array
    for (i=0; i<N; i++){
        std::cout << v[i] << '\t';
    }
    std::cout << std::endl;
    for (j=0; j<5; j++){
        QueryPerformanceCounter(&nBeginTime); //begin time of quick sort
        quickSort_rand(v, 0, N-1);                
        QueryPerformanceCounter(&nEndTime); //end time of quick sort
        t = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart; //running time of quick sort
        std::cout << "The running time of trial "<< j+1 << " is: " << t << " seconds" << std::endl;
    }
    
    return 0;
}