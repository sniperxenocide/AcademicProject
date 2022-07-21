/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "1305053.y" /* yacc.c:339  */

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


#line 325 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IF = 258,
    ELSE = 259,
    FOR = 260,
    DO = 261,
    WHILE = 262,
    BREAK = 263,
    INT = 264,
    CHAR = 265,
    FLOAT = 266,
    DOUBLE = 267,
    VOID = 268,
    RETURN = 269,
    CASE = 270,
    DEFAULT = 271,
    CONTINUE = 272,
    MAIN = 273,
    PRINTLN = 274,
    ASSIGNOP = 275,
    NOT = 276,
    SEMICOLON = 277,
    COMMA = 278,
    LPAREN = 279,
    RPAREN = 280,
    LCURL = 281,
    RCURL = 282,
    LTHIRD = 283,
    RTHIRD = 284,
    INCOP = 285,
    DECOP = 286,
    CONST_INT = 287,
    CONST_FLOAT = 288,
    ID = 289,
    ADDOP = 290,
    MULOP = 291,
    RELOP = 292,
    LOGICOP = 293,
    CONST_CHAR = 294
  };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define DO 261
#define WHILE 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define CASE 270
#define DEFAULT 271
#define CONTINUE 272
#define MAIN 273
#define PRINTLN 274
#define ASSIGNOP 275
#define NOT 276
#define SEMICOLON 277
#define COMMA 278
#define LPAREN 279
#define RPAREN 280
#define LCURL 281
#define RCURL 282
#define LTHIRD 283
#define RTHIRD 284
#define INCOP 285
#define DECOP 286
#define CONST_INT 287
#define CONST_FLOAT 288
#define ID 289
#define ADDOP 290
#define MULOP 291
#define RELOP 292
#define LOGICOP 293
#define CONST_CHAR 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 263 "1305053.y" /* yacc.c:355  */

        char *a;
	double db;
	int i;
	char ch;

#line 450 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 467 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   226

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   303,   303,   307,   308,   309,   313,   314,   320,   321,
     322,   325,   332,   338,   344,   352,   353,   357,   358,   359,
     363,   367,   371,   375,   380,   383,   384,   387,   398,   410,
     411,   431,   436,   444,   449,   461,   462,   470,   471,   478,
     481,   482,   486,   487,   488,   489,   490,   491,   492
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "DO", "WHILE",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "CASE",
  "DEFAULT", "CONTINUE", "MAIN", "PRINTLN", "ASSIGNOP", "NOT", "SEMICOLON",
  "COMMA", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "INCOP", "DECOP", "CONST_INT", "CONST_FLOAT", "ID", "ADDOP", "MULOP",
  "RELOP", "LOGICOP", "CONST_CHAR", "$accept", "Program",
  "compound_statement", "var_declaration", "type_specifier",
  "declaration_list", "statements", "statement", "expression_statement",
  "variable", "expression", "logic_expression", "rel_expression",
  "simple_expression", "term", "unary_expression", "factor", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -39

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,    -1,    20,     0,   -39,    -2,     9,    50,   -39,     1,
      13,    14,   -39,   -39,   -39,   187,    15,   187,   -39,   187,
     -39,   -39,   -39,     5,   187,   -39,   -39,    83,     6,   105,
     -39,   -39,    22,    25,   -39,    11,   -27,    26,   -39,   -24,
     187,    -3,   187,    28,    17,   -39,   -39,    31,   187,   -39,
       6,   138,    30,   -10,   -39,   -39,   187,   -39,   187,   187,
     187,   187,   -39,   -39,    38,    -3,    40,   -39,    45,   -39,
      44,    -8,   -39,    43,   -39,    46,   -39,   -39,    26,    52,
     -39,   171,   187,   171,    56,   -39,   -39,    62,    51,    77,
      70,   -39,   -39,   -39,    64,   171,   171,    69,   -39,   -39,
     -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     2,     0,
       0,     0,     8,    10,     9,     0,     0,     0,    25,     0,
       5,    44,    45,    27,     0,    46,    18,     0,     0,     0,
      15,    17,    42,     0,    29,    31,    33,    35,    37,    41,
       0,     0,     0,     0,     0,    42,    40,     0,     0,    39,
       0,     0,    13,     0,     4,    16,     0,    26,     0,     0,
       0,     0,    47,    48,     0,     0,     0,    24,     0,    43,
       0,     0,     3,     0,     6,     0,    30,    32,    36,    34,
      38,     0,     0,     0,     0,    28,     7,     0,    11,    20,
       0,    22,    23,    14,     0,     0,     0,     0,    21,    19,
      12
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,    93,   -39,    73,    53,    74,   -29,   -38,   -15,
     -14,    55,    48,    54,    61,   -13,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    26,    27,    28,    53,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    43,    45,    65,    46,    47,    62,    63,    59,    45,
      60,    49,    74,    75,    86,    75,     1,     3,    17,    18,
       4,    19,    55,     6,     5,    40,    64,    82,    66,    21,
      22,    23,    24,    48,    70,     7,    25,    41,    42,    44,
      52,    45,    56,    45,    45,    45,    45,    57,    80,    58,
      67,    68,    89,     9,    91,    10,    69,    11,    73,    12,
      13,    14,    61,    81,    15,    83,    98,    99,    90,    16,
      84,    17,    18,    85,    19,    87,     7,    20,    92,    94,
      88,    95,    21,    22,    23,    24,     9,    59,    10,    25,
      11,    93,    12,    13,    14,    96,    97,    15,   100,     8,
      50,    51,    16,    71,    17,    18,    77,    19,     9,     7,
      10,    76,    11,     0,    79,    21,    22,    23,    24,    15,
      78,     0,    25,     0,    16,     0,    17,    18,     0,    19,
       0,     7,    54,     0,     0,     0,     0,    21,    22,    23,
      24,     9,     0,    10,    25,    11,     0,     0,     0,     0,
       0,     0,    15,     0,     0,     0,     0,    16,     0,    17,
      18,     0,    19,     0,     7,    72,     0,     0,     0,     0,
      21,    22,    23,    24,     9,     0,    10,    25,    11,     0,
       0,     0,     0,     0,     0,    15,     0,     0,     0,     0,
      16,     0,    17,    18,     0,    19,     0,     7,     0,     0,
       0,     0,     0,    21,    22,    23,    24,     0,    17,     0,
      25,    19,     0,     0,     0,     0,     0,     0,     0,    21,
      22,    23,    24,     0,     0,     0,    25
};

