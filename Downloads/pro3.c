#include<stdlib.h>
#include<string.h>
//#include<GL/GLUT.h>
//#include<GL/glut.h>
#include <GLUT/GLUT.h>

#include<stdio.h>
#include<math.h>
#include<time.h>

int x=5;
int y=5;
int c1=25;
int c2=85;
int b1=25;
int b2=85;
int temp=0;
int lock=1;
int lock1=0;
int level=1;
int ylimit=0;
void mytimer(int n);
void princess();
int death[]={0,0,0};
int wind[]={1,0,0};
int count=0;
int extra=0;
int win=0;
void dustbin();
void rubbies(int ,int,int ,int );
void window3();



void myinit()
{
    glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
   	gluOrtho2D(0,900,0,600);
   	glMatrixMode(GL_MODELVIEW);
}

void base()
{
	int k=0,n=0;
	glColor3f(1,1,1);
	
	// The bottom brick layer in the output.
  	glBegin(GL_POLYGON);
    glVertex2f(0,0);
    glVertex2f(0,85);
    glVertex2f(900,85);
    glVertex2f(900,0);
    glEnd();
    
    glColor3f(0.5,0,0);
    x=5;
	y=5;
	// Loop to draw the bricks in the bottom layer.
   	for(n=0;n<4;n++) {
		for(k=0;k<21;k++) {
			glBegin(GL_POLYGON);
            glVertex2f(x,y);
           	glVertex2f(x,y+15);
            glVertex2f(x+40,y+15);
            glVertex2f(x+40,y);
            glEnd();
            x=x+45;
        }
        
		if(n==0 || n==2)
            x=-15;
        else
	        x=5;

        y=y+20;
	}
}

// Creates the brick pattern on the white layers.
void bricks(int a,int b,int x2,int y1) {
	dustbin();
    int n,m=a,k;
    glColor3f(0.5,0,0);
    
	for(n=0;b<y1;n++) {
		if(n==0 || n==2){
           a=m;
           glBegin(GL_POLYGON);
           glVertex2f(a,b);
           glVertex2f(a,b+15);
           glVertex2f(a+15,b+15);
           glVertex2f(a+15,b);
           glEnd();
           
           a=a+20;
           for(;a<x2;) {
			k=a+40;
            if(a+40>x2)
            	k=x2;
            
            glBegin(GL_POLYGON);
            glVertex2f(a,b);
            glVertex2f(a,b+15);
            glVertex2f(k,b+15);
            glVertex2f(k,b);
            glEnd();
            
            a=a+45;
		   }
		}
        else {
			a=m;
         	for(;a<x2;) {
            	k=a+40;
            	if(a+40>x2)
                	k=x2;
            	glBegin(GL_POLYGON);
	            glVertex2f(a,b);
    	        glVertex2f(a,b+15);
    	        glVertex2f(k,b+15);
    	        glVertex2f(k,b);
    	        glEnd();
    	        a=a+45;
  			}
		}
        b=b+20;
   	 }
}

void diamond(int a, int b)
{
	// I don't know what this does :D
    glColor3f(1, 0.6, 0.9);
    glBegin(GL_POLYGON);
    glVertex2f(a,b);
    glVertex2f(a-5,b+20);
    glVertex2f(a,b+40);
    glVertex2f(a+5,b+20);
    glEnd();
    
    // Draws the actual diamonds in the output
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
    glVertex2f(a,b);
    glVertex2f(a-10,b+20);
    glVertex2f(a,b+40);
    glVertex2f(a+10,b+20);
    glEnd();
}

void support1()
{
	// White polygon for second level brick layer
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(150,200);
        glVertex2f(150,265);
        glVertex2f(300,265);
        glVertex2f(300,200);
    glEnd();
    
    // Creates the brick pattern.
    bricks(155,205,300,260);
}

void support2()
{
	// White polygon layer for the second level.
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(0,350);
        glVertex2f(0,415);
        glVertex2f(140,415);
        glVertex2f(140,350);
    glEnd();
    
    // Creates the brick pattern.
    bricks(5,355,130,415);

}

void support3()
{
	// White polygon layer for the top most layer.
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(275,450);
        glVertex2f(275,515);
        glVertex2f(550,515);
        glVertex2f(550,450);
    glEnd();
    
    // Creates the brick pattern.
    bricks(280,455,550,510);
}

void support4()
{
	// White polygon layer for the right most layer
    glColor3f(1,1,1);
    glBegin(GL_POLYGON);
        glVertex2f(670,300);
        glVertex2f(670,385);
        glVertex2f(900,385);
        glVertex2f(900,300);
    glEnd();
    
    // Creates the brick pattern.
    bricks(675,305,900,380);
}

