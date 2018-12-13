#include<bits/stdc++.h>
using namespace std;
struct node{
    int x;
    struct node* next;
};
//queue implemented here is a circular queue with MAX SIZE 100000 so after 100000 element will be inserted at 0 position
void enq(int s,int que[],int *fron,int *rear) //function to insert 's' in queue 'que' with given front and rear
{
    if(*rear==-1 && *fron==-1)  //Empty queue
    {
        *rear=*fron=0;
        que[*rear]=s;
    }
    else if(*rear==100000) //insertion at last element of queue
    {
        *rear=0;
        que[*rear]=s;
    }
    else
    {
        *rear=*rear+1;
        que[*rear]=s;
    }
}
void mydelete(struct node *p)// deletes all the node in linked list
{
    struct node *t2=p;
    while(p!=NULL)
    {
        t2=p;
        p=p->next;
        free(t2);
    }
}
bool isempty(int fron,int rear) //returns true if queue is empty else false
{
    if(fron==-1 && rear==-1)
        return true;
    return false;
}
void deq(int *fron,int *rear)   //used to delete front element from queue
{
    if(*fron==*rear)   //only one element present in queue
    {
        *fron=-1;*rear=-1;
    }
    else if(*fron==100000)
    {
        *fron=0;
    }
    else
        *fron=*fron+1;
}
void bfs(int s,bool visit[],struct node *a[],int *fron,int *rear,int que[]) //print the BFS-traversal of graph starting from vertex s
{
    enq(s,que,fron,rear);
    visit[s]=true;
    while(!isempty(*fron,*rear))
    {
        int r=que[*fron];
        printf("%d ",r);
        deq(fron,rear);
        struct node* h=a[r];
        while(h!=NULL)
        {
            if(!visit[h->x])
            {
                visit[h->x]=true;
                enq(h->x,que,fron,rear);
            }
            h=h->next;
        }
    }
    printf("\n");
}
void bfs2(int s,bool visit[],struct node *a[],int *fron,int *rear,int par[],int que[])//performs bfs to find shortest path from s to any other node
{
    enq(s,que,fron,rear);
    visit[s]=true;
    while(!isempty(*fron,*rear))
    {
        int r=que[*fron];
        deq(fron,rear);
        struct node* h=a[r];
        while(h!=NULL)
        {
            if(!visit[h->x])
            {
                visit[h->x]=true;
                par[h->x]=r;  //par of vertex holds the value of vertex just before that vertex in a shortest path from s
                enq(h->x,que,fron,rear);
            }
            h=h->next;
        }
    }
}
void path(int v1,int prevdata,int v2,bool visit[],int que[],int par[],int *fron,int *rear,int b[],struct node *a[],int vert) //prints a shortest path from v1 to v2
{
        int i;
        if(v1==v2)
        {
          printf("%d\n",v1);
          return;
        }
        while(!isempty(*fron,*rear))
            deq(fron,rear);
        if(prevdata!=v1) // if the source node of the previous searched shortest path was not v1 then perform BFS else not
        {
        for(i=1;i<=vert;i++)
        {visit[i]=false;
        par[i]=-1;
        }
        bfs2(v1,visit,a,fron,rear,par,que);
        }
        if(par[v2]==-1) //v2 is not reachable from v1
            printf("-1\n");
        else
        {
            int l=0;
            int s=v2;
            while(s!=v1)
            {
                b[l++]=s;
                s=par[s];
            }
            b[l++]=s;
            for(i=l-1;i>=0;i--)
            {
                printf("%d ",b[i]);
            }
            printf("\n");
        }
}
void edge(int v1,int v2,struct node *a[]) //checks whether there is an edge between v1 and v2 or not
{

        struct node *h = a[v1];
        int found=0;
        while(h!=NULL)
        {
            if(h->x==v2)
            {
                found=1;break; //"found=1" if edge is found else "found=0"
            }
            h=h->next;
        }
        printf("%d\n",found);
}
int main()
{
    int digit;
    int fl=0;           //denotes the option taken i.e. 0 for 'N',1 for 'E' ,2 for 'B'...
    int fir=0;          //denotes the number of spaces after 'E' option
    int start;           //denotes the vertex whose adjacent nodes are inserted in adjacency list
    int vert=-1;           //total number of vertices in graph
    struct node* a[100001]; //array of pointers holding the head of adjacency list of a particular vertex
    int que[100001];        //array used for implementing queue
    int b[100001];          //temporary array to print the path
    int par[100001];       // holds the value of vertex just before that vertex in a shortest path from source node
    int fron=-1,rear=-1;
    bool visit[100001]={false}; //checks if node is visited or not
    struct node *prev=NULL;
    int j;
    int v1=-1,v2=-1;
    int prevdata=-1;        //stores previous source node for printing the path
    int data=0;
    for(j=0;j<=100000;j++)
    {
        a[j]=NULL;
    }
    while((digit=fgetc(stdin))!=EOF){
    int y=digit-48;
    if(digit=='N')
    {
        fl=0;
        for(j=0;j<=vert;j++)
            {
                if(a[j]!=NULL)
                    mydelete(a[j]);
                a[j]=NULL;
            }
    }
    else if(digit=='E')
    {
        fl=1;
    }
    else if(digit=='B')
    {
        fl=2;
    }
    else if(digit=='?')
    {
        fl=3;
    }
    else if(digit=='P')
    {
        fl=4;
    }
    if(digit=='\n' && fl==0){
        vert=data;                  //total number of vertices in graph
        int i;
        data=0;
    }
    else if(digit==' ' && fl==1){
            if(fir==0)              //for first space do nothing
            {
                fir=1;
            }
            else if(fir==1)            //second spaces gives the value of node whose adjacency list is followed
            {
                start=data;             //'start' holds the value of node whose adjacency list is followed
                fir=2;
                data=0;
            }
            else if(fir==2)            //after third space we get all the vertices which are adjacent to 'start' node
            {
                struct node *temp=new(struct node);
                temp->x=data;
                a[start]=temp;
                temp->next=NULL;
                prev=temp;
                data=0;
                fir=3;
            }
            else
            {
                struct node *t1=new(struct node);
                t1->x=data;
                t1->next=NULL;
                prev->next=t1;
                prev=t1;
                data=0;
            }
    }
    else if(digit=='\n' && fl==2)
    {
        int i;
        for(i=1;i<=vert;i++)
            visit[i]=false;
        while(!isempty(fron,rear))
            deq(&fron,&rear);
        bfs(data,visit,a,&fron,&rear,que); //bfs from given source vertex i.e.,data
        data=0;fl=-1;
    }
    else if(digit==' ' && fl==4)
    {
      if(data>0)
        v1=data;
      data=0;
    }
    else if(digit=='\n' && fl==4)
    {
        v2=data;
        path(v1,prevdata,v2,visit,que,par,&fron,&rear,b,a,vert); //prints a shortest path from v1 to v2 if exists
        prevdata=v1;
        data=0;
        fl=-1;
        v1=-1;v2=-1;
    }
    else if(digit=='\n' && fl==1)
    {
        if(fir==1)
        {
            start=data;
            a[start]=NULL;
        }
        else if(fir==2)
        {
                struct node *temp=new(struct node);
                temp->x=data;
                a[start]=temp;
                temp->next=NULL;
        }
        else
        {
                struct node *t1=new(struct node);
                t1->x=data;
                t1->next=NULL;
                prev->next=t1;
        }
        data=0;
        fir=0;
        fl=-1;
    }
    else if(digit==' ' && fl==3)
    {
        if(data>0)
        {
            v1=data;
            data=0;
        }
    }
    else if(digit=='\n' && fl==3)
    {
        v2=data;
        edge(v1,v2,a);  //checks if there is an edge between v1 and v2
        v1=-1;v2=-1;
        data=0;
    }
    else if(digit>='0' && digit<='9')
    {
        data=data*10+y;
    }
    }
    return 0;
}
