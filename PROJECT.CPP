
//Various data encoding techniques

# include <graphics.h>
# include <iostream.h>
#include<stdio.h>
# include <conio.h>
# include <string.h>
# include <dos.h>
#include<string.h>
#include<time.h>
#include<fstream.h>
#include<stdlib.h>

int main(void)
{
	void about();
	void border();
   void drawgrid(int, int, int, int);
   void encode(char *,char *, int, int, int, int);
   void draw(int ,int ,char *, int);

   about();


   char *message;
   int len;

   clrscr();
   cout << "DIGITAL ENCODING TECHNIQUES";
   cout << "Enter the data to be encoded (max 24 bits) :\n ";

   do{
   cin >> message;
   len = strlen(message);
   if(len>24)
     cout << "Message is greater than 12 bits, please type new message: ";
   }while(len>24);

   char *o_mess =new char[len];
   char *e_mess =new char[len*2];
   strcpy(o_mess,message);

   int gd=DETECT, gm, i, x, y;

   initgraph(&gd,&gm,"..\BGI");
   setcolor(8);
   settextstyle(DEFAULT_FONT,0,2);
   outtextxy(100,10,"DIGITAL ENCODING TECHNIQUES");
   setcolor(YELLOW);
   rectangle(0,30,630,450);
   rectangle(1,31,629,449);
   setcolor(WHITE);
   settextstyle(DEFAULT_FONT,0,0);
   drawgrid(120,60,len,20);
   outtextxy(10,50, "Message");

   x= 137;
   for(i=0; i<len; i++, x+=20)
   {
     if(o_mess[i]=='1')
	outtextxy(x,50,"1");
     else
	outtextxy(x,50,"0");
   }

   x=120;
   y=80;
   outtextxy(10,100, "NRZ - L");
   encode(o_mess,e_mess,len,0,2,0);
   draw(x,y,e_mess,len*2);
   y+=60;

   outtextxy(10,160, "NRZ - I");
   encode(o_mess,e_mess,len,3,4,0);
   draw(x,y,e_mess,len*2);
   y+=60;

   outtextxy(10,220, "Bipolar AMI");
   encode(o_mess,e_mess,len,3,1,0);
   draw(x,y,e_mess,len*2);
   y+=60;

   outtextxy(10,280, "Pseudo Tenary");
   encode(o_mess,e_mess,len,4,3,0);
   draw(x,y,e_mess,len*2);
   y+=60;

   outtextxy(10,340, "Manchester");
   encode(o_mess,e_mess,len,0,2,1);
   draw(x,y,e_mess,len*2);
   y+=60;

   outtextxy(10,400, "D-Manchester");
   encode(o_mess,e_mess,len,4,3,1);
   draw(x,y,e_mess,len*2);
   y+=60;

   getch();
   closegraph();

   return 0;
}

void about()
{
	void border();
  char msg[80];
  int gdriver = EGA, gmode = EGAHI, errorcode;
  initgraph(&gdriver, &gmode, "C:\\TC\\bgi");
  setbkcolor(15);
  border();
  setcolor(RED);
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
  outtextxy(50,20, "Daulatrao Aher College Of Engineering Karad.");
  outtextxy(200,45,"Department Of CSE");
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
  setcolor(5);
  outtextxy(170,110,"LINE CODING SCHEME");
  settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
  setcolor(3);
  outtextxy(20,220,"GUIDENCE      :   Prof. S.P.Shinde");
  outtextxy(20,250,"GROUP MEMBERS :    1) Arati Pawar              2) Vishakha Patil");
  outtextxy(20,270,"                   3) Neha Shinde              4) Sakshi Patil");
  setcolor(1);
  settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
  int h=getmaxy() - 35;
  int k=10,j=618;
  for(int b=0;b<39;b++)
  {
   outtextxy(k,h,"=");
   outtextxy(j,h,"=");
   k+=8;
   j-=8;
   delay(100);
       }
  closegraph();
}

void border()
{
 char str[30];

 time_t timer;
 struct tm *tblock;
 timer = time(NULL);
 tblock = localtime(&timer);
 sprintf(str, asctime(tblock));
 setcolor(RED);
 int  left = 10;
 int  top = 10;
 int  right = getmaxx()-10;
 int  bottom = getmaxy()-15;
 rectangle(left,top,right,bottom);
 setcolor(1);
 circle(15,341,8);
 outtextxy(12,338,"C Friends (mini project)");
 outtextxy(210,338,asctime(tblock));
 setcolor(YELLOW);
}

void drawgrid(int x, int y, int pulses, int width)
{
   line(x,y,x+(pulses*width),y);
   line(x,y,x,y+(width*12+150));

   for(int i=0; i<pulses; i++)
   {
      setcolor(LIGHTBLUE);
      line(x+width,y+1,x+width,y+(width*12+150));
      setcolor(BLUE);
      line(x+width/2,y+1,x+width/2,y+(width*12+150));
      x+=width;
   }
   setcolor(WHITE);

   return;
}

void draw(int x, int y, char *data, int len)
{
   int prev_y, curr_y;

   prev_y = y;

   for(int i=0; i<len; i++, x+=10)
   {
       if(data[i]=='2')
	  curr_y = y;
       if(data[i]=='1')
	  curr_y = y+20;
       if(data[i]=='0')
	  curr_y = y+40;


       line(x,curr_y,x+10,curr_y);
       sound(70);
       delay(50);
       nosound();

       if(prev_y != curr_y)
	  line(x,prev_y,x,curr_y);
	  sound(170);
	  delay(50);
	  nosound();

       prev_y = curr_y;
      delay(10);
   }
   return;
}

void encode(char *o_mess,char *e_mess,int len,int one,int zero, int mid)
{
   int i, j, previous=2;

   for(i=0, j=0; i<len; i++, j+=2)
   {
      if(o_mess[i]=='1')
      {
	 if(one==0)
	    e_mess[j]='0';
	 if(one==1)
	    e_mess[j]='1';
	 if(one==2)
	    e_mess[j]='2';
	 if(one==3)
	 {
	   if(previous==2)
	   {
	     previous=0;
	     e_mess[j]='0';
	   }
	   else
	   {
	     previous=2;
	     e_mess[j]='2';
	   }
	 }
	 if(one==4)
	 {
	   if(previous==2)
	     e_mess[j]='2';
	   else
	     e_mess[j]='0';
	 }
      }
      else
      {
	 if(zero==0)
	    e_mess[j]='0';
	 if(zero==1)
	    e_mess[j]='1';
	 if(zero==2)
	    e_mess[j]='2';
	 if(zero==3)
	 {
	   if(previous==2)
	   {
	     previous=0;
	     e_mess[j]='0';
	   }
	   else
	   {
	     previous=2;
	     e_mess[j]='2';
	   }
	 }
	 if(zero==4)
	 {
	   if(previous==2)
	     e_mess[j]='2';
	   else
	     e_mess[j]='0';
	 }
      }
      if(mid==1)
      {
	 if(e_mess[j]=='2')
	     e_mess[j+1]='0';
	 else
	     e_mess[j+1]='2';
	 if(previous==2)
	    previous=0;
	 else
	    previous=2;
      }
      else
	e_mess[j+1]=e_mess[j];
   }
   return;
}