// This draws kio.
void kio()
{
	// Draws the foot
    glBegin(GL_POLYGON);
    glColor3f(1,0,0);
    glVertex2f(c1,c2);
    glVertex2f(c1,c2+3);
    glColor3f(1,1,1);
    glVertex2f(c1+25,c2+10);
    glColor3f(1,0,0);
    glVertex2f(c1+50,c2+3);
    glVertex2f(c1+50,c2);
    glEnd();

    int i;
    double angle;
    
    // Draws the black and white thingy.
    glBegin(GL_QUAD_STRIP);
    for(i=12;i<=24;i++)
    {
        angle=3.14/12*i;
        int t=i%2;
        if(t==0)
        glColor3f(1,1,1);
        else
            glColor3f(0,0,0);
        glVertex2f(c1+25+1*cos(angle),c2+25+1*sin(angle));
        glVertex2f(c1+25+25*cos(angle),c2+25+25*sin(angle));
    }
    glEnd();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(c1,c2+25);
    glColor3f(1,1,1);
    glVertex2f(c1+10,c2+40);
    glColor3f(1,0,0);
    glVertex2f(c1+40,c2+40);
    glColor3f(1,1,1);
    glVertex2f(c1+50,c2+25);
    glEnd();
    rubbies(c1+25,c2+50,0,15);
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(c1,c2+50);
    glVertex2f(c1,c2+60);
    glVertex2f(c1+15,c2+60);
    glVertex2f(c1+15,c2+65);
    glVertex2f(c1+35,c2+65);
    glVertex2f(c1+40,c2+60);
    glVertex2f(c1+50,c2+60);
    glVertex2f(c1+50,c2+50);
    glEnd();
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2f(c1+20,c2+45);
    glVertex2f(c1+30,c2+45);
    glEnd();
    glPointSize(3);
    glBegin(GL_LINES);
    glVertex2f(c1+24,c2+43);
    glVertex2f(c1+20,c2+40);
    glVertex2f(c1+26,c2+43);
    glVertex2f(c1+30,c2+40);
    glEnd();
}

void spikes()
{
    int i,l=480;
    glColor3f(.75,1,1);
    for(i=0;i<15;i++)
    {
    glBegin(GL_TRIANGLES);
        glVertex2f(l,85);
        glVertex2f(l+15,130);
        glVertex2f(l+15,85);
    glEnd();
    			l+=25;
    }
}

// This function draws the bule coins(or rubies) in the game.
void rubbies(int x,int y,int p,int q)
{
     p=1,q=10;
    int i;
    double angle;
    glBegin(GL_QUAD_STRIP);
    for(i=0;i<=24;i++)
    {
        angle=3.14/12*i;
        glVertex2f(x+p*cos(angle),y+p*sin(angle));
        glVertex2f(x+q*cos(angle),y+q*sin(angle));
    }
    glEnd();
}

int disp[]={0,0,0,0,0,0,0};
int posy[]={265,265,415,-415,515,-515};
int posx[]={170,250,26,98,400,499};
int check[]={2,2,3,4,4};

void diamondsdisp()
{
		// Determining where to place the diamonds.
    	for(int i=0;i<6;i++)
            if((c1==posx[i] || c1==posx[i]-1 || c1==posx[i]-2) && check[i]==level)
                disp[i]=1;
                
        count+=500;
        
        // Calls the function to draw diamond in a particular position.
    	for(int i=0;i<6;i++)
      		  if(disp[i]==0)
    				diamond(posx[i],posy[i]);
}

int rubx[]={50,250,525};
int ruby[]={200,150,575};
int dispr[]={1,1,1};
int checklevel[]={1,1,3};

void callrubies()
{
	// It is trying to add the positions where the rubies are to be placed.
    for(int i=0;i<2;i++)
        if((c1+50)>=rubx[i] && checklevel[i]==level && c1<rubx[i])
            if((c2+50)>=ruby[i])
                dispr[i]=0;
            
    count=count+250;
    
    // Draws rubies in the game.
    glColor3f(0,0.139,0.639);
    for(int i=0;i<2;i++)
        if(dispr[i]==1)
    		rubbies(rubx[i],ruby[i],0,0);
}

void ring()
{
    if(disp[6]==0)
    {
    	// Draws the gem on the ring
    	glColor3f(1,1,0);
    	rubbies(550,350,17,20);
    	// Draws the ring for the ring
    	glColor3f(0,1,1);
    	rubbies(550,370,0,0);
   }
   
   if((c1+50)>530 && c1<570)
       if(c2>=330 && c2<=380)
   	     disp[6]=1;
   	     
   count=count+2500;
}

