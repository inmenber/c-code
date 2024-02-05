#include "taxt.h"


//隐藏光标
void cursor_yc()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	curInfo.dwSize = 1; //如果没赋值的话，光标隐藏无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}
//光标跳转
void cursor_jump(int x,int y)
{
	COORD  pos; //定义光标位置的结构体变量
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

//颜色调整
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
}

//初始化界面
void Initface_first()
{
	color(5);
	for (int  i =0;i<ROW;i++)
	{
		for (int j =0;j<COL;j++)
		{
			if (j == 0 || j == COL - 1)
			{
				face[i][j] = WALL;
				cursor_jump(2 * j, i);
				printf("■");
			}
			else if (i == 0 || i == ROW - 1)
			{
				face[i][j] = WALL;
				cursor_jump(2 * j, i);
				printf("■");
			}
			else
			{
				face[i][j] = KONG;
			}
		}
	}
	color(7);
	cursor_jump(0, ROW);
	printf("当前得分%d", grade);
	cursor_jump(COL, ROW);
	printf("历史最高得分%d", max);

}

//查找最高分
void readgrade()
{
	FILE* pf = fopen("贪吃蛇最高纪录.txt", "r");
	if (pf == NULL)
	{
		pf = fopen("贪吃蛇最高纪录.txt", "w");
		fwrite(&max, sizeof(int), 1, pf);//将本局游戏数据存入
		
	}
		fseek(pf, 0, SEEK_SET);//是pf指向文件开头
		fread(&max, sizeof(int), 1, pf);
		fclose(pf);//关闭文件
		pf = NULL;
}

//更新最高分
void writegrade()
{
	FILE* pf = fopen("贪吃蛇最高纪录.txt", "w"); //打开文件，以写的方式
	if (pf == NULL)
	{
		printf("打开文件失败\n");
		exit(0);
	}
	
	
		fwrite(&grade, sizeof(int), 1, pf);//将本局游戏数据存入
		fclose(pf);//关闭文件
		pf = NULL;
	
}


//蛇的初始化
void Initsnack()
{
	snackhead.len = 2; //蛇身初始化为2
	snackhead.x = COL / 2; //默认出生位置为程序的最中间
	snackhead.y = ROW / 2;
	//初始化蛇身的坐标
	snackbody[0].x = COL / 2 - 1;
	snackbody[1].x = COL / 2 - 2;
	snackbody[0].y = ROW / 2;
	snackbody[1].y = ROW / 2;
	//标记舌头与蛇身
	face[snackhead.x][snackhead.y] = HEAD;
	face[snackbody[0].y][snackbody[0].x] = BODY;
	face[snackbody[1].y][snackbody[1].x] = BODY;
}

//随机生成食物
void randfood()
{
	int i, j;
	do
	{
		
		i = rand() % ROW;
		j = rand() & COL;

	} while (face[i][j] != KONG);//如果为空，再随机生成一个随机值
	face[i][j] = FOOD;
	color(6);//调整颜色
	cursor_jump(2 * j, i);//光标跳转
	printf("●");

}


//判断结束条件
void gameover(int x ,int y)
{
	//首先判断我们蛇头的下一个位置是不是食物
	if (face[snackhead.y + y][snackhead.x + x] == FOOD)
	{
		snackhead.len++;
		grade += 10;
		color(7);//变为白色
		cursor_jump(0, ROW);
		printf("当前得分%d", grade);
		randfood();
	}
	else if (face[snackhead.y + y][snackhead.x + x] == WALL || face[snackhead.y + y][snackhead.x + x] == BODY)
	{
		Sleep(1200);  //程序预留的反应时间

		system("cls");  //清空屏幕

		color(7); //变为白色

		cursor_jump(2 * (COL / 3), ROW / 3);
		if (grade > max)
		{
			printf("恭喜你，这是您的新纪录\n");
			printf("您的最高得分是%d,当前的得分为%d\n", max, grade);
			writegrade();
		}
		else if (grade == max)
		{
			printf("这个成绩和您的最高记录相同，请再接再厉\n");
			printf("您的最高得分是%d,当前的得分为%d\n", max, grade);
		}
		else if (grade < max)
		{
			printf("对不起，您未打破您的最高记录\n");
			printf("您的最高得分是%d,当前的得分为%d\n", max, grade);
		}
		cursor_jump(2 * 15, 22);
		printf("GAME OVER\n");
		while (1)
		{
			char ch;
			printf("是否继续进行游戏？\n");
			printf("y/n");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();//重新调用主函数，程序继续运行
			}
			else if (ch == 'n' || ch == 'N')
			{
				system("cls");
				exit(0);
			}
			else
			{
				
				printf("选择错误，请重新选择\n");
			}
		}
	}
}

