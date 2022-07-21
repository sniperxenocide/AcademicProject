class State
{
    public int n;
    public int level=0;
    public State previous=null;
    public String move;
    public int which;
    public int[][] elements;

    public int[][] X;
    public int[][] Y;
    public int[] index;

    State(int r,int c,int[][] matrix,String m,int wh,int lvl,State prv)
    {
        this.move=m;
        this.which=wh;
        this.level=lvl;
        this.previous=prv;
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

