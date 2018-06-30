# include "model.h"
# include <stdlib.h>
# include <math.h>
# define GROUND 500
# define RIGHTBOUNDARY 900
plane *plane_list;
bomb *bomb_list;
bullet *bullet_list;
crash *crash_list;
//people *people_list;
cannon Cannon;


void initPlay(void)
{
	//对各对象的列表指针进行初始化
	//设置大炮的参数 xy如何设置 
	Cannon.x_base = 488; //488
	Cannon.y_base = 497; //497
	Cannon.x_top = 0;
	Cannon.y_top = 0;
	Cannon.angle = 0;
	
	//对飞机列表初始化 
	plane_list = (plane*)malloc(sizeof(plane));
	plane_list->x = 0;
	plane_list->y = 10;
	plane_list->velocity = 5;
	plane_list->bomb_cnt = 10;
	plane_list->hit = 0;
	plane_list->next = NULL;
	
	//对炸弹列表初始化 
	bomb_list = (bomb*)malloc(sizeof(bomb));
	bomb_list->x = 0;
	bomb_list->y = 0;
	bomb_list->velocity = 20;
	bomb_list->hit = 0;
	bomb_list->next = NULL;
	
	//对炮弹列表初始化 
	bullet_list = (bullet*)malloc(sizeof(bullet));
	bullet_list->x = 0;
	bullet_list->y = 0;
	bullet_list->angle = 0;
	bullet_list->hit = 0;
	bullet_list->velocity = 40;
	bullet_list->next = NULL;
	
	//对crash事件列表初始化 
	crash_list = (crash*)malloc(sizeof(crash));
	crash_list->x = 0;
	crash_list->y = 0;
	crash_list->cnt = 0;
	
}

void addPlane(void)
{
	/*
	创建一个飞机节点挂到飞机列表末尾，
	列表按照时间飞机产生的时间排列 
	*/ 
	plane *nplane,*tmp;
	nplane = (plane*)malloc(sizeof(struct plane));
	tmp = plane_list;
	
	if(nplane){
		nplane->x = 0;
		nplane->y = rand()%300; 
		//飞机的坐标x=0，y为一个0~400的随机数,
		//后期需要修改成界面上半部分 
		nplane->velocity = plane_list->velocity;
		nplane->bomb_cnt = 10;
		nplane->hit = 0;
		nplane->next = NULL;
		
		while(tmp->next)
			tmp = tmp->next;
		
		tmp->next = nplane;
	}
}

void addBomb(int x,int y)
{
	/*
	创建一个炸弹节点挂到炸弹列表末尾，
	列表按照时间炸弹产生的时间排列 
	炸弹的坐标由飞机的坐标提供 
	*/ 
	bomb *nbomb,*tmp;
	nbomb = (bomb*)malloc(sizeof(bomb));
	tmp = bomb_list;
	
	if(nbomb){
		nbomb->x = x;
		nbomb->y = y; 
		nbomb->velocity = bomb_list->velocity;
		nbomb->hit = 0;
		nbomb->next = NULL;
		while(tmp->next)
			tmp = tmp->next;
		
		tmp->next = nbomb;
	}
}

void addCrash(int x,int y)
{
	/*
	创建一个爆炸事件挂到爆炸列表末尾，
	*/ 
	crash *ncrash,*tmp;
	ncrash = (crash*)malloc(sizeof(crash));
	tmp = crash_list;
	
	if(ncrash){
		ncrash->x = x;
		ncrash->y = y; 
		ncrash->cnt = 0;
		while(tmp->next)
			tmp = tmp->next;
		
		tmp->next = ncrash;
	}
}

void addbullet(int x,int y,int angle)
{
	/*
	创建一个炮弹节点挂到炮弹列表末尾，
	列表按照时间炮弹产生的时间排列
	炮弹的坐标和出射角度由大炮给定 
	*/ 
	bullet *nbullet,*tmp;
	nbullet = (bullet*)malloc(sizeof(bullet));
	tmp = bullet_list;
	
	if(nbullet){
		nbullet->x = x;
		nbullet->y = y;
		nbullet->angle = angle;
		//飞机的坐标x=0，y为一个0~400的随机数,
		//后期需要修改成界面上半部分 
		nbullet->velocity = bullet_list->velocity;
		nbullet->hit = 0;
		nbullet->next = NULL;
		while(tmp->next)
			tmp = tmp->next;
		
		tmp->next = nbullet;
	}
}

