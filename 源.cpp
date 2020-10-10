#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
/// <summary>
/// 初始墙壁判定 待改进 
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
/// 绘制所需要说明的东西 已测试
/// </summary>
void Explain()
{
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("游戏说明"));
	settextstyle(30, 18, _T("normal"));
	outtextxy(160, 180, _T("使用WASD键进行操控贪吃蛇，回车键确定，按Esc键可直接退出游戏"));
	outtextxy(160, 220, _T("游戏目标：不要撞到墙壁上或咬到自身，存活尽可能的久以获得高分"));
	outtextxy(760, 280, _T("阅毕请按回车以继续。。。"));
	FlushBatchDraw();
	int waitkey = 0;
	while (waitkey != 13)
	{
		if (_kbhit())
			waitkey = _getch();
	}
}
/// <summary>
/// 初始界面绘制函数 已测试
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
		case 1:outtextxy(520, 30 + i * 120, _T("开始游戏"));break;
		case 2:outtextxy(520, 30 + i * 120, _T("关卡选择"));break;
		case 3:outtextxy(520, 30 + i * 120, _T("难度选择"));break;
		case 4:outtextxy(520, 30 + i * 120, _T("游戏说明"));break;
		case 5:outtextxy(520, 30 + i * 120, _T("退出游戏"));break;
		}
	}
}
/// <summary>
/// 对回车键的反应
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
/// 绘制画面 已测试
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
	int level, diffcult，score;//游戏关卡，游戏难度，游戏积分
	initgraph(1280, 800);

	int Map[21][26];//创建初始地图,值为0代表空地，1为墙壁，2为蛇身，3为物品，4为传送门；0白 1黄 2绿 3红 4蓝
	int* Mapp;//地图指针
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			Mapp=&Map[y][x];
			NewJudge(Mapp, y, x);
		}
	}

	Explain();
	char key = 0;;//预备获取按键
	int select = 1;//用户当前选择项目
	while (key != 27)//按键获取部分
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
	closegraph();                                // 关闭绘图屏幕
}
