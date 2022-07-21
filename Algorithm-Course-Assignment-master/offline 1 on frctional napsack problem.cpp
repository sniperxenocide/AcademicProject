#include<iostream>
#define LOWVALUE -9999999

using namespace std;

int item,knapsackCapacity;
float preference[100],weight[100],value[100],order[100];

void MAX_HEAPIFY(float ARA[],int i)
{
    int l,r,largest;
    l=2*i;
    r=2*i+1;
    if(l<=item && ARA[l]>ARA[i])
    {
        largest=l;
    }
    else largest=i;

    if(r<=item && ARA[r]>ARA[largest]) largest=r;

    if(largest!=i)
    {
       float tmp;
        tmp=ARA[i];
        ARA[i]=ARA[largest];
        ARA[largest]=tmp;

        int t;
        t=order[i];
        order[i]=order[largest];
        order[largest]=t;

        MAX_HEAPIFY(ARA,largest);
    }

}

void BUILD_HEAP(float ara[])
{
    int i;
    for(i=1;i<=item/2;i++)
    {
        MAX_HEAPIFY(ara,i);
    }
}


int EXTRACT_MAX(float A[])
{
    int i=order[1];
    A[1]=LOWVALUE;
    MAX_HEAPIFY(A,1);
    return i;
}

int main()
{
    cout<<"Number of Item:";
    cin>>item;
    cout<<"capacity:";
    cin>>knapsackCapacity;
    int i;
    float total=0,profit=0,rest=0;
    for(i=1;i<=item;i++)
    {
        cin>>weight[i]>>value[i];
        preference[i]=value[i]/weight[i];
        order[i]=i;
    }

    BUILD_HEAP(preference);
    int n;
    while(1)
    {
        n=EXTRACT_MAX(preference);
        rest=knapsackCapacity-total;
        total+=weight[n];
        if(total>=knapsackCapacity) break;
        cout<<"Taken "<<n<<" th item, weight: "<<weight[n]<<" value "<<value[n]<<endl;
        profit+=value[n];
    }

    cout<<"Taken "<<n<<" th item, weight: "<<rest<<" value "<<(value[n]/weight[n])*rest<<endl;

    profit=profit+(value[n]/weight[n])*rest;

    cout<<"profit: "<<profit<<endl;

    return 0;
}
