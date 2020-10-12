#include <graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include <string>
#include <ctime>
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
/// �˳�����ĺ��� �д�������ֹ���
/// </summary>
/// <param name="score">����</param>
void EndGame(int score)
{
	cleardevice();
	FlushBatchDraw();
	settextstyle(50, 30, _T("normal"));
	outtextxy(120, 120, _T("��Ϸ����"));
	outtextxy(120, 180, _T("���ĵ÷֣�"));
	char num[10];
	sprintf_s(num, "%d", score);
	outtextxy(400, 180, num);
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
/// �������
/// </summary>
/// <param name="Map"></param>
/// <param name="kind">1Ϊʳ��2Ϊը��3Ϊ����</param>
/// <returns></returns>
int Creat(int Map[21][26],int kind)
{
	srand(time(NULL)+rand()%1000);int y = random(2, 19);int x = random(2, 24);
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
				return 1;
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
				return 1;
			}
		}
	}
	return 0;
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
void ChangeRoom(int Select, bool* p, int* diffcult)
{
	cleardevice();
	switch (Select)
	{
	case 1:
	{
		*p = true;
	};break;
	case 2:;break;
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
				}FlushBatchDraw();
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
			solidrectangle(x * 30, y * 30, x * 30 + 22, y * 30 + 22);
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
void ControlSnake(int score, int Map[21][26], int direction, int* length, int* head_x, int* head_y,bool* crash,bool* next)
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
			EndGame(score);
		}
		else if (Map[*head_y][*head_x] == 2)//ʳ���ж�
		{
			ChangeLength(Map, 1);
			*length += 1;
		}
		else if (*Mapp==3)
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
				ChangeLength(Map, (*length +1)/(-2));
				*length += (*length + 1) / (-2);
			}
			Creat(Map, 2);
		}
		else if (*Mapp == 5)//ǡ����
		{
			ChangeLength(Map, -1);
			*length -= 1;
		}
	}
	*Mapp = 101 + *length;
	ChangeLength(Map, -1);
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
	}snake = { 5,10,13,1 };
	int* p_length = &snake.length;int* p_head_x = &snake.head_x;int* p_head_y = &snake.head_y;bool* p_crash=&snake.crash;
	int level, diffcult, score;/*��Ϸ�ؿ�����Ϸ�Ѷȣ���Ϸ����*/score = 9900;level = 1;diffcult = 1;//�Ѷ�123��Ӧeasy normal hard
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
		case 's': if (select != 5)
		{
			select += 1;
			key = 0;
		};  break;
		case 27: exit(0);
		case 13: {cleardevice();FlushBatchDraw();ChangeRoom(select, bp, p_diffcult), key = 0;};break;
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
	key = 0;
	//��һ��

	if (level == 1) 
	{
		for (int y = 1;y < 21;y++)
		{
			for (int x = 1;x < 26;x++)
			{
				Mapp = &Map[y][x];
				NewJudge(Mapp, y, x);
			}
		}/*��ʼ����ͼ*/
		Map[random(2, 19)][random(2, 24)] = 2;TargetScore = 10000;//��ʼ��ʳ��λ��,Ԥ�ڷ���
		int Tigger = 0;//���ݲ���������
		while (key != 27)
		{
			BeginBatchDraw();
			Stillin = false;
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
			if (Stillin == false)Creat(Map, 1);
			//
			ControlSnake(score, Map, snake.direction, p_length, p_head_x, p_head_y,p_crash,p_next);
			cleardevice();
			if (snake.length < 1)EndGame(score);
			Draw(Map, score, level);
			FlushBatchDraw();
			EndBatchDraw();
			score += (snake.length / 3) / (0.5 * diffcult);
			if (snake.crash == false) 
			{
				Tigger++;
				if (Tigger % (30*diffcult) == 0)
				{
					Tigger = 0;
					Creat(Map, 3);
					Creat(Map, 3);
					if (diffcult >= 2)Creat(Map, 3);
					if (diffcult == 3)Creat(Map, 3);Creat(Map, 3);
				}
			}
			if (score > TargetScore) { Map[10][13] = 3; }
			if (next == true) { break; };
			Sleep(250 / diffcult);
		}
		next = false;
		level += 1;
	}

	//�ڶ���
	if (level == 2)
	{
		for (int y = 1;y < 21;y++)
		{
			for (int x = 1;x < 26;x++)
			{
				Mapp = &Map[y][x];
				NewJudge(Mapp, y, x);
			}
		}/*��ʼ����ͼ*/
		Map[random(2, 19)][random(2, 24)] = 2;TargetScore = 25000;key = 0;snake = { 5,13,10, snake.direction};//��ʼ��ʳ��λ��,Ԥ�ڷ���,��λ,����
		int Tigger = 0;//���ݲ���������
		int BoomTigger = 0;//ը������������
		while (key != 27)
		{
			BeginBatchDraw();
			Stillin = false;
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
			if (Stillin == false)Creat(Map, 1);
			//
			ControlSnake(score, Map, snake.direction, p_length, p_head_x, p_head_y, p_crash, p_next);
			cleardevice();
			if (snake.length < 1)EndGame(score);
			Draw(Map, score, level);
			FlushBatchDraw();
			EndBatchDraw();
			score += (snake.length / 3) / (0.5 * diffcult);
			if (snake.crash == false)
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
			//���Ŀ��ƣ�������������
			if (score > TargetScore) { Map[10][13] = 3; }
			if (next == true) { break; };
			Sleep(350 / diffcult);
		}
	}


	closegraph();                                // �رջ�ͼ��Ļ
}
