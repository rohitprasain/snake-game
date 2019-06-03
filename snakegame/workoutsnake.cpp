#include<fstream>           //file stream
#include<iostream>          //cin , cout
#include<iomanip>           //setw() , setiosflags()
#include<conio.h>           //kbhit(),getch()    
#include<stdlib.h>          //srand(),rand(),system()
#include<windows.h>         //tolower()
#include<time.h>            //time(NULL)
#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
using namespace std;
class color
 {
 	public:
    	void textcolor(int fc,int bc=-1)                   //function overloading 
           {
               if(fc<0 || fc>15)
               return;
               HANDLE h;
               h = GetStdHandle(STD_OUTPUT_HANDLE);
               if(bc>=0 && bc<16)
               SetConsoleTextAttribute(h,fc|bc*16);
               else
                SetConsoleTextAttribute(h,fc);
            }
        void gotoxy(int x, int y)                     //function overloading 
          {                                          
            COORD coord;
            coord.X = x;
            coord.Y = y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
          } 
		inline void score(int sc)                      //inline function
          {
            gotoxy(40,21);
            textcolor(3);
            cout<<setw(3)<<setiosflags(ios::left)<<sc*10;
          }
 };
class getup:public color                              //single inheritance
{
	public:
     display()
      {
         HANDLE hout; 
         hout = GetStdHandle(STD_OUTPUT_HANDLE);
         system("cls");
         textcolor(7);
         
           //algorithm for boarder
                         
         cout<<endl<<setw(3)<<setiosflags(ios::right)<<char(218);
         int x;
         for(x=0;x<75;x++)
          {
	         cout<<char(196);
          }
         cout<<char(191);
         for(x=0;x<18;x++)
	      {
             gotoxy(2,x+2);
             cout<<char(179);
             gotoxy(78,x+2);
             cout<<char(179);
          }
         gotoxy(0,19);
         cout<<setw(3)<<setiosflags(ios::right)<<char(192);
         for(x=0;x<75;x++)
     	 cout<<char(196);
         cout<<char(217);
              //boarder end 
          
		  //score display
         gotoxy(30,21);
         textcolor(10);
         cout<<"Score:      ";
         textcolor(7);        
      }	
};

