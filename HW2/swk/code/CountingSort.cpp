//Counting sort
#include <iostream>
#include <windows.h>
#include <algorithm>

void counting_sort(int a[],int n){
    int k;
    k = *std::max_element(a, a + n);
    int i;
    int c[k+1];
    int b[n];
    for (i = 0; i <= k; i++){
        c[i] = 0;
    }
    for (i = 0; i < n; i++){
        c[a[i]] = c[a[i]] + 1;
    }
    for (i = 1; i <= k; i++){
        c[i] = c[i] + c[i-1];
    }
    for (i = n-1; i >= 0; i--){
        b[c[a[i]]-1] = a[i];
        c[a[i]] = c[a[i]]-1;
    }
    for (i = 0; i < n; i++){
        a[i] = b[i];
    }
}
int main(){
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq); // get the frequency of the counter
    double t;
    int a[] = {20,18,5,7,16,10,9,3,12,14,0};
    int n;
    n = sizeof(a)/sizeof(a[0]);
    int i;
    std::cout << "Original array is:" << std::endl;
    for (i = 0; i < sizeof(a)/sizeof(a[0]); i++){
        std::cout << a[i] << '\t';
    }
    std::cout << std::endl;
    QueryPerformanceCounter(&nBeginTime);
    counting_sort(a, n);
    QueryPerformanceCounter(&nEndTime);
    t = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    std::cout << "Sorted array is:" << std::endl;
    for (i = 0; i < sizeof(a)/sizeof(a[0]); i++){
        std::cout << a[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "The running time is: " << t << " seconds" << std::endl;
}