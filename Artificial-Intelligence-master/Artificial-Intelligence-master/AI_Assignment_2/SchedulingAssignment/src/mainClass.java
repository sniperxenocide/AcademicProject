import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;


class Element
{
    public int roomNo;
    public int classNo;
    public int teacherNo;
    public int frequency;
    Element(int a,int b,int c,int d)
    {
        roomNo=a;
        classNo=b;
        teacherNo=c;
        frequency=d;
    }
}


public class mainClass {

    public static Scanner s= new Scanner(System.in);
    public static Random rand = new Random();
    public static int[][][] mainInput;
    public static int[][] currentGRID;
    public static ArrayList<Element> elementList= new ArrayList<Element>();

    public static String FileName="src/hdtt5req.txt";
    public static int REQUIREMENT=175;
    public static int nTeacher=5;
    public static int nRoom=5;
    public static int nClass=5;
    public static int nPeriod;
    public static int roomWgt=1;
    public static int classWgt=1;
    public static int teacherWgt=1;


    public static boolean isEqual(Element a,Element b)
    {
        if(a.frequency==b.frequency && a.teacherNo==b.teacherNo && a.classNo==b.classNo && a.roomNo==b.roomNo) return true;

        return false;
    }

    public static void createInitialState()
    {
        int index=0,r,p;
        int randomPosition=rand.nextInt(120);

        for(r=0;r<nRoom;r++)
        {
            for(p=0;p<nPeriod;p++)
            {
                currentGRID[r][p]=-1;
            }
        }

        while(true)
        {
            if(index==elementList.size()) break;
            int i=0;
            while (i<elementList.get(index).frequency)
            {
                //randomPosition=randomPosition%120;
                randomPosition=rand.nextInt(REQUIREMENT);
                p=randomPosition%nPeriod;
                r=randomPosition/nPeriod;
                if(currentGRID[r][p]==-1)
                {
                    currentGRID[r][p]=index;
                    i++;
                    //randomPosition++;
                }
                else continue;
            }

            index++;
        }
    }

    public static int COST(int[][] Matrix,int r,int c)
    {
        int sum=0;

        for(int j=0;j<c;j++)
        {
            int[] roomCost=new int[nRoom];
            int[] classCost=new int[nClass];
            int[] teacherCost=new int[nTeacher];
            for(int i=0;i<r;i++)
            {
                if(Matrix[i][j]!=-1)
                {
                    roomCost[elementList.get(Matrix[i][j]).roomNo]++;
                    classCost[elementList.get(Matrix[i][j]).classNo]++;
                    teacherCost[elementList.get(Matrix[i][j]).teacherNo]++;
                }
            }

            for(int p=0;p<nRoom;p++)
            {
                if(roomCost[p]>1) sum+= ((roomCost[p]-1)*roomWgt);
            }
            for(int p=0;p<nClass;p++)
            {
                if(classCost[p]>1) sum+= ((classCost[p]-1)*classWgt);
            }
            for(int p=0;p<nTeacher;p++)
            {
                if(teacherCost[p]>1) sum+= ((teacherCost[p]-1)*teacherWgt);
            }
        }

        return sum;
    }

    public static void printState(int[][] Matrix,int r,int c)
    {
        for(int i=0;i<r;i++)
        {
            for(int j=0;j<c;j++)
            {
                System.out.print(Matrix[i][j]+" ");
            }
            System.out.println();
        }
    }

    public static void Swap(int a,int b,int c,int d)
    {
        int temp;
        temp=currentGRID[a][b];
        currentGRID[a][b]=currentGRID[c][d];
        currentGRID[c][d]=temp;
    }

