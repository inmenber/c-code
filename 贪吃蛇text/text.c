#include "taxt.h"


int main()
{
	#pragma warning (disable:4996) //��������
	grade = 0;
	max = 0;//��ʼ��ȫ�ֱ���
	system("title ̰����"); //���ô�������
	system("mode con cols=80 ��lines =30"); //���ô��ڵĴ�С
	cursor_yc();  //���ع��
	readgrade();  //����ʷ��¼�в�����߷�
	//writegrade(); //������߷�
	Initface_first(); //��ʼ������
	Initsnack();  //��ʼ����
	srand((unsigned int)time(NULL));  //����һ�����ֵ
	randfood();   //�������һ��ʳ��
	drawsnack(1);  //��ӡ��
	game();       //������Ϸ
	return 0;
}

