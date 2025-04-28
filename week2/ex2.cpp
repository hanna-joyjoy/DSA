#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k)
{
    int i=0;
    while (a[i]!=k) i++;
    if (i<n) return i;
    return -1;
}


int main()
{
    int n;
    int key;
    int a[10000];
    cin>>n;
    for (int i=0; i<n; i++)
        cin>>a[i];
    cin>>key;
    a[n]=key;
    cout<<linearSearch(a,n,key);
    return 0;
}
