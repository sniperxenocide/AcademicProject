%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
//#include "SymbolTable.h"
#include "SymbolInfo.h"

#define YYSTYPE SymbolInfo*

using namespace std;

extern int yylex();
void yyerror(const char *s);
extern FILE *yyin;
extern int line_count;
extern int error;


int labelCount=0;
int tempCount=0;


char *newLabel()
{
	char *lb= new char[4];
	strcpy(lb,"L");
	char b[3];
	sprintf(b,"%d", labelCount);
	labelCount++;
	strcat(lb,b);
	return lb;
}

char *newTemp()
{
	char *t= new char[4];
	strcpy(t,"t");
	char b[3];
	sprintf(b,"%d", tempCount);
	tempCount++;
	strcat(t,b);
	return t;
}

//SymbolTable *table= new SymbolTable(31);

%}

%error-verbose

%token IF ELSE FOR WHILE DO INT FLOAT DOUBLE CHAR RETURN VOID BREAK SWITCH CASE DEFAULT CONTINUE ADDOP MULOP ASSIGNOP RELOP
%token LOGICOP SEMICOLON COMMA LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD INCOP DECOP CONST_INT CONST_FLOAT ID NOT PRINTLN MAIN

%nonassoc THEN
%nonassoc ELSE
%%

Program : INT MAIN LPAREN RPAREN compound_statement
		{
			cout << "\nProgram : INT MAIN LPAREN RPAREN compound_statement\n";
			// insert appropriate data segment register initialization code and others like main proc
			$$=new SymbolInfo("c","d");
			$$->code=".MODEL SMALL\n.STACK 100h\n.DATA\n";
			int i;
			for(i=0;i<tempCount;i++)
			{
				char *t=new char[4];
				strcpy(t,"t");
				char b[3];
				sprintf(b,"%d",i);
				strcat(t,b);
				$$->code+=string(t)+" dw ?\n";
			}
			$$->code+=$5->code;
	//$$->code+="\n\nmov ah,4ch\nint 21h\nmain endp\n\n\n";
	$$->code+="\n\nPRINTLN PROC\nPUSH AXvPUSH BX\nPUSH CX\nPUSH DX\nOR AX,AX\nJGE @END_IF1\nPUSH AX\nMOV DL,'-'\nMOV AH,2";
	$$->code+="\nINT 21H\nPOP AX\nNEG AX\n@END_IF1:\nXOR CX,CX\nMOV BX,10D\n@REPEAT1:\nXOR DX,DX\nDIV BX\nPUSH DX\nINC CX";
	$$->code+="\nOR AX,AX\nJNE @REPEAT1\nMOV AH,2\n@PRINT_LOOP:\nPOP DX\nOR DL,30H\nINT 21H\nLOOP @PRINT_LOOP";
	$$->code+="\nPOP DX\nPOP CX\nPOP BX\nPOP AX\nRET\nPRINTLN ENDP\nEND MAIN\n";
			ofstream fout;
			fout.open("code.asm");
			fout << $$->code;
			cout << endl;
			
		}


compound_statement	: LCURL var_declaration statements RCURL
						{
							cout << "\ncompound_statement : LCURL var_declaration statements RCURL\n";
							$$=new SymbolInfo("a","b");
							$$->code=$2->code;
							$$->code+=".CODE\nmain proc\nmov ax,@DATA\nmov ds,ax\n";	
							$$->code+=$3->code;
							cout << endl;
						}
					| LCURL statements RCURL
						{
							cout << "\ncompound_statement : LCURL statements RCURL\n";
							$$=$2;
							cout << endl;
						}
					| LCURL RCURL
						{
							cout << "\ncompound_statement	: LCURL RCURL\n";
							$$=new SymbolInfo("compound_statement","dummy");
							cout << endl;
						}
					;

			 
