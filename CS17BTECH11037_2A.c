#include<stdio.h>
#include<stdlib.h>
struct node{
    int x;
    struct node *next;
    struct node *prev;
};
int l1=0,l2=0;
int ans=1;
struct node *head1=NULL;
struct node *head2=NULL;
void mydelete(struct node *p) //This function is used to delete nodes after each pair of 'a' and 'b'
{
    struct node *t2=p;
    while(p!=NULL)
    {
        t2=p;
        p=p->next;
        free(t2);
    }
}
void deletezero() // This function is used to delete leading zeros from input
{
    struct node *p=head1;
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
        l1--;
    }
    }
    p=head2;
    if(p!=NULL)
    {
    while(p->next!=NULL && p!=NULL)
    {
        p=p->next;
    }
    while(p->x==0 && p->prev!=NULL && p!=NULL)
    {
        (p->prev)->next=NULL;
        struct node *t1=p->prev;
        free(p);
        p=t1;
        l2--;
    }
    }
}
void findans()  //This function is used to compare two integers of arbitrary length.
{
    if(l1<l2)
    {
        ans=0;
    }
    else if(l1==l2)
    {
        struct node *t1=head1,*t2=head2;
        if(t1!=NULL)
        {
        while(t1->next!=NULL )
        {
            t1=t1->next;
        }
        }
        if(t2!=NULL)
        {
        while(t2->next!=NULL )
        {
            t2=t2->next;
        }
        }
        while(t1!=NULL && t2!=NULL)
        {
        if(t1->x < t2->x)
        {
            ans=0;return;
        }
        else if(t1->x > t2->x)
        {
            return;
        }
        t1=t1->prev;t2=t2->prev;
        }
    }
}
int main()
{
    int digit;
  int fl=0;
  while((digit=fgetc(stdin))!=EOF){
    int y=digit-48;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    if(digit=='\n'){
        fl=0;
        deletezero();
        findans();
        if(head1==NULL && head2==NULL)
        printf("\n");
        else
        printf("%d\n",ans);
        mydelete(head1);
        mydelete(head2);
        head1=NULL;
        head2=NULL;
        l1=0;l2=0;
        ans=1;
    }
    else if(digit==' '){
            fl=1;
    }
    else{
        if(fl==0)
        {
        if(head1!=NULL)
        {
        head1->prev=temp;
        }
        temp->next=head1;// Insertion takes place at head
        temp->prev=NULL;
        temp->x=y;
        head1=temp;
        l1++;
        }
    else
    {
        if(head2!=NULL)
        {
        head2->prev=temp;
        }
        temp->next=head2;// Insertion takes place at head
        temp->prev=NULL;
        temp->x=y;
        head2=temp;
        l2++;
    }
    }
  }
    return 0;
}
