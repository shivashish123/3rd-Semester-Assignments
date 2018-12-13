#include<bits/stdc++.h>
using namespace std;
#define INF 1e9+7 //maximum distance
struct node{
    int v,distance;  //structure for holding the minimum 'distance' of that vertex 'v' from source node
};
struct adj{
    int v,weight;  //structure for adjacency list along with weight of each edge
    adj* next;
};
void min_heapify (node arr[ ], int i, int N)
{
    int left = 2*i;                   //left child
    int right = 2*i +1 ;             //right child
    int small;
    if(left<= N and arr[left].distance < arr[i].distance )
          small = left;
    else
         small = i;
    if(right <= N and arr[right].distance < arr[small].distance ) //find the smallest among left and right child and parent
        small = right;
    if(small != i )             //if smallest is not parent then swap smallest child with parent
    {
        swap (arr[i] ,arr[small]);
        min_heapify (arr, small,N);
    }
 }
 void build_minheap (node arr[ ],int N)//create min-heap of given arr values according to the minimum distance of that vertex from source node
{
    int i;
    for(i = (N/2) ; i >= 1 ; i-- )
    {
        min_heapify (arr,i,N) ;
    }
}
node extract_min(node arr[],int *N) //returns the minimum value of heap and delete it from the heap
{
    node mini = arr[1];   //first element is the smallest
    arr[1].distance = arr[*N].distance;
    arr[1].v= arr[*N].v;
    *N=*N-1;
    min_heapify(arr,1,*N);
    return mini;
}
void edge(int v1,int v2,adj *a[]) //prints weight of edge v1 to v2 if it exists else -1
{
    adj *temp=a[v1];
    int flag=0;
    while(temp!=NULL)
    {
        if(temp->v==v2)
        {
            cout<<temp->weight<<endl;
            flag=1;break;
        }
        temp=temp->next;
    }
    if(flag==0)
    {
        cout<<-1<<endl;
    }
}
void decrease_key(int vertex,int value,node arr[],int N) //decreases distance of a 'vertex' to 'value' in the heap
{
    int j;
    for(j=1;j<=N;j++)
    {
        if(arr[j].v==vertex)
        {
            arr[j].distance=value;
            while(j>1 && arr[(j/2)].distance>arr[j].distance) //if decreasing the value, violates the property of heap then swap with its parent
            {
                swap(arr[j],arr[(j/2)]);
                j=j/2;
            }
            break;
        }
    }
}
void dij(int v,adj *a[],node arr[],int vert,bool visit[],int par[],int d[]) //runs Dijkstra’s algorithm from v
{
    int N=vert;
    while(N>0)
    {
        node u=extract_min(arr,&N);   //extracts node with minimum distance
        if(u.distance!=INF)
        cout<<u.v<<" "<<u.distance<<endl;  //print the node with distance
        else
        cout<<u.v<<" "<<-1<<endl;
        visit[u.v]=true;
        adj *temp=a[u.v];
        while(temp!=NULL)
        {
            if(!visit[temp->v])   //decreasing the distance of adjacent nodes using edge weight and distance of extracted vertex 'u.v'
            {
                if((d[u.v]+temp->weight)<d[temp->v])
                {
                    d[temp->v]=d[u.v]+temp->weight;
                    decrease_key(temp->v,d[temp->v],arr,N);
                    par[temp->v]=u.v;
                }
            }
            temp=temp->next;
        }
    }
}
void mydelete(adj *p)// deletes all the node in linked list with head p
{
    adj *t2=p;
    while(p!=NULL)
    {
        t2=p;
        p=p->next;
        delete t2;
    }
}
void path(int v1,int v2,adj *a[],node arr[],int par[],bool visit[],int vert,int d[],int prevdata,int b[]) //prints shortest path from v1 to v2
{
    int N=vert;
    int i;
    if(prevdata!=v1)  //if Dijkstra’s algorithm is already performed on v1 then we just print the path else perform Dijkstra’s algorithm on v1
    {
    for(i=1;i<=vert;i++)
        {
            arr[i].v=i;
            arr[i].distance=INF;
            d[i]=INF;
            visit[i]=false;
            par[i]=-1;
        }
        arr[v1].distance=0;
        d[v1]=0;
        build_minheap (arr,vert);
    while(N>0)
    {
        node u=extract_min(arr,&N);
        visit[u.v]=true;
        adj *temp=a[u.v];
        while(temp!=NULL)
        {
            if(!visit[temp->v])
            {
                if((d[u.v]+temp->weight)<d[temp->v])
                {
                    d[temp->v]=d[u.v]+temp->weight;
                    decrease_key(temp->v,d[temp->v],arr,N);
                    par[temp->v]=u.v;
                }
            }
            temp=temp->next;
        }
    }
    }
    if(d[v2]==INF)
    {
        cout<<-1<<endl;return;
    }
    cout<<d[v2]<<" ";
    int s=v2;
    int l=0;
    while(s!=v1)
    {
        b[l++]=s;
        s=par[s];  //storing the parents of vertices from v2 and then print in backward direction
    }
    b[l++]=v1;
    for(i=l-1;i>=0;i--)
    {
        cout<<b[i]<<" ";
    }
    cout<<endl;
}
int main()
{
int digit;
    int fl=0;           //denotes the option taken i.e. 0 for 'N',1 for 'E' ,2 for 'B'...
    int fir=0;          //denotes the number of spaces after 'E' option
    int start;           //denotes the vertex whose adjacent nodes are inserted in adjacency list
    int vert=-1;           //total number of vertices in graph
    adj* a[100001];     //array of pointers holding the head of adjacency list of a particular vertex
    node arr[100001];          //temporary array to print the path
    int d[100001];             //holds the minimum distance of a vertex from source node
    int par[100001];       // holds the value of vertex just before that vertex in a shortest path from source node
    int b[1000001];             //used for printing a shortest path from v1 to v2
    bool visit[100001]={false}; //checks if node is visited or not
    adj *prev=NULL;             //used for inserting a node after the previous node in linked list
    int j;
    int des;
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
    else if(digit=='?')
    {
        fl=2;
    }
    else if(digit=='D')
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
        for(i=0;i<=vert;i++)
            {
              if(a[i]!=NULL)
              mydelete(a[i]);
                a[i]=NULL;
            }
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
            else if(fir==2)
            {
                des=data;
                data=0;
                fir=3;
            }
            else if(fir==3)            //after third space we get all the vertices which are adjacent to 'start' node and the edge weight alternatively
            {
                adj *temp=new adj;
                temp->v=des;
                temp->weight=data;
                a[start]=temp;
                temp->next=NULL;
                prev=temp;
                data=0;
                fir++;
            }
            else if(fir%2==1) //before even space we get edge weight which is inserted in adjacency linked list along with vertex
            {
                adj *t1=new adj;
                t1->v=des;
                t1->weight=data;
                t1->next=NULL;
                prev->next=t1;
                prev=t1;
                data=0;
                fir++;
            }
            else //before odd space gives the adjacent vertex
            {
                des=data;
                data=0;
                fir++;
            }
    }
    else if(digit==' ' && fl==2)
    {
      if(data>0)
        v1=data;
      data=0;
    }
    else if(digit=='\n' && fl==2)
    {
        edge(v1,data,a);   //prints weight of edge v1 to v2 if it exists else -1
        data=0;fl=-1;
    }
    else if(digit=='\n' && fl==3)
    {
        int i;
        for(i=1;i<=vert;i++)
        {
            arr[i].v=i;
            arr[i].distance=INF;
            d[i]=INF;
            visit[i]=false;
            par[i]=-1;
        }
        arr[data].distance=0;
        d[data]=0;
        build_minheap (arr,vert);    //build the min heap
        dij(data,a,arr,vert,visit,par,d); //performs Dijkstra’s algorithm on the given vertex
        prevdata=data;                   //stores the vertex for consecutive access of same vertex
        data=0;fl=-1;
    }
    else if(digit=='\n' && fl==1)
    {
        if(fir==1)    //adjacency list contains no vertex i.e. node is isolated
        {
            start=data;
            a[start]=NULL;
        }
        else if(fir==3)   //only one element is adjacent to the node
        {
                adj *temp=new adj;
                temp->v=des;
                temp->weight=data;
                a[start]=temp;
                temp->next=NULL;
                prev=temp;
        }
        else
        {
                adj *t1=new adj;
                t1->v=des;
                t1->weight=data;
                t1->next=NULL;
                prev->next=t1;
                prev=t1;
                fir++;
        }
        data=0;
        fir=0;
        fl=-1;
    }
    else if(fl==4 && digit==' ')
    {
        if(data>0)
            v1=data;
        data=0;
    }
    else if(fl==4 && digit=='\n')
    {
        v2=data;
        path(v1,v2,a,arr,par,visit,vert,d,prevdata,b);//prints shortest path from v1 to v2
        prevdata=v1;    //stores the vertex for consecutive access of same vertex
        data=0;
        fl=-1;
    }
    else if(digit>='0' && digit<='9')
    {
        data=data*10+y;
    }
    }
     for(j=0;j<=100000;j++)  //delete all the adjacency lists
        {
        if(a[j]!=NULL)
            mydelete(a[j]);
         a[j]=NULL;
        }
    return 0;
}
