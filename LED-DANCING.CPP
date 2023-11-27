#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <iostream.h>
void shape_78();
void move1_updown(int,int);
void blink(int,int,int);
void ambulance();
void keyboard(int,int);
void last_move(int);
void k();
//************************
int main(void)
{
  int index=0;
  char key;
  clrscr();
  printf("Please Press Enter to Continue For switch bitween dance LED's...\n");
  scanf("%c",&key);
  printf("Move 1...");
  while(((int)key)==10)
  {
      switch(index)
      {
	case 0:move1_updown(1,1);printf("\nMove 2...");break;
	case 1:move1_updown(1,2);printf("\nMove 3...");break;
	case 2:shape_78();printf("\nMove 4...");break;
	case 3:blink(0,2000,100);printf("\nMove 5...");break;
	case 4:last_move(1);printf("\nMove 6...");break;
	case 5:k();printf("\nMove 7...");break;
	case 6:ambulance();printf("\nDance Keyboard...");break;
	case 7:keyboard(1,1);printf("\nCheck Keyboard...");break;
	case 8:keyboard(0,0);break;
     }//end switch
     index++;
     scanf("%c",&key);
     index=(index>6?0:index);
   }//end while
  outport(0x378,0);
  return 0;
}
void shape_78()
{
  int dlay=0,k=0,bl=1,j=7;
  for(int i=1;i<20;i++)
    {
      for(int m=0;m<2;m++)
	{
	  for(int p=0;p<4;p++)
	   {
	     dlay=(400/i);
	     j+=(bl==1?-1:1);
	     k=((int)pow((double)2,(double)j)+(int)pow((double)2,(double)(7-j)));
	     outport(0x378,k);
	     delay(dlay);
	   }//end for(p...
	  bl=(bl==1?0:1);
	 }//end for(m..
      outport(0x378,0x0);//all off
    }//end for(i..
}//end _78
void blink(int on_off_sound,int delaynum,int step)
{
   int dlay=0,bl=0,k=0;
   for(int i=1;i<step;i++)
     {
       if(delaynum!=0)
	 dlay=(1500/i);
       else
	 dlay=400;
       if(bl==1)
	 outport(0x378,0xff);
       else
	 outport(0x378,0x00);
       if(on_off_sound==1)
	  sound((bl==1?200:100));
       bl=(bl==1?0:1);
       delay(dlay);
       nosound();
     }//end for(i...
}//end blink
void move1_updown(int on_off_sound,int one_two)
{
 int dlay=400,k=0,bl=1;
 for(int i=1;i<35;i++)
  {
    for(int j=7;j>=0;j--)
    { dlay=(500/i)+10;
	if(one_two==1)
	   outport(0x378,(int)pow((double)2,(double)j));//move1
	else
	 {
	   if(bl==1)
	    outport(0x378,(int)pow((double)2,(double)j)+(int)pow((double)2,(double)j-1));
	   else
	    outport(0x378,(int)pow((double)2,(double)(7-j))+(int)pow((double)2,(double)(7-j+1)));
	 }//end else
	if(on_off_sound==1)sound(k);
	delay(dlay);
	if(on_off_sound==1)nosound();
       k+=200;
      }//end for (j..
      k=0;bl=(bl==0?1:0);
  }//end for(i...
}//end move
void ambulance()
{
  int dlay=0,bl=1;
 for(int j=0;j<2;j++){
  for(int i=1;i<21;i++)
   {
      if(bl==1)
	{outport(0x378,(j==0?3:8));sound(900);}
     else
	{outport(0x378,(j==0?192:16));sound(700);}
     delay((j==0?400:150));
     nosound();
     bl=(bl==1?0:1);
   }//end for(i...
 }//end for(j..
   blink(1,0,16);
}//end ambulance
void k()
{
  int dlay=0,k=0,bl=0;
  for(int i=1;i<20;i++)
   {
      if(bl==0)
	{outport(0x378,24);sound(900);}
     else if(bl==1)
	{outport(0x378,60);sound(700);}
     else if(bl==2)
	{outport(0x378,0xff);sound(700);}
     else
	{outport(0x378,0);sound(700);}
     delay(100);
     nosound();
     bl=(bl==0?1:(bl==1?2:(bl==2?3:0)));
   }//end for(i...
}//end ambulance

void last_move(int _sound)

{
int bl=0;
for(int j=0;j<2;j++)
  {
    for(int i=0;i<80;i++)
     {
       if(bl==1)
	 outport(0x378,170);
       else
	 outport(0x378,85);
       bl=(bl==0?1:0);
       if(_sound)sound((bl==1?900:700));
       delay((j==1?400-(i*4):i*4));
       nosound();
      }//end for(i..
  }//end for(j...
}//end last move
void keyboard(int sound,int check_key_or_dance)
{
  int n=600;
  pokeb(0x0040,0x0017,0); //ALL OFF
  if(check_key_or_dance==0)
   {
     clrscr();
     while(getch()!='a')
	{
	  switch(peekb(0x0040,0x0017))
	    {
		case 0:printf("\nall is off");break;
		case 2:printf("\nPress Shift");break;
		case 4:printf("\nPress Ctrl");break;
		case 8:printf("\nPress Alt");break;
		case 16:printf("\nScroll Lock is on, Num Lock & Caps Lock is off.");break;
		case 32:printf("\nNum Lock is on, Scroll Lock & Caps Lock is off.");break;
		case 64:printf("\nCaps Lock is on, Num Lock & Scroll Lock is off.");break;
		case 48:printf("\nScroll Lock & Num Lock is on.");break;
		case 80:printf("\nCaps Lock & Scroll Lock is on.");break;
		case 96:printf("\nCaps Lock & Num Lock is on.");break;
		case 112:printf("\nCaps Lock & Num Lock & Scroll Lock is on.");break;
	    }//end switch
	}//end while
     getch();
   }//end if
 else
    {
       pokeb(0x0040,0x0017,32);
	 delay(n);
       pokeb(0x0040,0x0017,64);
	 delay(n);
       pokeb(0x0040,0x0017,16);
	 delay(n);
       pokeb(0x0040,0x0017,0);
	 delay(n);
       pokeb(0x0040,0x0017,16);
	 delay(n);
       pokeb(0x0040,0x0017,64);
	 delay(n);
       pokeb(0x0040,0x0017,32);
	 delay(n);
       pokeb(0x0040,0x0017,0);
	 delay(n+1000);
       for(int i=0;i<3;i++)
	  {
	    pokeb(0x0040,0x0017,48);
	       delay(n);
	    getch();
	    pokeb(0x0040,0x0017,0);
	       delay(n);
	  }
    }//end else
}//end keyborad