int end=0;

void death1()
{
    if(c2<90 && (c1+50)>=515)
    {
        wind[1]=0;
        end=1;
        window3();
    }
}

int q1=800;
int q2=385;


void dustbin()
{
    glBegin(GL_POLYGON);
        glColor3f(.73,0,0.56);
        glVertex2f(q1,q2+30);
        glVertex2f(q1,q2+33);
        glColor3f(1,1,1);
        glVertex2f(q1+25,q2+40);
        glColor3f(.73,0,0.56);
        glVertex2f(q1+50,q2+33);
        glVertex2f(q1+50,q2+30);
        glEnd();

    glBegin(GL_POLYGON);
        glColor3f(.73,0,0.56);
        glVertex2f(q1+10,q2);
        glVertex2f(q1,q2+33);
        glColor3f(1,1,1);
        glVertex2f(q1+50,q2+33);
        glColor3f(.73,0,0.56);
        glVertex2f(q1+40,q2);
        glEnd();
}
/*
void princess()
{
   	glBegin(GL_POLYGON);
        glColor3f(.73,0,0.56);
        glVertex2f(q1,q2);
        glVertex2f(q1,q2+3);
        glColor3f(1,1,1);
        glVertex2f(q1+25,q2+10);
        glColor3f(.73,0,0.56);
        glVertex2f(q1+50,q2+3);
        glVertex2f(q1+50,q2);
        glEnd();
       int i;
    double angle;
    glBegin(GL_QUAD_STRIP);
    for(i=12;i<=24;i++)
    {
        angle=3.14/12*i;
        int t=i%2;
        if(t==0)
        glColor3f(1,1,1);
        else
            glColor3f(0.196,0.6,0.8);
        glVertex2f(q1+25+1*cos(angle),q2+25+1*sin(angle));
        glVertex2f(q1+25+25*cos(angle),q2+25+25*sin(angle));
    }
    glEnd();
    glColor3f(.196,0.6,0.8);
    glBegin(GL_POLYGON);
    glVertex2f(q1,q2+25);
    glColor3f(1,1,1);
    glVertex2f(q1+10,q2+40);
    glColor3f(.196,0.6,0.8);
    glVertex2f(q1+40,q2+40);
    glColor3f(1,1,1);
    glVertex2f(q1+50,q2+25);
    glEnd();

    rubbies(q1+25,q2+50,0,15);

    glColor3f(0.63,0.15,0.56);
    glBegin(GL_POLYGON);
    glVertex2f(q1,q2+50);
    glVertex2f(q1,q2+60);
    glVertex2f(q1+15,q2+60);
    glVertex2f(q1+15,q2+65);
    glVertex2f(q1+35,q2+65);
    glVertex2f(q1+40,q2+60);
    glVertex2f(q1+50,q2+60);
    glVertex2f(q1+50,q2+50);
    glEnd();

    glColor3f(0,0,0);
    rubbies(q1+20,q2+45,0,2);
    rubbies(q1+30,q2+45,0,2);
    glColor3f(1,0,0);

    glBegin(GL_LINES);
    glVertex2f(q1+25,q2+37);
    glVertex2f(q1+20,q2+40);
    glVertex2f(q1+25,q2+37);
    glVertex2f(q1+30,q2+40);
    glEnd(); 
    dustbin();

    if(c1>750 && c2>300)
    {
        win=1;
        wind[1]=0;
    window3();
    }
}
*/

void window2()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draws the bottom most brick layer.
    base();
    
    // Creates all the brick layers.
    support1();
    support2();
    support3();
    support4();
    
    // Adds the rubies in the game.
    callrubies();
    
    // Draws the diamonds in the game.
    diamondsdisp();
    
    // Draws Kio
    kio();
    
    // Draws the spikes. This is a death trap. BEWARE. Simran is bad.
    spikes();
    
    death1();
    glFlush();
    glutSwapBuffers();
}

