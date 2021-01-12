#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct  { int data[MAX]; int top;}stack;


void initialize(stack *);
int pop(stack *);
void push(stack *, int );
int top (stack *);
int isempty (stack *);
int isfull (stack *);
int evaluate_postfix(char *);
int evaluate(char ,int ,int );
void infix_to_postfix(char infix[],char postfix[]);
int prec(char );


void main()
{
    char infix[50],postfix[50];
    int result;
    printf("enter your infix expression : ");
    gets(infix);
    infix_to_postfix(infix,postfix);
    result = evaluate_postfix(&postfix);
    printf("\n postfix expression is : %s",postfix);
    printf("\n value of expression is : %d",result);

}


void initialize (stack *s)
{
    s->top=-1;
}
int pop (stack *s)
{
    if (isempty(s))
    {
        printf("stack empty");
    }
    else
    {
        s->top--;
    return s->data[s->top];
    }
}
void push (stack *s,int v)
{
    if (isfull(s))
    {
        printf("stack full");
    }
    else
    {
        s->data[s->top]=v;
    s->top++;
    }
}
int top (stack *s)
{
    return s->data[s->top-1];
}
int isempty (stack *s)
{
    if (s->top==-1)
        return 1;
    else
        return 0;
}
int isfull (stack *s)
{
    if (s->top==MAX-1)
        return 1;
    else
        return 0;
}
int evaluate_postfix(char *exp)
{
    stack s;
    int op1,op2,v;
    initialize (&s);
    int i;
    for(i=0; i<strlen(exp);i++)
    {
        if(isdigit(exp[i]))
            push(&s,exp[i]-'0');
        else
        {
            op2=pop(&s);
            op1=pop(&s);
            v=evaluate(exp[i],op1,op2);
            push(&s,v);
        }
    }
    v=pop(&s);
    return v;
}
int evaluate(char x,int op1,int op2)
{
    if(x=='+')
    {
        return (op1+op2);
    }
    if(x=='-')
    {
        return (op1-op2);
    }
    if(x=='*')
    {
        return (op1*op2);
    }
    if(x=='/')
    {
        return (op1/op2);
    }
    if(x=='%')
    {
        return (op1%op2);
    }
}
void infix_to_postfix(char infix[],char postfix[])
{
   stack s;
   char y,t;
   int i,j;
   initialize(&s);
   j=0;
   for (i=0;infix[i]!='\0';i++)
   {
       t=infix[i];
       if(isalnum(t))
        postfix[j++]=t;
       else
        if(t=='(')
           push(&s,'(');
       else
        if(t==')')
        while((y=pop(&s))!='(')
              postfix[j++]=y;
       else
       {
           while(prec(t)<=prec(top(&s))&&!isempty(&s))
           {
               y=pop(&s);
               postfix[j++]=y;
           }
           push(&s,t);
       }
   }
   while(!isempty(&s))
   {
       y=pop(&s);
       postfix[j++]=y;
   }
   postfix[j]='\0';

}
int prec(char y)
{
    if(y=='(')
        return(0);
    if(y=='+'||y=='-')
        return(1);
    if(y=='*'||y=='/'||y=='%')
        return(2);


    return(3);
}



