import java.util.*;



public class class1305053_FixedGoal
{
    public static Scanner s=new Scanner(System.in);
    public static ArrayList<State> Q=new ArrayList<State>();
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

    public static int distanceFromGoal_V3(State C,State G,int r,int c)                 // C: current state ... G: goal state
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
                sum+= mn1+mn2;
            }
        }
        return sum;
    }

    public static int distanceFromGoal_V1(State C,State G,int r,int c)                 // C: current state ... G: goal state
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

    public static int distanceFromGoal(State C,State G,int r,int c)                 // C: current state ... G: goal state
    {
        int i,j,sum=0;
        for(i=0;i<r;i++)
        {
            for (j=0;j<c;j++)
            {
               if( C.elements[i][j] != G.elements[i][j] ) sum++;
            }
        }
        return sum;
    }

    public static void printFromRoot(State s)
    {
        if(s.previous!=null) printFromRoot(s.previous);
        System.out.println("Now Move: "+s.level+" by moving "+s.move+s.which);
        print(s.elements,s.n,s.n);
    }


    public static void main(String[] args)
    {
        int r,c,moves=0;
        System.out.print("Board Size : ");
        r=s.nextInt();
        c=r;
        int[][] MAT= new int[r][c];
        State goalA,goalB,goalC,goalD;

        System.out.println("Intital State:");
        getMatrix(MAT, r, c);
        State initial=new State(r,c,MAT,"",-1,0,null);

        System.out.println("Printing initial state:");
        print(initial.elements, r, c);

        System.out.println("Goal State:");
        getMatrix(MAT, r, c);
        State goal=new State(r,c,MAT,"",-1,0,null);

        goalA=new State(r,c,MAT,"",-1,0,null);
        goalB=new State(r,c,MAT,"",-1,0,null);
        goalC=new State(r,c,MAT,"",-1,0,null);
        goalD=new State(r,c,MAT,"",-1,0,null);

        for(int i=0;i<r;i++)
        {
            for (int j=0;j<c;j++)
            {
                goalB.elements[r-i-1][j]=MAT[i][j];
                goalC.elements[j][i]=MAT[i][j];
                goalD.elements[j][c-i-1]=MAT[i][j];
            }
        }



        System.out.println("Printing Goal State:");
        print(goalA.elements, r, c);
        print(goalB.elements, r, c);
        print(goalC.elements, r, c);
        print(goalD.elements, r, c);


        Q.add(initial);
        State current=null;

        while (true)
        {

            for(State i:Q)
            {
                if(match(i,goal,r,c))
                {
                    printFromRoot(i);
                    System.out.println("reached goal after "+i.level+" moves");
                    return;
                }
            }


            double min=9999;
            for(State i:Q)
            {
                int d=distanceFromGoal(i,goal,r,c);
                double e=((d+0.0)/r)+i.level;
                if( e  < min && isAlreadyUsed(UsedState,i,r,c)==false)
                {
                    min=e;
                    current=i;
                }
            }

            UsedState.add(current);


            int i,j,temp;
            State T;

            for(i=0;i<r;i++)    // creating states for row
            {
                copyMatrix(MAT,current.elements,r,c);
                temp=MAT[i][0];
                for(j=1;j<c;j++)
                {
                    MAT[i][j-1]=MAT[i][j];       ///move left
                }
                MAT[i][c-1]=temp;
                T=new State(r,c,MAT,"left, row: ",i,current.level+1,current);
                Q.add(T);


                copyMatrix(MAT, current.elements, r, c);
                temp=MAT[i][c-1];
                for(j=c-2;j>=0;j--)
                {
                    MAT[i][j+1]=MAT[i][j];      ///move right
                }
                MAT[i][0]=temp;
                T=new State(r,c,MAT,"right, row: ",i,current.level+1,current);
                Q.add(T);

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
                T=new State(r,c,MAT,"up, collum: ",j,current.level+1,current);
                Q.add(T);


                copyMatrix(MAT, current.elements, r, c);
                temp=MAT[r-1][j];
                for(i=r-2;i>=0;i--)
                {
                    MAT[i+1][j]=MAT[i][j];      ///move down
                }
                MAT[0][j]=temp;
                T=new State(r,c,MAT,"down, collum: ",j,current.level+1,current);
                Q.add(T);

            }
            moves++;
            Q.remove(current);
        }

    }
}