void window1()
{
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1,0.5,0.5);
        glBegin(GL_POLYGON);
        glVertex2f(0,0);
        glColor3f(1,1,0);
        glVertex2f(0,600);
        glColor3f(0,1,1);
        glVertex2f(900,600);
        glColor3f(1,0,1);
        glVertex2f(900,0);
        glEnd();

        char str[]="!THE RESPONSIBLE CITIZEN!";
        char str1[]="Instructions:-";
        char str2[]="w-to jump up.";   
        char str3[]="a-to move left";
        char str4[]="d-to move right";
        char str5[]="By";
        char str6[]="SIMRAN";
        char str7[]="and";
        char str8[]="SURYA KIRAN K";
        char str9[]="Left click to continue";

        glColor3f(1,0,0);
        glRasterPos2f(425,400);
            for(int i=0;i<strlen(str);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
            glColor3f(1,0,1);
            glRasterPos2f(200,200);
            for(int i=0;i<strlen(str1);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str1[i]);
            glRasterPos2f(200,175);
            for(int i=0;i<strlen(str2);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str2[i]);
            glRasterPos2f(200,150);
            for(int i=0;i<strlen(str3);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str3[i]);
            glRasterPos2f(200,125);
            for(int i=0;i<strlen(str4);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str4[i]);
            glColor3f(1,1,0.75);
            glRasterPos2f(625,200);
            for(int i=0;i<strlen(str5);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str5[i]);
            glRasterPos2f(625,175);
            for(int i=0;i<strlen(str6);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str6[i]);
            glRasterPos2f(625,150);
            for(int i=0;i<strlen(str7);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str7[i]);
            glRasterPos2f(625,125);
            for(int i=0;i<strlen(str8);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str8[i]);
            glFlush();
            glutSwapBuffers();
}

void mouse(int bt,int st,int x,int y)
{
    if(bt==GLUT_LEFT_BUTTON && st==GLUT_DOWN )
        wind[1]=1,wind[0]=0;
    glutPostRedisplay();
}

void window3()
{
    char str1[]="score=";
    char str[20];
    char str2[]="!!YOU HAVE BEEN A RESPONSIBLE CITIZEN!!";
    char str3[]="!!WINNER!! : ";
    char str4[]="!!!YOU TOOK A WRONG STEP!!!";
    char str5[]="!!GAMEOVER!!";
    char str6[]="!!YOU MISSED ON FEW !!";
    glClearColor(0,1,1,0);
        glClear(GL_COLOR_BUFFER_BIT);
        if(win==1 && disp[6]==1)
        {
            glRasterPos2f(400,400);
            for(int i=0;i<strlen(str3);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str3[i]);
            glRasterPos2f(275,375);
            for(int i=0;i<strlen(str2);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str2[i]);
        }
        else if(win==1 && disp[6]==0)
        {
            glRasterPos2f(150,400);
            for(int i=0;i<strlen(str6);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str6[i]);
            glRasterPos2f(350,375);
            for(int i=0;i<strlen(str3);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str3[i]);
        }
        else
        {
            glRasterPos2f(250,400);
            for(int i=0;i<strlen(str4);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str4[i]);
            glRasterPos2f(350,375);
            for(int i=0;i<strlen(str5);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str5[i]);
        }

        //_itoa_s(count,str,10);
        glColor3f(1,1,0);
        glRasterPos2f(425,300);
        for(int i=0;i<strlen(str);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
       
        glRasterPos2f(350,300);
        for(int i=0;i<strlen(str1);i++)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str1[i]);
        glFlush();
       }

void display1()
{   
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    if(wind[0]==1)
        window1();
    if(wind[1]==1)
        window2();
    glFlush();
   
}

void mytimer(int n)
{
	//printf("Inside timer temp: %d\n",temp );
    n=60;
    if(level==4 && ylimit==2 && temp==200)
    {
        temp=364;
        ylimit=0;
        extra=431;
        level=1;
    }
    if(level==2 && ylimit==30 && temp==200)
    {
        temp=349;
        ylimit=0;
    }
    if(level==2 && ylimit==10 && temp==348)
    {
           temp=398;
           ylimit=0;
    }
    if(level==2 && (c1>300) && temp==398)
        {
            level--;
            temp=218;
            glutTimerFunc(1,mytimer,60);
        }
    if(level==3 && ylimit==20 && temp==200)
    {
        temp=249;
        ylimit=0;
    }
    if(lock==1 && level==3 && c1>140)
        {
            level--;
            temp=250;
            glutTimerFunc(1,mytimer,60);
        }
    if((c1+50)>670 && c2>=385)
    {
        temp=399;
        extra=0;
        level=5;
        lock=1;
    }
    else
        if(level==4 && (c2-5)<=85)
        {
            level=1;
            lock1=0;
        }
    if(ylimit==4 && temp==200)
    {
        temp=320;
        ylimit=0;
    }
    if(temp<400)
    {	
    	printf("Inside timer temp: %d\n",temp );
    	printf("c2: %d \n",c2 );
        if(temp<200){
        	printf("Incrementing c2\n");
            c2 = c2+2;
        }
        if(temp>=200){
        	printf("Decrementing c2\n");
            c2=c2-2;
        }
        if(level==1 && (c1+35)>=150 && c2>=265 && c1<300 && ylimit==0)
        {    int c3=c2-265;
        	printf("Something complicated\n");
            temp=400-c3;
            level++;
        }
        if(level==2 && c1<140 && c2>=415 )
        {
            int c3=c2-415;
            temp=400-c3;
            level++;
        }
        if(level==3 && (c1+50)>=275 && c2>515)
        {
            int c3=c2-515;
            temp=400-c3;
            level++;
        }
        if(level==4 && temp==200 && ylimit==1)
        {   
            temp=364;
            ylimit=0;
        }
    glutPostRedisplay();
    if(extra<=0)
        temp++;
    else
        extra--;
    if(temp>=400)
        lock=1;
    glutTimerFunc(8,mytimer,60);
    }
}

