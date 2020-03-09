# include "iGraphics.h"
# include <stdio.h>
# include <stdlib.h>


double position(); //proto type
void virus();

double x_co=600,y_co=400.5,radius=100; //for the circle, around which man moves
double manx=500; //for man's x co ordinate
double randomx,randomy;  // for randomly generate enemies
double bulletx1,bullety1,bulletx2,bullety2;

byte flag=1;   
double bx1,bx2,by1,by2,changex,changey,checkPosition;  // for changing bullet' co-or.


byte enflag=1;  // for changing co-ordinates of enemies
double enchangex,enchangey;

int score = -1, crntScore;
int lifeCount = 3, killCount=0;



char text[20] ;
char hscore[20];
char jibon[20] ;
char stageArray[20];


char back[3][15] = {"back1.bmp","back2.bmp","back3.bmp"};
char Menu[3][15] = {"main.bmp","back.bmp","over.bmp"};

char germs[5][15] = {"vir1.bmp","vir2.bmp","vir1.bmp","vir2.bmp","vir1.bmp"};
int virusNo = 0;

int MenuIndex = 0;

int bcIndex = 0;

byte fireFlag = 0;


int speed=150;
int stage = 1;


void shoot (){

	if(flag){
		bx1=bulletx1;
		bx2=bulletx2;
		by1=bullety1;
		by2=bullety2;
		changex= bx2-bx1;
		changey = by2-by1;
		flag=0;
		checkPosition = bulletx1;
	}
	else {
	bx1 = bx1 + changex;
	by1 = by1 + changey;
	bx2 = bx2 + changex;
	by2 = by2 + changey;
	}

	if(by1>800 || bx1 <0 || bx1 > 1500  || by1 <0){ flag=1; fireFlag = 0; }
	


}



void kill (){
	if(abs(bx2-randomx) <50  && abs(by2-randomy)<50){
		enflag=1; killCount++;
	}

	if( checkPosition != bulletx1 ){ flag = 1; }

}


void life() {
	if(randomx == x_co || randomy == y_co) lifeCount--;

	if(lifeCount <= 0) MenuIndex = 0;

}
  


void virus(){

if(enflag){	
	virusNo ++;
	int i=rand();

if(i%2==0){
randomx=rand()%1200;
if(randomx !=0 && randomx !=1199){
	if(i>RAND_MAX/2) randomy=0;
	 else randomy=750;
//iFilledCircle(randomx,randomy,50,50);
}

else {randomy=rand()%800;
//iFilledCircle(randomx,randomy,50,50);
}
  }

else {
randomy=rand()%800;
if(randomy!=0 && randomy!=799){
	if(i>RAND_MAX/2) randomx=0;
	else randomx=1200;
//iFilledCircle(randomx,randomy,50,50);
}

else {
	randomx=rand()%1200;
	//iFilledCircle(randomx,randomy,50,50);
}

  }

enflag=0;
enchangex = (randomx - x_co) /speed;
enchangey = (randomy - y_co)/speed ;

score++;
}


else{
	randomx = randomx - enchangex;
	randomy = randomy - enchangey;

}

if( abs(randomx - x_co) < 10 || abs(randomy - y_co) < 10 ) {enflag = 1; lifeCount--; score--; }

if(virusNo > 4) { virusNo = 0; }

}



double position(double x){

if(x>0)
return abs(sqrt(pow(radius,2)-pow(x-x_co,2))+y_co);

else
{   x*=-1;
	return abs(sqrt(pow(radius,2)-pow(x-x_co,2))-y_co);}

}




void bullet(){

if(manx>0){
  bulletx1 = manx,   bullety1 = position(manx),    bulletx2 = (manx+(manx-x_co)/2);
  bullety2=  ((position(manx)-y_co)/2+position(manx));
}

else  {bullety2=-(-position(manx)+y_co)/2+position(manx);
bulletx1=abs(manx);
bullety1=position(manx);
bulletx2=abs(manx)+(abs(manx)-x_co)/2;

}

}





	

void iDraw()
{
	//place your drawing codes here	
	
	 
	iClear();


	
	FILE *fread, *fwrite;
	iShowBMP(0,0,Menu[0]);
 
	
   fread = fopen("score.txt","r");
    fscanf(fread,"%d",&crntScore);
    fclose(fread);
	
	 if(MenuIndex==1){

		 iClear();
	  
		itoa(score,text,10);
		itoa(crntScore,hscore,10);
		itoa(lifeCount,jibon,10);
		itoa(stage,stageArray,10);

	
	iShowBMP(0,0,back[bcIndex]);
	


	iShowBMP2(randomx-50,randomy-50,germs[virusNo],0);
	iShowBMP2(bx2-50,by2-30,"fire.bmp",0);
	iShowBMP2(abs(manx)-35,position(manx)-30,"man.bmp",0);

	kill();  
	iCircle (x_co,y_co,radius,100);

	
	bullet();
	iLine(bulletx1,bullety1,bulletx2,bullety2);
	
	
	if(fireFlag){shoot();}
	if(lifeCount <= 0) MenuIndex = 2;

	
	iText(1300,720,"SCORE");
    iText(1300,700,text);


	iText(1300,650,"HIGH SCORE");
    iText(1300,630,hscore);

	iText(1300,580,"LIFE");
    iText(1300,560,jibon);

	iText(1300,520,"STAGE");
	iText(1300,500,stageArray);


	if(killCount >3){
		stage++;
		speed = speed -10;
		killCount=0;

	}


	if(score>crntScore){
        fwrite = fopen("score.txt","w");
    fprintf(fwrite,"%d",score);
    fclose(fread);
	
	}

	

}

	else if(MenuIndex == 2){
		iShowBMP(0,0,Menu[MenuIndex]);
	}

}



/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here	
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/
void iKeyboard(unsigned char key)
{
	if(key == 'q')
	{
		//do something with 'q'
	}
	//place your codes for other keys here
		if(key==' ') {
	           fireFlag = 1;
		}
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}

	if(key == GLUT_KEY_UP)
	{
		MenuIndex++;
		if(MenuIndex>=2) MenuIndex=0;
	}

	
	//place your codes for other keys here
	if(key==GLUT_KEY_RIGHT) {
		if(manx+5>x_co+radius) { manx=5-manx;}
		else if(manx==-500) manx=500;
		else manx+=5;
		
	
	}

	
	if(key==GLUT_KEY_LEFT) {
	
		if(abs(manx)-5<x_co-radius) manx=-(manx+5);
		else if (manx==-700) manx=700;
		else manx-=5;
	}

		
}


void background(){
	if(bcIndex >= 2) bcIndex = 0;

	else bcIndex++;

}



int main()
{
	
	iDraw();

	PlaySound("sound.wav",NULL,SND_ASYNC);
	
	iSetTimer(100,virus);

	iInitialize(1500, 800, "Anti Virus");
	

	
	return 0;
}	