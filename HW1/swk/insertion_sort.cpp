#include <iostream>
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
void print_vector(int v[], int n)
{
    int i;
    std::cout << "vector:";
    for (i = 0; i < n; i++)
        std::cout << "" << v[i];
    std::cout << std::endl;
}
int main()
{
    int v[] = { 9, 8, 7, 6 ,5 ,4 ,3 ,2 ,1 ,0 };
    print_vector(v,10);
    insertion_sort(v,10);
    print_vector(v, 10);
}