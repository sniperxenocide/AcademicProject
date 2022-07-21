%{
#include<bits/stdc++.h>
using namespace std;

extern FILE *yyin;
extern char *yytext;

FILE *outputlog;
FILE *outputtoken;

extern int line_count;
extern int error_count;
extern int word_count;

string recent_variable;
int array_index;
string type;
int aFlag=0;
string var;
int fLock=0;

void yyerror(char *p)
{
	printf("%s\n",p);
}

int yylex(void);
int yyparse(void);

class SymbolInfo
{
    public:
    string name;
    string type;
    double value;
    int size;
    double *array;
    SymbolInfo *next;

    public:
    SymbolInfo(string n,string t,double v,int s,int idx)
    {
        this->name=n;
        this->type=t;
        this->value=v;
	this->size=s;
	this->array=new double[idx];
    }

    SymbolInfo()
    {
        this->name=" ";
        this->type=" ";
	this->value=-32145.000;
        this->next=0;
	this->size=-1;
	this->array=0;
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

    void setValue(double v){this->value=v;}
    double getValue(){return this->value;}

    void setSize(int s) {this->size=s;}
    int getSize(){return this->size;}
    
    void setArrayVal(int i, double n) {this->array[i]=n;}
    double getArrayVal(int i) {return array[i];}
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

        void Insert(string s1,string s2,int s=-1,double v=-32145.000)
        {
            int index,k=0;
            if(Look_up(s1)!=0)
            {
                cout<<s1<<" Already exists"<<endl;
                fprintf(outputlog,"Already exists\n\n");
                return;
            }
            SymbolInfo *newNode,*temp,*prev;
            newNode=new SymbolInfo;
            newNode->setName(s1);
            newNode->setType(s2);
	    newNode->setValue(v);
	    newNode->setSize(s);
	    if(s!=-1) { newNode->array=new double[s];}

            index=HashFunction(s1);
            temp=smif[index].next;
            prev=temp;
            if(temp==0) {
                smif[index].next=newNode;
                cout<<s1<<" Inserted at "<<index<<","<<0<<endl;
		fprintf(outputlog,"Inserted at %d,0\n\n",index);
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
		    fprintf(outputlog,"Inserted at %d,%d\n\n",index,k);
            }


        }
        SymbolInfo* Look_up(string s)
        {
            int index , k=0;
            index=HashFunction(s);
            SymbolInfo *temp=smif[index].next;
            while(temp!=0)
            {
                if(temp->getName()==s)
                {
                   cout<<"Found at "<<index<<","<<k<<","<< s <<" ptr "<<temp<<endl;
			fprintf(outputlog,"Found at %d , %d  %s\n\n",index,k,s.c_str());
                    return temp;
                }
                k++;
                temp=temp->next;
            }
             cout<<"Not Found "<< s <<endl;
		fprintf(outputlog,"Not Found\n\n");
            return 0;

        }

        

        void Print()
        {
            for(int i=0;i<n;i++)
            {
                cout<<i<<" -> ";
		fprintf(outputlog,"%d ->",i);
                SymbolInfo *temp=smif[i].next;
                while(temp!=0)
                {
                    cout<<" < "<<temp->getName()<<" , "<<temp->getType()<<" > ";
		    char t[1000],t1[1000];
		    strcpy(t,temp->getName().c_str());
		    strcpy(t1,temp->getType().c_str());
		    if(temp->getSize()==-1) {fprintf(outputlog," < %s , %s , %lf , %d > ",t,t1,temp->getValue(),temp->getSize());}
		    else{
			fprintf(outputlog," < %s , %s , %lf , %d , { ",t,t1,temp->getValue(),temp->getSize());
			int x;
			for(x=0;x<temp->getSize();x++) fprintf(outputlog," %lf ",temp->getArrayVal(x));
			fprintf(outputlog,"} >\n");
		    }
                    temp = temp->next;
                }
		cout<<endl;
                fprintf(outputlog,"\n");
            }

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
            //cout<<"Could not Delete"<<endl;

        }*/


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

SymbolTable ST(15);

%}


%token IF ELSE FOR DO WHILE BREAK INT CHAR FLOAT DOUBLE VOID RETURN CASE DEFAULT CONTINUE MAIN PRINTLN ASSIGNOP NOT SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP 
%union
{
        char *a;
	double db;
	int i;
	char ch;
}

%nonassoc RPAREN
%nonassoc ELSE

%token<i>CONST_INT
%token<db>CONST_FLOAT
%token<a>ID
%token<a>ADDOP
%token<a>MULOP
%token<a>RELOP
%token<a>LOGICOP
%token<ch>CONST_CHAR


%type <db> factor
%type <db> expression
%type <db> variable
%type <db> unary_expression
%type <db> term
%type <db> simple_expression
%type <db> rel_expression
%type <db> logic_expression
%type <db> expression_statement
%type <db> statements
%type <db> statement
%type <db> declaration_list
%type <db> type_specifier
%type <db> var_declaration
%type <db> compound_statement
%type <db> Program

//grammar
%%

Program : INT MAIN LPAREN RPAREN compound_statement			{fprintf(outputlog,"Program : INT MAIN LPAREN RPAREN compound_statement\n");}
	;


compound_statement : LCURL var_declaration statements RCURL	{fprintf(outputlog,"compound_statement : LCURL var_declaration statements RCURL\n");}
		   | LCURL statements RCURL				{fprintf(outputlog,"compound_statement : LCURL statements RCURL\n");}
		   | LCURL RCURL					{fprintf(outputlog,"compound_statement : LCURL RCURL\n");}
		   ;

			 
var_declaration	: type_specifier declaration_list SEMICOLON   {fprintf(outputlog,"var_declaration : type_specifier declaration_list SEMICOLON\n");}
		|  var_declaration type_specifier declaration_list SEMICOLON   
{
	fprintf(outputlog,"var_declaration	: var_declaration type_specifier declaration_list SEMICOLON \n");
}
		;

type_specifier	: INT 							{fprintf(outputlog,"type_specifier	: INT \n");type="INT";}
		| FLOAT							{fprintf(outputlog,"type_specifier	: FLOAT\n");type="FLOAT";}
		| CHAR							{fprintf(outputlog,"type_specifier	: CHAR	\n");type="CHAR";}
		;
			
declaration_list : declaration_list COMMA ID 				
{
	fprintf(outputlog,"declaration_list : declaration_list COMMA ID \n%s\n",$3);
	string s=$3; 
	if(ST.Look_up(s)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d, Mltiple declaration of variable %s\n",line_count,$3);} 
	ST.Insert($3,type);ST.Print();
}
		 | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD	
{
	fprintf(outputlog,"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n%s\n",$3);
	string s=$3;int x=$5;  if(ST.Look_up($3)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,$3);}
	ST.Insert($3,type,x);ST.Print(); //SymbolInfo *si=ST.Look_up($3); si->setSize(x);
}
		 | ID 							
{
	fprintf(outputlog,"declaration_list : ID \n%s\n",$1);
	string s=$1;   if(ST.Look_up(s)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,$1);}
	ST.Insert(s,type);ST.Print();
}
		 | ID LTHIRD CONST_INT RTHIRD 				
{
	fprintf(outputlog,"declaration_list : ID LTHIRD CONST_INT RTHIRD \n%s\n",$1);
	string s=$1;int x=$3;   if(ST.Look_up($1)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,$1);}
	ST.Insert($1,type,x);ST.Print(); //SymbolInfo *si=ST.Look_up($1); si->setSize(x);
}
		 ;