void refreshPlane(plane *Plane_list)
{
	plane *parent, *current;
	parent = Plane_list;
	if (parent->next == NULL)
		return;
	else{
		current = parent->next;
		while(current)
		{
			current->x += current->velocity;
			if (current->x > RIGHTBOUNDARY || current->hit == 1){
				removeNextPlane(parent);
				current = parent->next;
			}
			else{
				parent = current;
				current = current->next;
			}	
		}
	}
}
 
void refreshBomb(bomb *Bomb_list)
{
	bomb *parent, *current;
	parent = Bomb_list;
	if (parent->next == NULL)
		return;
	else{
		current = parent->next;
		while(current)
		{
			current->y += current->velocity;
			if (current->y > GROUND || current->hit == 1){
				removeNextBomb(parent);
				current = parent->next;
			}
			else{
				parent = current;
				current = current->next;
			}	
		}
	}
}
void refreshBullet(bullet *Bullet_list)
{
	bullet *parent, *current;
	parent = Bullet_list;
	if (parent->next == NULL)
		return;
	else{
		current = parent->next;
		while(current)
		{
			current->y -= (int)((current->velocity)*cos(current->angle/180.0*PI));
			current->x += (int)((current->velocity)*sin(current->angle/180.0*PI));
			if (current->y < 0 || current->x < 0 || current->hit \
			|| current->x > RIGHTBOUNDARY || current->hit == 1){
				removeNextBullet(parent);
				current = parent->next;
			}
			else{
				parent = current;
				current = current->next;
			}	
		}
	}
}

void crashBullet(bullet *Bullet_list)
{
	plane *plt;
	bomb *bolist;
	bullet *curBullet = Bullet_list->next;
	int dist;
	while(curBullet){
		if(!curBullet->hit){
			plt = plane_list->next;
			while(plt){
				dist = distance(plt->x,plt->y,curBullet->x,curBullet->y);
				if (distance(plt->x,plt->y,curBullet->x,curBullet->y) <= 40)
				{
					plt->hit = curBullet->hit = 1;
					break;
				}
				else{
					plt = plt->next;
				}
			}
		}
		//printf("curBullet--distance:%d  hit %d\n",dist,curBullet->hit);
//		if(!curBullet->hit){
//			bolist = bomb_list->next;
//			while(bolist){
//				if (distance(bolist->x,bolist->y,curBullet->x,curBullet->y) <= 5)
//				{
//					bolist->hit = curBullet->hit = 1;
//					break;
//				}
//				else{
//					bolist = bolist->next;
//				}
//			}
//		}
		curBullet = curBullet->next;
	}
	
	
	}
void refreshCannon(void)
{
	const int radius = 60;
	Cannon.x_top = Cannon.x_base + radius*sin(Cannon.angle/180.0*PI);
	Cannon.y_top = Cannon.y_base - radius*cos(Cannon.angle/180.0*PI);
	//printf("cannon x_top = %d, cannon y_top = %d sin(angle) = %f \n",Cannon.x_top,Cannon.y_top,sin(Cannon.angle/180.0*PI));
}

void removeNextPlane(plane *Plane)
{
	plane *tmp;
	tmp = Plane->next;
	Plane->next = tmp->next;
	free(tmp);
}

void removeNextBomb(bomb *Bomb)
{
	bomb *tmp;
	tmp = Bomb->next;
	Bomb->next = tmp->next;
	free(tmp);
}

void removeNextBullet(bullet *Bullet)
{
	bullet *tmp;
	tmp = Bullet->next;
	Bullet->next = tmp->next;
	free(tmp);
}

void ThrowBomb(plane *Plane)
{
	
}
void Shoot(const cannon C)
{
	addbullet(C.x_top,C.y_top,C.angle);
}
void setCannon(int deta_angle)
{
	if (Cannon.angle + deta_angle < 90 &&Cannon.angle + deta_angle > -90)
	Cannon.angle += deta_angle;
}

int distance(int x1,int y1,int x2,int y2)
{
	return (int)sqrt((double)((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}