var_declaration	: var_declaration type_specifier declaration_list SEMICOLON {
						cout << "\nvar_declaration : type_specifier declaration_list SEMICOLON\n";
						$$=$1;
						$$->code+=$3->code;
						cout << endl;
						delete $2;
					}
					
				|	type_specifier declaration_list SEMICOLON {
						cout << "\nvar_declaration : type_specifier declaration_list SEMICOLON\n";
						$$=$2;
						cout << endl;
						delete $1;
					}
				;

type_specifier	: INT {
				cout << "\ntype_specifier : INT\n";
				$$= new SymbolInfo("int","type");
				cout << endl;
			}
		| FLOAT {
				cout << "\ntype_specifier : FLOAT\n";
				$$= new SymbolInfo("int","type");
				cout << endl;
			}
		;
				
declaration_list : declaration_list COMMA ID {
						cout << "\ndeclaration_list : declaration_list COMMA ID\n";
						$$=$1;
						/* should be easy */
						//$$=new SymbolInfo($3);
						$$->code+=string($3->getSymbol())+" dw " + "?\n";
						cout << endl;
					}
				 |	declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
						cout << "\ndeclaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n"  ;
						$$=$1;
						/* should be easy */
						//$$=new SymbolInfo($1);
						int length;
						sscanf($5->getSymbol(),"%d",&length);
						cout << length << endl;
						$$->code+=string($3->getSymbol())+" dw ";
						for(int i=0;i<length-1;i++){
							$$->code += "?, " ;
						}
						$$->code+="?\n";
						cout << endl;
					}
				 |	ID {
						cout << "\ndeclaration_list : ID\n"  << $1->getSymbol() << endl;
						$$=new SymbolInfo($1);
						$$->code=string($1->getSymbol())+" dw " + "?\n";
						cout << endl;
					}
				 |	ID LTHIRD CONST_INT RTHIRD {
						cout << "\ndeclaration_list : ID LTHIRD CONST_INT RTHIRD\n"  << $1->getSymbol() << endl;
						$$=new SymbolInfo($1);
						int length;
						sscanf($3->getSymbol(),"%d",&length);
						cout << length << endl;
						$$->code=string($1->getSymbol())+" dw ";
						for(int i=0;i<length-1;i++){
							$$->code += "?, " ;
						}
						$$->code+="?\n";
						cout << endl;
					}
				 ;

statements : statement {
				cout << "\nstatements : statement\n";
				$$=$1;
				cout << endl;
			}
	       | statements statement {
				cout << "\nstatements : statements statement\n";
				$$=$1;
				$$->code += $2->code;
				delete $2;
				cout << endl;
			}
	       ;


