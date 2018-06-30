#include "view.h"
#include "acllib.h"
#include "model.h"

ACL_Image *bg,*plImg, *bombImg, *bulletImg;

void initView(void)
{
	bg = (ACL_Image*)malloc(sizeof(ACL_Image));
	plImg = (ACL_Image*)malloc(sizeof(ACL_Image));
	bombImg = (ACL_Image*)malloc(sizeof(ACL_Image));
	bulletImg = (ACL_Image*)malloc(sizeof(ACL_Image));
	
	loadImage("E:/programming/cprogram/zheda_c/assignment1/source/background.jpg",bg);
	loadImage("E:/programming/cprogram/zheda_c/assignment1/source/plane.jpg",plImg);
	loadImage("E:/programming/cprogram/zheda_c/assignment1/source/bomb.jpg",bombImg);
	loadImage("E:/programming/cprogram/zheda_c/assignment1/source/bullet.jpg",bulletImg);
	beginPaint();
	drawbackground();
	//drawCannon();
	//putImageTransparent(plImg,20,40,100,50,RGB(253,252,250));
	//putImageTransparent(plImg,20,200,100,50,RGB(253,252,250));
	endPaint();
}

void drawbackground(void)
{
	putImage(bg,0,0);
}
void drawPlanelist(void)
{
	plane *tmp = plane_list->next;
	while(tmp)
	{
		putImageTransparent(plImg,tmp->x,tmp->y,100,50,RGB(255,255,255));
		tmp = tmp->next;
	}
}

void drawCannon(void)
{
	const int upWidth = 5;
	const int downWidth = 8;
	POINT p[] = 
	{
		{(Cannon.x_base - downWidth*cos(Cannon.angle/180.0*PI)),(Cannon.y_base - downWidth*sin(Cannon.angle/180.0*PI))},
		{Cannon.x_top - upWidth*cos(Cannon.angle/180.0*PI),Cannon.y_top - upWidth*sin(Cannon.angle/180.0*PI)},
		{Cannon.x_top + upWidth*cos(Cannon.angle/180.0*PI),Cannon.y_top + upWidth*sin(Cannon.angle/180.0*PI)},
		{Cannon.x_base + downWidth*cos(Cannon.angle/180.0*PI),Cannon.y_base + downWidth*sin(Cannon.angle/180.0*PI)}
	};
	setBrushColor(BLUE);
	ellipse(Cannon.x_base-downWidth,Cannon.y_base-downWidth,Cannon.x_base+downWidth,Cannon.y_base+downWidth);
	polygon(p,4);
}
void drawBulletlist(void)
{
	bullet *tmp = bullet_list->next;
	while(tmp)
	{
		putImageTransparent(bulletImg,tmp->x-13,tmp->y-20,30,30,RGB(255,255,255));
		tmp = tmp->next;
	}
}
