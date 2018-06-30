#include "acllib.h"
#include <stdio.h>
#include "model.h"
#include "view.h"

/*
void MouseListener(int x,int y,int button,int event)
{
	
	static int ox = 0;
	static int oy = 0;
	static int flag = 0;
	static int color = 0;
	
	if (button == 1 && event == 0)
		flag = 1;
	if (button == 1 && event == 2)
		flag = 0;
	if (button ==2 && event == 3){
		color = (color-1)%4;
		if (color < 0)
			color += 4;
		return;
	}
	if (button == 2 && event == 4){
		color = (color+1)%4;
		return;
	}
	printf("x = %d, y = %d, button = %d, event = %d, color = %d\n",x,y,button,event,color);
	if(flag){
		beginPaint();
		switch (color) {
			case 0:setPenColor(BLACK);break;
			case 1:setPenColor(RED);break;
			case 2:setPenColor(GREEN);break;
			case 3:setPenColor(BLUE);break;
			default:setPenColor(BLACK);
		}
		setPenWidth(5);
		line(ox,oy,x,y);
		endPaint();
	}
	
	ox = x;oy = y;
}
*/
void timerListener(int id)
{
	static int cnt = 0;
	printf("id = %d, cnt = %d\n",id,cnt++);
	if (id == 0)
	{
		refreshPlane(plane_list);
		refreshCannon();
		refreshBullet(bullet_list);
		crashBullet(bullet_list);
		beginPaint();
		drawbackground();
		drawPlanelist();
		drawCannon();
		drawBulletlist();
		endPaint();
		if(plane_list->next)
			printf("current plane x = %d,y = %d\n",plane_list->next->x,plane_list->next->y);
	}
	if(id == 1)
	{
		addPlane();
	}
	if (cnt == 2000){
		cancelTimer(0);
		cancelTimer(1);
	}
}
void KeyboardListener(int key,int event)
{
	printf("key = %d, event = %d\n",key,event);
	if (key == 37 && event == 0)
	{
		setCannon(-5);
	}
	if (key == 39 && event == 0){
		setCannon(5);
	}
	if (key == 32 && event == 0){
		Shoot(Cannon);
	}
}

int Setup()

{
	//initConsole();
	initWindow("让你欲罢不能的船新打飞机游戏", DEFAULT, DEFAULT, 900, 600);
	
	initPlay();
	//registerMouseEvent(MouseListener);
	registerTimerEvent(timerListener);
	registerKeyboardEvent(KeyboardListener);
	startTimer(0,100);//refresh使用的timer 
	startTimer(1,2000);//add plane使用的timer 
	addPlane();
	initView();
	return 0;
}
