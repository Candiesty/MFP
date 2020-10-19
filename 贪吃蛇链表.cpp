#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<fstream> 
#include <string>
#include <ctime>
#include<algorithm>
#include<time.h>
#define random(a,b) (rand()%(b-a)+a)
using namespace std;

struct Data
{
	double x;
	double y;
	int lasttime;
};
struct Node
{
	Data data;
	Node* next;
};
struct Snake
{
	double head_x;
	double head_y;
	int length;
	int direction;
	bool crash;
};
void CreatItem()
{
	srand(time(NULL));int x = (random(1, 1275));int y = random(1, 795);
	
}
/// <summary>
/// 碰撞判定
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <param name="r"></param>
/// <returns></returns>
bool IfCrash(double x1,double y1,double x2,double y2,double r)
{
	double d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (d < r) return true;
	else return false;
}
bool IfSnakeCrash(Node* headnode)
{
	Node* pnode = headnode->next;
	if (pnode)
	{
		Node* mnode = pnode->next;
		while (mnode)
		{
			if (IfCrash(pnode->data.x, pnode->data.y, mnode->data.x, mnode->data.y, 25))return true;
			mnode = mnode->next;
		}
		return false;
	}
	else return false;
}

/// <summary>
/// 绘制所需要说明的东西 已测试
/// </summary>
void Explain()
{
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("游戏说明"));
	settextstyle(30, 18, _T("normal"));
	outtextxy(160, 180, _T("使用AD键操控贪吃蛇转向，回车键确定，按Esc键可直接退出游戏"));
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
/// 暂停界面
/// </summary>
void DrawPause()
{
	cleardevice();
	settextstyle(50, 30, _T("normal"));
	outtextxy(300, 400, _T("游戏暂停，按空格以继续"));
	FlushBatchDraw();
}
/// <summary>
/// 粒子效果
/// </summary>
/// <param name="y"></param>
/// <param name="x"></param>
/// <param name="Map"></param>
/// <param name="score"></param>
/// <param name="level"></param>
/// <param name="time"></param>
void Granule(int y, int x, int Map[21][26], int score, int level, int time);
/// <summary>
/// 绘制积分榜
/// </summary>
/// <param name="rank"></param>
void DrawScore(int rank[], int score);
/// <summary>
/// 存储函数
/// </summary>
/// <param name="score"></param>
/// <param name="level"></param>
void Save(int rank[], int score, int level, int loadlevel);
/// <summary>
/// 退出界面的函数 有待加入积分功能
/// </summary>
/// <param name="score">积分</param>
void EndGame(int rank[], int score, int level, int loadlevel)
{
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 30, _T("normal"));
	if (level == 5) { outtextxy(120, 120, _T("恭喜过关")); }
	else { outtextxy(120, 120, _T("游戏结束")); }
	outtextxy(120, 180, _T("您的得分："));
	char num[10];
	sprintf_s(num, "%d", score);
	outtextxy(400, 180, num);
	outtextxy(600, 240, _T("按回车以退出"));
	Save(rank, level, score, loadlevel);
	ifstream fin("D:\\savel.txt", ios::in);	//从硬盘到内存
	for (int i = 0;i < 10;i++)
	{
		fin >> rank[i];
	}
	DrawScore(rank, score);
	FlushBatchDraw();
	int waitkey = 0;
	while (waitkey != 13)
	{
		if (_kbhit())
			waitkey = _getch();
	}
	exit(3);
}

