#include "taxt.h"


//���ع��
void cursor_yc()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����
	curInfo.dwSize = 1; //���û��ֵ�Ļ������������Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}
//�����ת
void cursor_jump(int x,int y)
{
	COORD  pos; //������λ�õĽṹ�����
	pos.X = x; //������
	pos.Y = y; //������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

//��ɫ����
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
}

//��ʼ������
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
				printf("��");
			}
			else if (i == 0 || i == ROW - 1)
			{
				face[i][j] = WALL;
				cursor_jump(2 * j, i);
				printf("��");
			}
			else
			{
				face[i][j] = KONG;
			}
		}
	}
	color(7);
	cursor_jump(0, ROW);
	printf("��ǰ�÷�%d", grade);
	cursor_jump(COL, ROW);
	printf("��ʷ��ߵ÷�%d", max);

}

//������߷�
void readgrade()
{
	FILE* pf = fopen("̰������߼�¼.txt", "r");
	if (pf == NULL)
	{
		pf = fopen("̰������߼�¼.txt", "w");
		fwrite(&max, sizeof(int), 1, pf);//��������Ϸ���ݴ���
		
	}
		fseek(pf, 0, SEEK_SET);//��pfָ���ļ���ͷ
		fread(&max, sizeof(int), 1, pf);
		fclose(pf);//�ر��ļ�
		pf = NULL;
}

//������߷�
void writegrade()
{
	FILE* pf = fopen("̰������߼�¼.txt", "w"); //���ļ�����д�ķ�ʽ
	if (pf == NULL)
	{
		printf("���ļ�ʧ��\n");
		exit(0);
	}
	
	
		fwrite(&grade, sizeof(int), 1, pf);//��������Ϸ���ݴ���
		fclose(pf);//�ر��ļ�
		pf = NULL;
	
}


//�ߵĳ�ʼ��
void Initsnack()
{
	snackhead.len = 2; //�����ʼ��Ϊ2
	snackhead.x = COL / 2; //Ĭ�ϳ���λ��Ϊ��������м�
	snackhead.y = ROW / 2;
	//��ʼ�����������
	snackbody[0].x = COL / 2 - 1;
	snackbody[1].x = COL / 2 - 2;
	snackbody[0].y = ROW / 2;
	snackbody[1].y = ROW / 2;
	//�����ͷ������
	face[snackhead.x][snackhead.y] = HEAD;
	face[snackbody[0].y][snackbody[0].x] = BODY;
	face[snackbody[1].y][snackbody[1].x] = BODY;
}

//�������ʳ��
void randfood()
{
	int i, j;
	do
	{
		
		i = rand() % ROW;
		j = rand() & COL;

	} while (face[i][j] != KONG);//���Ϊ�գ����������һ�����ֵ
	face[i][j] = FOOD;
	color(6);//������ɫ
	cursor_jump(2 * j, i);//�����ת
	printf("��");

}


//�жϽ�������
void gameover(int x ,int y)
{
	//�����ж�������ͷ����һ��λ���ǲ���ʳ��
	if (face[snackhead.y + y][snackhead.x + x] == FOOD)
	{
		snackhead.len++;
		grade += 10;
		color(7);//��Ϊ��ɫ
		cursor_jump(0, ROW);
		printf("��ǰ�÷�%d", grade);
		randfood();
	}
	else if (face[snackhead.y + y][snackhead.x + x] == WALL || face[snackhead.y + y][snackhead.x + x] == BODY)
	{
		Sleep(1200);  //����Ԥ���ķ�Ӧʱ��

		system("cls");  //�����Ļ

		color(7); //��Ϊ��ɫ

		cursor_jump(2 * (COL / 3), ROW / 3);
		if (grade > max)
		{
			printf("��ϲ�㣬���������¼�¼\n");
			printf("������ߵ÷���%d,��ǰ�ĵ÷�Ϊ%d\n", max, grade);
			writegrade();
		}
		else if (grade == max)
		{
			printf("����ɼ���������߼�¼��ͬ�����ٽ�����\n");
			printf("������ߵ÷���%d,��ǰ�ĵ÷�Ϊ%d\n", max, grade);
		}
		else if (grade < max)
		{
			printf("�Բ�����δ����������߼�¼\n");
			printf("������ߵ÷���%d,��ǰ�ĵ÷�Ϊ%d\n", max, grade);
		}
		cursor_jump(2 * 15, 22);
		printf("GAME OVER\n");
		while (1)
		{
			char ch;
			printf("�Ƿ����������Ϸ��\n");
			printf("y/n");
			scanf("%c", &ch);
			if (ch == 'y' || ch == 'Y')
			{
				system("cls");
				main();//���µ����������������������
			}
			else if (ch == 'n' || ch == 'N')
			{
				system("cls");
				exit(0);
			}
			else
			{
				
				printf("ѡ�����������ѡ��\n");
			}
		}
	}
}

