#include<iostream>

using namespace std;

int cnt=0;

void Merge(int A[],int p,int q,int r)
{
    int B[r-p+1];
    int i=p;
    int k=p;
    int j=q+1;
    while(i<=q && j<=r)
    {
        if(A[i]<=A[j]) B[k++]=A[i++];
        else B[k++]=A[j++];
    }

    while(i<=q) B[k++]=A[i++];
    while(j<=r) B[k++]=A[j++];

    for(i=p;i<=r;i++) A[i]=B[i];
}

void inversionCountMerge(int A[],int p,int q,int r)
{
    int B[r-p+1];
    int i=p;
    int k=p;
    int j=q+1;
    while(i<=q && j<=r)
    {
        if(A[i]<=A[j]) B[k++]=A[i++];
        else { B[k++]=A[j++]; cnt=cnt+q-i+1;}
    }

    while(i<=q) B[k++]=A[i++];
    while(j<=r) B[k++]=A[j++];

    for(i=p;i<=r;i++) A[i]=B[i];
}

void MergeSort(int A[],int p,int r)
{
    if(p<r)
    {
        int q=(p+r)/2;

        MergeSort(A,p,q);

        MergeSort(A,q+1,r);

        inversionCountMerge(A,p,q,r);
    }
}

void InsertionSort(int A[],int p,int q)
{
    int i,j,key;
    for(i=p+1;i<=q;i++)
    {
        key=A[i];
        j=i-1;
        while(j>=p && A[j]>key)
        {
            A[j+1]=A[j];
            j=j-1;
        }
        A[j+1]=key;
    }
}



void HybridSort(int A[],int p,int r)
{
    if(r-p+1>14)
    {
        int q=(p+r)/2;

        HybridSort(A,p,q);

        HybridSort(A,q+1,r);

        Merge(A,p,q,r);
    }
    else InsertionSort(A,p,r);
}



int main()
{
    int i,n;
    cin>>n;
    int A[n];
    for(i=0;i<n;i++) cin>>A[i];

    HybridSort(A,0,n-1);

    for(i=0;i<n;i++) cout<<A[i]<<" ";
    return 0;
}


/*int main()
{
    int i,n;
    cin>>n;
    int A[n];
    for(i=0;i<n;i++) cin>>A[i];

    MergeSort(A,0,n-1);

    for(i=0;i<n;i++) cout<<A[i]<<" ";
    cout<<"\nTotal Inversions: "<<cnt;
    return 0;
}*/

