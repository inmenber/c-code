#include "taxt.h"


int main()
{
	#pragma warning (disable:4996) //消除警告
	grade = 0;
	max = 0;//初始化全局变量
	system("title 贪吃蛇"); //设置窗口名称
	system("mode con cols=80 ，lines =30"); //设置窗口的大小
	cursor_yc();  //隐藏光标
	readgrade();  //在历史记录中查找最高分
	//writegrade(); //更新最高分
	Initface_first(); //初始化界面
	Initsnack();  //初始化蛇
	srand((unsigned int)time(NULL));  //设置一个随机值
	randfood();   //随机生成一个食物
	drawsnack(1);  //打印蛇
	game();       //进入游戏
	return 0;
}

