#include<iostream>
#include<string>

using namespace std;

int maxarray(int a,int b,int c)
{
    int m;
    if(a>b)
    {
        if(a>c) m=a;
        else m=c;
    }
    else
    {
        if(b>c) m=c;
        else m=c;
    }
    return m;
}


void optimizeDP(string X,string Y,int row[])
{
    int i,j;
    int lnX=X.length();
    int lnY=Y.length();
    int collum[lnX], temp[lnY];
    for(i=1;i<=lnY;i++) row[i]=-i;
    for(i=1;i<lnX;i++) collum[i]=-i;
    row[0]=0;
    collum[0]=0;

    for(i=1;i<=lnX;i++)
    {
        for(j=1;j<=lnY;j++)
        {
            if(X[i]==Y[j])
            {
                if(j==1)
                {
                    temp[j]=maxarray(row[j]-1,collum[j]-1,collum[j-1]+1);
                }
                else
                {
                    temp[j]=maxarray(row[j]-1,temp[j-1]-1,row[j-1]+1);
                }
            }
            else
            {
                if(j==1)
                {
                    temp[j]=maxarray(row[j]-1,collum[j]-1,collum[j-1]-1);
                }
                else
                {
                    temp[j]=maxarray(row[j]-1,temp[j-1]-1,row[j-1]-1);

                }
            }
        }

        for(int p=1;p<=lnY;p++)  row[i]=temp[i];
    }
    return ;
}

void findPath(string A,string B)
{
    int lnA,lnB,mid,k,i,j;
    lnA=A.length();
    lnB=B.length();
    mid = lnA/2;

    cout<<lnA<<" "<<lnB<<" "<<mid<<endl;

    if(lnA==1)
    {
        if(lnB==0)
            cout<<"-";
        else
        {
            for(i=1;i<=lnB;i++)
            {
                if(i==lnB)
                    cout<<B[i];
                else
                    cout<<"-";
            }
        }
        return;
    }
    if(lnB==0)
    {
        return;
    }



    string A_1st_hlf_frd ,A_2nd_half_rev,B_frd,B_rev;

    for(i=0;i<mid;i++)  A_1st_hlf_frd[i]=A[i];
    for(j=lnA,i=0;j>=mid;j--,i++) A_2nd_half_rev[i]=A[j];
    for(i=0;i<lnB;i++) B_frd[i]=B[i];
    for(i=0;i<lnB;i++) B_rev[i]=B[lnB-i-1];

    //cout<<A_1st_hlf_frd<<" "<<A_2nd_half_rev<<" "<<B_frd<<" "<<B_rev<<endl;

    int valueSetA[lnB+1],valueSetB[lnB+1];

    optimizeDP(A_1st_hlf_frd,B_frd,valueSetA);
    optimizeDP(A_2nd_half_rev,B_rev,valueSetB);

    int m=-999999;
    for(i=0,j=lnB;i<=lnB;i++,j--)
    {
        if(valueSetA[i]+valueSetB[j]>m) {m=valueSetA[i]+valueSetB[j]; k=i;}
    }

    string A1,A2,B1,B2;
    for( i=0;i<mid;i++) A1[i]=A[i];
    for( i=mid,j=0;i<lnA;i++,j++) A1[j]=A[i];

    for( i=0;i<k;i++) B1[i]=B[i];
    for( i=k,j=0;i<lnB;i++,j++) B1[j]=B[i];

    findPath(A1,B1);
    findPath(A2,B2);


    return ;

}

int main()
{
    string A,B;
    cin>>A;
    cin>>B;
    findPath(A,B);
    return 0;
}
