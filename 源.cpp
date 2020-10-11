#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <string>
using namespace std;
/// <summary>
/// �˳�����ĺ��� �д�������ֹ���
/// </summary>
/// <param name="score">����</param>
void EndGame(int score)
{
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("��Ϸ����"));
	outtextxy(120, 180, _T("���ĵ÷֣�") + score);
	outtextxy(600, 240, _T("���س����˳�"));
	FlushBatchDraw();
	int waitkey = 0;
	while (waitkey != 13)
	{
		if (_kbhit())
			waitkey = _getch();
	}
	exit(0);
}
/// <summary>
/// ��ʼǽ���ж� ���Ľ� �ؿ����Ѷȣ�
/// </summary>
/// <param name="Mapp"></param>
/// <param name="y"></param>
/// <param name="x"></param>
void NewJudge(int* Mapp, int y, int x)
{
	if (y == 1 || y == 20)
		*Mapp = 1;
	else
	{
		if (x == 1 || x == 25)*Mapp = 1;
		else *Mapp = 0;
	}
}
/// <summary>
/// ��������Ҫ˵���Ķ��� �Ѳ���
/// </summary>
void Explain()
{
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("��Ϸ˵��"));
	settextstyle(30, 18, _T("normal"));
	outtextxy(160, 180, _T("ʹ��WASD�����вٿ�̰���ߣ��س���ȷ������Esc����ֱ���˳���Ϸ"));
	outtextxy(160, 220, _T("��ϷĿ�꣺��Ҫײ��ǽ���ϻ�ҧ�����������ܵľ��Ի�ø߷�"));
	outtextxy(760, 280, _T("�ı��밴�س��Լ���������"));
	FlushBatchDraw();
	int waitkey = 0;
	while (waitkey != 13)
	{
		if (_kbhit())
			waitkey = _getch();
	}
}
/// <summary>
/// ��ʼ������ƺ��� �Ѳ���
/// </summary>
/// <param name="Select"></param>
void InitialInterface(int Select)
{
	settextstyle(50, 30, _T("normal"));
	for (int i = 1;i <= 5;i++)
	{
		if (i == Select)
		{
			settextcolor(RED), setlinecolor(RED);;
		}
		else
		{
			settextcolor(WHITE), setlinecolor(WHITE);
		}
		rectangle(500, i * 120, 780, 100 + i * 120);
		outtextxy(540, 30 + i * 120, _T("newgame"));
		switch (i)
		{
		case 1:outtextxy(520, 30 + i * 120, _T("��ʼ��Ϸ"));break;
		case 2:outtextxy(520, 30 + i * 120, _T("�ؿ�ѡ��"));break;
		case 3:outtextxy(520, 30 + i * 120, _T("�Ѷ�ѡ��"));break;
		case 4:outtextxy(520, 30 + i * 120, _T("��Ϸ˵��"));break;
		case 5:outtextxy(520, 30 + i * 120, _T("�˳���Ϸ"));break;
		}
	}
}
/// <summary>
/// �Իس����ķ�Ӧ
/// </summary>
/// <param name="Select"></param>
void ChangeRoom(int Select, bool* p)
{
	cleardevice();
	switch (Select)
	{
	case 1:
	{
		*p = true;
	};break;
	case 2:;break;
	case 3:;break;
	case 4:
	{
		Explain();
		cleardevice();
		FlushBatchDraw();
	};break;
	case 5:exit(0);break;
	}
}
/// <summary>
/// ���ƻ��� �Ѳ���
/// </summary>
/// <param name="array"></param>
void Draw(int array[21][26],int score,int level)
{
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			switch (array[y][x])
			{
			case 0:setlinecolor(WHITE);break;
			case 1:setlinecolor(YELLOW);break;
			case 2:setlinecolor(RED);break;
			case 3:setlinecolor(BLUE);break;
			case 4:setlinecolor(DARKGRAY);break;
			case 5:setlinecolor(MAGENTA);break;
			}
			if (array[y][x] > 100)
			{
				setlinecolor(GREEN);
			}
			rectangle(x * 30, y * 30, x * 30 + 22, y * 30 + 22);
		}
	}
	settextstyle(50, 30, _T("normal"));
	outtextxy(800, 120, _T("�ؿ�:"));
	outtextxy(800, 180, _T("Ŀǰ�÷֣�"	));
}
/// <summary>
/// �����㷨 ������
/// </summary>
/// <param name="Mapp"></param>
/// <param name="num"></param>
/// <param name="Map"></param>
/// <param name="direction"></param>
/// <param name="length"></param>
/// <param name="head_x"></param>
/// <param name="head_y"></param>
void ControlSnake(int score, int Map[21][26], int direction, int* length, int* head_x, int* head_y)
{
	switch (direction)
	{
	case 1: *head_x++;break;
	case 2: *head_y--;break;
	case 3: *head_x--;break;
	case 4: *head_y++;break;
	}
	if (Map[*head_y][*head_x] != 0)
	{
		if (Map[*head_y][*head_x] == 1 || Map[*head_y][*head_x] > 100)
		{
			EndGame(score);
		}
		else if (Map[*head_y][*head_x] == 2) *length++;
	}
}


void main()
{
	struct Snake
	{
		int length;//������
		int head_x;//ͷλ��
		int head_y;//ͷλ��
		int direction;//��ͷ����,1234��������
		bool knock;//����Ƿ���ײ
	}snake = { 1,10,13,1,false };

	int level, diffcult, score;/*��Ϸ�ؿ�����Ϸ�Ѷȣ���Ϸ����*/score = 0;level = 1;diffcult = 1;//�Ѷ�123��Ӧeasy normal hard
	bool Startroom = false;//��ת�ú���
	initgraph(1280, 800);

	int Map[21][26];//������ʼ��ͼ,ֵΪ0����յأ�1Ϊǽ�ڣ�2Ϊʳ�3Ϊ�����ţ�4Ϊը����5Ϊ���� ����100Ϊ����0�� 1�� 2�� 3�� 4�� 5�� >100��
	int* Mapp;/*��ͼָ��*/bool* bp = &Startroom;
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			Mapp = &Map[y][x];
			NewJudge(Mapp, y, x);
		}
	}

	Explain();
	char key = 0;;//Ԥ����ȡ����
	int select = 1;//�û���ǰѡ����Ŀ
	while (key != 27)//������ȡ����
	{
		BeginBatchDraw();
		cleardevice();
		if (_kbhit())
			key = _getch();
		switch (key)
		{
		case 'w': if (select != 1)
		{
			select -= 1;
			key = 0;
		};  break;
		case 's': if (select != 5)
		{
			select += 1;
			key = 0;
		};  break;
		case 27: exit(0);
		case 13: {cleardevice();FlushBatchDraw();ChangeRoom(select, bp), key = 0;};break;
		}
		if (Startroom == true)break;
		InitialInterface(select);
		FlushBatchDraw();
		Sleep(33);
		EndBatchDraw();
	}
	cleardevice();
	FlushBatchDraw();
	EndBatchDraw();

	BeginBatchDraw();




	closegraph();                                // �رջ�ͼ��Ļ
}
