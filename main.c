#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>

#define MAXLINE 100
#define NUMBER '0'
int my_getline(char line[], int lim);
int li=0;
char line[MAXLINE];
int getop(char s[]);

void push(double f);
double pop(void);

int main(){
    int type;
    double op2;
    char s[MAXLINE];

    while ((type=getop(s))!=EOF)
    {
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop()+pop());
            break; 
        case '-':
            op2=pop();
            push(pop()-op2);
            break;   
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    printf("End\n");
    return 0;
}

int my_getline(char line[], int lim)
{
    int i, c;
    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; i++){
        line[i]=c;
    }
    if(c=='\n'){
        line[i++]=c;
    }
    line[i]='\0';
    return i;
}

int getop(char s[])
{
    int c, i;
    if(line[li]=='\0'){
        if(my_getline(line,MAXLINE)==0){
            return EOF;
        }else{
            li=0;
        }
    }
    while ((s[0]=c=line[li++])==' ' || c=='\t');
    s[1]='\0';
    i=0;
    if(!isdigit(c) && c!='.' && c!='-'){
        return c;
    }

    if(c=='-'){
        if(isdigit(c=line[li++])){
            s[++i]=c;
        }else{
            if(c!=EOF){
                --li;
            }
            return '-';
        }
    }

    if(isdigit(c)){
        while (isdigit(s[++i]=c=line[li++]));       
    }
    if(c=='.'){
        while (isdigit(s[++i]=c=line[li++]));
    }
    s[i]='\0';
    li--;
    return NUMBER;
}

#define MAXVAL 100
int sp=0;
double val[MAXVAL];

void push(double f)
{
    if(sp<MAXVAL){
        val[sp++]=f;
    }else
    {
        printf("error: stack full, can't push %g\n", f);
    }
    
}

double pop(void)
{
    if(sp>0){
        return val[--sp];
    }else{
        printf("error: stack empty\n");
        return 0.0;
    }
}