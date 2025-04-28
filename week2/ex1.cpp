#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k)
{
    for (int i=0; i<n; ++i)
    {
        if (a[i]==k)
            return i;
    }
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
    cout<<linearSearch(a,n,key);
    return 0;
}
