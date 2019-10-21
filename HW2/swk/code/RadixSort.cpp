//Radix Sort
#include <iostream>
#include <windows.h>
#include <algorithm>

void counting_sort_d(int a[], int n, int digit){
    int b[n];
    int c[10];
    int i;
    for (i = 0; i < 10; i++){
        c[i] = 0;
    }
    for (i = 0; i < n; i++){
        c[a[i]/digit % 10] = c[a[i]/digit % 10] + 1;
    }
    for (i = 1; i < 10; i++){
        c[i] = c[i] + c[i-1];
    }
    for (i = n-1; i >= 0; i--){
        b[c[a[i]/digit % 10]-1] = a[i];
        c[a[i]/digit % 10] = c[a[i]/digit % 10] - 1;
    }
    for (i = 0; i < n; i++){
        a[i] = b[i];
    }
}
void radix_sort(int a[], int n){
    int digit;
    for (digit = 1; digit <= 100; digit = digit*10){
        counting_sort_d(a, n, digit);
    }
}
int main(){
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq); // get the frequency of the counter
    double t;
    int a[] = {329,457,657,839,436,720,353};
    int n;
    int i;
    n = sizeof(a)/sizeof(a[0]);
    std::cout << "Original array is:" << std::endl;
    for (i = 0; i < n; i++){
        std::cout << a[i] << '\t';
    }
    std::cout << std::endl;
    QueryPerformanceCounter(&nBeginTime);
    radix_sort(a, n);
    QueryPerformanceCounter(&nEndTime);
    t = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    std::cout << "Sorted array is:" << std::endl;
    for (i = 0; i < n; i++){
        std::cout << a[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "The running time is: " << t << " seconds" << std::endl;
}