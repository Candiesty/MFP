#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
/// <summary>
/// ��ʼǽ���ж� ���Ľ� 
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
void ChangeRoom(int Select)
{
	cleardevice();
	switch (Select)
	{
	case 1: 
	{

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
void Draw(int array[21][26])
{
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			switch (array[y][x])
			{
			case 0:setlinecolor(WHITE);break;
			case 1:setlinecolor(YELLOW);break;
			case 2:setlinecolor(GREEN);break;
			case 3:setlinecolor(RED);break;
			case 4:setlinecolor(BLUE);break;
			}
			rectangle(x*30, y*30, x*30+22, y * 30 + 22);
		}
	}
}


void main()
{
	int level, diffcult��score;//��Ϸ�ؿ�����Ϸ�Ѷȣ���Ϸ����
	initgraph(1280, 800);

	int Map[21][26];//������ʼ��ͼ,ֵΪ0����յأ�1Ϊǽ�ڣ�2Ϊ����3Ϊ��Ʒ��4Ϊ�����ţ�0�� 1�� 2�� 3�� 4��
	int* Mapp;//��ͼָ��
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			Mapp=&Map[y][x];
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
		case 13: {cleardevice();FlushBatchDraw();ChangeRoom(select), key = 0;};break;
		}
		InitialInterface(select);
		FlushBatchDraw();
		Sleep(33);
		EndBatchDraw();
	}
	closegraph();                                // �رջ�ͼ��Ļ
}
