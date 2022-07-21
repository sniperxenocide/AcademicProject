import java.util.Scanner;

class State
{

    public int[][] Grid=new int[8][8];
    public int level=0;
    public State parent = null;

    State(int[][] matrix,int lvl,State prnt)
    {
        MainClass.copyMatrix(this.Grid, matrix);
        this.level=lvl;
        this.parent=prnt;
    }


}

public class MainClass {

    public static int[][] currentGrid=new int[8][8];
    public static int[][] tempGrid=new int[8][8];
    public static int CPU              =  1;
    public static int HUMAN            = -1;
    public static int EMPTY            =  0;
    public static int LegalMove        = -2;
    public static int DEPTH            =  10;
    public static int HuA              =  1;
    public static int HuB              =  2;
    public static int HuC              =  3;
    public static int HuD              =  4;
    public static int INFINITY         =  99999;
    public static int R,C;
    public static Scanner s=new Scanner(System.in);

    public static int[][] WeightA=
            {
                { 4 ,-3, 2, 2, 2, 2, -3, 4},
                {-3 ,-4,-1,-1,-1,-1, -4,-3},
                { 2 ,-1, 1, 0, 0, 1, -1, 2},
                { 2 ,-1, 0, 1, 1, 0, -1, 2},
                { 2 ,-1, 0, 1, 1, 0, -1, 2},
                { 2 ,-1, 1, 0, 0, 1, -1, 2},
                {-3 ,-4,-1,-1,-1,-1, -4,-3},
                { 4 ,-3, 2, 2, 2, 2, -3, 4}
            };

    public static int[][] WeightB=
            {
                {100, -20, 10,  5,  5, 10, -20, 100},
                {-20, -50, -2, -2, -2, -2, -50, -20},
                { 10,  -2, -1, -1, -1, -1,  -2,  10},
                {  5,  -2, -1, -1, -1, -1,  -2,   5},
                {  5,  -2, -1, -1, -1, -1,  -2,   5},
                { 10,  -2, -1, -1, -1, -1,  -2,  10},
                {-20, -50, -2, -2, -2, -2, -50, -20},
                {100, -20, 10,  5,  5, 10, -20, 100}
            };


