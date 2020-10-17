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
/*int* Mapp;
for (int y = 1;y < 21;y++)
{
	for (int x = 1;x < 26;x++)
	{
		Mapp = &Map[y][x];

	}
}*//*��׼��ģ��*/

/// <summary>
/// ������Χ�ߵ�����
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <returns></returns>
int CountSnake(int Map[21][26], int y, int x)
{
	int countSnake = 0;int countWall=0;
	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			if (Map[y - 1 + i][x - 1 + j] > 100)
			{
				countSnake++;
			}
			if (Map[y - 1 + i][x - 1 + j] ==1)
			{
				countWall++;
			}
		}
	}
	return countSnake+countWall*2;
}
/// <summary>
/// ��������֮��ľ���
/// </summary>
/// <param name="x1"></param>
/// <param name="y1"></param>
/// <param name="x2"></param>
/// <param name="y2"></param>
/// <returns></returns>
double Distance(int x1, int y1, int x2, int y2)
{
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
/// <summary>
/// �ҵ�ʳ�����겢���
/// </summary>
/// <param name="Map"></param>
/// <param name="p_x"></param>
/// <param name="p_y"></param>
void FindFood(int Map[21][26], int* p_x, int* p_y)
{
	for (int y=1;y < 21;y++)
	{
		for (int x=1;x < 26;x++)
		{
			if (Map[y][x] == 2)
			{
				*p_x = x;
				*p_y = y;
				return;
			}
		}
	}
	*p_x = 13;
	*p_y = 10;
	return;
}
/// <summary>
/// 
/// </summary>
/// <param name="Map"></param>
/// <param name="y"></param>
/// <param name="x"></param>
/// <returns></returns>
int ValueJudge(int Map[21][26], int snake_y, int snake_x)
{
	int food_x = 0;int food_y = 0;int* p_food_x = &food_x;int* p_food_y = &food_y;
	FindFood(Map, p_food_x, p_food_y);
	double diretion[4] = { 1,1,1,1 };
	if ((Map[snake_y][snake_x+1] == 1) || (Map[snake_y][snake_x+1] > 100))
	{
		diretion[0] = 999999;
	}
	else
	{
		if (Distance(food_x, food_y, snake_x + 1, snake_y) < 0.5)diretion[0] = 0;
		else diretion[0] = Distance(food_x,food_y, snake_x + 1, snake_y);
	}
	if ((Map[snake_y][snake_x - 1] == 1) || (Map[snake_y][snake_x - 1] > 100))
	{
		diretion[2] = 999999;
	}
	else
	{
		if (Distance(food_x, food_y, snake_x - 1, snake_y) < 0.5)diretion[2] = 0;
		else diretion[2] = Distance(food_x, food_y, snake_x - 1, snake_y);
	}
	if ((Map[snake_y-1][snake_x ] == 1) || (Map[snake_y-1][snake_x] > 100))
	{
		diretion[1] = 999999;
	}
	else
	{
		if (Distance(food_x, food_y, snake_x, snake_y+1) < 0.5)diretion[1] = 0;
		else diretion[1] = Distance(food_x, food_y, snake_x , snake_y-1);
	}
	if ((Map[snake_y + 1][snake_x] == 1) || (Map[snake_y + 1][snake_x] > 100))
	{
		diretion[3] = 999999;
	}
	else
	{
		if (Distance(food_x, food_y, snake_x, snake_y-1) < 0.5)diretion[3] = 0;
		else diretion[3] = Distance(food_x, food_y, snake_x, snake_y + 1);
	}
	int nummin = 999999;int load = 0;
	for (int i = 0;i < 4;i++)
	{
		if (diretion[i] <= nummin) { nummin = diretion[i];load = i; }
	}
	return load + 1;
}
/// <summary>
/// ��������
/// </summary>
/// <param name="y"></param>
/// <param name="x"></param>
/// <param name="Map"></param>
/// <param name="score"></param>
/// <param name="level"></param>
/// <param name="time"></param>
void Granule(int y, int x, int Map[21][26], int score, int level, int time);
/// <summary>
/// ���ƻ��ְ�
/// </summary>
/// <param name="rank"></param>
void DrawScore(int rank[], int score);
/// <summary>
/// �洢����
/// </summary>
/// <param name="score"></param>
/// <param name="level"></param>
void Save(int rank[], int score, int level, int loadlevel);
/// <summary>
/// ��ͣ����
/// </summary>
void DrawPause()
{
	cleardevice();
	settextstyle(50, 30, _T("normal"));
	outtextxy(300, 400, _T("��Ϸ��ͣ�����ո��Լ���"));
	FlushBatchDraw();
}
/// <summary>
/// ������ʼ��ͼģ��
/// </summary>
/// <param name="Map">����</param>
/// <param name="level">�ؿ�</param>
void CreatMap(int Map[21][26], int level)
{
	int* Mapp;

	if (level >= 3)
	{
		for (int y = 2;y < 5;y++)
		{
			for (int x = 2;x < 5;x++)
			{
				Mapp = &Map[y][x];
				*Mapp = 1;
			}
		}
		for (int y = 17;y < 21;y++)
		{
			for (int x = 2;x < 5;x++)
			{
				Mapp = &Map[y][x];
				*Mapp = 1;
			}
		}
		for (int y = 17;y < 21;y++)
		{
			for (int x = 22;x < 25;x++)
			{
				Mapp = &Map[y][x];
				*Mapp = 1;
			}
		}
		for (int y = 2;y < 5;y++)
		{
			for (int x = 22;x < 25;x++)
			{
				Mapp = &Map[y][x];
				*Mapp = 1;
			}
		}
	}

	if (level == 4)
	{
		for (int y = 1;y < 21;y++)
		{
			for (int x = 1;x < 26;x++)
			{
				if (y == 2)
				{
					Mapp = &Map[y][x];
					*Mapp = 1;
				}
				else if (y == 19)
				{
					Mapp = &Map[y][x];
					*Mapp = 1;
				}
				else if (x == 2)
				{
					Mapp = &Map[y][x];
					*Mapp = 1;
				}
				else if (x == 24)
				{
					Mapp = &Map[y][x];
					*Mapp = 1;
				}
			}
		}
	}
}
/// <summary>
/// �˳�����ĺ��� �д�������ֹ���
/// </summary>
/// <param name="score">����</param>
void EndGame(int rank[], int score, int level, int loadlevel)
{
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 30, _T("normal"));
	if (level == 5) { outtextxy(120, 120, _T("��ϲ����")); }
	else { outtextxy(120, 120, _T("��Ϸ����")); }
	outtextxy(120, 180, _T("���ĵ÷֣�"));
	char num[10];
	sprintf_s(num, "%d", score);
	outtextxy(400, 180, num);
	outtextxy(600, 240, _T("���س����˳�"));
	Save(rank, level, score, loadlevel);
	ifstream fin("D:\\save.txt", ios::in);	//��Ӳ�̵��ڴ�
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
/// �������
/// </summary>
/// <param name="Map"></param>
/// <param name="kind">1Ϊʳ��2Ϊը��3Ϊ����</param>
/// <returns></returns>
void Creat(int Map[21][26], int kind)
{
	srand(time(NULL) + rand() % 1000);int y = random(2, 19);int x = random(2, 24);
	for (;y < 21;y++)
	{
		for (;x < 26;x++)
		{
			if (Map[y][x] == 0)
			{
				int* Mapp = &Map[y][x];
				if (kind == 1)
				{
					*Mapp = 2;
				}
				else if (kind == 2)
				{
					*Mapp = 4;
				}
				else if (kind == 3)
				{
					*Mapp = 5;
				}
				return;
			}
		}
	}
	srand(time(NULL) + rand() % 1000);y = random(2, 19);x = random(2, 24);
	for (;y < 21;y++)
	{
		for (;x < 26;x++)
		{
			if (Map[y][x] == 0)
			{
				int* Mapp = &Map[y][x];
				*Mapp = 2;
				return;
			}
		}
	}
	return;
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
				case 1:outtextxy(520, 30 + i * 120, _T("�ؿ�1"));break;
				case 2:outtextxy(520, 30 + i * 120, _T("�ؿ�2"));break;
				case 3:outtextxy(520, 30 + i * 120, _T("�ؿ�3"));break;
				case 4:outtextxy(520, 30 + i * 120, _T("�ؿ�4"));break;
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
				case 1:outtextxy(520, 30 + i * 120, _T("��ģʽ"));break;
				case 2:outtextxy(520, 30 + i * 120, _T("��ͨģʽ"));break;
				case 3:outtextxy(520, 30 + i * 120, _T("����ģʽ"));break;
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
/// ���ƻ��� �Ѳ���
/// </summary>
/// <param name="array"></param>
void Draw(int array[21][26], int score, int level)
{
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			switch (array[y][x])
			{
			case 0:setfillcolor(WHITE);break;
			case 1:setfillcolor(YELLOW);break;
			case 2:setfillcolor(RED);break;
			case 3:setfillcolor(BLUE);break;
			case 4:setfillcolor(DARKGRAY);break;
			case 5:setfillcolor(MAGENTA);break;
			}
			if (array[y][x] > 100)
			{
				setfillcolor(GREEN);
			}
			solidrectangle(x * 30, y * 30, x * 30 + 30, y * 30 + 30);
		}
	}
	settextstyle(50, 30, _T("normal"));
	outtextxy(800, 120, _T("�ؿ�:"));
	outtextxy(800, 180, _T("Ŀǰ�÷֣�"));
	char num[10];
	sprintf_s(num, "%d", level);
	outtextxy(1000, 120, num);
	sprintf_s(num, "%d", score);
	outtextxy(1060, 180, num);
}
/// <summary>
/// �ı䲽���㷨
/// </summary>
/// <param name="Map"></param>
/// <param name="Change"></param>
void ChangeLength(int Map[21][26], int Change)
{
	int* Mapp;
	for (int y = 1;y < 21;y++)
	{
		for (int x = 1;x < 26;x++)
		{
			Mapp = &Map[y][x];
			if (*Mapp > 100)
			{
				*Mapp += Change;
				if (*Mapp <= 100) { *Mapp = 0; }
			}
		}
	}
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
int ControlSnake(int score, int Map[21][26], int direction, int* length, int* head_x, int* head_y, bool* crash, bool* next, int level, int rank[], int loadlevel)
{
	*crash = false;
	switch (direction)
	{
	case 1: *head_x += 1;break;
	case 2: *head_y -= 1;break;
	case 3: *head_x -= 1;break;
	case 4: *head_y += 1;break;
	}
	int* Mapp;Mapp = &Map[*head_y][*head_x];
	if (*Mapp != 0)
	{
		*crash = true;
		if (Map[*head_y][*head_x] == 1 || Map[*head_y][*head_x] > 100)//ײǽ������ײ�Լ�
		{
			EndGame(rank, score, level, loadlevel);
		}
		else if (Map[*head_y][*head_x] == 2)//ʳ���ж�
		{
			ChangeLength(Map, 1);
			*length += 1;
			*Mapp = 101 + *length;
			ChangeLength(Map, -1);
			return 1;
		}
		else if (*Mapp == 3)
		{
			*next = true;
		}
		else if (*Mapp == 4)//ը���ж�
		{
			if (*length % 2 == 0)
			{
				ChangeLength(Map, *length / (-2));
				*length = *length / 2;
			}
			else
			{
				ChangeLength(Map, (*length + 1) / (-2));
				*length += (*length + 1) / (-2);
			}
		}
		else if (*Mapp == 5)//ǡ����
		{
			ChangeLength(Map, -1);
			*length -= 1;
		}
	}
	*Mapp = 101 + *length;
	ChangeLength(Map, -1);
	return 0;
}
void main()
{
	struct Snake
	{
		int length;//������
		int head_x;//ͷλ��
		int head_y;//ͷλ��
		int direction;//��ͷ����,1234��������
		bool crash;//��ײ���
	}snake = { 5,10,13,1 };int HaveChange = 0;int* p_HaveChange = &HaveChange;
	int level, diffcult, score;/*��Ϸ�ؿ�����Ϸ�Ѷȣ���Ϸ����*/int* p_level = &level;int loadlevel;
	int rank[10];
	for (int i = 0;i < 10;i++)
	{
		rank[i] = 0;//���ֳ�ʼ��
	}
	ifstream fin("D:\\save.txt", ios::in);	//��Ӳ�̵��ڴ�
	if (!fin)
	{
		Save(rank, 1, 0, 1);
		level = 1;
		loadlevel = 1;
	}
	else
	{
		//�������а�
		for (int i = 0;i < 10;i++)
		{
			fin >> rank[i];
		}
		sort(rank, rank + 10);
		fin >> level;
	}
	loadlevel = level;
	int timeline = 1;//ʱ����
	int* p_length = &snake.length;int* p_head_x = &snake.head_x;int* p_head_y = &snake.head_y;bool* p_crash = &snake.crash;
	diffcult = 1;score = 0;//�Ѷ�123��Ӧeasy normal hard
	bool Startroom = false;/*��ת�ú���*/int* p_diffcult = &diffcult;/*�Ѷ�ָ��*/int TargetScore = 0;
	initgraph(1280, 800);

	int Map[21][26];//������ʼ��ͼ,ֵΪ0����յأ�1Ϊǽ�ڣ�2Ϊʳ�3Ϊ�����ţ�4Ϊը����5Ϊ���� ����100Ϊ����0�� 1�� 2�� 3�� 4�� 5�� >100��
	int* Mapp;/*��ͼָ��*/bool* bp = &Startroom;


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
	bool Stillin = false;/*�ж�ʳ���Ƿ�����ڳ��ϵĺ���*/bool next = false;bool* p_next = &next;;//��һ������/ָ��
	key = 0;if (HaveChange == 0) { level = 1; }
	while (level <= 4)
	{
		for (int y = 1;y < 21;y++)
		{
			for (int x = 1;x < 26;x++)
			{
				Mapp = &Map[y][x];
				NewJudge(Mapp, y, x);
			}
		}/*��ʼ����ͼ*/
		//�����ص�ͼ
		CreatMap(Map, level);

		//��������ϵͳ
		timeline = 1;/*ʱ�����һ */int timeplay = 0;/*����ʱ�����*/
		int play_x = 0;
		int play_y = 0;
		//���������ʳ��
		Map[random(2, 19)][random(2, 24)] = 2;
		
		TargetScore = 5000 * level;key = 0;snake = { 5,13,10, snake.direction };//��ʼ��ʳ��λ��,Ԥ�ڷ���,��λ,����
		int Tigger = 0;//���ݲ���������
		int BoomTigger = 0;//ը������������
		while (key != 'p')
		{
			if ((timeline % (6 - diffcult)) == 0)
			{
				BeginBatchDraw();
				Stillin = false;
				//̰��
				snake.direction = ValueJudge(Map, snake.head_y, snake.head_x);
				//���ƶ���
				
				if (_kbhit())
					key = _getch();
				switch (key)
				{
				case 'd':if (snake.direction == 3)break;
					snake.direction = 1;break;
				case 'w':if (snake.direction == 4)break;
					snake.direction = 2;break;
				case 'a':if (snake.direction == 1)break;
					snake.direction = 3;break;
				case 's':if (snake.direction == 2)break;
					snake.direction = 4;break;
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
				

				//�����жϳ����Ƿ����ʳ��
				for (int y = 1;y < 21;y++)
				{
					for (int x = 1;x < 26;x++)
					{
						if (Map[y][x] == 2)
						{
							Stillin = true;
						}
					}
				}
				//��һ������
				if (snake.crash == false && level == 1)
				{
					Tigger++;
					if (Tigger % (30 * diffcult) == 0)
					{
						Tigger = 0;
						Creat(Map, 3);
						Creat(Map, 3);
						if (diffcult >= 2)Creat(Map, 3);
						if (diffcult == 3)Creat(Map, 3);Creat(Map, 3);
					}
				}

				//�ڶ�������
				if (snake.crash == false && level == 2)
				{
					Tigger++;
					if (Tigger % (30 * diffcult) == 0)
					{
						Tigger = 0;
						Creat(Map, 3);
						Creat(Map, 3);
						if (diffcult >= 2)Creat(Map, 3);
						if (diffcult == 3)Creat(Map, 3);Creat(Map, 3);
					}
					BoomTigger++;
					if (BoomTigger % (45 * diffcult) == 0)
					{
						BoomTigger = 0;
						Creat(Map, 2);
						if (diffcult == 3)Creat(Map, 2);
					}
				}

				//����������
				if (snake.crash == false && level == 3)
				{
					Tigger++;
					if (Tigger % (30 * diffcult) == 0)
					{
						Tigger = 0;
						Creat(Map, 3);
						Creat(Map, 3);
						if (diffcult >= 2)Creat(Map, 3);
						if (diffcult == 3)Creat(Map, 3);Creat(Map, 3);
					}
					BoomTigger++;
					if (BoomTigger % (45 * diffcult) == 0)
					{
						BoomTigger = 0;
						Creat(Map, 2);
						if (diffcult == 3)Creat(Map, 2);
					}
				}

				//���Ĺ�����
				if (snake.crash == false && level == 4)
				{
					Tigger++;
					if (Tigger % (25 * diffcult) == 0)
					{
						Tigger = 0;
						Creat(Map, 3);
						Creat(Map, 3);
						if (diffcult >= 2)Creat(Map, 3);
						if (diffcult == 3)Creat(Map, 3);Creat(Map, 3);
					}
					BoomTigger++;
					if (BoomTigger % (35 * diffcult) == 0)
					{
						BoomTigger = 0;
						Creat(Map, 2);
						if (diffcult == 3)Creat(Map, 2);
					}
				}

				if (Stillin == false) { Creat(Map, 1);Stillin = true; };

				if (ControlSnake(score, Map, snake.direction, p_length, p_head_x, p_head_y, p_crash, p_next, level, rank, loadlevel) == 1)
				{
					timeplay = 1;
					play_x = snake.head_x;
					play_y = snake.head_y;
				}
				cleardevice();
				if (snake.length < 1)EndGame(rank, score, level, loadlevel);
				if (score > TargetScore) { Map[10][13] = 3; }
				if (next == true) { break; };
				Draw(Map, score, level);
				FlushBatchDraw();
				EndBatchDraw();
				//����ϵͳ
				score += (snake.length / 3) * diffcult / 1.5;
			}
			timeline++;
			if (timeline == 481)
			{
				timeline = 1;
			}
			if (timeplay != 0)
			{
				timeplay++;
				Granule(play_y, play_x, Map, score, level, timeplay);
				if (timeplay == 15)
				{
					timeplay = 0;
				}
			}
			Sleep(20);
		}
		next = false;
		level += 1;
	}
	EndGame(rank, score, level, loadlevel);
	closegraph();                                // �رջ�ͼ��Ļ
}
void Save(int rank[], int level, int score, int loadlevel)
{
	if (score > rank[0])rank[0] = score;
	sort(rank, rank + 10);
	ofstream fout("D:\\save.txt", ios::out);	//���ù��캯�����ļ�
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
	char num[10];int lock = 1;//��һ�����
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
	outtextxy(320, 235, _T("���а�"));
}
void Granule(int y, int x, int Map[21][26], int score, int level, int time)
{
	Draw(Map, score, level);
	setfillcolor(RED);
	solidcircle(x * 30 + 15, y * 30 + 15, time);
	FlushBatchDraw();
}