#include<iostream>
#include<stdio.h>
#include <fstream>
#include<string>

using namespace std;

class SymbolInfo
{
    public:
    string name;
    string type;
    SymbolInfo *next;

    public:
    SymbolInfo(string n,string t)
    {
        this->name=n;
        this->type=t;
    }

    SymbolInfo()
    {
        this->name=" ";
        this->type=" ";
        this->next=0;
    }

    void setName(string n)
    {
        this->name=n;
    }
    string getName()
    {
        return this->name;
    }

    void setType(string t){ this->type=t;}
    string getType(){ return this->type;}
};




class SymbolTable
{
    public:
    int n;
    SymbolInfo *smif;

    public:
        SymbolTable(int n)
        {
            this->n=n;
            smif=new SymbolInfo[n];
            for(int i=0;i<n;i++)
            {
                smif[i].next=0;
            }
        }

        int HashFunction(string str)
        {
            int sum=0;
            for(int i=0;i<str.length();i++) sum+=str[i];
            return sum%n;
        }

        void Insert(string s1,string s2)
        {
            int index,k=0;
            if(Look_up(0,s1)==1)
            {
                cout<<"Already exists"<<endl;
                return;
            }
            SymbolInfo *newNode,*temp,*prev;
            newNode=new SymbolInfo;
            newNode->setName(s1);
            newNode->setType(s2);


            index=HashFunction(s1);
            temp=smif[index].next;
            prev=temp;
            if(temp==0) {
                smif[index].next=newNode;
                cout<<"Inserted at "<<index<<","<<0<<endl;
            }
            else{
                while(temp!=0)
                    {
                        prev=temp;
                        temp=temp->next;
                        k++;
                    }
                    prev->next=newNode;
                    cout<<"Inserted at "<<index<<","<<k<<endl;
            }


        }
        int Look_up(int m,string s)
        {
            int index , k=0;
            index=HashFunction(s);
            SymbolInfo *temp=smif[index].next;
            while(temp!=0)
            {
                if(temp->getName()==s)
                {
                    if(m==1) cout<<"Found at "<<index<<","<<k<<endl;
                    return 1;
                }
                k++;
                temp=temp->next;
            }
            if(m==1) cout<<"Not Found"<<endl;
            return 0;

        }

        void Delete(string s)
        {
            int index , k=0;
            index=HashFunction(s);
            SymbolInfo *temp=smif[index].next,*prev=temp;
            while(temp!=0)
            {
                if(temp->getName()==s)
                {
                    if(temp==smif[index].next)
                    {
                        smif[index].next=temp->next;
                        delete temp;
                    }
                    else if(temp->next==0)
                    {
                        prev->next=0;
                        delete temp;
                    }
                    else
                    {
                        prev->next=temp->next;
                        delete temp;
                    }
                    cout<<"Deleted From "<<index<<","<<k<<endl;
                    return ;
                }
                k++;
                prev=temp;
                temp=temp->next;
            }
            cout<<"Could not Delete"<<endl;

        }

        void Print()
        {
            for(int i=0;i<n;i++)
            {
                cout<<i<<" -> ";
                SymbolInfo *temp=smif[i].next;
                while(temp!=0)
                {
                    cout<<" < "<<temp->getName()<<" , "<<temp->getType()<<" > ";
                    temp = temp->next;
                }
                cout<<endl;
            }

        }

        ~SymbolTable()
        {
            for(int i=0;i<n;i++)
            {
                SymbolInfo *temp,*prev;
                temp=smif[i].next;
                prev=&smif[i];
                delete prev;
                while(temp!=0)
                {
                    temp=temp->next;
                    prev=temp;
                    delete prev;
                }
            }

        }
};



int main()
{
    int n;
    ifstream F;
    F.open("input.txt");
    if (!F.is_open()) return 0;
    string s1,s2,input;
    F>>n;
    //cin>>n;
    SymbolTable st(n);
    while(F>>input)
    {
        if(input=="I")
        {
            //cin>>s1>>s2;
            //SymbolInfo si(s1,s2);
            F>>s1;
            F>>s2;
            st.Insert(s1,s2);
        }
        else if(input=="L")
        {
            //cin>>s1;
            F>>s1;
            st.Look_up(1,s1);

        }
        else if(input=="D")
        {
            //cin>>s1;
            F>>s1;
            st.Delete(s1);

        }
        else if(input=="P")
        {
            st.Print();

        }
    }


    return 0;
}