//��ӡ�͸�����
void drawsnack(int flag)
{
	if (flag == 1)
	{
		color(10);
		cursor_jump(2 * snackhead.x, snackhead.y);
		printf("��"); //��ӡ��ͷ
		for (int i = 0; i < snackhead.len; i++)
		{
			cursor_jump(2 * snackbody[i].x, snackbody[i].y);
			printf("��"); //��ӡ����
		}
	}
	else  //������
	{
		if (snackbody[snackhead.len - 1].x != 0)  //��ֹlen++�󸲸�ǽ
		{
			//�������λ�ø��ǿո񼴿�
			cursor_jump(2 * snackbody[snackhead.len - 1].x, snackbody[snackhead.len - 1].y);
			printf("  ");
		}
	}

}

//�ƶ���
void movesnack(int x,int y)
{
	drawsnack(0); //�ȸ��ǵ�ǰ����ʾ����
	face[snackbody[snackhead.len - 1].y][snackbody[snackhead.len - 1].x] = KONG; //���ƶ�����β���±��Ϊ��
	face[snackhead.y][snackhead.x] = BODY; //���ƶ�����ͷ��λ�ñ�Ϊ����
	//���ƶ����������λ��������Ҫ����
	for (int i = snackhead.len - 1; i > 0; i--)
	{
		snackbody[i].x = snackbody[i - 1].x;
		snackbody[i].y = snackbody[i - 1].y;
	}
	//���ƶ�����ͷλ����Ϣ��Ϊ��0�������λ����Ϣ
	snackbody[0].x = snackhead.x;
	snackbody[0].y = snackhead.y;
	//��ͷ��λ�ø���
	snackhead.x = snackhead.x + x;
	snackhead.y = snackhead.y + y;
	drawsnack(1); //��ӡ�ƶ������
}

//ִ�а���
void run(int x, int y)
{
	int t = 0;
	while (1)
	{
		if (t == 0)
			t = 3000; //����tԽС�����ƶ��ٶ�Խ�죨���Ը��ݴ�������Ϸ�Ѷȣ�
		while (--t)
		{
			if (kbhit() != 0) //�����̱��û������˳�ѭ��
				break;
		}
		if (t == 0) //����δ���û�
		{
			gameover(x, y); //�жϵ����λ�ú��Ƿ�÷�����Ϸ����
			movesnack(x, y); //�ƶ���
		}
		else //���̱��û�
		{
			break; //����Game������ȡ��ֵ
		}
	}
}
//��Ϸ�����߼�����
void game()
{
	int n = RIGHT; //��ʼ��Ϸʱ��Ĭ������ƶ�
	int tmp = 0; //��¼�ߵ��ƶ�����
	goto first; //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
	while (1)
	{
		n = getch(); //��ȡ��ֵ
		//��ִ��ǰ����Ҫ������ȡ�İ������е���
		switch (n)
		{
		case UP:
		case DOWN: //����û����ǡ��ϡ����¡�
			if (tmp != LEFT && tmp != RIGHT) //������һ���ߵ��ƶ������ǡ��󡱻��ҡ�
			{
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
			}
			break;
		case LEFT:
		case RIGHT: //����û����ǡ��󡱻��ҡ�
			if (tmp != UP && tmp != DOWN) //������һ���ߵ��ƶ������ǡ��ϡ����¡�
			{
				n = tmp; //��ô��һ���ߵ��ƶ���������Ϊ��һ���ߵ��ƶ�����
			}
		case SPACE:
		case ESC:
		case 'r':
		case 'R':
			break; //���ĸ��������
		default:
			n = tmp; //��������Ч��Ĭ��Ϊ��һ�����ƶ��ķ���
			break;
		}
	first: //��һ�ν���ѭ������Ĭ�Ϸ���ǰ��
		switch (n)
		{
		case UP: //���������
			run(0, -1); //�����ƶ���������ƫ��Ϊ0��������ƫ��Ϊ-1��
			tmp = UP; //��¼��ǰ�ߵ��ƶ�����
			break;
		case DOWN: //���������
			run(0, 1); //�����ƶ���������ƫ��Ϊ0��������ƫ��Ϊ1��
			tmp = DOWN; //��¼��ǰ�ߵ��ƶ�����
			break;
		case LEFT: //���������
			run(-1, 0); //�����ƶ���������ƫ��Ϊ-1��������ƫ��Ϊ0��
			tmp = LEFT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case RIGHT: //���������
			run(1, 0); //�����ƶ���������ƫ��Ϊ1��������ƫ��Ϊ0��
			tmp = RIGHT; //��¼��ǰ�ߵ��ƶ�����
			break;
		case SPACE: //��ͣ
			system("pause>nul"); //��ͣ�����������
			break;
		case ESC: //�˳�
			system("cls"); //�����Ļ
			color(7); //��ɫ����Ϊ��ɫ
			cursor_jump(COL - 8, ROW / 2);
			printf("  ��Ϸ����  ");
			cursor_jump(COL - 8, ROW / 2 + 2);
			exit(0);
		case 'r':
		case 'R': //���¿�ʼ
			system("cls"); //�����Ļ
			main(); //����ִ��������
		}
	}
}