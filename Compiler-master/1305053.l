%option noyywrap

%{
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<stdio.h>
#include <fstream>
#include<string>
#include<bits/stdc++.h>
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

//SymbolTable ST(15);

%}

whitespace  [ \t\v\f\r]+
newline     [\n]
float       [\+-]?[0-9]+(\.[0-9]+(E[\+-]?[0-9]+)?)
error       [\+-]?[0-9]+(\.[0-9]+(E[\+-]?[0-9]+(\.)+[0-9]+))
identifier  [a-zA-Z_]+[a-zA-Z0-9_]*
char       '[^\n\t\a\b\v\r\f\0\\\"]'
string      (\"(\\.|[^\\"])*\")

%%

{whitespace}    {word_count++;}
{newline}       {line_count++;}

"if"              { fprintf(outputtoken,"<IF>");
                    fprintf(outputlog,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);}
"else"            { fprintf(outputtoken,"<ELSE>");
                    fprintf(outputlog,"Line no %d: TOKEN <ELSE> Lexeme %s found\n",line_count,yytext);}
"for"             { fprintf(outputtoken,"<FOR>");
                    fprintf(outputlog,"Line no %d: TOKEN <FOR> Lexeme %s found\n",line_count,yytext);}
"do"              { fprintf(outputtoken,"<DO>");
                    fprintf(outputlog,"Line no %d: TOKEN <DO> Lexeme %s found\n",line_count,yytext);}
"while"           { fprintf(outputtoken,"<WHILE>");
                    fprintf(outputlog,"Line no %d: TOKEN <WHILE> Lexeme %s found\n",line_count,yytext);}
"break"           { fprintf(outputtoken,"<BREAK>");
                    fprintf(outputlog,"Line no %d: TOKEN <BREAK> Lexeme %s found\n",line_count,yytext);}
"int"             { fprintf(outputtoken,"<INT>");
                    fprintf(outputlog,"Line no %d: TOKEN <INT> Lexeme %s found\n",line_count,yytext);}
"char"            { fprintf(outputtoken,"<CHAR,>");
                    fprintf(outputlog,"Line no %d: TOKEN <CHAR> Lexeme %s found\n",line_count,yytext);}
"float"           { fprintf(outputtoken,"<FLOAT>");
                    fprintf(outputlog,"Line no %d: TOKEN <FLOAT> Lexeme %s found\n",line_count,yytext);}
"double"          { fprintf(outputtoken,"<DOUBLE>");
                    fprintf(outputlog,"Line no %d: TOKEN <DOUBLE> Lexeme %s found\n",line_count,yytext);}
"void"            { fprintf(outputtoken,"<VOID>"); 
                    fprintf(outputlog,"Line no %d: TOKEN <VOID> Lexeme %s found\n",line_count,yytext);}
"return"          { fprintf(outputtoken,"<RETURN>");
                    fprintf(outputlog,"Line no %d: TOKEN <RETURN> Lexeme %s found\n",line_count,yytext);}
"switch"          { fprintf(outputtoken,"<SWITCH>");
                    fprintf(outputlog,"Line no %d: TOKEN <SWITCH> Lexeme %s found\n",line_count,yytext);}
"case"            { fprintf(outputtoken,"<CASE>");
                    fprintf(outputlog,"Line no %d: TOKEN <CASE> Lexeme %s found\n",line_count,yytext);}
"default"         { fprintf(outputtoken,"<DEFAULT>");
                    fprintf(outputlog,"Line no %d: TOKEN <DEFAULT> Lexeme %s found\n",line_count,yytext);}
"continue"        { fprintf(outputtoken,"<CONTINUE>");
                    fprintf(outputlog,"Line no %d: TOKEN <CONTINUE> Lexeme %s found\n",line_count,yytext);}