int main()                                      //main function
  {
  	color col;             
    getup get;
    string text;
    int sp;
    fstream name;                              //file creation
    name.open("myname.txt",fstream::in);
    col.gotoxy(32,7);
    col.textcolor(11);
    cout<<"Enter your name "<<endl<<endl;
    col.textcolor(14);
    col.gotoxy(33,8);
    getline(std::cin, text);
    name<<text;
    system("cls");
    col.gotoxy(0,4);
    col.textcolor(11);
    cout<<"Enter a number to set the difficulty level "<<endl;
    col.textcolor(10);
    cout<<endl<<"100+ for slow mode"<<endl;
	cout<<"50-100 for normal mode"<<endl;
	cout<<"1-50 for fast mode"<<endl<<endl;
	col.textcolor(9);
    cin>>sp;
    get.display();
    int flow,size,i,xb,yb,l=8;
    int speed,restart=1,temp,xpos[100],ypos[100],scr;
    srand(time(NULL));
    while(true){
        if(restart)
		 {
		 	get.display();  
            size=6;                              //initial snake size
            speed=sp;
            scr=0;         
            col.score(scr);
            flow=RIGHT;
            xpos[0]=20;
            for(i=0;i<size;i++)
			  {
                xpos[i]=xpos[0]-i;
                ypos[i]=10;
              }
            for(i=0;i<size;i++)
			  {
                col.gotoxy(xpos[i],ypos[i]);
                cout<<"*";           
              }
            for(temp=1;true;)
			  {
                do
				 {
                    xb=rand()%75+3;
                 }while(xb%2!=0);
                yb=rand()%17+2;
                for(i=0;i<size;i++)
                    if(xb==xpos[i] && yb==ypos[i])
					 {
                        temp=0; break;
                     }
                if(temp)
                    break;
              }
            col.gotoxy(xb,yb);
            col.textcolor(l+1);                   //food color
            cout<<"$";                            //food shape
            restart=0;
        }
         l1: char ch=getch();
    switch(tolower(ch))
	  {
	  	 case 'e' : 
          {
            system("cls");
            return 0;
  		  }
         case -32:
		  {
            char chh=getch();
            if(chh==72 && flow!=DOWN)
              flow=UP;
            else if(chh==80 && flow!=UP)
              flow=DOWN;
            else if(chh==75 && flow!=RIGHT)
              flow=LEFT;
            else if(chh==77 && flow!=LEFT)
              flow=RIGHT;
            break;
            }   
      }


    while(!kbhit() && !restart)
	  {
        if(xpos[0]==xb && ypos[0]==yb)           //after snake eats food
		  {
            for(temp=1;true;)
			  {
                do
				  {
                    xb=rand()%75+3;
                  }while(xb%2!=0);
                yb=rand()%17+2;
                for(i=0;i<size;i++)
                  {
                  	if(xb==xpos[i] && yb==ypos[i])
				      {
                        temp=0;
					    break;
                      }
				  }
                if(temp)
                  break;
               }
                scr++;
                col.textcolor(7);
                col.score(scr);
                col.gotoxy(xb,yb);
                l++;
                if(l>15)
                 {
                	l=1;
		         }
                col.textcolor(l+1);
                cout<<"$";        
                size++;                                 //increase size of snake
	      }
        col.gotoxy(xpos[size-1],ypos[size-1]);
        for(i=size-1;i>0;i--)
		  {               
            xpos[i]=xpos[i-1];
            ypos[i]=ypos[i-1];
          }
        switch(flow)                                     //movement via keys
		  {
            case RIGHT :xpos[i]+=2;
			  break;
            case LEFT : xpos[i]-=2; 
			  break;
            case UP :   ypos[i]-=1; 
			  break;
            case DOWN : ypos[i]+=1; 
          }
        temp=1;
        for(i=1;i<size;i++)
         if(xpos[i]==xpos[0] && ypos[i]==ypos[0])
			 {
                temp=0;
                break;
             }
        if(xpos[0]>76 || xpos[0]<4 || ypos[0]<2 ||ypos[0]>18)
          temp=0;
        if(temp)
		  { 
		    col.textcolor(l);
           	cout<<" ";
            col.gotoxy(xpos[0],ypos[0]);
            cout<<"O";
            col. gotoxy(xpos[1],ypos[1]);
            cout<<"*";  
          }
        else
		  {
            col.textcolor(12);
            cout<<"*"; 
            col.gotoxy(xpos[1],ypos[1]);
            cout<<"O"; 
            for(i=2;i<size;i++)
			  {
                col.gotoxy(xpos[i],ypos[i]);
                cout<<"*"; 
              }
            restart=1;
            l=9;
            col.textcolor(7);
            Sleep(400);
            system("cls");
            col.textcolor(11);
            cout <<"name:  " ;
            name>> text;
            col.textcolor(12);
            cout << text << endl;
            col.textcolor(11);
            cout<<"score: " ;
            name<<scr;
            col.textcolor(12);
            cout<<scr*10<<endl;  
            if(sp>0&&sp<=50)
               {
               	  col.textcolor(11);
               	  cout<<"speed mode:  FAST";
			   }
			else if(sp>50&&sp<=100)
               {  
                  col.textcolor(11);
               	  cout<<"speed mode: NORMAL";
			   }
			else
               {
               	  col.textcolor(11);
               	  cout<<"speed mode: SLOW";
			   } 
			col.textcolor(14);
            cout<<endl<<endl<<endl<<"press E to exit"<<endl<<"press anykey to continue" ;
		    goto l1;      
			system("cls"); 
         } 
        Sleep(speed);	                 
      }
          }
}
   
