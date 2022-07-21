#include<iostream>
#include<string>

using namespace std;

int getMax(int a,int b,int c)
{
    int max=a;
    if(b>max) max=b;
    if(c>max) max=c;
    return max;
}



int main()
{
    string A,B;

    cin>>A;
    cin>>B;

    int m,n;
    m=A.length();
    n=B.length();


    int dp[m+1][n+1];

    for(int i=0;i<=m;i++) dp[i][0]=-i;
    for(int j=0;j<=n;j++) dp[0][j]=-j;


    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(A[i-1]==B[j-1])
            {
                dp[i][j]=getMax(dp[i-1][j-1]+1,dp[i-1][j]-1,dp[i][j-1]-1);
            }
            else
            {
                dp[i][j]=getMax(dp[i-1][j-1]-1,dp[i-1][j]-1,dp[i][j-1]-1);

            }
        }
    }

    cout<<"Answer: "<<dp[m][n]<<endl;

    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(dp[i][j]<0) cout<<" "<<dp[i][j];
            else cout<<"  "<<dp[i][j];
        }
        cout<<endl;
        cout<<endl;
    }
    int i,j,p=0,q=0;
    char sqnA[300],sqnB[300];
    for(i=m,j=n;i>0 && j>0;)
    {
        if(A[i-1]==B[j-1])
        {
            sqnA[p++]=A[i-1];
            sqnB[q++]=B[j-1];
            i--;
            j--;
        }
        else
        {
            if(dp[i][j]==dp[i-1][j-1]-1)
            {
                sqnA[p++]=A[i-1];
                sqnB[q++]=B[j-1];
                i--;
                j--;
            }
            else if(dp[i][j]==dp[i-1][j]-1)
            {
                sqnA[p++]=A[i-1];
                sqnB[q++]='-';
                i--;
            }
            else if(dp[i][j]==dp[i][j-1]-1)
            {
                sqnA[p++]='-';
                sqnB[q++]=B[j-1];
                j--;
            }

        }
    }
    if(i==0)
    {
       while(j>0)
       {
           sqnB[q++]=B[j-1];
           sqnA[p++]='-';
           j--;
       }
    }
    else if(j==0)
    {
        while(i>0)
        {
           sqnB[q++]='-';
           sqnA[p++]=A[i-1];
           i--;
        }
    }
    sqnA[p]='\0';
    sqnB[q]='\0';

    for(i=p-1;i>=0;i--)
    {
        cout<<sqnA[i];
    }
    cout<<endl;
    for(i=q-1;i>=0;i--)
    {
        cout<<sqnB[i];
    }
    cout<<endl;
    return 0;

}




/*
int main()
{
    string A,B;

    cin>>A;
    cin>>B;

    int m,n;
    m=A.length();
    n=B.length();


    int dp[m+1][n+1];

    for(int i=0;i<=m;i++) dp[i][0]=0;
    for(int j=0;j<=n;j++) dp[0][j]=0;

    int r;
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<=n;j++)
        {
            if(A[i-1]==B[j-1])
            {
                r=getMax(dp[i-1][j-1]+1,dp[i-1][j]-1,dp[i][j-1]-1);
                if(r<0) r=0;
                dp[i][j]=r;
            }
            else
            {
                r=getMax(dp[i-1][j-1]-1,dp[i-1][j]-1,dp[i][j-1]-1);
                if(r<0) r=0;
                dp[i][j]=r;
            }
        }
    }
    int mxi,mxj,mx=dp[0][0];
    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(dp[i][j]>mx)
            {
                mx=dp[i][j];
                mxi=i;
                mxj=j;
            }
        }
    }

    cout<<"Answer: "<<dp[m][n]<<endl;

    for(int i=0;i<=m;i++)
    {
        for(int j=0;j<=n;j++)
        {
            if(dp[i][j]<0) cout<<" "<<dp[i][j];
            else cout<<"  "<<dp[i][j];
        }
        cout<<endl;
        cout<<endl;
    }
    int i,j,p=0,q=0;
    char sqnA[300],sqnB[300];
    for(i=mxi,j=mxj;i>0 && j>0;)
    {
        if(A[i-1]==B[j-1])
        {
            sqnA[p++]=A[i-1];
            sqnB[q++]=B[j-1];
            i--;
            j--;
        }
        else
        {
            if(dp[i][j]==dp[i-1][j-1]-1)
            {
                sqnA[p++]=A[i-1];
                sqnB[q++]=B[j-1];
                i--;
                j--;
            }
            else if(dp[i][j]==dp[i-1][j]-1)
            {
                sqnA[p++]=A[i-1];
                sqnB[q++]='-';
                i--;
            }
            else if(dp[i][j]==dp[i][j-1]-1)
            {
                sqnA[p++]='-';
                sqnB[q++]=B[j-1];
                j--;
            }

        }
    }

    sqnA[p]='\0';
    sqnB[q]='\0';

    for(i=p-1;i>=0;i--)
    {
        cout<<sqnA[i];
    }
    cout<<endl;
    for(i=q-1;i>=0;i--)
    {
        cout<<sqnB[i];
    }
    cout<<endl;
    return 0;

}
*/