[\+-]?[0-9]+     { fprintf(outputtoken,"<CONST_INT,%s>",yytext);
                  fprintf(outputlog,"Line no %d: TOKEN <CONST_INT> Lexeme %s found\n",line_count,yytext);
		  ST.Insert(yytext,"CONST_INT");
		  ST.Print();}
{float}         { fprintf(outputtoken,"<CONST_FLOAT,%s>",yytext);
                  fprintf(outputlog,"Line no %d: TOKEN <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
		  ST.Insert(yytext,"CONST_FLOAT");
		  ST.Print();}
{char}          { fprintf(outputtoken,"<CONST_CHAR,%s>",yytext);
                  fprintf(outputlog,"Line no %d: TOKEN <CONST_CHAR> Lexeme %s found\n",line_count,yytext);
		  ST.Insert(yytext,"CONST_CHAR");
		  ST.Print();}
{identifier}    { fprintf(outputtoken,"<ID,%s>",yytext);
                  fprintf(outputlog,"Line no %d: TOKEN <ID> Lexeme %s found\n",line_count,yytext);
		  ST.Insert(yytext,"ID");
		  ST.Print();}


("+"|"-")             { fprintf(outputtoken,"<ADDOP,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <ADDOP> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"ADDOP");
			ST.Print();}
("*"|"/"|"%")         { fprintf(outputtoken,"<MULOP,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <MULOP> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"MULOP");
			ST.Print();}
("++"|"--")           { fprintf(outputtoken,"<INCOP,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <INCOP> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"INCOP");
			ST.Print();}
("<"|"<="|">"|">="|"=="|"!=")  { fprintf(outputtoken,"<RELOP,%s>",yytext);
                                fprintf(outputlog,"Line no %d: TOKEN <RELOP> Lexeme %s found\n",line_count,yytext);
				ST.Insert(yytext,"RELOP");
				ST.Print();}
"="                           { fprintf(outputtoken,"<ASSIGNOP,%s>",yytext);
				fprintf(outputlog,"Line no %d: TOKEN <ASSIGNOP> Lexeme %s found\n",line_count,yytext);
				ST.Insert(yytext,"ASSIGNOP");
				ST.Print();}
                      
("&&"|"||"|"!")       { fprintf(outputtoken,"<LOGICOP,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <LOGICOP> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"LOGICOP");
			ST.Print();}
("("|")")             { fprintf(outputtoken,"<PAREN,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <PAREN> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"PAREN");
			ST.Print();}

("{"|"}")             { fprintf(outputtoken,"<CURL,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <CURL> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"CURL");
			ST.Print();}
("["|"]")             { fprintf(outputtoken,"<BRACKET,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <BRACKET> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"BRACKET");
			ST.Print();}
","                   { fprintf(outputtoken,"<COMMA,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <COMMA> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"COMMA");
			ST.Print();}
";"                   { fprintf(outputtoken,"<SEMICOLON,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <SEMICOLON> Lexeme %s found\n",line_count,yytext);
			ST.Insert(yytext,"SEMICOLON");
			ST.Print();}
{string}              { fprintf(outputtoken,"<STRING,%s>",yytext);
                        fprintf(outputlog,"Line no %d: TOKEN <IF> Lexeme %s found\n",line_count,yytext);}


'[^'\n\t\a\b\v\r\f\0\\\"]+'  {fprintf(outputlog,"Line no %d: ERROR:Multi Character Constant, Lexeme %s found\n",line_count,yytext);
                             error_count++;}
[0-9]+\.([0-9]*|\.)*   {fprintf(outputlog,"Line no %d: ERROR:Too Many decimal point, Lexeme %s found\n",line_count,yytext);
                                 error_count++;}
{error}                     {fprintf(outputlog,"Line no %d: ERROR:Ill formed number, Lexeme %s found\n",line_count,yytext);
                            error_count++;}
([0-9]+[a-zA-Z_0-9]+)            {fprintf(outputlog,"Line no %d: ERROR:Invalid identifier, Lexeme %s found\n",line_count,yytext);
                             error_count++;}
.                           {fprintf(outputlog,"Line no %d: ERROR:Unrecognized character, Lexeme %s found\n",line_count,yytext);
                             error_count++;}



%%
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("error");
        return 0;
    }
    yyin=fopen(argv[1],"r");
    if(yyin==NULL)
    {
        printf("cannot open file");
        return 0;
    }

    outputlog= fopen("log.txt","w");
	outputtoken= fopen("token.txt","w");

	yylex();
	fclose(yyin);
	fclose(outputlog);
	fclose(outputtoken);
	return 0;

}



