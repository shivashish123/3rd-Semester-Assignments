#include<stdio.h>
#include<stdlib.h>
struct bst //structure for creating the binary search tree
{
    struct bst *left;
    struct bst *right;
    struct bst *parent;
    long long int val;
};
struct bst *root=NULL;
void deletebst(struct bst *p)//deletes the entire binary search tree
{
    if(p->left!=NULL)
    {
        deletebst(p->left);
    }
    if(p->right!=NULL)
    {
        deletebst(p->right);
    }
    free(p);
}
void myprint(struct bst *p)//prints the preorder traversal of binary search tree
{
    printf("%lld ",p->val);
    if(p->left!=NULL)
    myprint(p->left);
    if(p->right!=NULL)
    myprint(p->right);
}
void myinsert(struct bst *p, struct bst *par)//insert a node 'p' in binary search tree with parent 'par' is possible
{
    if(root==NULL)
    {
        root=p;
        return;
    }
        if(p->val==par->val)
            return;
        else if(p->val>par->val)
        {
            if(par->right==NULL)
            {
                par->right=p;
                p->parent=par;
            }
            else
            {
                myinsert(p,par->right);
            }
        }
        else
        {
            if(par->left==NULL)
            {
                par->left=p;
                p->parent=par;
            }
            else
            {
                myinsert(p,par->left);
            }
        }
}
int mysearch(int p,struct bst *b)//search for arbitrary large integer in binary search tree
{
    if(b==NULL)
        return 0;
    if(b->val==p)
    {
        return 1;
    }
    if(p<b->val && mysearch(p,b->left)==1)
    {
        return 1;
    }
    if(p>b->val && mysearch(p,b->right)==1)
    {
        return 1;
    }
    return 0;
}
void search2(int p , struct bst *b)//prints path to that searched element if present in binary search tree
{
    if(p==b->val)
    {printf("\n");return;}
    else if(p>b->val)
    {
        printf("1");
        search2(p,b->right);
    }
    else
    {
        printf("0");
        search2(p,b->left);
    }
}
struct bst *ans=NULL; //holds the successor node of given number
void findsucc(struct bst *b,int p) //returns the node with smallest value greater than 'p'
{
    if(p==b->val)
    {
        if(b->right!=NULL)
            return findsucc(b->right,p);
        return;
    }
    else if(p>b->val)
    {
        if(b->right!=NULL)
            return findsucc(b->right,p);
        return ;
    }
    else
    {
        ans=b;
        if(b->left==NULL)
        {
            return;
        }
        else
        {
          return findsucc(b->left,p);
        }

    }
}
struct bst* constree(int low,int high,int size,long long a[],int *indx) //construct a tree recursively from given pre-order traversal
{
    if(*indx>=size || high<low)
        return NULL;
    struct bst *temp=(struct bst*)malloc(sizeof(struct bst));
    temp->val=a[*indx];
    temp->parent=NULL;
    int i;
    *indx=*indx+1;
    for (i = low; i <= high; i++ )
        if ( a[i] > temp->val )
            break;
    // partition the array in two parts - one carrying values greater than a[*indx] which will form right subtree and rest will form left subtree
    struct bst *t1=constree(*indx,i-1,size,a,indx); //constructing left subtree
    struct bst *t2=constree(i,high,size,a,indx);    //constructing right subtree
    temp->left=t1;
    temp->right=t2;
    temp->parent=NULL;
    if(t1!=NULL)
    {
        t1->parent=temp;
    }
    if(t2!=NULL)
    {
        t2->parent=temp;
    }
    return temp;
}
struct bst* finddel(struct bst *b,int p) //find a node with value 'p' in it
{
    if(b==NULL)
        return b;
    if(p==b->val)
        return b;
    else if(p>b->val)
    {
        return finddel(b->right,p);
    }
    else
        return finddel(b->left,p);
}
void delnode(struct bst *b) //deleting a node in BST
{
    if(b==NULL)
        return;
    if(b->left==NULL && b->right==NULL) //no children
    {
        if(b==root)
          root=NULL;
        else if((b->parent)->left==b)
            (b->parent)->left=NULL;
        else
            (b->parent)->right=NULL;
        free(b);
    }
    else if(b->left==NULL) //one child(right)
    {
        if(b==root)
        {
          root=b->right;
          free(b);
        }
        else if((b->parent)->left==b)
        {
            (b->parent)->left=b->right;
            (b->right)->parent=b->parent;
            free(b);
        }
        else
        {
            (b->parent)->right=b->right;
            (b->right)->parent=b->parent;
            free(b);
        }
    }
    else if(b->right==NULL) //one child(left)
    {
        if(b==root)
        {
          root=b->left;
          free(b);
        }
        else if((b->parent)->left==b)
        {
            (b->parent)->left=b->left;
            (b->left)->parent=b->parent;
            free(b);
        }
        else
        {
            (b->parent)->right=b->left;
            (b->left)->parent=b->parent;
            free(b);
        }
    }
    else                    //two children
    {
        ans=NULL;
        findsucc(root,b->val);//deleted node is replaced by its successor
        b->val=ans->val;
        delnode(ans);
    }
}
void children(struct bst *t1) //t1 is the node whose children needs to be printed
{
    if(t1==NULL)
        {
            printf("-1\n");
        }
        else
        {
            if(t1->left==NULL)
                printf("Nil ");
            else
                printf("%lld ",(t1->left)->val);
            if(t1->right==NULL)
                printf("Nil\n");
            else
                printf("%lld\n",(t1->right)->val);
        }
}
void uncle(struct bst *t1) //t1 is the node whose uncle needs to be printed
{
    if(t1==NULL)
        {
            printf("-1\n");
        }
        else if(t1->parent==NULL) //print -1 when node is NULL, parent is NULL, grandparent is NULL,or uncle is NULL
        {
            printf("-1\n");
        }
        else if(((t1->parent)->parent)==NULL)
        {
            printf("-1\n");
        }
        else
        {
            struct bst* t2=t1->parent;
            struct bst* t3=(t1->parent)->parent;
            if((t3->left)==t2)
            {
                if((t3->right)==NULL)
                    printf("-1\n");
                else
                    printf("%lld\n",(t3->right)->val);
            }
            else
            {
                if((t3->left)==NULL)
                    printf("-1\n");
                else
                    printf("%lld\n",(t3->left)->val);
            }
        }
}
void leftrotate(struct bst *t1)//Left Rotation at given node(t1)
{
    if(t1!=NULL && ((t1->right)!=NULL))
        {
            struct bst *t2=t1->parent;
            struct bst *t3=t1->right;
            struct bst *t4=t3->left;
            t3->left=t1;
            t1->right=t4;
            t3->parent=t1->parent;
            t1->parent=t3;
            if(t2!=NULL)
            {
                if((t2->right)==t1)
                    t2->right=t3;
                else
                    t2->left=t3;
            }
            else
            {
                root=t3;
            }
            if(t4!=NULL)
                t4->parent=t1;

        }
}
void rightrotate(struct bst *t1)//Right rotation at given node(t1)
{
    if(t1!=NULL && ((t1->left)!=NULL))
        {
            struct bst *t2=t1->parent;
            struct bst *t3=t1->left;
            struct bst *t4=t3->right;
            t3->right=t1;
            t1->left=t4;
            t3->parent=t1->parent;
            t1->parent=t3;
            if(t2!=NULL)
            {
                if((t2->right)==t1)
                    t2->right=t3;
                else
                    t2->left=t3;
            }
            else
            {
                root=t3;
            }
            if(t4!=NULL)
                t4->parent=t1;
        }
}
int main()
{
    int digit;
    int fl=-1;              //contains the option chosen like 0 for 'N',1 for 'S'...
    int first=0;            //for first space in 'N' option which should be neglected
    int fir=0;              //for first space in 'B' option which should be neglected
    long long int data=0;   //contains the number formed by input digits
    int n=0;                //holds the number of elements in given pre-order traversal
    int indx;               //holds the index of element to be inserted in binary tree
    long long int a[100001];//contains the pre-order traversal of BST
    while((digit=fgetc(stdin))!=EOF){
    int y=digit-48;
    if(digit=='\n' && (fl==0 || fl==3)){
        struct bst *temp=(struct bst *)malloc(sizeof(struct bst)); //inserting node in BST
        temp->left=NULL;temp->right=NULL;
        temp->val=data;temp->parent=NULL;
        myinsert(temp,root);
        fl=-1;
        data=0;
    }
    else if(digit=='\n' && fl==1)
    {
         if(mysearch(data,root)==1) //finding an element in BST
        {
            search2(data,root);     //printing the path to that searched element ,if found
        }
        else
            printf("-1\n");
        data=0;
        fl=-1;
    }
    else if(digit=='\n' && fl==4)
    {
        ans=NULL;
        findsucc(root,data); //finds successor of given element
         if(ans==NULL)
            {
                printf("-1\n");
            }
        else
            {printf("%lld\n",ans->val);
            }
          fl=-1;
          data=0;
    }
    else if(digit=='N')
    {
       fl=0;first=0;
      if(root!=NULL)
        deletebst(root);
        data=0;
      root=NULL;
    }
    else if(digit=='S')
    {
        fl=1;
    }
    else if(digit=='P')
    {
      fl=2;
      if(root!=NULL)
        myprint(root);
        printf("\n");
    }
    else if(digit==' ' && fl==0 )
    {
        if(first!=0)
        {
        struct bst *temp=(struct bst *)malloc(sizeof(struct bst)); //inserting node in BST
        temp->left=NULL;temp->right=NULL;
        temp->val=data;temp->parent=NULL;
        myinsert(temp,root);
        data=0;
        }
        first=1;
    }
    else if(digit==' ' && fl==6)
    {
        if(fir==0)
            fir=1;
        else
        {
            a[n]=data; //inserting a number in pre-order traversal array
            data=0;
            n++;
        }
    }
    else if(digit=='\n' && fl==6)
    {
        a[n]=data;
        n++;
        indx=0;
        root=constree(0,n-1,n,a,&indx); //constructing tree based on given pre-order traversal
        data=0;
        fl=-1;
    }
    else if(digit=='\n' && fl==5)
    {
      struct bst *s=finddel(root,data); //Gives the node to be deleted
      delnode(s);
        data=0;
          fl=-1;
    }
    else if(digit=='\n' && fl==7)
    {
        struct bst* t1=finddel(root,data); //gives the node which contains the value 'data'
        children(t1);   //prints the children of node t1
        fl=-1;
        data=0;
    }
    else if(digit=='\n' && fl==8)
    {
        struct bst* t1=finddel(root,data); //gives the node which contains the value 'data'
        uncle(t1);
        data=0;
        fl=-1;
    }
    else if(digit=='\n' && fl==9)
    {
        struct bst* t1=finddel(root,data); //contains the node to be rotated
        leftrotate(t1);
        data=0;
        fl=-1;
    }
    else if(digit=='\n' && fl==10)
    {
        struct bst* t1=finddel(root,data); //contains the node to be rotated
        rightrotate(t1);
        data=0;
        fl=-1;
    }
    else if(digit=='+')
    {
        fl=3;
    }
    else if(digit=='>')
    {
        fl=4;
    }
    else if(digit=='-')
    {
        fl=5;
    }
    else if(digit=='B')
    {
        fl=6;fir=0;data=0;n=0;
        if(root!=NULL)
        deletebst(root);
        root=NULL;
    }
    else if(digit=='C')
    {
        fl=7;
    }
    else if(digit=='U')
    {
        fl=8;
    }
    else if(digit=='L')
    {
        fl=9;
    }
    else if(digit=='R')
    {
        fl=10;
    }
    else if(digit>='0' && digit<='9')
    {
        data=data*10+y;
    }
    }
    if(root!=NULL)
        deletebst(root); //Deleting the BST
    root=NULL;
    return 0;
}


