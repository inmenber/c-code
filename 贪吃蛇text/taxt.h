#pragma warning(disable:4996) 
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define KONG 0//Ϊ�յ����
#define WALL 1//����ǽ�ĺ�
#define FOOD 2//����ʳ��ĺ�
#define HEAD 3//������ͷ�ĺ�
#define BODY 4//��������ĺ�

#define ROW 22 //��Ϸ������
#define COL 42 //��Ϸ������

#define UP 72 //��
#define DOWN 80 //��
#define LEFT 75 //��
#define RIGHT 77 //��
#define ESC 27 //�˳�
#define SPACE 32 //��ͣ


int max, grade; //ȫ�ֱ���
struct snackhead  //��ͷ�Ľṹ��
{
	int len; //��¼�߳���
	int x;   //��¼��ͷ��x����
	int y;   //��¼��ͷ��y����
}snackhead;

struct snackbody  //����Ľṹ��
{
	int x;  //��¼�����x����
	int y;  //��¼�����y����
}snackbody[ROW*COL]; //���ٳ��㹻�Ŀռ�

int face[ROW][COL];  //���������λ��


//���ع��
void cursor_yc();
//�����ת
void cursor_jump(int x,int y);
//��ɫ����
void color(int c);
//��ʼ������
void Initface_first();

//������߷�
void readgrade();
//������߷�
void writegrade();

//�������ʳ��
void randfood();
//��ʼ����
void Initsnack();
//�жϽ�������
void gameover(int x, int y);
//��ӡ�͸�����
void drawsnack(int flag);
//�ƶ���
void movesnack();
//ִ�а���
void run();
//��Ϸ���庯��
void game();
