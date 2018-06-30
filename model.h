#ifndef __MODE__
#define __NODE__
#include <math.h>
#define PI 3.1415926
typedef struct cannon{
	int x_base;
	int y_base;
	int x_top;
	int y_top;
	int angle;
} cannon;

typedef struct plane{
	int x;
	int y;
	int velocity;
	int bomb_cnt;
	int hit;
	struct plane *next;
} plane;

typedef struct bomb{
	int x;
	int y;
	int velocity;
	int hit;
	struct bomb *next;
} bomb;

typedef struct bullet{
	int x;
	int y;
	int angle;
	int velocity;
	int hit;
	struct bullet *next;
} bullet;

typedef struct crash{
	int x;
	int y;
	int cnt;
	struct crash *next;
} crash;

//typedef struct people{
//	int x;
//	int y;
//	int angle;
//	int velocity;
//	struct people *next;
//} people;
extern cannon Cannon;
extern plane *plane_list;
extern bomb *bomb_list;
extern bullet *bullet_list;
extern crash *crash_list;
//extern people *people_list;
	
void initPlay(void);//��ʼ����Ϸ

void addPlane(void);//����Ļ�����ӷɻ����߶����
void addBomb(int x,int y);//�ӷɻ��õ����꣬�ų�һ��ը��
void addbullet(int x,int y,int angle);
//�ڰ��¿ո�ʱ������һ���ڵ�������ͽǶ��ɴ��ڸ���
void addCrash(int x,int y); 
void refreshPlane(plane *Plane_list);
void refreshBomb(bomb *Bomb_list);
void refreshBullet(bullet *Bullet_list);
void refreshCannon(void);
//void refreshPeople(people *People);
void removeNextPlane(plane *Plane);
void removeNextBomb(bomb *Bomb);
void removeNextBullet(bullet *Bullet);
void crashBullet(bullet *Bullet_list); 
void ThrowBomb(plane *Plane);
void Shoot(const cannon C);//��ȡ����״̬������һ���ڵ�
void setCannon(int);
int distance(int x1,int y1,int x2,int y2);
#endif