statement 	: 	expression_statement {
					cout << "\nstatement : expression_statement\n";
					$$=$1;
					cout << endl;
				}
			| 	compound_statement {
					cout << "\nstatement : compound_statement\n";
					$$=$1;
					cout << endl;
				}
			|	FOR LPAREN expression_statement expression_statement expression RPAREN statement {
					cout << "\nstatement : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n";
					
					/*
						$3's code at first, which is already done by assigning $$=$3
						create two labels and append one of them in $$->code
						compare $4's symbol with 1
						if not equal jump to 2nd label
						append $7's code
						append second label in the code
					*/
					
					$$=$1;
					$$->code+=$3->code;
					char *label1=newLabel();
					char *label2=newLabel();
					$$->code+=string(label1)+":\n";
					$$->code+="mov ax,1\n";
					$$->code+="cmp "+string($4->getSymbol())+",ax\n";
					$$->code+="jne "+string(label2)+"\n";
					$$->code+=$7->code;
					$$->code+=$5->code;
					$$->code+="jmp "+string(label1)+"\n";
					$$->code+=string(label2)+":\n";
					cout << endl;
				}
			|	IF LPAREN expression RPAREN statement %prec THEN {
					cout << "\nstatement : IF LPAREN expression RPAREN statement\n";
					
					$$=$3;
					
					char *label=newLabel();
					$$->code+="mov ax, "+string($3->getSymbol())+"\n";
					$$->code+="cmp ax, 1\n";
					$$->code+="jne "+string(label)+"\n";
					$$->code+=$5->code;
					$$->code+=string(label)+":\n";
					
					$$->setSymbol("if");//not necessary
					
					cout << endl;
				}
			|	IF LPAREN expression RPAREN statement ELSE statement {
					cout << "\nstatement : IF LPAREN expression RPAREN statement ELSE statement\n";
					$$=$3;
					//similar to if part
					char *label=newLabel();
					$$->code+="mov ax, "+string($3->getSymbol())+"\n";
					$$->code+="cmp ax, 1\n";
					$$->code+="jne "+string(label)+"\n";
					$$->code+=$5->code;
					$$->code+=string(label)+":\n";
					$$->code+=$7->code;
					cout << endl;
				}
			|	WHILE LPAREN expression RPAREN statement {
					cout << "\nstatement : WHILE LPAREN expression RPAREN statement\n";
					$$=$1;
					char *label1=newLabel();
					char *label2=newLabel();
					$$->code+=string(label1)+":\n";
					$$->code+="mov ax,0\n";
					$$->code+="cmp "+string($3->getSymbol())+",ax\n";
					$$->code+="je "+string(label2)+"\n";
					$$->code+=$5->code;
					$$->code+="jmp "+string(label1)+"\n";
					$$->code+=string(label2)+":\n";
					// should be easy given you understood or implemented for loops part
					cout << endl;
				}
			|	PRINTLN LPAREN ID RPAREN SEMICOLON {
					cout << "\nstatement : PRINTLN LPAREN ID RPAREN SEMICOLON\n";
					// write code for printing an ID. You may assume that ID is not an integer variable.
					$$=new SymbolInfo("println","nonterminal");
					$$->code+="push ax\nmov ax,"+string($3->getSymbol())+"\ncall println\npop ax\n";
					cout << endl;
				}
			| 	RETURN expression SEMICOLON {
					cout << "\nstatement : RETURN expression SEMICOLON\n";
					// write code for dos return.
					$$=$1;
					$$->code+="mov ah,4ch\nint 21h\nmain endp\n";
					cout << endl;
				}
			;
		
expression_statement	: SEMICOLON	{
							cout << "\nexpression_statement : SEMICOLON\n";
							$$=new SymbolInfo(";","SEMICOLON");
							$$->code="";
							cout << endl;
						}			
					| expression SEMICOLON {
							cout << "\nexpression_statement : expression SEMICOLON\n";
							$$=$1;
							cout << endl;
						}		
					;
						
variable	: ID {
				cout << "\nvariable : ID\n" << $1->getSymbol() << endl;
				
				$$= new SymbolInfo($1);
				
				cout << endl;
		}		
		| ID LTHIRD expression RTHIRD {
				
				cout << "\nvariable : ID LTHIRD expression RTHIRD\n"  << $1->getSymbol() << endl;
				
				$$= new SymbolInfo($1);
				
				$$->code=$3->code;
				$$->arrIndexHolder=string($3->getSymbol());
				
				delete $3;
				cout << endl;
		}	
		;
			
expression : logic_expression {
			cout << "\nexpression : logic_expression\n";
			$$= $1;
			cout << endl;
		}	
		| variable ASSIGNOP logic_expression {
				cout << "\nexpression : variable ASSIGNOP logic_expression\n";
				$$=$1;
				$$->code=$3->code+$1->code;
				$$->code+="mov ax, "+string($3->getSymbol())+"\n";
				if($$->arrIndexHolder==""){ //actualy it is more appropriate to use arrayLength to make decision
					$$->code+= "mov "+string($1->getSymbol())+", ax\n";
				}
				
				else{
					$$->code+="lea di, " + string($1->getSymbol())+"\n";
					for(int i=0;i<2;i++){
						$$->code += "add di, " + $1->arrIndexHolder +"\n";
					}
					$$->code+= "mov [di], ax\n";
					$$->arrIndexHolder="";
				}
				delete $3;
				cout << endl;
			}	
		;
			