void mykey(unsigned char key,int x,int y)
{
    if(key=='d'|| key=='D') {   
    	printf("Level: %d c1: %d lock: %d \n",level,c1,lock );
		if(level==2 && c1>300 && lock==1) {
			printf("Inside if 1\n");
			level--;
            temp=219;
            lock=0;
            glutTimerFunc(1,mytimer,60);
        }

        if(lock==1 && level==3 && c1>140) {
        	printf("Inside if 2\n");
            level--;
            lock=0;
            temp=250;
            glutTimerFunc(1,mytimer,60);
        }

        if(lock1==0) {
        	printf("Inside if 3\n");
            if(c1>550 && lock==1) {
                temp=200;
                extra=230;
                lock1=1;
                lock=0;
                ylimit=0;
                glutTimerFunc(1,mytimer,60);
            }
        }

        if((level==3 || level==4) && (c1+50)<900 ){
        	printf("Inside if 4\n");
           c1=c1+3;
        }

        else if((c1+50)<900){
        	printf("Inside if 5\n");
            c1=c1+2;
        }
    }

    if(key=='a' || key=='A') {
        if(level==2 && (c1+25)<150 && lock==1) {
            level--;
            temp=219;
            lock=0;
            glutTimerFunc(1,mytimer,60);
        }
        
        if(lock==1 && level==3 && c1>140) {
            level--;
            temp=250;
            glutTimerFunc(1,mytimer,60);
        }

        if(level==4 && (c1+50)<275) {
            level=level-2;
            lock=0;
            temp=200;
            extra=50;
            glutTimerFunc(1,mytimer,60);
        }
        
        if(level>=5 && (c1+50)<670) {
            extra=100;
            temp=200;
            glutTimerFunc(6,mytimer,60);
        }
        
        if((level==3 || level==4) && c1>0 )
            c1=c1-3;
        
        else if(c1>0)
            c1=c1-2;
    }

	lock = 0;
    if(lock==0) {
        if(key=='w' || key=='W') {
        	printf("Level: %d , c1: %d , c2: %d \n",level,c1,c2);
        	//printf("Hello world");
        	//printf("Level: %d , c1: %d , c2: %d",level,c1,c2);
           // if(level==1 && (c1+40)>150 && c2<100 && (c1+10)<300) {
           	if (level==1){
            	printf("Inside Level 1\n");
                temp=120;
                ylimit=4;
                lock=0;
            }
            
            else if(level==2 && c1<140 )
            {
            	printf("Inside Level 2\n");
                temp=149;
                ylimit=30;
                lock=0;
            }
            else if(level==3 && c1<140)
            {
            	printf("Inside Level 3\n");
                temp=49;
                ylimit=20;
                lock=0;
            }
            else if(level==4 && c1<525)
            {
            	printf("Inside Level 4\n");
                temp=164;
                lock=0;
                ylimit=1;
            }
            else if(level==5 && c1>=525)
            {
            	printf("Inside Level 5\n");
                temp=164;
                lock=0;
                ylimit	=2;
            }
            else if(level==2 && (c1+50)>=275)
            {
            	printf("Inside Level 2\n");
                temp=49;
                lock=0;
                ylimit=10;
            }
            else
            {
            	printf("Inside else\n");
                temp=0;
                lock=0;
  			}
            glutTimerFunc(1,mytimer,60);
      }
	}
    glutPostRedisplay();
}

void main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(900,600);
    glutCreateWindow("THE RESPONSIBLE CITIZEN");
    myinit();
    glutMouseFunc(mouse);
    if(end==0)
 	   glutKeyboardFunc(mykey);
    glutDisplayFunc(display1);
   	glutMainLoop();
}