statements : statement 							{fprintf(outputlog,"statements : statement 	\n");}
	   | statements statement 					{fprintf(outputlog,"statements : statements statement \n");}
	   ;


statement  : expression_statement 					{fprintf(outputlog,"statement  : expression_statement\n");}
	   | compound_statement 					{fprintf(outputlog,"statement  : compound_statement \n");}
	   | FOR LPAREN expression_statement expression_statement expression RPAREN statement   
{
	fprintf(outputlog,"statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n");
}
	   | IF LPAREN expression RPAREN statement			
{
	fprintf(outputlog,"statement  : IF LPAREN expression RPAREN statement\n");
}
	   | IF LPAREN expression RPAREN statement ELSE statement	
{
	fprintf(outputlog,"statement  : IF LPAREN expression RPAREN statement ELSE statement\n");
}
	   | WHILE LPAREN expression RPAREN statement 			
{
	fprintf(outputlog,"statement  : WHILE LPAREN expression RPAREN statement\n");
}
	   | PRINTLN LPAREN ID RPAREN SEMICOLON 			
{
	fprintf(outputlog,"statement  : PRINTLN LPAREN ID RPAREN SEMICOLON\n%s\n",$3);
	string s=$3; ST.Insert($3,type);ST.Print();
}
	   | RETURN expression SEMICOLON 				{fprintf(outputlog,"statement  : RETURN expression SEMICOLON \n");}
	   ;
		
expression_statement	: SEMICOLON					{fprintf(outputlog,"expression_statement	: SEMICOLON\n");}
			| expression SEMICOLON 				{fprintf(outputlog,"expression_statement	: expression SEMICOLON \n");}
			;

variable : ID 								
{
	
	recent_variable=$1;
	fprintf(outputlog,"variable : ID \n%s\n",$1);
	string s=$1;  if(ST.Look_up(s)==0)  {error_count++; fprintf(outputlog,"***Error:Line: %d,  Undefined  variable %s\n",line_count,$1); 		aFlag=2;}
	else  {ST.Insert($1,type);ST.Print(); //recent_variable=$1; 
	aFlag=0;
	//$$=ST.Look_up($1)->getValue();
		}
}
	 | ID LTHIRD expression RTHIRD 				        
{
	recent_variable=$1;
	array_index=$3; 
	fprintf(outputlog,"variable : ID LTHIRD expression RTHIRD \n%s\n",$1);
	string s=$1;  if(ST.Look_up(s)==0)  {error_count++; fprintf(outputlog,"***Error:Line: %d,  Undefined  variable %s\n",line_count,$1); 		aFlag=2;}
	else {ST.Insert($1,type);ST.Print();aFlag=1;
	//$$=ST.Look_up($1)->getArrayVal($3);
		}
}
	 ;
			