logic_expression : rel_expression {
					cout << "\nlogic_expression : rel_expression\n";
					$$= $1;
					cout << endl;			
				}	
		| rel_expression LOGICOP rel_expression {
					cout << "\nlogic_expression : rel_expression LOGICOP rel_expression\n";
					$$=$1;
					$$->code+=$3->code;
					char *temp=newTemp();
					if(strcmp($2->getSymbol(),"&&")==0){
						/* 
						Check whether both operands value is 1. If both are one set value of a temporary variable to 1
						otherwise 0
						*/
					if($1->getValue()==1 && $3->getValue()==1)      
						$$->code+= "mov "+string(temp)+",1\n";						
					else   $$->code+= "mov "+string(temp)+",0\n";
					}
					else if(strcmp($2->getSymbol(),"||")==0) {
					if($1->getValue()==1 || $3->getValue()==1)      
						$$->code+= "mov "+string(temp)+",1\n";						
					else   $$->code+= "mov "+string(temp)+",0\n";	
					}
					delete $3;
					cout << endl;
				}	
			;
			
rel_expression	: simple_expression {
				cout << "\nrel_expression : simple_expression\n";
				$$= $1;
				cout << endl;
			}	
		| simple_expression RELOP simple_expression {
				cout << "\nrel_expression : simple_expression RELOP simple_expression\n";
				$$=$1;
				$$->code+=$3->code;
				$$->code+="mov ax, " + string($1->getSymbol())+"\n";
				$$->code+="cmp ax, " + string($3->getSymbol())+"\n";
				char *temp=newTemp();
				char *label1=newLabel();
				char *label2=newLabel();
				if(strcmp($2->getSymbol(),"<")==0){
					$$->code+="jl " + string(label1)+"\n";
				}
				else if(strcmp($2->getSymbol(),"<=")==0){
					$$->code+="jle " + string(label1)+"\n";
				}
				else if(strcmp($2->getSymbol(),">")==0){
					$$->code+="jg " + string(label1)+"\n";
				}
				else if(strcmp($2->getSymbol(),">=")==0){
					$$->code+="jge " + string(label1)+"\n";
				}
				else if(strcmp($2->getSymbol(),"==")==0){
					$$->code+="je " + string(label1)+"\n";
				}
				else{
					$$->code+="jne " + string(label1)+"\n";
				}
				
				$$->code+="mov "+string(temp) +", 0\n";
				$$->code+="jmp "+string(label2) +"\n";
				$$->code+=string(label1)+":\nmov "+string(temp)+", 1\n";
				$$->code+=string(label2)+":\n";
				$$->setSymbol(temp);
				delete $3;
				cout << endl;
			}	
		;
				
simple_expression : term {
				cout << "\nsimple_expression : term\n";
				$$= $1;
				cout << endl;
			}
		| simple_expression ADDOP term {
				cout << "\nsimple_expression : simple_expression ADDOP term\n";
				$$=$1;
				$$->code+=$3->code;
				
				// move one of the operands to a register, perform addition or subtraction with the other operand and move the result in a temporary variable  
				$$->code += "mov ax, "+ string($1->getSymbol())+"\n";
				char *temp=newTemp();
				if(strcmp($2->getSymbol(),"+")==0){
				$$->code +="add ax, "+string($3->getSymbol())+"\n";
				$$->code += "mov "+ string(temp) + ", ax\n";
				}
				else if(strcmp($2->getSymbol(),"-")==0){
				$$->code +="sub ax, "+string($3->getSymbol())+"\n";
				$$->code += "mov "+ string(temp) + ", ax\n";
				}
				$$->setSymbol(temp);
				delete $3;
				cout << endl;
			}
				;
				
