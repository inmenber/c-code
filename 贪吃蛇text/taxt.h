#pragma warning(disable:4996) 
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#define KONG 0//为空的情况
#define WALL 1//设置墙的宏
#define FOOD 2//设置食物的宏
#define HEAD 3//设置蛇头的宏
#define BODY 4//设置蛇身的宏

#define ROW 22 //游戏区行数
#define COL 42 //游戏区列数

#define UP 72 //上
#define DOWN 80 //下
#define LEFT 75 //左
#define RIGHT 77 //右
#define ESC 27 //退出
#define SPACE 32 //暂停


int max, grade; //全局变量
struct snackhead  //蛇头的结构体
{
	int len; //记录蛇长度
	int x;   //记录蛇头的x坐标
	int y;   //记录蛇头的y坐标
}snackhead;

struct snackbody  //蛇身的结构体
{
	int x;  //记录蛇身的x坐标
	int y;  //记录蛇身的y坐标
}snackbody[ROW*COL]; //开辟出足够的空间

int face[ROW][COL];  //标记所处的位置


//隐藏光标
void cursor_yc();
//光标跳转
void cursor_jump(int x,int y);
//颜色调整
void color(int c);
//初始化界面
void Initface_first();

//查找最高分
void readgrade();
//更新最高分
void writegrade();

//随机生成食物
void randfood();
//初始化蛇
void Initsnack();
//判断结束条件
void gameover(int x, int y);
//打印和覆盖蛇
void drawsnack(int flag);
//移动蛇
void movesnack();
//执行按键
void run();
//游戏主体函数
void game();