//打印和覆盖蛇
void drawsnack(int flag)
{
	if (flag == 1)
	{
		color(10);
		cursor_jump(2 * snackhead.x, snackhead.y);
		printf("■"); //打印蛇头
		for (int i = 0; i < snackhead.len; i++)
		{
			cursor_jump(2 * snackbody[i].x, snackbody[i].y);
			printf("□"); //打印蛇身
		}
	}
	else  //覆盖蛇
	{
		if (snackbody[snackhead.len - 1].x != 0)  //防止len++后覆盖墙
		{
			//将后面的位置覆盖空格即可
			cursor_jump(2 * snackbody[snackhead.len - 1].x, snackbody[snackhead.len - 1].y);
			printf("  ");
		}
	}

}

//移动蛇
void movesnack(int x,int y)
{
	drawsnack(0); //先覆盖当前所显示的蛇
	face[snackbody[snackhead.len - 1].y][snackbody[snackhead.len - 1].x] = KONG; //蛇移动后蛇尾重新标记为空
	face[snackhead.y][snackhead.x] = BODY; //蛇移动后蛇头的位置变为蛇身
	//蛇移动后各个蛇身位置坐标需要更新
	for (int i = snackhead.len - 1; i > 0; i--)
	{
		snackbody[i].x = snackbody[i - 1].x;
		snackbody[i].y = snackbody[i - 1].y;
	}
	//蛇移动后蛇头位置信息变为第0个蛇身的位置信息
	snackbody[0].x = snackhead.x;
	snackbody[0].y = snackhead.y;
	//蛇头的位置更改
	snackhead.x = snackhead.x + x;
	snackhead.y = snackhead.y + y;
	drawsnack(1); //打印移动后的蛇
}

//执行按键
void run(int x, int y)
{
	int t = 0;
	while (1)
	{
		if (t == 0)
			t = 3000; //这里t越小，蛇移动速度越快（可以根据次设置游戏难度）
		while (--t)
		{
			if (kbhit() != 0) //若键盘被敲击，则退出循环
				break;
		}
		if (t == 0) //键盘未被敲击
		{
			gameover(x, y); //判断到达该位置后，是否得分与游戏结束
			movesnack(x, y); //移动蛇
		}
		else //键盘被敲击
		{
			break; //返回Game函数读取键值
		}
	}
}
//游戏主体逻辑函数
void game()
{
	int n = RIGHT; //开始游戏时，默认向后移动
	int tmp = 0; //记录蛇的移动方向
	goto first; //第一次进入循环先向默认方向前进
	while (1)
	{
		n = getch(); //读取键值
		//在执行前，需要对所读取的按键进行调整
		switch (n)
		{
		case UP:
		case DOWN: //如果敲击的是“上”或“下”
			if (tmp != LEFT && tmp != RIGHT) //并且上一次蛇的移动方向不是“左”或“右”
			{
				n = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
			}
			break;
		case LEFT:
		case RIGHT: //如果敲击的是“左”或“右”
			if (tmp != UP && tmp != DOWN) //并且上一次蛇的移动方向不是“上”或“下”
			{
				n = tmp; //那么下一次蛇的移动方向设置为上一次蛇的移动方向
			}
		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //这四个无需调整
		default:
			n = tmp; //其他键无效，默认为上一次蛇移动的方向
			break;
		}
	first: //第一次进入循环先向默认方向前进
		switch (n)
		{
		case UP: //方向键：上
			run(0, -1); //向上移动（横坐标偏移为0，纵坐标偏移为-1）
			tmp = UP; //记录当前蛇的移动方向
			break;
		case DOWN: //方向键：下
			run(0, 1); //向下移动（横坐标偏移为0，纵坐标偏移为1）
			tmp = DOWN; //记录当前蛇的移动方向
			break;
		case LEFT: //方向键：左
			run(-1, 0); //向左移动（横坐标偏移为-1，纵坐标偏移为0）
			tmp = LEFT; //记录当前蛇的移动方向
			break;
		case RIGHT: //方向键：右
			run(1, 0); //向右移动（横坐标偏移为1，纵坐标偏移为0）
			tmp = RIGHT; //记录当前蛇的移动方向
			break;
		case SPACE: //暂停
			system("pause>nul"); //暂停后按任意键继续
			break;
		case ESC: //退出
			system("cls"); //清空屏幕
			color(7); //颜色设置为白色
			cursor_jump(COL - 8, ROW / 2);
			printf("  游戏结束  ");
			cursor_jump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //重新开始
			system("cls"); //清空屏幕
			main(); //重新执行主函数
		}
	}
}