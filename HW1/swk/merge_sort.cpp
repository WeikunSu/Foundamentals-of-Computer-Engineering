#include <iostream>
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
    merge_sort(v,0,9);
    print_vector(v, 10);
}