static const yytype_int8 yycheck[] =
{
      29,    15,    17,    41,    17,    19,    30,    31,    35,    24,
      37,    24,    22,    23,    22,    23,     9,    18,    21,    22,
       0,    24,    51,    25,    24,    24,    40,    65,    42,    32,
      33,    34,    35,    28,    48,    26,    39,    24,    24,    24,
      34,    56,    20,    58,    59,    60,    61,    22,    61,    38,
      22,    34,    81,     3,    83,     5,    25,     7,    28,     9,
      10,    11,    36,    25,    14,    25,    95,    96,    82,    19,
      25,    21,    22,    29,    24,    32,    26,    27,    22,    28,
      34,     4,    32,    33,    34,    35,     3,    35,     5,    39,
       7,    29,     9,    10,    11,    25,    32,    14,    29,     6,
      27,    27,    19,    50,    21,    22,    58,    24,     3,    26,
       5,    56,     7,    -1,    60,    32,    33,    34,    35,    14,
      59,    -1,    39,    -1,    19,    -1,    21,    22,    -1,    24,
      -1,    26,    27,    -1,    -1,    -1,    -1,    32,    33,    34,
      35,     3,    -1,     5,    39,     7,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    -1,    -1,    -1,    19,    -1,    21,
      22,    -1,    24,    -1,    26,    27,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,     3,    -1,     5,    39,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,
      19,    -1,    21,    22,    -1,    24,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    32,    33,    34,    35,    -1,    21,    -1,
      39,    24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      33,    34,    35,    -1,    -1,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    41,    18,     0,    24,    25,    26,    42,     3,
       5,     7,     9,    10,    11,    14,    19,    21,    22,    24,
      27,    32,    33,    34,    35,    39,    42,    43,    44,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      24,    24,    24,    50,    24,    49,    55,    50,    28,    55,
      44,    46,    34,    45,    27,    47,    20,    22,    38,    35,
      37,    36,    30,    31,    50,    48,    50,    22,    34,    25,
      50,    45,    27,    28,    22,    23,    51,    52,    54,    53,
      55,    25,    48,    25,    25,    29,    22,    32,    34,    47,
      50,    47,    22,    29,    28,     4,    25,    32,    47,    47,
      29
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    42,    42,    42,    43,    43,    44,    44,
      44,    45,    45,    45,    45,    46,    46,    47,    47,    47,
      47,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    53,    53,    54,    54,    55,
      55,    55,    56,    56,    56,    56,    56,    56,    56
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     4,     3,     2,     3,     4,     1,     1,
       1,     3,     6,     1,     4,     1,     2,     1,     1,     7,
       5,     7,     5,     5,     3,     1,     2,     1,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     2,
       2,     1,     1,     3,     1,     1,     1,     2,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 303 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"Program : INT MAIN LPAREN RPAREN compound_statement\n");}
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 307 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"compound_statement : LCURL var_declaration statements RCURL\n");}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 308 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"compound_statement : LCURL statements RCURL\n");}
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 309 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"compound_statement : LCURL RCURL\n");}
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 313 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"var_declaration : type_specifier declaration_list SEMICOLON\n");}
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 315 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"var_declaration	: var_declaration type_specifier declaration_list SEMICOLON \n");
}
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 320 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"type_specifier	: INT \n");type="INT";}
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 321 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"type_specifier	: FLOAT\n");type="FLOAT";}
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 322 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"type_specifier	: CHAR	\n");type="CHAR";}
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 326 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"declaration_list : declaration_list COMMA ID \n%s\n",(yyvsp[0].a));
	string s=(yyvsp[0].a); 
	if(ST.Look_up(s)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d, Mltiple declaration of variable %s\n",line_count,(yyvsp[0].a));} 
	ST.Insert((yyvsp[0].a),type);ST.Print();
}
#line 1696 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 333 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD\n%s\n",(yyvsp[-3].a));
	string s=(yyvsp[-3].a);int x=(yyvsp[-1].i);  if(ST.Look_up((yyvsp[-3].a))!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,(yyvsp[-3].a));}
	ST.Insert((yyvsp[-3].a),type,x);ST.Print(); //SymbolInfo *si=ST.Look_up($3); si->setSize(x);
}
#line 1706 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 339 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"declaration_list : ID \n%s\n",(yyvsp[0].a));
	string s=(yyvsp[0].a);   if(ST.Look_up(s)!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,(yyvsp[0].a));}
	ST.Insert(s,type);ST.Print();
}
#line 1716 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 345 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"declaration_list : ID LTHIRD CONST_INT RTHIRD \n%s\n",(yyvsp[-3].a));
	string s=(yyvsp[-3].a);int x=(yyvsp[-1].i);   if(ST.Look_up((yyvsp[-3].a))!=0){error_count++; fprintf(outputlog,"***Error:Line: %d,  Mltiple declaration of variable %s\n",line_count,(yyvsp[-3].a));}
	ST.Insert((yyvsp[-3].a),type,x);ST.Print(); //SymbolInfo *si=ST.Look_up($1); si->setSize(x);
}
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 352 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"statements : statement 	\n");}
#line 1732 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 353 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"statements : statements statement \n");}
#line 1738 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 357 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"statement  : expression_statement\n");}
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 358 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"statement  : compound_statement \n");}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 360 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"statement  : FOR LPAREN expression_statement expression_statement expression RPAREN statement\n");
}
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 364 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"statement  : IF LPAREN expression RPAREN statement\n");
}
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 368 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"statement  : IF LPAREN expression RPAREN statement ELSE statement\n");
}
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 372 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"statement  : WHILE LPAREN expression RPAREN statement\n");
}
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 376 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"statement  : PRINTLN LPAREN ID RPAREN SEMICOLON\n%s\n",(yyvsp[-2].a));
	string s=(yyvsp[-2].a); ST.Insert((yyvsp[-2].a),type);ST.Print();
}
#line 1791 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 380 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"statement  : RETURN expression SEMICOLON \n");}
#line 1797 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 383 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"expression_statement	: SEMICOLON\n");}
#line 1803 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 384 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"expression_statement	: expression SEMICOLON \n");}
#line 1809 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 388 "1305053.y" /* yacc.c:1646  */
    {
	
	recent_variable=(yyvsp[0].a);
	fprintf(outputlog,"variable : ID \n%s\n",(yyvsp[0].a));
	string s=(yyvsp[0].a);  if(ST.Look_up(s)==0)  {error_count++; fprintf(outputlog,"***Error:Line: %d,  Undefined  variable %s\n",line_count,(yyvsp[0].a)); 		aFlag=2;}
	else  {ST.Insert((yyvsp[0].a),type);ST.Print(); //recent_variable=$1; 
	aFlag=0;
	//$$=ST.Look_up($1)->getValue();
		}
}
#line 1824 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 399 "1305053.y" /* yacc.c:1646  */
    {
	recent_variable=(yyvsp[-3].a);
	array_index=(yyvsp[-1].db); 
	fprintf(outputlog,"variable : ID LTHIRD expression RTHIRD \n%s\n",(yyvsp[-3].a));
	string s=(yyvsp[-3].a);  if(ST.Look_up(s)==0)  {error_count++; fprintf(outputlog,"***Error:Line: %d,  Undefined  variable %s\n",line_count,(yyvsp[-3].a)); 		aFlag=2;}
	else {ST.Insert((yyvsp[-3].a),type);ST.Print();aFlag=1;
	//$$=ST.Look_up($1)->getArrayVal($3);
		}
}
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 410 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"expression : logic_expression\n");}
#line 1844 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 412 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"expression : variable ASSIGNOP logic_expression\n"); 
	SymbolInfo *si=ST.Look_up(recent_variable);
	if(aFlag==0) { 
			if(si->getSize()==-1) {si->setValue((yyvsp[0].db));}
			else {error_count++; fprintf(outputlog,"***Error:Line: %d,  invalid assignment , data type is array\n",line_count);}
			ST.Print();
		     }
	else if(aFlag==1) {
				if(array_index>=si->getSize() || array_index<0) 
					{error_count++; fprintf(outputlog,"***Error:Line: %d,  Array index out of  bound\n",line_count);}
				else {si->setArrayVal(array_index,(yyvsp[0].db));}
				ST.Print();
				
			  }
	
}
#line 1866 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 432 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"logic_expression : rel_expression\n");
	(yyval.db)=(yyvsp[0].db);
}
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 437 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"logic_expression : rel_expression LOGICOP rel_expression \n");
	if(strcmp((yyvsp[-1].a),"&&")==0) (yyval.db)=(yyvsp[-2].db) && (yyvsp[0].db);
	else if(strcmp((yyvsp[-1].a),"||")==0) (yyval.db)=(yyvsp[-2].db) || (yyvsp[0].db);
}
#line 1885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 445 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"rel_expression	: simple_expression\n");
	(yyval.db)=(yyvsp[0].db);
}
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 450 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"rel_expression	: simple_expression RELOP simple_expression\n");
	if(strcmp("<",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) < (yyvsp[0].db);
	else if(strcmp("<=",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) <= (yyvsp[0].db);
	else if(strcmp(">",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) > (yyvsp[0].db);
	else if(strcmp(">=",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) >= (yyvsp[0].db);
	else if(strcmp("!=",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) != (yyvsp[0].db);
	else if(strcmp("==",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) == (yyvsp[0].db);
}
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 461 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"simple_expression : term\n");(yyval.db)=(yyvsp[0].db);}
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 463 "1305053.y" /* yacc.c:1646  */
    {
	fprintf(outputlog,"simple_expression : simple_expression ADDOP term\n");
	if(strcmp("+",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) + (yyvsp[0].db);
	else if(strcmp("-",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) - (yyvsp[0].db);
}
#line 1924 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 470 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"term :	unary_expression\n");(yyval.db)=(yyvsp[0].db);}
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 471 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"term :  term MULOP unary_expression\n");
										if(strcmp("*",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) * (yyvsp[0].db);
										else if(strcmp("/",(yyvsp[-1].a)) == 0)(yyval.db) = (yyvsp[-2].db) / (yyvsp[0].db);
										else if(strcmp("%",(yyvsp[-1].a)) == 0)(yyval.db) = (int)(yyvsp[-2].db) % (int)(yyvsp[0].db);
									}
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 478 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"unary_expression : ADDOP unary_expression\n");
										if(strcmp((yyvsp[-1].a),"+")==0)(yyval.db)=+(yyvsp[0].db);
										else if(strcmp((yyvsp[-1].a),"-")==0) (yyval.db)=-(yyvsp[0].db);}
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 481 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"unary_expression : NOT unary_expression\n");												(yyval.db) = !(yyvsp[0].db);}
#line 1954 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 482 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"unary_expression : factor \n"); 
										(yyval.db)=(yyvsp[0].db);}
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 486 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: variable\n");(yyval.db)=(yyvsp[0].db);}
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 487 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: LPAREN expression RPAREN \n");(yyval.db)=(yyvsp[-1].db);}
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 488 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: CONST_INT\n%d\n",(yyvsp[0].i));(yyval.db)=(yyvsp[0].i);}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 489 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: CONST_FLOAT\n%lf\n",(yyvsp[0].db));(yyval.db)=(yyvsp[0].db);}
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 490 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: CONST_CHAR\n%s\n",yylval);(yyval.db)=(yyvsp[0].ch);}
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 491 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: factor INCOP\n");(yyval.db)=(yyvsp[-1].db)++;}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 492 "1305053.y" /* yacc.c:1646  */
    {fprintf(outputlog,"factor	: factor DECOP\n");(yyval.db)=(yyvsp[-1].db)--;}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2007 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 495 "1305053.y" /* yacc.c:1906  */


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
