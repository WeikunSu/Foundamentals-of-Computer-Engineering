#include<iostream>
#include<limits>
#include <windows.h>

int sum(int a[], int l, int h){
    int s = 0;
    int i;
    for (i = l; i <= h; i++){
        s += a[i-1];
    }
    return s;
}

int Max_min_Grouping(int A[], int N, int M, int G[], int disp_mat = 0){
    int i,j,k;
    int s;
    int c[M+1][N+1];
    int B[M+1][N+1];
    int Max_B_min;
    int num_temp = N;
    for (j = 0; j <= M; j++){
        for (i = 0; i <= N; i++){
            c[j][i] = INT32_MAX;
        }
    }
    for (j = 0; j <= M; j++){
        for (i = 0; i <= N; i++){
            B[j][i] = 0;
        }
    }
    for (j = 1; j <= M; j++){
        for (i=1; i<=N; i++){
            if (i>=j){
                Max_B_min = 0;
                for (k = j-1; k <= i-1; k++){
                    s = sum(A, k+1, i);
                    if (c[j-1][k] <= s && c[j-1][k] > Max_B_min){
                        Max_B_min = c[j-1][k];
                        B[j][i] = k;
                    }
                    else if (c[j-1][k] > s && s > Max_B_min)
                    {
                        Max_B_min = s;
                        B[j][i] = k;
                    }
                c[j][i] = Max_B_min;
                }
            }
            else
            {
                c[j][i] = 0;
            }
        }
    }
    if (disp_mat == 1){
        std::cout << "C[i,j]:" << std::endl;
        for (j=1; j<=M; j++){
            for (i=1; i<=N; i++){
                std::cout << c[j][i] << '\t';
            }
            std::cout << std::endl;
        }
        std::cout << "B[i,j]:" << std::endl;
        for (j=1; j<=M; j++){
            for (i=1; i<=N; i++){
                std::cout << B[j][i] << '\t';
            }
            std::cout << std::endl;
        }
    }
    
    for (i=M; i>0; i--){
        G[i-1] = num_temp - B[i][num_temp];
        num_temp -= G[i-1];
    }
    return 0;
}

int main(){
    int disp_mat = 0;                 // Setting 1 to show the table C[i,j] and B[i,j]
    // int A[] = {3,9,7,8,2,6,5,10,1,7,6,4};
    // int A[] = {1,1,1,1,1,1,1,1,1,1,1,1};
    int A[] = {1,2,3,4,5,6,7,8,9,10};
    int M = 10;
    int N = sizeof(A)/sizeof(A[0]);
    int G[N];
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq); // get the frequency of the counter
    double t;
    QueryPerformanceCounter(&nBeginTime);
    Max_min_Grouping(A, N, M, G, disp_mat);
    QueryPerformanceCounter(&nEndTime);
    t = (double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;

    std::cout << "Input array: " <<std::endl;
    for (int i=0; i<N; i++){
        std::cout << A[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "M = " << M << std::endl;

    std::cout << "Grouping result:" <<std::endl;
    for (int i=0; i<M; i++){
        std::cout << G[i] << '\t';
    }
    std::cout << std::endl;
    std::cout << "Running time: " << t << " s" << std::endl;
}