void Creat(Node* foodhead)
{
	foodhead->data.x = random(50, 1230);
	foodhead->data.y = random(50, 750);
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
void ChangeRoom(int Select, bool* p, int* diffcult, int* plevel, int level, int* p_HaveChange, int loadlevel)
{
	cleardevice();
	switch (Select)
	{
	case 1:
	{
		*p = true;
	};break;
	case 2:
	{
		char key = 0;int select = 1;bool out = false;
		while (out == false)
		{
			BeginBatchDraw();
			if (_kbhit())
				key = _getch();
			switch (key)
			{
			case 'w': if (select != 1)
			{
				select -= 1;
				key = 0;
			};  break;
			case 's': if (select < loadlevel)
			{
				select += 1;
				key = 0;
			};  break;
			case 27: out = true;break;
			case 13: {*plevel = select;*p_HaveChange = 1;out = true;}break;
			}
			settextstyle(30, 16, _T("normal"));
			for (int i = 1;i <= 4;i++)
			{
				if (i == select)
				{
					settextcolor(RED), setlinecolor(RED);;
				}
				else if (i <= loadlevel)
				{
					settextcolor(WHITE), setlinecolor(WHITE);
				}
				else
				{
					settextcolor(DARKGRAY);setlinecolor(DARKGRAY);
				}
				rectangle(510, i * 120, 610, 100 + i * 120);
				switch (i)
				{
				case 1:outtextxy(520, 30 + i * 120, _T("关卡1"));break;
				case 2:outtextxy(520, 30 + i * 120, _T("关卡2"));break;
				case 3:outtextxy(520, 30 + i * 120, _T("关卡3"));break;
				case 4:outtextxy(520, 30 + i * 120, _T("关卡4"));break;
				}
				FlushBatchDraw();
			}
		};break;
	}
	case 3:
	{
		char key = 0;int select = 1;bool out = false;
		while (out == false)
		{
			BeginBatchDraw();
			if (_kbhit())
				key = _getch();
			switch (key)
			{
			case 'w': if (select != 1)
			{
				select -= 1;
				key = 0;
			};  break;
			case 's': if (select != 3)
			{
				select += 1;
				key = 0;
			};  break;
			case 27: out = true;break;
			case 13: {*diffcult = select;out = true;}break;
			}
			settextstyle(50, 30, _T("normal"));
			for (int i = 1;i <= 3;i++)
			{
				if (i == select)
				{
					settextcolor(RED), setlinecolor(RED);;
				}
				else
				{
					settextcolor(WHITE), setlinecolor(WHITE);
				}
				rectangle(500, i * 120, 780, 100 + i * 120);
				switch (i)
				{
				case 1:outtextxy(520, 30 + i * 120, _T("简单模式"));break;
				case 2:outtextxy(520, 30 + i * 120, _T("普通模式"));break;
				case 3:outtextxy(520, 30 + i * 120, _T("困难模式"));break;
				}
				FlushBatchDraw();
			}
		};break;
	}
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
/// 创建链表
/// </summary>
struct Node* CreateList()
{
	struct Node* headnode = (struct Node*)malloc(sizeof(struct Node));
	headnode->next = NULL;
	return headnode;
}
/// <summary>
/// 创建新蛇身
/// </summary>
struct Node* CreateNewNode(Data data)
{
	struct Node* node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = NULL;
	return node;
}
/// <summary>
/// 插入蛇身
/// </summary>
/// <param name="data"></param>
/// <param name="headnode"></param>
void InsertNode(Data data, Node* headnode)
{
	Node* node = CreateNewNode(data);Node* pnode = headnode->next;
	headnode->next = node;
	node->next = pnode;

}
/// <summary>
/// 绘制蛇
/// </summary>
/// <param name="headnode"></param>
void DrawSnake(Node* headnode)
{
	Node* pnode = headnode->next;
	while (pnode)
	{
		setfillcolor(GREEN);
		fillcircle(pnode->data.x, pnode->data.y, 15);
		FlushBatchDraw();
		pnode = pnode->next;
	}
}
/// <summary>
/// 改变长度
/// </summary>
/// <param name="headnode"></param>
/// <param name="Changenumber"></param>
void Changelength(Node* headnode, int Changenumber)
{
	Node* pnode = headnode->next;Node* load;Node* lastnode = headnode;
	while (pnode)
	{
		pnode->data.lasttime += Changenumber;
		if (pnode->data.lasttime <= 0)
		{
			lastnode->next = NULL;
			free(pnode);
			/*while (pnode)
			{
				load = pnode->next;
				free(pnode);
				pnode = load;
			}*/
			break;
		}
		lastnode = pnode;
		pnode = pnode->next;
	}
}

int main()
{
	Node* headnode = CreateList();
	Node* foodhead = CreateList();
	Node* Itemheadnode = CreateList();
	Snake snake = { 640,400,5,0 };
	snake = { 5,10,13,1 };int HaveChange = 0;int* p_HaveChange = &HaveChange;
	int level, diffcult, score;/*游戏关卡，游戏难度，游戏积分*/int* p_level = &level;int loadlevel;
	int rank[10];
	for (int i = 0;i < 10;i++)
	{
		rank[i] = 0;//积分初始化
	}
	ifstream fin("D:\\savel.txt", ios::in);	//从硬盘到内存
	if (!fin)
	{
		Save(rank, 1, 0, 1);
		level = 1;
		loadlevel = 1;
	}
	else
	{
		//导入排行榜
		for (int i = 0;i < 10;i++)
		{
			fin >> rank[i];
		}
		sort(rank, rank + 10);
		fin >> level;
	}
	loadlevel = level;
	int timeline = 1;//时间轴
	int* p_length = &snake.length;bool* p_crash = &snake.crash;
	diffcult = 1;score = 0;//难度123对应easy normal hard
	bool Startroom = false;/*跳转用函数*/int* p_diffcult = &diffcult;/*难度指针*/int TargetScore = 0;
	initgraph(1280, 800);
    bool* bp = &Startroom;


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
		case 'W': if (select != 1)
		{
			select -= 1;
			key = 0;
		};  break;
		case 's': if (select != 5)
		{
			select += 1;
			key = 0;
		};  break;
		case 'S': if (select != 5)
		{
			select += 1;
			key = 0;
		};  break;
		case 27: exit(4);
		case 13: {cleardevice();FlushBatchDraw();ChangeRoom(select, bp, p_diffcult, p_level, level, p_HaveChange, loadlevel), key = 0;};break;
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
	bool Stillin = false;/*判断食物是否存留于场上的函数*/bool next = false;bool* p_next = &next;;//下一个房间/指针
	key = 0;if (HaveChange == 0) { level = 1; }
	while (level <= 4)
	{
		TargetScore = 5000 * level;key = 0;snake = { 640,400,28, snake.direction };//初始化食物位置,预期分数,键位,长度
		int Tigger = 0;//毒草产生计数器
		int BoomTigger = 0;//炸弹产生计数器
		while (key != 'p')
		{
			if (_kbhit())
				key = _getch();
			switch (key)
			{
				case 'a':
					if (snake.direction != 0) snake.direction -= 60;
					else snake.direction = 280; 
					key = 0;break;
				case 'd':
					if (snake.direction != 360) snake.direction += 60;
					else snake.direction = 60;
					key = 0;break;
				case 32:
				{
					key = 0;
					DrawPause();
					while (key != 32)
					{
						if (_kbhit())
							key = _getch();
						Sleep(100);
					}
					key = 0;
			    }
			}
				BeginBatchDraw();
				snake.head_x += 30 * cos(snake.direction / 180.0);
				snake.head_y += 30 * sin(snake.direction / 180.0);
				if (snake.head_x < 5 || snake.head_x>1275 || snake.head_y < 5 || snake.head_y>795||IfSnakeCrash(headnode))EndGame(rank,score,level,loadlevel);
				Changelength(headnode,-1);
				InsertNode({ snake.head_x,snake.head_y,snake.length }, headnode);
				cleardevice();
				DrawSnake(headnode);
				FlushBatchDraw();
				if (snake.length < 1)EndGame(rank, score, level, loadlevel);

				//传送门

				if (next == true) { break; };
				
				EndBatchDraw();
				//积分系统
				score += (snake.length*5 / 3) * diffcult / 1.5;
			    Sleep(250/diffcult);
		}
		next = false;
		level += 1;
	}
	EndGame(rank, score, level, loadlevel);
	closegraph();                                // 关闭绘图屏幕
}

void Save(int rank[], int level, int score, int loadlevel)
{
	if (score > rank[0])rank[0] = score;
	sort(rank, rank + 10);
	ofstream fout("D:\\savel.txt", ios::out);	//调用构造函数打开文件
	for (int i = 0;i < 10;i++)
	{
		fout << rank[i];
		fout << ' ';
	}
	fout << max(level, loadlevel);
	fout.close();
}
void DrawScore(int rank[], int score)
{
	settextstyle(34, 24, _T("normal"));
	char num[10];int lock = 1;//锁一个变红
	for (int i = 0;i < 10;i++)
	{
		if ((rank[i] == score) && lock == 1)
		{
			settextcolor(RED);lock = 0;
		}
		else settextcolor(WHITE);
		sprintf_s(num, "%d", rank[i]);
		outtextxy(400, 750 - i * 50, num);
	}
	lock = 1;
	for (int i = 10;i > 0;i--)
	{
		if ((rank[10 - i] == score) && lock == 1)
		{
			settextcolor(RED);lock = 0;
		}
		else settextcolor(WHITE);
		sprintf_s(num, "%d", i);
		outtextxy(320, 750 - (10 - i) * 50, num);
	}
	settextstyle(50, 30, _T("normal"));
	settextcolor(WHITE);
	outtextxy(320, 235, _T("排行榜"));
}
void Granule(int y, int x, int Map[21][26], int score, int level, int time)
{
	setfillcolor(RED);
	solidcircle(x * 30 + 15, y * 30 + 15, time);
	FlushBatchDraw();
}