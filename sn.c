#include <stdio.h>
#include<stdlib.h>
struct food                                  //declare food
{
  int f,g;
  char val;
};
struct snake                            //declare  snake
{
  int x,y;
  char c;
  struct snake*next;
};
struct node         //struct for hashing
{
 int xco,yco;
 struct node*next;
};
struct poison                 //declare poison
{
int p1,p2;
char pois;
};
int level=1;
struct node*heading[10]={NULL};
struct snake* getsnakefromfile(struct snake*head,struct snake**tail,struct food*s,char mat[][30],int*score);
struct snake*eatfood(struct snake*head,struct snake*prev);
void makefood(char mat[][30],struct food *s,struct snake*head);  
struct snake* formsnake(struct snake*head,struct snake**tail,int len);                      //prototypes
void printsnake(char mat[][30],struct snake*head,int *score);
struct snake* move(struct snake*head,struct snake**tail,char mat[][30],struct food *s,int *score,char *c,struct poison*po);   

struct snake* formsnake(struct snake*head,struct snake**tail,int len)            //form initial snake
{
struct snake*u,*p,*i;
   char o;
   int t,key;
     for(int l=0;l<len-1;l++)
         {if(head==NULL)
  	    {
     		i= (struct snake*)malloc(sizeof(struct snake));  //creating head of snake(-_-)
    		i->x=5;
    		i->y=5;
                key=(i->x+i->y)%9;
                
                 struct node*dp=(struct node*)malloc(sizeof(struct node));
                   heading[key]=dp;
                 heading[key]->xco=i->x;
                 heading[key]->yco=i->y;
                 heading[key]->next=NULL;
                
    		t=i->x;
    		i->c='@';
          	head=i;
    		p=head;
            }
   	else
            {
     		u=(struct snake*)(malloc(sizeof(struct snake)));//body of snake
     		t++;
     		u->x=t;
		u->y=head->y;
                key=(u->x+u->y)%9;
                 struct node*kl=(struct node*)malloc(sizeof(struct node));
                 heading[key]=kl;
                 heading[key]->xco=u->x;
                 heading[key]->yco=u->y;
                 heading[key]->next=NULL;
	        u->c='|';
     		p->next=u;
     		u->next=NULL;
     		p=p->next;
   	    }
         }
struct snake*j;
 j=(struct snake*)malloc(sizeof(struct snake));
t++;
 j->x=t;
 j->y=head->y;
 j->c='Y';
 j->next=NULL;
 key=(j->x+j->y)%9;
struct node*ko=(struct node*)malloc(sizeof(struct node));
                 heading[key]=ko;
                 heading[key]->xco=j->x;
                 heading[key]->yco=j->y;
                 heading[key]->next=NULL;
 *tail=j;
 p->next=j;

return head;
}
void formboundaries(char mat [30][30])              //forming boundaries
{
	for(int i=0;i<30;i++)
		{
		for(int j=0;j<30;j++)
		{
		if(i==0 || i==29 || j==0 || j==29)
				{mat[i][j]='_';}	
		else
			{mat[i][j]=' ';}
		}
		}
}

struct snake*eatfood(struct snake*head,struct snake*prev)        //snake eat food
{int key;
	struct snake*n=(struct snake*)malloc(sizeof(struct snake));  //creating new node for snake
         struct snake*ptr=head;
           while(ptr->next!=NULL)
          {
            ptr=ptr->next;
          }	
        n->x=prev->x;
        n->y=prev->y;
	n->c='Y';
        key=(n->x+n->y)%9;
         if(heading[key]==NULL)
                {
                 struct node*kl=(struct node*)malloc(sizeof(struct node));
                 heading[key]=kl;
                 heading[key]->xco=head->x;
                 heading[key]->yco=head->y;
                 heading[key]->next=NULL;
                }
                else
                {
                 struct node*id=heading[key];
		while(id->next!=NULL)
		{
		id=id->next;
		}
		struct node*n=(struct node*)malloc(sizeof(struct node));
		id->next=n;
		n->yco=head->y;
                n->xco=head->x;
		n->next=NULL;
                }
	ptr->next=n;
        ptr->c='|';
	n->next=NULL;
	return head;
}