expression : logic_expression						{fprintf(outputlog,"expression : logic_expression\n");}
	   | variable ASSIGNOP logic_expression 			
{
	fprintf(outputlog,"expression : variable ASSIGNOP logic_expression\n"); 
	SymbolInfo *si=ST.Look_up(recent_variable);
	if(aFlag==0) { 
			if(si->getSize()==-1) {si->setValue($3);}
			else {error_count++; fprintf(outputlog,"***Error:Line: %d,  invalid assignment , data type is array\n",line_count);}
			ST.Print();
		     }
	else if(aFlag==1) {
				if(array_index>=si->getSize() || array_index<0) 
					{error_count++; fprintf(outputlog,"***Error:Line: %d,  Array index out of  bound\n",line_count);}
				else {si->setArrayVal(array_index,$3);}
				ST.Print();
				
			  }
	
}
	   ;
			
logic_expression : rel_expression 					
{
	fprintf(outputlog,"logic_expression : rel_expression\n");
	$$=$1;
}
		 | rel_expression LOGICOP rel_expression 		
{
	fprintf(outputlog,"logic_expression : rel_expression LOGICOP rel_expression \n");
	if(strcmp($2,"&&")==0) $$=$1 && $3;
	else if(strcmp($2,"||")==0) $$=$1 || $3;
}
		 ;
			
rel_expression	: simple_expression 					
{
	fprintf(outputlog,"rel_expression	: simple_expression\n");
	$$=$1;
}
		| simple_expression RELOP simple_expression		
{
	fprintf(outputlog,"rel_expression	: simple_expression RELOP simple_expression\n");
	if(strcmp("<",$2) == 0)$$ = $1 < $3;
	else if(strcmp("<=",$2) == 0)$$ = $1 <= $3;
	else if(strcmp(">",$2) == 0)$$ = $1 > $3;
	else if(strcmp(">=",$2) == 0)$$ = $1 >= $3;
	else if(strcmp("!=",$2) == 0)$$ = $1 != $3;
	else if(strcmp("==",$2) == 0)$$ = $1 == $3;
}
		;
				
simple_expression : term 						{fprintf(outputlog,"simple_expression : term\n");$$=$1;}
		  | simple_expression ADDOP term 			
{
	fprintf(outputlog,"simple_expression : simple_expression ADDOP term\n");
	if(strcmp("+",$2) == 0)$$ = $1 + $3;
	else if(strcmp("-",$2) == 0)$$ = $1 - $3;
}
		  ;
					
term :	unary_expression						{fprintf(outputlog,"term :	unary_expression\n");$$=$1;}
     |  term MULOP unary_expression					{fprintf(outputlog,"term :  term MULOP unary_expression\n");
										if(strcmp("*",$2) == 0)$$ = $1 * $3;
										else if(strcmp("/",$2) == 0)$$ = $1 / $3;
										else if(strcmp("%",$2) == 0)$$ = (int)$1 % (int)$3;
									}
     ;

unary_expression : ADDOP unary_expression  				{fprintf(outputlog,"unary_expression : ADDOP unary_expression\n");
										if(strcmp($1,"+")==0)$$=+$2;
										else if(strcmp($1,"-")==0) $$=-$2;}
		 | NOT unary_expression 				{fprintf(outputlog,"unary_expression : NOT unary_expression\n");												$$ = !$2;}
		 | factor 						{fprintf(outputlog,"unary_expression : factor \n"); 
										$$=$1;}			
		 ;
	
factor	: variable 							{fprintf(outputlog,"factor	: variable\n");$$=$1;}
	| LPAREN expression RPAREN 					{fprintf(outputlog,"factor	: LPAREN expression RPAREN \n");$$=$2;}
	| CONST_INT 				{fprintf(outputlog,"factor	: CONST_INT\n%d\n",$1);$$=$1;}
	| CONST_FLOAT				{fprintf(outputlog,"factor	: CONST_FLOAT\n%lf\n",$1);$$=$1;}
	| CONST_CHAR				{fprintf(outputlog,"factor	: CONST_CHAR\n%s\n",yylval);$$=$1;}
	| factor INCOP 							{fprintf(outputlog,"factor	: factor INCOP\n");$$=$1++;}
	| factor DECOP							{fprintf(outputlog,"factor	: factor DECOP\n");$$=$1--;}
	;

%%

//grammar

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
	yyparse();
	fprintf(outputlog,"Total Line: %d\n",line_count);
	fprintf(outputlog,"Total Error: %d\n",error_count);
	ST.Print();
	fclose(yyin);
	fclose(outputlog);
	fclose(outputtoken);
	return 0;

}
