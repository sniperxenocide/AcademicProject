#include <iostream>

using namespace std;

int main()
{
    int n,capasity,i,val=0;
    cout<<"no of item:";
    cin>>n;
    cout<<"capasity:";
    cin>>capasity;
    int weight[n],value[n];
    for(i=0;i<n;i++)
    {
        cin>>weight[i]>>value[i];
    }

    double priority[n];
    for(i=0;i<n;i++) {priority[i]=(double)value[i]/(double)weight[i];}

    int present=0;
    int max,rest;
    while(1)
    {
        max=0;
        for(i=1;i<n;i++)
        {
            if(priority[i]>priority[max]) max=i;
        }
        priority[max]=-1;
        rest=capasity-present;
        present+=weight[max];
        if(present>capasity) break;
        cout<<"taken "<<max+1<<"th item, weight: "<<weight[max]<<" value: "<<value[max]<<endl;
        val+=value[max];
    }


    cout<<"taken "<<max+1<<"th item, weight: "<<rest<<" value: "<<((double)value[max]/(double)weight[max])*rest<<endl;

    val=val+((double)value[max]/(double)weight[max])*rest;

    cout<<" total value: "<<val;

    return 0;
}