void makefood(char mat[][30],struct food *s,struct snake*head)       //assign value to food
{	s->val='g';
	s->g=rand() %29;
	s->f=rand() %29;
	int flag=0;
	struct snake *ptr=head;
         int k=(s->f+s->g)%9;
struct node*u=heading[k];
	while(u!=NULL)
		{
			if(u->xco==s->f && u->yco==s->g)
				{
					flag=1;
					break;
				}
		u=u->next;
		}
	if(flag==1 || s->f==28 || s->g==28 || s->g==0 || s->f==0)
	{
	makefood(mat,s,head);  //recursive call until food gets a value
	}
	else
	{
	mat[s->f][s->g]=s->val;
	}
}
void make_poison(char mat[][30],struct poison*ds)
{
ds->pois='M';
ds->p1=rand()%29;
ds->p2=rand()%29;
	if(mat[ds->p1][ds->p2]==' ')
		{
		mat[ds->p1][ds->p2]=ds->pois;
		return;
		}
	else
		{
		make_poison(mat,ds);
		}

}
int constrtonum(char*str,int*i,char k)
{int sum=0;
int g=*i;
int d;
	while(str[g]!=k)
	{
	d=str[g]-48;
	sum=sum*10+d;
	g++;
	}
*i=g;
return sum;
}
struct snake* getsnakefromfile(struct snake*head,struct snake**tail,struct food*s,char mat[][30],int*score)
{int a,b,i=0,key;
struct snake*p,*n,*u;
int d=0,sum=0;
FILE*f;
f=fopen("snakesgame.txt","r");
char str[1000];
fscanf(f,"%[^\n]s",str);  //converting file to string
fclose(f);
sum=constrtonum(str,&i,',');  //loading previous game
i++;
s->f=sum;
sum=constrtonum(str,&i,'#');
s->g=sum;
mat[s->f][s->g]='g';
i++;
while(str[i]!='s')
{sum=0;
sum=constrtonum(str,&i,',');
a=sum;
sum=0;
i++;
sum=constrtonum(str,&i,'-');
b=sum;
i++;
if(head==NULL)
  	    {
     		n= (struct snake*)malloc(sizeof(struct snake));  //creating head of snake(-_-)
    		n->x=a;
    		n->y=b;
                     key=(n->x+n->y)%9;     //updating hash table
                 struct node*kl=(struct node*)malloc(sizeof(struct node));
                 heading[key]=kl;
                 heading[key]->xco=n->x;
                 heading[key]->yco=n->y;
                 heading[key]->next=NULL;
    		n->c='@';
          	head=n;
    		p=head;
            }
   	else
            {
     		u=(struct snake*)(malloc(sizeof(struct snake)));//body of snake
     		u->x=a;
		u->y=b;
                key=(u->x+u->y)%9;
                 if(heading[key]==NULL)
                {
                 struct node*kl=(struct node*)malloc(sizeof(struct node));
                 heading[key]=kl;
                 heading[key]->xco=u->x;
                 heading[key]->yco=u->y;
                 heading[key]->next=NULL;
                }
                else
                {
                 struct node*id=heading[key];
		while(id->next!=NULL)
		{
		id=id->next;
		}
		struct node*l=(struct node*)malloc(sizeof(struct node));
		l->yco=u->y;
                l->xco=u->x;
                id->next=l;
		l->next=NULL;
                }	                
	        u->c='|';
     		p->next=u;
     		u->next=NULL;
     		p=p->next;
   	    }
}
struct snake*t=head;
while(t->next!=NULL)
{
t=t->next;
}
t->c='Y';
*tail=t;
i++;
sum=constrtonum(str,&i,'\0');
*score=sum;
return head;
}
void showmine(char mat[][30],struct poison*ds)
{
mat[ds->p1][ds->p2]=ds->pois;
}
struct snake* move(struct snake*head,struct snake**tail,char mat[][30],struct food *s,int *score,char *c,struct poison*po)           //move
{        struct snake*prev;
	int flag=0,key,xcord=0,ycord=0;
	char sd;
	int a=0,b=0,e=0,d=0;
struct snake *ptr=head;
	do
	{   
                if(head->x+1==s->f || head->y+1==s->g || head->x-1==s->f || head->y-1==s->g)
                {
		prev=*tail;
		
                }
		if(head->x==s->f && head->y==s->g)
		{(*score)++;
			if((*score)==10 && (*score)<20)                                //increasing levels
			{
				showmine(mat,po);
				level=2;
				make_poison(mat,po);
				printsnake(mat,head,score);
			}
			else if(*score==20 && *score<30)
			{
				level=3;
					
			}
                  makefood(mat,s,head); 
		head=eatfood(head,prev);
                 struct snake*new=head;
		        while(new->next!=NULL)
		        {
		         new=new->next;
		        }
                *tail=new;
		
		/*printsnake(mat,head,score);*/
		}
		
		
		else if(head->x!=s->f || head->y!=s->g)
		{
		a=head->x;
                b=head->y;
		        if(*c=='a')
		        {
		         head->y=head->y-1;
		        }
		        else if(*c=='d')
		        {
		        head->y=head->y+1;
		        }
		        else if(*c=='s')
		        {
		        head->x=head->x+1;
		        }
		        else if(*c=='w')
		        {
		         head->x=head->x-1;
		        }
      		ptr=head->next;
			while(ptr!=NULL)
			{e=ptr->x;
			d=ptr->y;
			if(ptr->next==NULL)
			{
                        key=(ptr->x+ptr->y)%9;
                        struct node*ki=heading[key];
		                while(ki!=NULL)
		                {
		                 if(ki->xco==ptr->x && ki->yco==ptr->y)
		                 {
		                  ki=NULL;
		                  break;
		                  }
		                 ki=ki->next;
		                }
			mat[ptr->x][ptr->y]=' ';
			}
			ptr->x=a;
			ptr->y=b;
			a=e;
			b=d;
			ptr=ptr->next;
			} 
                if((head->x==0 || head->x==29 || head->y==0 || head->y==29) && *score<=20)
		{ptr=head->next->next;
		 if(*c=='a')
                {
                 head->y=28;
                }
                else if(*c=='d')
                {
                head->y=1;
                }
                else if(*c=='s')
                {
                head->x=1;
                }
                else if(*c=='w')
                {
                 head->x=28;
                }
                }
		else if(*score>20 && (head->x==0 || head->x==29 || head->y==0 || head->y==29))
		{
			system("clear");
			printf("GAMEOVER");
		                 printf("\nscore:%d",*score);
			exit(0);
		}
                   key=(head->x+head->y)%9;     //updating hash table
                 if(heading[key]==NULL)
                {
		         struct node*kl=(struct node*)malloc(sizeof(struct node));
		         heading[key]=kl;
		         heading[key]->xco=head->x;
		         heading[key]->yco=head->y;
		         heading[key]->next=NULL;
		        printsnake(mat,head,score);
                }
                else
                {
                 	struct node*id=heading[key];
				while(id->next!=NULL)
				{
				id=id->next;
				}
			struct node*n=(struct node*)malloc(sizeof(struct node));
			id->next=n;
			n->yco=head->y;
		        n->xco=head->x;
			n->next=NULL;
                }
			if(*score>=10)
			{
			if(head->x==po->p1 && head->y==po->p2)
			{system("clear");
			printf("GAMEOVER");
		                 printf("\nscore:%d",*score);
			exit(0);
			}
			}
	  	
                	printsnake(mat,head,score);
		}
       		scanf(" %c",&sd);
                *c=sd;
	}while(sd=='w' || sd=='a' || sd=='s' || sd=='d');
*c=sd;
return head;
}
void printsnake(char mat[][30],struct snake*head,int *score)           //print board
{ 	system("clear");
	printf("\nLevel:%d\n",level);
 int yk,hj;
	struct snake*ptr=head;
        struct node*g,*h;
                mat[head->x][head->y]=head->c;
                hj=(head->x+head->y)%9;
                g=heading[hj];
                while(g!=NULL)
                {
                    if(g->xco==head->x && g->yco==head->y)
                    {
                     break;
                    } 
                   g=g->next;
                }
                ptr=ptr->next;
 		while(ptr!=NULL)      //assigning value to matrix/board
		{
			mat[ptr->x][ptr->y]=ptr->c;
                        yk=(ptr->x+ptr->y)%9;
                         h=heading[yk];
                                 while(h!=NULL)
                                {
				    if(h->xco==ptr->x && h->yco==ptr->y)
				    {
				     break;
				    } 
				   h=h->next;
                                 }
                        if(g->xco==h->xco && g->yco==h->yco)
                        {
                         printf("GAMEOVER");
                         printf("\nscore:%d",*score);
                         exit(0);
                        }
			ptr=ptr->next;
		}
	
               printf("   save game-x                      score-%d\n",*score);
  	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			printf(" %c",mat[i][j]);
		}
		printf("\n");
	}
