//This program allows arbitrary size integers.
#include<stdio.h>
#include<stdlib.h>
int isequal=0,isgreat=0;
struct node //structure for each node in the linked list(for arbitrary large numbers)
{
    int x;
    struct node* next;
    struct node* prev;
};
struct bst //structure for creating the binary search tree
{
    struct bst *left;
    struct bst *right;
    struct bst *parent;
    struct node *val;
};
struct bst *root=NULL;
void deletezero(struct node *p) //deletes all leading zeros in input
{
    if(p!=NULL)
    {
    while(p->next!=NULL )
    {
        p=p->next;
    }
    while(p->x==0 && p->prev!=NULL)
    {
        (p->prev)->next=NULL;
        struct node *t1=p->prev;
        free(p);
        p=t1;
    }
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
    mydelete(p->val);
    free(p);
}
void print(struct node *p)//prints all the node in linked list
{
    while(p->next!=NULL)
    {
        p=p->next;
    }
    while(p!=NULL)
    {
        printf("%d",p->x);
        p=p->prev;
    }
}
void myprint(struct bst *p)//prints the preorder traversal of binary search tree
{
    print(p->val);
     printf(" ");
    if(p->left!=NULL)
    myprint(p->left);
    if(p->right!=NULL)
    myprint(p->right);
}
void equal(struct node *p1,struct node *p2)//compares two arbitrary large numbers
{
    isequal=0;
    isgreat=0;
    int l1=0,l2=0;
    while(p1->next!=NULL)
    {
        p1=p1->next;
        l1++;
    }
    while(p2->next!=NULL)
    {
        p2=p2->next;
        l2++;
    }
    if(l1>l2)
    {
      isgreat=1;return;
    }
    else if(l1<l2)
    {
      return;
    }
    int cl=0;
    while(p1!=NULL && p2!=NULL)
    {
        if(p1->x > p2->x)
        {
            isgreat=1;
            return;
        }
        if(p1->x < p2->x)
        {
            return;
        }
        p1=p1->prev;
        p2=p2->prev;
    }
    isequal=1;
}
void insert(struct bst *p, struct bst *par)//insert a arbitrary large integer(linked list) in binary search tree
{
    if(root==NULL)
    {
        root=p;
        return;
    }
    equal(p->val,par->val);
        if(isequal==1)
            return;
        else if(isgreat==1)
        {
            if(par->right==NULL)
            {
                par->right=p;
                p->parent=par;
            }
            else
            {
                insert(p,par->right);
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
                insert(p,par->left);
            }
        }
}
int search(struct node *p,struct bst *b)//search for arbitrary large integer in binary search tree
{
    if(p==NULL || b==NULL)
        return 0;
    equal(b->val,p);
    if(isequal==1)
    {
        return 1;
    }
    if(isgreat==1 && search(p,b->left)==1)
    {
        return 1;
    }
    if(isgreat==0 && search(p,b->right)==1)
    {
        return 1;
    }
    return 0;
}
void search2(struct node *p , struct bst *b)//prints path to that searched element if present in binary search tree
{
    equal(p,b->val);
    if(isequal==1)
    {printf("\n");return;}
    else if(isgreat==1)
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
int main()
{
    int digit;
    int fl=-1;
    int newl=0;
    int first=0;
    struct node *head=NULL;
    while((digit=fgetc(stdin))!=EOF){
    int y=digit-48;
    if(digit=='\n' && fl==0){
        if(head!=NULL)
        {
        struct bst *temp=(struct bst *)malloc(sizeof(struct bst));
        deletezero(head);
        temp->left=NULL;temp->right=NULL;
        temp->val=head;temp->parent=NULL;
        head=NULL;
        insert(temp,root);
        }
        fl=-1;
    }
    else if(digit=='\n' && fl==1)
    {
        deletezero(head);
         if(search(head,root)==1)
        {
            search2(head,root);
        }
        else
            printf("-1\n");
        if(head!=NULL)
        mydelete(head);
            head=NULL;
    }
    else if(digit=='N')
    {
       fl=0;first=0;
      if(root!=NULL)
        deletebst(root);
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
        newl=1;
        if(first!=0)
        {
        if(head!=NULL)
        {
        struct bst *temp=(struct bst *)malloc(sizeof(struct bst));
        deletezero(head);
        temp->left=NULL;temp->right=NULL;
        temp->val=head;temp->parent=NULL;
        insert(temp,root);
        head=NULL;
        }
        }
        first=1;
    }
    else if(digit>='0' && digit<='9')
    {
        struct node *temp1=(struct node *)malloc(sizeof(struct node));
        if(newl==1)
        {
            newl=0;
        }
        temp1->x=(digit-48);
        temp1->next=head;//insertion takes place at head
        temp1->prev=NULL;
        if(head!=NULL)
            head->prev=temp1;
        head=temp1;
    }
    }
    if(head!=NULL)
        mydelete(head);
            head=NULL;
    if(root!=NULL)
        deletebst(root);
    root=NULL;
    return 0;
}
//This program allows arbitrary size integers.