    public static void SteepestAscendHillClimbing()
    {
        int currentPosition;
        int positionToBeSwapped;
        int x1,y1,x2,y2,x1_=0,y1_=0,x2_=0,y2_=0;
        int minCost=1000;
        int prevCost=minCost;
        int localMinCnt=0;
        int currentCost;
        int count=0;

        while(true)
        {
            count++;
            int flag=0;
            prevCost=minCost;
            for(currentPosition=0;currentPosition<REQUIREMENT;currentPosition++)
            {
                x1=currentPosition/nPeriod;
                y1=currentPosition%nPeriod;
                for(positionToBeSwapped=0;positionToBeSwapped<REQUIREMENT;positionToBeSwapped++)
                {
                    x2=positionToBeSwapped/nPeriod;
                    y2=positionToBeSwapped%nPeriod;
                    Swap(x1,y1,x2,y2);
                    currentCost=COST(currentGRID,nRoom,nPeriod);
                    if(currentCost < minCost)
                    {
                        minCost=currentCost;
                        x1_=x1;
                        y1_=y1;
                        x2_=x2;
                        y2_=y2;
                        flag=1;
                    }
                    Swap(x1,y1,x2,y2);
                }
            }
            if(flag==1) Swap(x1_,y1_,x2_,y2_);
            minCost=COST(currentGRID,nRoom,nPeriod);
            System.out.println(count+" : "+minCost);

            if(prevCost==minCost) localMinCnt++;
            else localMinCnt=0;

            if(localMinCnt>20)
            {
                localMinCnt=0;
                createInitialState();
                minCost=COST(currentGRID,nRoom,nPeriod);
            }

            if(minCost==0)
            {
                System.out.println("found optimized routine after "+count+" count");
                break;
            }

        }
    }

    public static void FirstChoiceHillClimbing()
    {
        int currentPosition;
        int positionToBeSwapped;
        int x1,y1,x2,y2;
        int minCost=1000;
        int prevCost=minCost;
        int localMinCnt=0;
        int currentCost;
        int count=0;

        while(true)
        {
            count++;
            int flag=0;
            prevCost=minCost;
            for(currentPosition=0;currentPosition<REQUIREMENT;currentPosition++)
            {
                x1=currentPosition/nPeriod;
                y1=currentPosition%nPeriod;
                for(positionToBeSwapped=0;positionToBeSwapped<REQUIREMENT;positionToBeSwapped++)
                {
                    x2=positionToBeSwapped/nPeriod;
                    y2=positionToBeSwapped%nPeriod;
                    Swap(x1,y1,x2,y2);
                    currentCost=COST(currentGRID,nRoom,nPeriod);
                    if(currentCost < minCost)
                    {
                        flag=1;
                        break;
                    }
                    Swap(x1,y1,x2,y2);
                }
                if(flag==1) break;
            }
            minCost=COST(currentGRID,nRoom,nPeriod);
            System.out.println(count+" : "+minCost);

            if(prevCost==minCost) localMinCnt++;
            else localMinCnt=0;

            if(localMinCnt>20)
            {
                localMinCnt=0;
                createInitialState();
                minCost=COST(currentGRID,nRoom,nPeriod);
            }

            if(minCost==0)
            {
                System.out.println("found optimized routine after "+count+" count");
                for(int i=0;i<nRoom;i++)
                {
                    for (int j = 0; j < nPeriod; j++)
                    {
                        if(currentGRID[i][j]!=-1) System.out.print(elementList.get(currentGRID[i][j]).teacherNo+" "+elementList.get(currentGRID[i][j]).classNo+" "+elementList.get(currentGRID[i][j]).roomNo+"   ");
                    }
                    System.out.println();
                }

                break;
            }

        }
    }


    public static void main(String[] args)
    {
        mainInput=new int[nRoom][nClass][nTeacher];
        nPeriod= REQUIREMENT/nRoom;
        currentGRID=new int[nRoom][nPeriod];
        int rm,cls,tchr;

        try {
            File f = new File(FileName);
            FileInputStream fis = new FileInputStream(f);
            int x;
            rm=0;
            while (rm<nRoom)
            {
                cls=0;
                while (cls<nClass)
                {
                    tchr=0;
                    while (tchr<nTeacher)
                    {
                        x=fis.read();
                        if(x==32 || x==13 || x==10)  continue;
                        else
                        {
                            x=x-48;
                            mainInput[rm][cls][tchr]=x;
                            tchr++;
                        }
                    }
                    cls++;
                }
                rm++;
            }
            fis.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        for(rm=0;rm<nRoom;rm++)
        {
            for(cls=0;cls<nClass;cls++)
            {
                for (tchr = 0; tchr < nTeacher; tchr++)
                {
                    elementList.add(new Element(rm, cls, tchr, mainInput[rm][cls][tchr]));
                }
            }
        }


        createInitialState();

        System.out.println("COST: " + COST(currentGRID, nRoom, nPeriod));


        //SteepestAscendHillClimbing()

        FirstChoiceHillClimbing();


    }
}