printf("\ta-right \t d-left \t w-up \t s-down\n");
printf("directions:");
}
void contostring(char *savestring,char *nam,int *i)  //saves number to string.
{int e=0;
int r=*i;
  while(nam[e]!='\0')
        {
        savestring[r]=nam[e];
        e++;
        r++;
        }
   *i=r;
}
int main()
{
	int score=0,len=0;
	struct food s;
	struct poison po;
	char c,option,mat[30][30];
	struct snake*head=NULL;
 	struct snake*tail=NULL;
	formboundaries(mat);        //forming board
	printf("How to play:-\ng-Score increases\nM-If you touch it,GaMeOvEr\nControls-w,a,s,d\n\n");
	
	printf("continue saved game-y\nPlay new-n\n");
	scanf(" %c",&option);

		if(option=='n')                //start afresh
		{
			printf("choose your initial length:");
			scanf("%d",&len);
			head=formsnake(head,&tail,len);
			makefood(mat,&s,head);
			
		}
		else if(option=='y')                  //previous game
		{
			head=getsnakefromfile(head,&tail,&s,mat,&score);
		}
 	printsnake(mat,head,&score);
	scanf(" %c",&c);
	while(1)
	{
		if(c=='h')
		{
			printf("GAMEOVER\n");
			printf("___SCORE____:%d\n",score);
			break;
		}
		if(c=='a' || c=='s' || c=='w' || c=='d')
		{
			head=move(head,&tail,mat,&s,&score,&c,&po);          //moving in right dir
		}
		 if(c=='x')         //saving in file
		{
			int e=0,i=0;      
			 char nam[4];
			FILE*fp;
			fp=fopen("snakesgame.txt","w");
			char savestring[100];
			sprintf(nam, "%d",s.f); //convert num to string.
			contostring(savestring,nam,&i);
			 nam[0]='\0';
			   sprintf(nam, "%d",s.g);
			savestring[i]=',';
			i++;
			contostring(savestring,nam,&i);
			  nam[0]='\0';
			savestring[i]='#';
			i++;
			while(head!=NULL)
			{
				sprintf(nam, "%d", head->x);
				 contostring(savestring,nam,&i);
				savestring[i]=',';
				nam[0]='\0';
				i++;
				sprintf(nam, "%d", head->y);
				contostring(savestring,nam,&i);
				nam[e]='\0';
				savestring[i]='-';
				i++;
				head=head->next;
			}
			savestring[i]='s';
			i++;
			 sprintf(nam,"%d",score);
		       contostring(savestring,nam,&i);
			savestring[i]='\0';        
			fprintf(fp,"%s", savestring);  
			printf("\nyour game is saved!!\n");
			fclose(fp);
			exit(0);
		}
	}
    return 0;
}


