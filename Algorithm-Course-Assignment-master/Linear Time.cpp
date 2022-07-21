#include<stdio.h>
#include<iostream>
#include<stdlib.h>
using namespace std;
#define NULL_VALUE -999999
#define INFINITY 99999
#define SUCCESS_VALUE 5000
#define WHITE 1
#define GREY 2
#define BLACK 3



//linkedList
struct listNode
{
    int item;
    struct listNode * next;
};

class linkedList{
        struct listNode * list;
        struct listNode * tail;
        //struct listNode *pos;
        int length;
    public:
        linkedList();
        ~linkedList();
        int insertItem(int item);
        int deleteItem(int item);
        struct listNode* searchItem(int item);
        void printList();
        int insertLast(int item);
        int getLength();
        struct listNode* getHead();
        //int getNext(void);
};

linkedList::linkedList()
{
    length=0;
    list = 0;  //initially set to NULL
	tail = 0;
}


//add required codes to set up tail pointer
int linkedList::insertItem(int item) //insert at the beginning
{
	struct listNode * newNode ;
	newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
	newNode->item = item ;
	if(list==0){
        tail=newNode;
        tail->next=0;
        list=tail;
        length++;
        return SUCCESS_VALUE;
	}
	newNode->next = list ; //point to previous first node
	list = newNode ; //set list to point to newnode as this is now the first node
	length++;
	return SUCCESS_VALUE ;
}

//add required codes to set up tail pointer
int linkedList::deleteItem(int item)//modified
{
	struct listNode *temp, *prev ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) break ;
		prev = temp;
		temp = temp->next ; //move to next node
	}
	if (temp == 0) return NULL_VALUE ; //item not found to delete
	if (temp == list) //delete the first node
	{//main modification
		list = list->next ;
		if(list==0)tail=0;
		free(temp) ;
	}
	else
	{
	    if(temp->next==0)tail=prev;
		prev->next = temp->next ;
		free(temp);
	}
	length--;
	return SUCCESS_VALUE ;
}

//add required codes to set up tail pointer
struct listNode* linkedList::searchItem(int item)
{
	struct listNode * temp ;
	temp = list ; //start at the beginning
	while (temp != 0)
	{
		if (temp->item == item) return temp ;
		temp = temp->next ; //move to next node
	}
	return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void linkedList::printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}


int linkedList::insertLast(int item)//newly written
{
    //write your codes here
    struct listNode *newNode;
    newNode=(struct listNode*)malloc(sizeof(listNode));
    newNode->item=item;
    if(list==0){list=newNode;tail=newNode;length++;return SUCCESS_VALUE;}
    tail->next=newNode;
    newNode->next=0;
    tail=newNode;
    length++;
    return SUCCESS_VALUE;
}

int linkedList::getLength(){
    return length;
}

struct listNode* linkedList::getHead(){
    return list;
}

linkedList::~linkedList(){
    if(list)list=0;
    tail=0;
    length=0;
}
//linkedList complete




//******************Graph class starts here**************************
class Graph
{
	int *parent,*color,*start,*finish;
	int nVertices, nEdges,time ;
	bool directed ;
	//ArrayList  * adjList ;
	//ArrayList * weighted;
	linkedList *adjecencyList;
	linkedList sortedList;
	linkedList *weight;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
    int *dist;
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v,int w);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    //bool hasCommonAdjacent(int u, int v);
    //int getDist(int u, int v);
    void printGraph();
	//void bfs(int source); //will run bfs in the graph
	void dfs(int source); //will run dfs in the graph
	void dfs_visit(int s);
	void top_sort(int s);
	void linear_sp(int s);
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	//adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	parent=new int[nVertices];
	start=new int[nVertices];
	finish=new int[nVertices];
	color=new int[nVertices];
	dist=new int[nVertices];
	for(int i=0;i<nVertices;i++){
      parent[i]=-100;dist[i]=INFINITY;color[i]=WHITE;
	}
	//if(adjecencyList!=0) delete[] adjecencyList ; //delete previous list
	adjecencyList = new linkedList[nVertices] ;
	weight=new linkedList[nVertices];
	//if(weighted!=0)delete[] weighted;
	//weighted=new ArrayList[nVertices];
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    //if(isEdge(u,v)==false){
        this->nEdges++ ;
        adjecencyList[u].insertLast(v) ;
        weight[u].insertLast(w);
        //weighted[u].insertItem(w);
        if(!directed)adjecencyList[v].insertLast(u);
    //}
}

void Graph::removeEdge(int u, int v,int w)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    //int pos=gList[u].searchItem(v);
    adjecencyList[u].deleteItem(v);
    weight[u].deleteItem(w);

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)return false;
    if(adjecencyList[u].searchItem(v)->item==v)return true;
    return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)return -1;
    return adjecencyList[u].getLength();
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices)return;
    adjecencyList[u].printList();
    printf("\n");
}



void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        adjecencyList[i].printList();
        printf("\n");
    }
}

void Graph::dfs(int s){
    int i;
    for(i=0;i<nVertices;i++){
        color[i]=WHITE;parent[i]=-100;
    }
    time=0;
    dfs_visit(s);
    for(i=0;i<nVertices;i++){
        if(color[i]==WHITE)dfs_visit(i);
    }

}

void Graph::dfs_visit(int u){
    int v;
    time =time+1;
    start[u]=time;
    color[u]=GREY;
    struct listNode *temp=adjecencyList[u].getHead();
    for(int j=0;j<adjecencyList[u].getLength();j++){
        v=temp->item;
        temp=temp->next;
        if(color[v]=WHITE){
            parent[v]=u;
            dfs_visit(v);
        }
    }
    color[u]=BLACK;
    time++;
    finish[u]=time;
    sortedList.insertItem(u);
}

void Graph::top_sort(int s){
    dfs(s);
}

void Graph::linear_sp(int s){
    int i;
    dist[s]=0;
    dfs(s);
    struct listNode *val= sortedList.getHead();
    for(int p=0;p<sortedList.getLength();p++){
        int node=val->item;

        struct listNode *temp=adjecencyList[node].getHead();
        struct listNode *temp2=weight[node].getHead();
        for(i=0;i<adjecencyList[node].getLength();i++){
            if(dist[temp->item]>dist[node]+temp2->item){
                dist[temp->item]=dist[node]+temp2->item;
            }
            temp=temp->next;
            temp2=temp2->next;
        }
        val=val->next;
    }
}

Graph::~Graph()
{
    //write your destructor here
    //delete [] adjList;
    //delete [] color;
    //delete [] parent;
    //delete [] dist;
    delete [] adjecencyList;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g(true);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)

    {
        printf("press 1 to add edge, 2 to finish\n");
        int ch;
        cin>>ch;
        if(ch==1){
            int u, v, w;
            scanf("%d %d %d", &u, &v,&w);
            g.addEdge(u, v, w);
        }
        else if(ch==2) break;
    }


    int s;
    cout<<"source"<<endl;
    cin>>s;
    g.linear_sp(s);
    for(int i=0;i<n;i++)printf("%d ",g.dist[i]);

    return 0;

}