    public static int Heuristic(int[][] Matrix,int Hu )
    {
        clearMoveMarks(Matrix);

        if(Hu==HuD)
        {

        }

        int cnt=0;
        for (int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Hu==HuA)      cnt+=WeightA[i][j]*Matrix[i][j];
                else if(Hu==HuB) cnt+=WeightB[i][j]*Matrix[i][j];
                else if(Hu==HuC) cnt+=Matrix[i][j];
            }
        }
        return cnt;
    }

    public static boolean isTerminalState(int[][] Matrix)
    {
        int cnt=0,cpu=0,human=0;
        clearMoveMarks(Matrix);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Matrix[i][j]!=0) cnt++;
                if(Matrix[i][j]==CPU) cpu++;
                if(Matrix[i][j]==HUMAN) human++;
            }
        }

        if(cnt==64 || cpu==0 || human==0) return true;
        return false;
    }


    public static void copyMatrix(int[][] dest,int[][] src)
    {
        int i,j;
        for(i=0;i<8;i++)
        {
            for(j=0;j<8;j++)
            {
                dest[i][j]=src[i][j];
            }
        }
    }

    public static void print(int[][] matrix)
    {
        System.out.println();
        System.out.print("  ");
        for(int i=0;i<8;i++) System.out.print(" " + i);
        System.out.println("\n");
        for(int i=0;i<8;i++)
        {
            System.out.print(i + "  ");
            for(int j=0;j<8;j++)
            {
                if(matrix[i][j]==1)           System.out.print("C ");
                else if(matrix[i][j]==-1)     System.out.print("H ");
                else if(matrix[i][j]==-2)     System.out.print("X ");
                else System.out.print(matrix[i][j] + " ");
            }
            System.out.println("");
        }
        System.out.println();
    }

    public static void initiateCurrentGrid()
    {
        for (int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                currentGrid[i][j]=EMPTY;
            }
        }
        currentGrid[3][3]=HUMAN;
        currentGrid[4][4]=HUMAN;
        currentGrid[3][4]=CPU;
        currentGrid[4][3]=CPU;
    }

    public static void clearMoveMarks(int[][] Matrix)
    {
        for (int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Matrix[i][j]==LegalMove) Matrix[i][j]=EMPTY;
            }
        }
    }

    public static void printScore()
    {
        int cpu=0,human=0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(currentGrid[i][j]==CPU) cpu++;
                else if(currentGrid[i][j]==HUMAN) human++;
            }
        }
        System.out.println();
        System.out.println("SCORE:: CPU: "+cpu+" HUMAN: "+human);
        System.out.println();
    }

    public static void printScore_()
    {
        int cpu=0,human=0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(currentGrid[i][j]==CPU) cpu++;
                else if(currentGrid[i][j]==HUMAN) human++;
            }
        }
        System.out.println();
        System.out.println("SCORE:: CPU_1: "+cpu+" CPU_2: "+human);
        System.out.println();
    }



    public static int legalMoves(int[][] Matrix,int whom )
    {
        int opposit=whom*(-1);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Matrix[i][j]==whom)
                {
                    for(int k=j+1;k<8;k++)            ///direction right
                    {
                        if(Matrix[i][k]!=EMPTY) continue;
                        else if( Matrix[i][k] == EMPTY && Matrix[i][k-1]== opposit)
                        {
                            Matrix[i][k]=LegalMove;
                            break;
                        }
                        else break;
                    }
                    for(int k=j-1;k>=0;k--)            ///direction left
                    {
                        if(Matrix[i][k]!=EMPTY) continue;
                        else if( Matrix[i][k] == EMPTY && Matrix[i][k+1]== opposit)
                        {
                            Matrix[i][k]=LegalMove;
                            break;
                        }
                        else break;

                    }
                    for(int k=i+1;k<8;k++)            ///direction down
                    {
                        if(Matrix[k][j]!=EMPTY) continue;
                        else if( Matrix[k][j] == EMPTY && Matrix[k-1][j]== opposit)
                        {
                            Matrix[k][j]=LegalMove;
                            break;
                        }
                        else break;

                    }
                    for(int k=i-1;k>=0;k--)            ///direction up
                    {
                        if(Matrix[k][j]!=EMPTY) continue;
                        else if( Matrix[k][j] == EMPTY && Matrix[k+1][j]== opposit)
                        {
                            Matrix[k][j]=LegalMove;
                            break;
                        }
                        else break;
                    }
                    int x,y;
                    for(x=i-1,y=j+1  ; x>=0 && y<8 ; x--,y++)          ///direction up-right
                    {
                        if(Matrix[x][y]!=EMPTY) continue;
                        else if( Matrix[x][y] == EMPTY && Matrix[x+1][y-1]== opposit)
                        {
                            Matrix[x][y]=LegalMove;
                            break;
                        }
                        else break;
                    }
                    for(x=i-1,y=j-1  ; x>=0 && y>=0 ; x--,y--)          ///direction up-left
                    {

                        if(Matrix[x][y]!=EMPTY) continue;
                        else if( Matrix[x][y] == EMPTY && Matrix[x+1][y+1]== opposit)
                        {
                            Matrix[x][y]=LegalMove;
                            break;
                        }
                        else break;
                    }
                    for(x=i+1,y=j-1  ; x<8 && y>=0 ; x++,y--)          ///direction down-left
                    {
                        if(Matrix[x][y]!=EMPTY) continue;
                        else if( Matrix[x][y] == EMPTY && Matrix[x-1][y+1]== opposit)
                        {
                            Matrix[x][y]=LegalMove;
                            break;
                        }
                        else break;

                    }
                    for(x=i+1,y=j+1  ; x<8 && y<8 ; x++,y++)          ///direction down-right
                    {

                        if(Matrix[x][y]!=EMPTY) continue;
                        else if( Matrix[x][y] == EMPTY && Matrix[x-1][y-1]== opposit)
                        {
                            Matrix[x][y]=LegalMove;
                            break;
                        }
                        else break;
                    }

                }
            }
        }

        int cnt=0;
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(Matrix[i][j]==LegalMove) cnt++;
            }
        }
        return cnt;
    }

    public static void commitMove(int[][] Matrix,int whom,int i,int j)
    {
        clearMoveMarks(Matrix);
        Matrix[i][j]=whom;
        int opposit=whom*(-1);
        int r=0,c=0,flag=0;

        ///direction right
        for(int k=j+1;k<8;k++)
        {
            if(Matrix[i][k]==EMPTY) break;
            else if(Matrix[i][k]==whom) {c=k ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(int k=j+1;k<c;k++) Matrix[i][k]=whom;
        }
        ///direction right



        ///direction left
        for(int k=j-1;k>=0;k--)
        {
            if(Matrix[i][k]==EMPTY) break;
            else if(Matrix[i][k]==whom) {c=k ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(int k=j-1;k>c;k--) Matrix[i][k]=whom;
        }
        ///direction left



        ///direction down
        for(int k=i+1;k<8;k++)
        {
            if(Matrix[k][j]==EMPTY) break;
            else if(Matrix[k][j]==whom) {r=k ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(int k=i+1;k<r;k++) Matrix[k][j]=whom;
        }
        ///direction down



        ///direction up
        for(int k=i-1;k>=0;k--)
        {
            if(Matrix[k][j]==EMPTY) break;
            else if(Matrix[k][j]==whom) {r=k ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(int k=i-1;k>r;k--) Matrix[k][j]=whom;
        }
        ///direction up

        int x,y;


        ///direction up-right
        for(x=i-1,y=j+1  ; x>=0 && y<8 ; x--,y++)
        {
            if(Matrix[x][y]==EMPTY) break;
            else if(Matrix[x][y]==whom) {r=x;c=y ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(x=i-1,y=j+1  ; x>r && y<c ; x--,y++) Matrix[x][y]=whom;
        }
        ///direction up-right



        ///direction up-left
        for(x=i-1,y=j-1  ; x>=0 && y>=0 ; x--,y--)
        {
            if(Matrix[x][y]==EMPTY) break;
            else if(Matrix[x][y]==whom) {r=x;c=y ;flag=1; break;}
            else continue;
        }

        if(flag==1)
        {
            flag=0;
            for(x=i-1,y=j-1  ; x>r && y>c ; x--,y--) Matrix[x][y]=whom;
        }
        ///direction up-left



        ///direction down-left
        for(x=i+1,y=j-1  ; x<8 && y>=0 ; x++,y--)
        {
            if(Matrix[x][y]==EMPTY) break;
            else if(Matrix[x][y]==whom) {r=x;c=y ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(x=i+1,y=j-1  ; x<r && y>c ; x++,y--) Matrix[x][y]=whom;
        }
        ///direction down-left



        ///direction down-right
        for(x=i+1,y=j+1  ; x<8 && y<8 ; x++,y++)
        {
            if(Matrix[x][y]==EMPTY) break;
            else if(Matrix[x][y]==whom) {r=x;c=y ;flag=1; break;}
            else continue;
        }
        if(flag==1)
        {
            flag=0;
            for(x=i+1,y=j+1  ; x<r && y<c ; x++,y++) Matrix[x][y]=whom;
        }
        ///direction down-right

    }

    public static int getMax(int a,int b)
    {
        if(a>b) return a;
        return b;
    }

    public static int getMin(int a,int b)
    {
        if(a>b) return b;
        return a;
    }



    public static int MINIMAX(State state,int depth,int whosTurn,int alpha,int beta,int H)
    {
        if(depth==DEPTH || isTerminalState(state.Grid)==true)
        {
            return Heuristic(state.Grid,H);
        }

        int bestVal,value;

        if(whosTurn==CPU)
        {
            bestVal=-INFINITY;
            legalMoves(state.Grid,whosTurn);
            int flag=0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(state.Grid[i][j]==LegalMove)
                    {
                        tempGrid=new int[8][8];
                        copyMatrix(tempGrid, state.Grid);
                        commitMove(tempGrid,CPU,i,j);
                        value=MINIMAX(new State(tempGrid,depth+1,state),depth+1,HUMAN,alpha,beta,H);
                        if(bestVal < value && depth==0 )
                        {
                            R=i;
                            C=j;
                        }
                        bestVal=getMax(bestVal,value);
                        alpha=getMax(alpha,bestVal);
                        if(beta<=alpha) {flag=1;break;}
                    }
                }
                if(flag==1) break;
            }
            return bestVal;
        }
        else
        {
            bestVal= +INFINITY;
            legalMoves(state.Grid,whosTurn);
            int flag=0;
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(state.Grid[i][j]==LegalMove)
                    {
                        tempGrid=new int[8][8];
                        copyMatrix(tempGrid, state.Grid);
                        commitMove(tempGrid,HUMAN,i,j);
                        value=MINIMAX(new State(tempGrid,depth+1,state),depth+1,CPU,alpha,beta,H);
                        if(bestVal > value && depth==0 )
                        {
                            R=i;
                            C=j;
                        }
                        bestVal=getMin(bestVal,value);
                        beta=getMin(beta,bestVal);
                        if(beta<=alpha) {flag=1;break;}
                    }
                }
                if(flag==1) break;
            }
            return bestVal;
        }

    }

    public static void HumanVsCPU()
    {
        initiateCurrentGrid();
        System.out.println("CPU: C\nHUMAN: H\nPossible Move: X");
        int r,c;
        while (true)
        {
            int mv=legalMoves(currentGrid, HUMAN);
            print(currentGrid);
            printScore();
            System.out.println();
            System.out.println("number of legal moves: " + mv);
            if(mv==0)
            {
                System.out.println("No legal moves available");
            }
            else
            {
                System.out.println("Humans Turn...");
                System.out.print("Row: ");
                r=s.nextInt();
                System.out.print("Collum: ");
                c=s.nextInt();
                if(currentGrid[r][c]!=LegalMove)
                {
                    System.out.println("Wrong move.try again");
                    continue;
                }
                commitMove(currentGrid, HUMAN, r, c);
                print(currentGrid);
            }


            if(isTerminalState(currentGrid)==true)
            {
                System.out.println("game over");
                printScore();
                break;
            }

            System.out.println("CPU Turn...");
            State s=new State(currentGrid,0,null);
            MINIMAX(s, 0, CPU, -INFINITY, INFINITY,HuA);
            System.out.println(R+" "+C);
            commitMove(currentGrid,CPU,R,C);

            if(isTerminalState(currentGrid)==true)
            {
                System.out.println("game over");
                printScore();
                break;
            }


        }

    }

    public static void CPUvsCPU()
    {

        initiateCurrentGrid();
        print(currentGrid);
        System.out.println("CPU1: C\nCPU2: H\nPossible Move: X");

        while (true)
        {
            System.out.println("CPU_1 turn...");
            State s=new State(currentGrid,0,null);
            MINIMAX(s, 0, CPU, -INFINITY, INFINITY, HuA);
            System.out.println(R + " " + C);
            commitMove(currentGrid, CPU, R, C);
            print(currentGrid);
            printScore_();

            if(isTerminalState(currentGrid)==true)
            {
                System.out.println("game over");
                printScore_();
                break;
            }

            System.out.println("CPU_2 turn...");
            MINIMAX(new State(currentGrid,0,null), 0, HUMAN, -INFINITY, INFINITY, HuC);
            System.out.println(R + " " + C);
            commitMove(currentGrid, HUMAN, R, C);
            print(currentGrid);
            printScore_();

            if(isTerminalState(currentGrid)==true)
            {
                System.out.println("game over");
                printScore_();
                break;
            }
        }
    }


    public static void main(String[] args)
    {


        HumanVsCPU();

        //CPUvsCPU();



    }
}
