import java.util.*;


class State
{
    public int n;
    public String move;
    public int which;
    public int[][] elements;

    public int[][] X;
    public int[][] Y;
    public int[] index;

    State(int r,int c,int[][] matrix,String m,int wh)
    {
        this.move=m;
        this.which=wh;
        this.n=r;
        int i,j;
        elements=new int[r][c];

        X=new int[r][c];
        Y=new int[r][c];
        index=new int[r];
        for(i=0;i<r;i++) index[i]=0;

        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                elements[i][j]=matrix[i][j];

                int t=elements[i][j]-1;
                X[t][index[t]]= i+1;
                Y[t][index[t]]= j+1;
                index[t]++;
            }
        }
    }
}


public class workingClass
{
    public static Scanner s=new Scanner(System.in);
    public static Queue<State> Q=new LinkedList<State>();
    public static ArrayList<State> UsedState= new ArrayList<State>();


    public static void getMatrix(int[][] matrix,int r,int c)
    {
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                System.out.println("("+i+","+j+"):");
                matrix[i][j]=s.nextInt();
            }
        }
    }
    public static void copyMatrix(int[][] dest,int[][] src,int r,int c)
    {
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                dest[i][j]=src[i][j];
            }
        }
    }
    public static void print(int[][] matrix,int r,int c)
    {
        System.out.println();
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println("");
        }
        System.out.println();
    }

    public static boolean match(State A,State B,int r,int c)
    {
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if (A.elements[i][j] != B.elements[i][j]) return false;
            }
        }
        return true;
    }

    public static boolean isAlreadyUsed(ArrayList<State> A,State S,int r,int c)
    {
        for(State i:A)
        {
            if(match(i,S,r,c)) return true;
        }
        return false;
    }

    public static int absolute(int x)
    {
        if(x<0)
        {
            x=-x;
        }
        return x;
    }

    public static int MIN(int x,int y)
    {
        if(x>y) return y;
        return x;
    }

    public static int distanceFromGoal_V1(State C,State G,int r,int c)                 // C: current state ... G: goal state
    {
        int i,j,sum=0;
        for(i=0;i<r;i++)
        {
            for (j=0;j<c;j++)
            {
                sum+=  MIN (  absolute( G.X[i][j]-C.X[i][j] ) , absolute( G.X[i][j]-r+C.X[i][j] )  );
                sum+=  MIN (  absolute( G.Y[i][j]-C.Y[i][j] ) , absolute( G.Y[i][j]-r+C.Y[i][j] )  );
            }
        }
        return sum;
    }

    public static int distanceFromGoal_V2(State C,State G,int r,int c)                 // C: current state ... G: goal state
    {
        int i,j,sum=0;
        for(i=0;i<r;i++)
        {
            for (j=0;j<c;j++)
            {
                int mn1=9999,mn2=9999;
                for(int k=0;k<c;k++)
                {
                    if(absolute(G.X[i][k] - C.X[i][j])<mn1) mn1=absolute(G.X[i][k] - C.X[i][j]);
                    if(absolute(G.Y[i][k] - C.Y[i][j])<mn2) mn2=absolute(G.Y[i][k] - C.Y[i][j]);
                }
                sum+=  mn1+mn2;
            }
        }
        return sum;
    }

    public static int distanceFromGoal(State C,State G,int r,int c)                 // C: current state ... G: goal state
    {
        int i,j,sum=0;
        for(i=0;i<r;i++)
        {
            for (j=0;j<c;j++)
            {
                sum+=  absolute( G.X[i][j]-C.X[i][j] );
                sum+=  absolute( G.Y[i][j]-C.Y[i][j] );
            }
        }
        return sum;
    }



    public static void main(String[] args)
    {
        int r,c,moves=0;
        System.out.print("Board Size : ");
        r=s.nextInt();
        c=r;
        int[][] MAT= new int[r][c];

        System.out.println("Intital State:");
        getMatrix(MAT, r, c);
        State initial=new State(r,c,MAT,"",-1);

        System.out.println("Printing initial state:");
        print(initial.elements, r, c);

        System.out.println("Goal State:");
        getMatrix(MAT, r, c);
        State goal=new State(r,c,MAT,"",-1);

        System.out.println("Printing Goal State:");
        print(goal.elements, r, c);



        Q.add(initial);
        State current;

        while (Q.isEmpty()==false)
        {
            int flag=0;
            current=Q.remove();
            if(match(current,goal,r,c))
            {
                System.out.println("Reached goal state after move: "+moves+" by moving "+current.move+current.which);
                print(current.elements,r,c);
                break;
            }

            if(UsedState.isEmpty()==false)
            {
                for(State i:UsedState)
                {
                    if(match(i,current,r,c)) {flag=1; break;}
                }
            }
            if(flag==1) continue;

            UsedState.add(current);
            System.out.println("Now Move: "+moves+" by moving "+current.move+current.which+"\nPrinting Current State: ");
            print(current.elements,r,c);
            int i,j,temp,min=9999;
            State T;
            State ToBeAdded=new State(r,c,current.elements,"",-1);

            for(i=0;i<r;i++)    // creating states for row
            {
                copyMatrix(MAT,current.elements,r,c);
                temp=MAT[i][0];
                for(j=1;j<c;j++)
                {
                    MAT[i][j-1]=MAT[i][j];       ///move left
                }
                MAT[i][c-1]=temp;
                T=new State(r,c,MAT,"left, row: ",i);
                if(isAlreadyUsed(UsedState,T,r,c)==false && distanceFromGoal(T,goal,r,c)<min)
                {
                    min=distanceFromGoal(T,goal,r,c);
                    ToBeAdded=T;
                }


                copyMatrix(MAT, current.elements, r, c);
                temp=MAT[i][c-1];
                for(j=c-2;j>=0;j--)
                {
                    MAT[i][j+1]=MAT[i][j];      ///move right
                }
                MAT[i][0]=temp;
                T=new State(r,c,MAT,"right, row: ",i);
                if(isAlreadyUsed(UsedState,T,r,c)==false && distanceFromGoal(T,goal,r,c)<min)
                {
                    min=distanceFromGoal(T,goal,r,c);
                    ToBeAdded=T;
                }
            }

            for(j=0;j<c;j++)    // creating states for collum
            {
                copyMatrix(MAT,current.elements,r,c);
                temp=MAT[0][j];
                for(i=1;i<r;i++)
                {
                    MAT[i-1][j]=MAT[i][j];       ///move up
                }
                MAT[r-1][j]=temp;
                T=new State(r,c,MAT,"up, collum: ",j);
                if(isAlreadyUsed(UsedState,T,r,c)==false && distanceFromGoal(T,goal,r,c)<min)
                {
                    min=distanceFromGoal(T,goal,r,c);
                    ToBeAdded=T;
                }

                copyMatrix(MAT, current.elements, r, c);
                temp=MAT[r-1][j];
                for(i=r-2;i>=0;i--)
                {
                    MAT[i+1][j]=MAT[i][j];      ///move down
                }
                MAT[0][j]=temp;
                T=new State(r,c,MAT,"down, collum: ",j);
                if(isAlreadyUsed(UsedState,T,r,c)==false && distanceFromGoal(T,goal,r,c)<min)
                {
                    min=distanceFromGoal(T,goal,r,c);
                    ToBeAdded=T;
                }
            }
            Q.add(ToBeAdded);
            moves++;
        }

    }
}
