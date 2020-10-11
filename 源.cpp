#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <string>
using namespace std;
/// <summary>
/// 退出界面的函数 有待加入积分功能
/// </summary>
/// <param name="score">积分</param>
void EndGame(int score)
{
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("游戏结束"));
	outtextxy(120, 180, _T("您的得分：") + score);
	outtextxy(600, 240, _T("按回车以退出"));
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
/// 初始墙壁判定 待改进 关卡和难度？
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
/// 绘制画面 已测试
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
	outtextxy(800, 120, _T("关卡:"));
	outtextxy(800, 180, _T("目前得分："	));
}
/// <summary>
/// 核心算法 测试中
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
		int length;//蛇身长度
		int head_x;//头位置
		int head_y;//头位置
		int direction;//蛇头方向,1234东北西南
		bool knock;//检测是否碰撞
	}snake = { 1,10,13,1,false };

	int level, diffcult, score;/*游戏关卡，游戏难度，游戏积分*/score = 0;level = 1;diffcult = 1;//难度123对应easy normal hard
	bool Startroom = false;//跳转用函数
	initgraph(1280, 800);

	int Map[21][26];//创建初始地图,值为0代表空地，1为墙壁，2为食物，3为传送门，4为炸弹，5为毒草 大于100为蛇身；0白 1黄 2红 3蓝 4灰 5紫 >100绿
	int* Mapp;/*地图指针*/bool* bp = &Startroom;
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			Mapp = &Map[y][x];
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




	closegraph();                                // 关闭绘图屏幕
}
