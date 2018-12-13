#include <stdio.h>
#include <stdlib.h>
struct node{
    int x;
    struct node *next;
    struct node *prev;
};
struct node *head1=NULL;
struct node *head2=NULL;
struct node *head3=NULL;
void mydelete(struct node *p)
{
    struct node *t2=p;
    while(p!=NULL)
    {
        t2=p;
        p=p->next;
        free(t2);
    }
}
void sum()
{
    struct node *t1=head1,*t2=head2;
    int carry=0;
    while(t1!=NULL && t2!=NULL)
    {
        int s1=t1->x+t2->x+carry;
        carry=s1/10;
        int r=s1%10;
        struct node *temp1=(struct node *)malloc(sizeof(struct node));
        if(head3!=NULL)
        {
        temp1->next=head3;
        head3->prev=temp1;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        else
        {
            head3=temp1;
            temp1->x=r;
            temp1->next=NULL;
            temp1->prev=NULL;
        }
        t1=t1->next;
        t2=t2->next;
    }
    while(t1!=NULL)
    {
        int s1=t1->x+carry;
        carry=s1/10;
        int r=s1%10;
        struct node *temp1=(struct node *)malloc(sizeof(struct node));
        if(head3!=NULL)
        {
        temp1->next=head3;
        head3->prev=temp1;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        else
        {
            temp1->next=head3;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        t1=t1->next;
    }
    while(t2!=NULL)
    {
        int s1=t2->x+carry;
        carry=s1/10;
        int r=s1%10;
        struct node *temp1=(struct node *)malloc(sizeof(struct node));
        if(head3!=NULL)
        {temp1->next=head3;
        head3->prev=temp1;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        else
        {
        temp1->next=head3;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        t2=t2->next;
    }
    while(carry!=0)
    {
        int r=carry%10;
        struct node *temp1=(struct node *)malloc(sizeof(struct node));
        if(head3!=NULL)
        {
        temp1->next=head3;
        head3->prev=temp1;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        else
        {
        temp1->next=head3;
        temp1->prev=NULL;
        temp1->x=r;
        head3=temp1;
        }
        carry=carry/10;
    }
}
void print()
{
    struct node *t=head3;
    int ul=0;
    while(t!=NULL)
    {
        if(t->x==0 && ul==0 && t->next==NULL)
        {
        printf("%d",t->x);
        }
        else if(t->x!=0)
        {
            printf("%d",t->x);
            ul=1;
        }
        else if(t->x==0 && ul==1)
        {
            printf("%d",t->x);
        }
        t=t->next;
    }
}
int main(){
  int digit;
  int fl=0;
  while((digit=fgetc(stdin))!=EOF){
    int y=digit-48;
    struct node *temp=(struct node *)malloc(sizeof(struct node));
    if(digit=='\n'){
        fl=0;
        sum();
        print();
        printf("\n");
        mydelete(head1);
        mydelete(head2);
        mydelete(head3);
        head1=NULL;
        head2=NULL;
        head3=NULL;
    }
    else if(digit==' '){
            fl=1;
    }
    else{
        if(fl==0)
    {
        if(head1!=NULL)
        {
        temp->next=head1;
        head1->prev=temp;
        temp->prev=NULL;
        temp->x=y;
        head1=temp;
        }
        else
        {
        temp->next=head1;
        temp->prev=NULL;
        temp->x=y;
        head1=temp;
        }
    }
    else
    {
        if(head2!=NULL)
        {
        temp->next=head2;
        head2->prev=temp;
        temp->prev=NULL;
        temp->x=y;
        head2=temp;
        }
        else
        {
        temp->next=head2;
        temp->prev=NULL;
        temp->x=y;
        head2=temp;
        }
    }
    }
  }
  return(0);
}
