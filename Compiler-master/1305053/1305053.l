
%{
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include <fstream>
#include<string>
#include<bits/stdc++.h>
#include "y.tab.h"
using namespace std;


int line_count=0;
int error_count=0;
int word_count=0;

extern FILE *outputlog;
extern FILE *outputtoken;


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
	    //cout << "n = " << n << endl;
            return sum%n;
        }

        void Insert(string s1,string s2)
        {
            int index,k=0;
            if(Look_up(0,s1)==1)
            {
                //cout<<"Already exists"<<endl;
                fprintf(outputlog,"Already exists\n");
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
                //cout<<"Inserted at "<<index<<","<<0<<endl;
		fprintf(outputlog,"Inserted at %d,0\n",index);
            }
            else{
                while(temp!=0)
                    {
                        prev=temp;
                        temp=temp->next;
                        k++;
                    }
                    prev->next=newNode;
                    //cout<<"Inserted at "<<index<<","<<k<<endl;
		    fprintf(outputlog,"Inserted at %d,%d\n",index,k);
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

        /*void Delete(string s)
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

        }*/

        void Print()
        {
            for(int i=0;i<n;i++)
            {
                //cout<<i<<" -> ";
		fprintf(outputlog,"%d ->",i);
                SymbolInfo *temp=smif[i].next;
                while(temp!=0)
                {
                    //cout<<" < "<<temp->getName()<<" , "<<temp->getType()<<" > ";
		    char t[1000],t1[1000];
		    strcpy(t,temp->getName().c_str());
		    strcpy(t1,temp->getType().c_str());
		    fprintf(outputlog," < %s , %s > ",t,t1);
                    temp = temp->next;
                }
                fprintf(outputlog,"\n");
            }

        }

        /*~SymbolTable()
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

        }*/
};

//SymbolTable ST(15);

%}

whitespace  [ \t\v\f\r]+
newline     [\n]
float       [\+-]?[0-9]+(\.[0-9]+(E[\+-]?[0-9]+)?)
error       [\+-]?[0-9]+(\.[0-9]+(E[\+-]?[0-9]+(\.)+[0-9]+))
identifier  [a-zA-Z_]+[a-zA-Z0-9_]*
char       '[^\n\t\a\b\v\r\f\0\\\"]'
string      (\"(\\.|[^\\"])*\")
ADDOP [+-] 
MULOP [*/%]

%%

{whitespace}    {word_count++;}
{newline}       {line_count++;}

"if"              {return IF;}
"else"            {return ELSE;}
"for"             {return FOR;}
"do"              {return DO;}
"while"           {return WHILE;}
"int"             {return INT;}
"char"            {return CHAR;}
"float"           {return FLOAT;}
"double"          {return DOUBLE;}
"void"            {return VOID;}
"return"          {return RETURN;}
"continue"        {return CONTINUE;}
"println"	  {return PRINTLN;}
"main"            {return MAIN;}
[\+-]?[0-9]+      {yylval.i=atoi(yytext);
		   return CONST_INT;}
{float}           {yylval.db=atof(yytext);
		   return CONST_FLOAT;}
{char}           {yylval.a=yytext;return CONST_CHAR;}
{identifier}     {yylval.a=strdup(yytext);return ID;}


{ADDOP} { 		yylval.a=strdup(yytext);
			return ADDOP;
		}



{MULOP}	{
			yylval.a=strdup(yytext);return MULOP;
		}


"=" 	{return ASSIGNOP;}

">" |
"<" |
">=" |
"<=" |
"==" |
"!=" {
		
		yylval.a=strdup(yytext);return RELOP;
	}

"&&"	|
"||"	        {
			
			yylval.a=strdup(yytext);return LOGICOP;
		}
"!"		{	return NOT; }


";" 	{ return SEMICOLON;}
"," 	{return COMMA;}
"(" 	{return LPAREN;}
")" 	{return RPAREN;}
"{" 	{return LCURL;}
"}" 	{return RCURL;}
"[" 	{return LTHIRD;}
"]" 	{return RTHIRD;}
"++" 	{return INCOP;}
"--" 	{return DECOP;}





%%

int yywrap(void)
{
	return 1;
}