term :	unary_expression {
						cout << "\nterm : unary_expression\n";
						$$= $1;
						cout << endl;
					}
	 | 	term MULOP unary_expression {
						cout << "\nterm : term MULOP unary_expression\n";
						$$=$1;
						$$->code += $3->code;
						$$->code += "mov ax, "+ string($1->getSymbol())+"\n";
						$$->code += "mov bx, "+ string($3->getSymbol()) +"\n";
						char *temp=newTemp();
						if(strcmp($2->getSymbol(),"*")==0){
							$$->code += "mul bx\n";
							$$->code += "mov "+ string(temp) + ", ax\n";
						}
						else if(strcmp($2->getSymbol(),"/")==0){
							// clear dx, perform 'div bx' and mov ax to temp
							$$->code += "xor dx,dx\n";
							$$->code += "div bx\n";
							$$->code += "mov "+ string(temp) + ", ax\n";
						}
						else{
							// clear dx, perform 'div bx' and mov dx to temp
							$$->code += "xor dx,dx\n";
							$$->code += "div bx\n";
							$$->code += "mov "+ string(temp) + ", dx\n";
						}
						$$->setSymbol(temp);
						delete $3;
						cout << endl;
					}
	 ;

unary_expression 	:	ADDOP unary_expression  {
							cout << "\nunary_expression : ADDOP unary_expression\n";
							$$=$2;
							// Perform NEG operation if the symbol of ADDOP is '-'
							char *temp=newTemp();
							$$->code="mov ax, " + string($2->getSymbol()) + "\n";
							if(strcmp($1->getSymbol(),"-")==0){
							$$->code+="neg ax\n";
							}
							$$->code+="mov "+string(temp)+", ax";
							cout << endl;
						}
					|	NOT unary_expression {
							cout << "\nunary_expression : NOT unary_expression\n";
							$$=$2;
							char *temp=newTemp();
							$$->code="mov ax, " + string($2->getSymbol()) + "\n";
							$$->code+="not ax\n";
							$$->code+="mov "+string(temp)+", ax";
							cout << endl;
						}
					|	factor {
							cout << "\nunary_expression : factor\n";
							$$=$1;
							cout << endl;
						}
					;
	
factor	: variable {
			cout << "\nfactor : variable\n";
			$$= $1;
			
			if($$->arrIndexHolder==""){//actualy it is better use arrayLength to make decision
				
			}
			
			else{
				$$->code+="lea di, " + string($1->getSymbol())+"\n";
				for(int i=0;i<2;i++){
					$$->code += "add di, " + $1->arrIndexHolder +"\n";
				}
				char *temp= newTemp();
				$$->code+= "mov " + string(temp) + ", [di]\n";
				$$->setSymbol(temp);
				$$->arrIndexHolder="";
			}
			cout << endl;
		}
	| LPAREN expression RPAREN {
			cout << "\nfactor : LPAREN expression RPAREN\n";
			$$= $2;
			cout << endl;
		}
	| CONST_INT {
			cout << "\nfactor : CONST_INT\n" <<  $1->getSymbol() << endl;
			$$= $1;
			cout << endl;
		}
	| CONST_FLOAT {
			cout << "\nfactor : CONST_FLOAT\n" <<  $1->getSymbol() <<  endl;
			$$= $1;
			cout << endl;
		}
	| variable INCOP {
			cout << "\nfactor : variable INCOP\n";
			$$=$1;
			$$->code += "inc " + string($1->getSymbol()) + "\n";
			cout << endl;
		}
	;
		
		
%%


void yyerror(const char *s){
	cout << "Error at line no " << line_count << " : " << s << endl;
}

int main(int argc, char * argv[]){
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	

	yyin= fin;
	yyparse();
	cout << endl;
	cout << endl << "\t\tsymbol table: " << endl;
	//table->dump();
	
	printf("\nTotal Lines: %d\n",line_count);
	printf("\nTotal Errors: %d\n",error);
	
	printf("\n");
	return 0;
}
