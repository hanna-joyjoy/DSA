#include <iostream>
using namespace std;

int binarySearch(int a[], int l, int r)
{
    int m;
    while (l<r)
    {
        m = (l+r)/2;
        if (a[m]>a[r]) l=m+1; //min is in the right half --> set l = m + 1
        if (a[m]<=a[r]) r=m; //min is in the left half or it could be the middle itself --> set r = m
    }
    return a[l]; //The loop will eventually narrow down to the smallest element when left == right
}



int main()
{
    int n;
    int a[10000];
    cin>>n;
    for (int i=0; i<n; i++)
        cin>>a[i];
    cout<<binarySearch(a,0,n-1);
    return 0;
}
