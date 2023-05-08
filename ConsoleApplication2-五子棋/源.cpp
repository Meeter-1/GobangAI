#include <graphics.h>
#include <math.h>
#include<easyx.h>//ͼ�ο�
#include <iostream>
#include <string>
#include <list>

using namespace std;

#define SIZE 40 //�����С
#define BOARD 610 //���泤����

int black = 0, white = 0;//�������Ͱ�����
int ipos, jpos;//���λ��
int xpos, ypos;

//ExMessage m;//��Ϣ����
IMAGE img[3];//���ͼƬ

bool gg = true;
bool ff = true;
bool flag = 0;
/*************�˻���ս***************/
double cut_count = 0;
double search_count = 0;
int pos[2] = { 0 };
//bool is_ai = 1;
int list11[250][2];
int list22[250][2];
int list33[250][2];
int list1[250][2];
int list2[250][2];
int list3[250][2];
int list_all[15][15];
int blank_list[250][2];
int pt[2] = { 0 };
int last_pos[2] = { 0 };
#define DEPTH 5;


double score_all_arr[250] = { 0 };  //�÷���״��λ�� ���ڼ���������ཻ �÷ַ���  �Լ�
int score_all_shape[250][5][2] = { 0 };
int score_all_direct[250][2] = { 0 };
double my_score = 0;
double score_all_enemy_arr[250] = { 0 };  //�з� �÷���״��λ��
int score_all_enemy_shape[250][5][2] = { 0 };
int score_all_enemy_direct[250][2] = { 0 };
double enemy_score = 0;
int my_list[250][2] = { 0 };
int enemy_list[250][2] = { 0 };


float ratio = 1;//����ϵ��  ����1 ������  С��1 ������
double shape_score[16][2][6] = { {{100}, {0, 1, 1, 0, 0} },
								{{100}, {0, 0, 1, 1, 0}},
								{{200}, {1, 1, 0, 1, 0 }},
	{{200}, {1, 0, 1, 1, 0 }},
								{{500}, {0, 0, 1, 1, 1 }},
								{{500}, {1, 1, 1, 0, 0} },
									{ {5000}, {0, 1, 1, 1, 0} },
									{ {5000 }, { 0, 1, 0, 1, 1, 0 } },
									{ {5000}, {0, 1, 1, 0, 1, 0} },
									{ {5000 }, { 1, 1, 1, 0, 1 } },
									{ {5000}, {1, 1, 0, 1, 1} },
									{ {5000 }, { 1, 0, 1, 1, 1 } },
									{ {5000}, {1, 1, 1, 1, 0} },
									{ {5000}, {0, 1, 1, 1, 1} },
									{ {30000}, {0, 1, 1, 1, 1, 0} },
								{ {99999999}, {1, 1, 1, 1, 1} } }; //99999999




/************************************/
void Loadimg()
{
	loadimage(&img[0], _T("./images/0.jpg"), BOARD, BOARD);
	loadimage(&img[1], _T("./images/1.jpg"), SIZE, SIZE);
	loadimage(&img[2], _T("./images/2.jpg"), SIZE, SIZE);
}

#define NUM 15

int map[NUM][NUM] = { 0 };
int num[NUM][NUM] = { 0 };

void initmap()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			map[i][j] = 0;
			num[i][j] = 0;
		}
	}
}


int prepos_x, prepos_y, pos_x, pos_y;
POINT lastpts[] = { 0 };
POINT pts[] = { 0 };
void Drawmap(int Pos_x ,int Pos_y)
{
	pos_x = Pos_x;
	pos_y = Pos_y;
	//prepos_x = 20;
	//prepos_y = 20;
	char demo[20] = "";
	int jiao1 = 10;
	int jiao2 = 4;
	POINT lastpts[] = { {prepos_x * SIZE + 20, prepos_y * SIZE + 20 - jiao1}, {prepos_x * SIZE + 20 + jiao2, prepos_y * SIZE + 20 - jiao2}, {prepos_x * SIZE + 20 + jiao1, prepos_y * SIZE + 20},{prepos_x * SIZE + 20 + jiao2, prepos_y * SIZE + 20 + jiao2}, {prepos_x * SIZE + 20, prepos_y * SIZE + 20 + jiao1}, {prepos_x * SIZE + 20 - jiao2, prepos_y * SIZE + 20 + jiao2}, {prepos_x * SIZE + 20 - jiao1, prepos_y * SIZE + 20}, {prepos_x * SIZE + 20 - jiao2, prepos_y * SIZE + 20 - jiao2} };
	 
	POINT pts[] =     { {pos_x * SIZE + 20, pos_y * SIZE + 20 - jiao1}, {pos_x * SIZE + 20 + jiao2, pos_y * SIZE + 20 - jiao2}, {pos_x * SIZE + 20 + jiao1, pos_y * SIZE + 20},{pos_x * SIZE + 20 + jiao2, pos_y * SIZE + 20 + jiao2}, {pos_x * SIZE + 20, pos_y * SIZE + 20 + jiao1}, {pos_x * SIZE + 20 - jiao2, pos_y * SIZE + 20 + jiao2}, {pos_x * SIZE + 20 - jiao1, pos_y * SIZE + 20}, {pos_x * SIZE + 20 - jiao2, pos_y * SIZE + 20 - jiao2}};
			if (map[pos_x][pos_y] == 1 && num[pos_x][pos_y] == 0)
			{
				putimage(pos_x * SIZE, pos_y * SIZE, &img[1]);
				string st = to_string(black + white);
				strcpy_s(demo, st.c_str());
				setbkmode(TRANSPARENT);
				settextcolor(YELLOW);
				outtextxy(pos_x * SIZE + 11, pos_y * SIZE + 7, demo);
				setlinecolor(YELLOW);//BLACK
				polyline(pts, 8);
				//polygon(pts, 8);
				num[pos_x][pos_y] = 1;
				if (black + white > 1)
				{
					putimage(prepos_x * SIZE, prepos_y * SIZE, &img[2]);
					string st = to_string(black + white - 1);
					strcpy_s(demo, st.c_str());
					setbkmode(TRANSPARENT);
					settextcolor(RED);
					outtextxy(prepos_x * SIZE + 11, prepos_y * SIZE + 7, demo);
				}
				
			}
			if (map[pos_x][pos_y] == 2 && num[pos_x][pos_y] == 0)
			{
				putimage(pos_x * SIZE, pos_y * SIZE, &img[2]);
				string st = to_string(black + white);
				strcpy_s(demo, st.c_str());
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				outtextxy(pos_x * SIZE + 11, pos_y * SIZE + 7, demo);
				setlinecolor(RED);//WHITE
				polyline(pts, 8);
				//polygon(pts, 8);
				num[pos_x][pos_y] = 1;
				if (black + white > 1)
				{
					putimage(prepos_x * SIZE, prepos_y * SIZE, &img[1]);
					string st = to_string(black + white - 1);
					strcpy_s(demo, st.c_str());
					setbkmode(TRANSPARENT);
					settextcolor(YELLOW);
					outtextxy(prepos_x * SIZE + 11, prepos_y * SIZE + 7, demo);
				}
				
			}
			prepos_x = Pos_x;
			prepos_y = Pos_y;
}

void draw_line()
{
	setlinecolor(BLACK);
	for (int i = 0; i < NUM ; i++)
	{
		line(i * SIZE + 20, 20, i * SIZE + 20, SIZE * NUM - 20);
		line(20, 20 + i * SIZE, SIZE * NUM - 20, i * SIZE + 20);
	}
}

void initlist()
{
	for (int i = 0; i < 250; i++)
	{
		list1[i][0] = -1;
		list1[i][1] = -1;
		list2[i][0] = -1;
		list2[i][1] = -1;
		list3[i][0] = -1;
		list3[i][1] = -1;
		list11[i][0] = -1;
		list11[i][1] = -1;
		list22[i][0] = -1;
		list22[i][1] = -1;
		list33[i][0] = -1;
		list33[i][1] = -1;
		enemy_list[i][0] = -1;
		enemy_list[i][1] = -1;
		my_list[i][0] = -1;
		my_list[i][1] = -1;
		blank_list[i][0] = -1;
		blank_list[i][1] = -1;
	}
	int sum = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			//list_all[sum][0] = i;
			//list_all[sum][1] = j;
			blank_list[sum][0] = i;
			blank_list[sum][1] = j;
			map[i][j] = 0;
			num[i][j] = 0;
			sum++;
		}
	}

}

void update_list3()
{
	for (int i = 0; i < 250; i++)
	{
		list3[i][0] = -1;
		list3[i][1] = -1;
	}
	int i = 0; int j = 0;
	while (list1[i][0] != -1)
	{
		i++;
	}
	while (list2[j][0] != -1)
	{
		j++;
	}
	if (flag == 1)
	{
		for (int k = 0; k < i + j; k++)
		{
			if (k % 2 == 0)
			{
				list3[k][0] = list1[k / 2][0];
				list3[k][1] = list1[k / 2][1];
			}
			else
			{
				list3[k][0] = list2[(k - 1) / 2][0];
				list3[k][1] = list2[(k - 1) / 2][1];
			}
		}
	}
	else
	{
		for (int k = 0; k < i + j; k++)
		{
			if (k % 2 == 0)
			{
				list3[k][0] = list2[k / 2][0];
				list3[k][1] = list2[k / 2][1];
			}
			else
			{
				list3[k][0] = list1[(k - 1) / 2][0];
				list3[k][1] = list1[(k - 1) / 2][1];
			}
		}
	}

}

void update_list33()
{
	int i = 0; int j = 0;
	while (list11[i][0] != -1)
	{
		i++;
	}
	while (list22[j][0] != -1)
	{
		j++;
	}
	if (flag == 1)
	{
		for (int k = 0; k < i + j; k++)
		{
			if (k % 2 == 0)
			{
				list33[k][0] = list11[k / 2][0];
				list33[k][1] = list11[k / 2][1];
			}
			else
			{
				list33[k][0] = list22[(k - 1) / 2][0];
				list33[k][1] = list22[(k - 1) / 2][1];
			}
		}
	}
	else
	{
		for (int k = 0; k < i + j; k++)
		{
			if (k % 2 == 0)
			{
				list33[k][0] = list22[k / 2][0];
				list33[k][1] = list22[k / 2][1];
			}
			else
			{
				list33[k][0] = list11[(k - 1) / 2][0];
				list33[k][1] = list11[(k - 1) / 2][1];
			}
		}
	}

}

void update_blank()
{
	int k = 0;
	while (list3[k][0] != -1)
	{
		int i = 0;
		while (blank_list[i][0] != -1)
		{
			if (blank_list[i][0] == list3[k][0] && blank_list[i][1] == list3[k][1])
			{
				int j = i;
				while (blank_list[j][0] != -1)
				{
					blank_list[j][0] = blank_list[j + 1][0];
					blank_list[j][1] = blank_list[j + 1][1];
					j++;
				}
			}
			i++;
		}
		k++;
	}
}
void fill_list()
{
	int i = 0;
	while (list11[i][0] != -1)
	{
		list1[i][0] = list11[i][0];
		list1[i][1] = list11[i][1];
		i++;
	}
	i = 0;
	while (list22[i][0] != -1)
	{
		list2[i][0] = list22[i][0];
		list2[i][1] = list22[i][1];
		i++;
	}
}

void Click()
{

	ExMessage m;
	flushmessage(EX_MOUSE);
	//ExMessage getmessage(BYTE filter = EX_MOUSE);
	m = getmessage(EX_MOUSE);//�õ������Ϣ
	if (m.message == WM_LBUTTONDOWN) {
		ipos = (int)(((double)m.x) / SIZE);//�������λ��
		jpos = (int)(((double)m.y) / SIZE);
		if (map[ipos][jpos] == 0 && black == white)
		{//���Ӵ�û�ӣ��Һ��ӺͰ���һ����
			map[ipos][jpos] = 1;
			black++;
			Drawmap(ipos, jpos);//���µ�ͼ
		}
		else if (map[ipos][jpos] == 0 && black > white)
		{//���Ӵ�û�ӣ��Һ��ӱȰ��Ӷ�
			map[ipos][jpos] = 2;
			white++;
			Drawmap(ipos, jpos);//���µ�ͼ	
		}
	}



}


int Judge(int a)
{


	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (j + 4 < NUM && map[i][j] == a && map[i][j + 1] == a && map[i][j + 2] == a && map[i][j + 3] == a && map[i][j + 4] == a)
				return 1;//�ж���
			else if (i + 4 < NUM && map[i][j] == a && map[i + 1][j] == a && map[i + 2][j] == a && map[i + 3][j] == a && map[i + 4][j] == a)
				return 1;//�ж���
			else if (i + 4 < NUM && j + 4 < NUM && map[i][j] == a && map[i + 1][j + 1] == a && map[i + 2][j + 2] == a && map[i + 3][j + 3] == a && map[i + 4][j + 4] == a)
				return 1;//�ж�����
			else if (i > 4 && j + 4 < NUM && map[i][j] == a && map[i - 1][j + 1] == a && map[i - 2][j + 2] == a && map[i - 3][j + 3] == a && map[i - 4][j + 4] == a)
				return 1;//�ж�����
		}
			//j > 3 && i + 4
	}
	return 0;
}

int Tie()
{//�ж�ƽ��
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (map[i][j] == 0)//�����ϻ��пո�
				return 0;
		}
	}
	return 1;
}

void Judge_ending()
{
	if (Judge(1))
	{//�жϺ����Ƿ��ʤ
		MessageBox(NULL, _T("���ӻ�ʤ��"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
		gg = false;
		//break;
	}
	if (Judge(2))
	{//�жϰ����Ƿ��ʤ
		MessageBox(NULL, _T("���ӻ�ʤ��"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
		gg = false;
		//break;
	}
	if (Tie())
	{//�����Ϸƽ��
		MessageBox(NULL, _T("����൱�Ķ��֣�"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
		gg = false;
		//break;
	}
}

int mmxMap[15][15] = { 0 };
void init_mmxMap()
{

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			mmxMap[i][j] = 0;
		}
	}
	for (int i = 0; i < 250; i++)
	{
		//if (list1[i][0] == -1)break;
		if (list1[i][0] != -1)mmxMap[list1[i][0]][list1[i][1]] = 1;
	}
	for (int i = 0; i < 250; i++)
	{
		//if (list2[i][0] == -1)break;
		if (list2[i][0] != -1)mmxMap[list2[i][0]][list2[i][1]] = 2;
	}
}


int Judge1(int a)
{

	init_mmxMap();
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (j + 4 < NUM && mmxMap[i][j] == a && mmxMap[i][j + 1] == a && mmxMap[i][j + 2] == a && mmxMap[i][j + 3] == a && mmxMap[i][j + 4] == a)
				return 1;//�ж���
			else if (i + 4 < NUM && mmxMap[i][j] == a && mmxMap[i + 1][j] == a && mmxMap[i + 2][j] == a && mmxMap[i + 3][j] == a && mmxMap[i + 4][j] == a)
				return 1;//�ж���
			else if (i + 4 < NUM && j + 4 < NUM && mmxMap[i][j] == a && mmxMap[i + 1][j + 1] == a && mmxMap[i + 2][j + 2] == a && mmxMap[i + 3][j + 3] == a && mmxMap[i + 4][j + 4] == a)
				return 1;//�ж�����
			else if (i > 4 && j + 4 < NUM && mmxMap[i][j] == a && mmxMap[i - 1][j + 1] == a && mmxMap[i - 2][j + 2] == a && mmxMap[i - 3][j + 3] == a && mmxMap[i - 4][j + 4] == a)
				return 1;//�ж�����
		}//j > 3 && i + 4
	}
	return 0;
}

int Tie1()
{//�ж�ƽ��
	init_mmxMap();
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			if (mmxMap[i][j] == 0)//�����ϻ��пո�
				return 0;
		}
	}
	return 1;
}



void play_board()
{
	initgraph(BOARD, BOARD);//��������
	Loadimg(); //����ͼƬ��Դ
	putimage(0, 0, &img[0]);//���̱���ɫ
	draw_line();//����
	black = 0, white = 0;
	for (int i = 0; i < NUM; i++)
	{
		for (int j = 0; j < NUM; j++)
		{
			map[i][j] = 0;
			num[i][j] = 0;
		}
	}
}

void end_board()
{
	initgraph(SIZE * 12, SIZE * 12);//��������
	Loadimg(); //����ͼƬ��Դ
	setbkcolor(RGB(206, 157, 113));
	putimage(0, 0, &img[0]);//���̱���ɫ
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	line(3 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 3);
	line(3 * SIZE, 6 * SIZE, 9 * SIZE, SIZE * 6);
	line(3 * SIZE, 9 * SIZE, 9 * SIZE, SIZE * 9);
	line(3 * SIZE, 3 * SIZE, 3 * SIZE, SIZE * 9);
	line(9 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 9);
	RECT s = { 120, 40, 360, 120 };
	drawtext(_T("��Ϸ����"), &s, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r = { 120, 120, 360, 240 };
	drawtext(_T("���¿�ʼ"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT t = { 120, 240, 360, 360 };
	drawtext(_T("�˳���Ϸ"), &t, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}


void begin_board()
{
	initgraph(SIZE * 12, SIZE * 12);//��������
	Loadimg(); //����ͼƬ��Դ
	setbkcolor(RGB(206, 157, 113));
	putimage(0, 0, &img[0]);//���̱���ɫ
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	line(3 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 3);
	line(3 * SIZE, 6 * SIZE, 9 * SIZE, SIZE * 6);
	line(3 * SIZE, 9 * SIZE, 9 * SIZE, SIZE * 9);
	line(3 * SIZE, 3 * SIZE, 3 * SIZE, SIZE * 9);
	line(9 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 9);
	RECT s = { 120, 40, 360, 120 };
	drawtext(_T("������"), &s, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r = { 120, 120, 360, 240 };
	drawtext(_T("��Ҷ�ս"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT t = { 120, 240, 360, 360 };
	drawtext(_T("�˻���ս"), &t, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}



void chose_board()
{
	initgraph(SIZE * 12, SIZE * 12);//��������
	Loadimg(); //����ͼƬ��Դ
	setbkcolor(RGB(206, 157, 113));

	putimage(0, 0, &img[0]);//���̱���ɫ
	setlinecolor(BLACK);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	line(3 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 3);
	line(3 * SIZE, 6 * SIZE, 9 * SIZE, SIZE * 6);
	line(3 * SIZE, 9 * SIZE, 9 * SIZE, SIZE * 9);
	line(3 * SIZE, 3 * SIZE, 3 * SIZE, SIZE * 9);
	line(9 * SIZE, 3 * SIZE, 9 * SIZE, SIZE * 9);
	RECT s = { 120, 40, 360, 120 };
	drawtext(_T("�˻���ս"), &s, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r = { 120, 120, 360, 240 };
	drawtext(_T("AI����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT t = { 120, 240, 360, 360 };
	drawtext(_T("�������"), &t, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

}

void PlayPVP() //��Ҷ�ս
{
	initmap();
	play_board();
	gg = true;
	while (gg)
	{
		Click();//����
		

		if (Judge(1))
		{//�жϺ����Ƿ��ʤ
			MessageBox(NULL, _T("���ӻ�ʤ��"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
			gg = false;
			break;
		}
		if (Judge(2))
		{//�жϰ����Ƿ��ʤ
			MessageBox(NULL, _T("���ӻ�ʤ��"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
			gg = false;
			break;
		}
		if (Tie())
		{//�����Ϸƽ��
			MessageBox(NULL, _T("����൱�Ķ��֣�"), _T("��Ϸ��ʾ"), MB_OK | MB_SYSTEMMODAL);
			gg = false;
			break;
		}
	}
	end_board();
}

class Gobang_AI
{
	enum class Chess
	{
		none = 0,
		player = 1,
		computer = 2
	};

	struct Move
	{
		int x = 0;
		int y = 0;
	};

	//Chess board[15][15];

	//int 
public:

	int next_point[2] = { 0 };
	double value = 0;
	int next_step[2] = { 0 };

	void order()
	{
		// list3 �����һ������
		int last_pt[2] = { 0 };

		int t = 0;
		while (list3[t + 1][0] != -1)
		{
			t++;
		}
		last_pt[0] = list3[t][0];
		last_pt[1] = list3[t][1];

		int i = 0;
		while (blank_list[i][0] != -1)
		{//��������Ӹ��������Ƿ��п������ӵĵ�
			for (int j = -1; j < 2; j++)
			{
				for (int k = -1; k < 2; k++)
				{//�� i = j = 0 �Ǳ�ʾ�������, ��Ϊ���丽�������������� i = j = 0;
					if (j == 0 && k == 0) continue;
					else if (blank_list[i][0] == (last_pt[0] + j) && blank_list[i][1] == (last_pt[1] + k))
					{//��������ӵ㸽���п�ѡ��ʱ, �ȴ�ɾ��, Ȼ��Ӻ�ѡ���б��ײ�����
						int p = i;
						for (p = i; p > 0; p--)
						{
							blank_list[p][0] = blank_list[p - 1][0];
							blank_list[p][1] = blank_list[p - 1][1];
						}
						blank_list[0][0] = last_pt[0] + j;
						blank_list[0][1] = last_pt[1] + k;
					}
				}
			}
			i++;
		}



	}

	bool is_ai()
	{
		int change = black + white + flag;
		if (change % 2 == 1)
			return true;
		else
			return false;
	}


	int calMap[15][15];
	double scoreMap[15][15];
	double cal_score(int m, int n, int x_decrict, int y_derice, bool is_mine)
	{
		if (is_mine)
		{
			double add_score = 0; //�ӷ���
			//��һ�������ϣ� ֻȡ���ĵ÷���
			double max_score = 0;
			int max_score_shape[6][2] = { {-2,-2},{-2,-2},{-2,-2},{-2,-2},{-2,-2},{-2,-2} };
			int max_score_direct[2] = { -2,-2 };

			//����˷����ϣ��õ��Ѿ��е÷���״�����ظ�����
			int p = 0;
			while (score_all_arr[p] != -2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (m == score_all_shape[p][i][0] && n == score_all_shape[p][i][1] && x_decrict == score_all_direct[p][0] && y_derice == score_all_direct[p][1])
						return 0;
				}
				p++;
			}
			int a = 1;
			for (int offset = -5; offset < 1; offset++)
			{
				int pos[6] = { -1,-1,-1,-1,-1,-1 };
				int t = 0; int c = 0;

				for (int i = 0; i < 6; i++, t++)
				{
					if (pos[t] == -1 && (m + (i + offset) * x_decrict) >= 0 && (n + (i + offset) * y_derice) >= 0)
					{
						pos[t] = calMap[m + (i + offset) * x_decrict][n + (i + offset) * y_derice];
					}
					if (((pos[t] == 2 )&& (t != 5)) || pos[t] == -1) {
						c++; break;
					}
				}

				if (c != 0) continue;

				int lp = 0;
				int tmp_shap5[5] = { pos[0], pos[1], pos[2], pos[3], pos[4] };
				int tmp_shap6[6] = { pos[0], pos[1], pos[2], pos[3], pos[4], pos[5] };

				for (int i = 0; i < 16; i++)
				{
					a = 1;
					for (int j = 0; j < 5; j++)
					{
						if (shape_score[i][1][j] != tmp_shap5[j])
						{
							a = 0;
							goto trmy5;
						}
					}
					if (a == 1) {
						goto trmy5;
					}
					to5_6:a = 2;
					for (int j = 0; j < 6; j++)
					{
						if (shape_score[i][1][j] != tmp_shap6[j])
						{
							a = 0;
							goto trmy6;
						}
					}
					if (a == 2) {
						goto trmy6;
					}

			  trmy5:if (shape_score[i][0][0] > max_score && a == 1)
					{
						max_score = shape_score[i][0][0];
						for (int j = 0; j < 5; j++)
						{
							max_score_shape[j][0] = (j + offset) * x_decrict + m;
							max_score_shape[j][1] = (j + offset) * y_derice + n;
						}
						max_score_direct[0] = x_decrict;
						max_score_direct[1] = y_derice;
					}
					if (a == 1) {
						goto to5_6;
					}
			  
			  trmy6:if (shape_score[i][0][0] > max_score && a == 2)
				   {
						max_score = shape_score[i][0][0];
						for (int j = 0; j < 6; j++)
						{
							max_score_shape[j][0] = (j + offset) * x_decrict + m;
							max_score_shape[j][1] = (j + offset) * y_derice + n;
						}
						max_score_direct[0] = x_decrict;
						max_score_direct[1] = y_derice;
					}

				}
			}
			//����������״�ཻ�� ������3�� �ཻ�� �÷����� һ���ӵĳ���
			if (max_score_direct[1] != -2 && a == 1)
			{
				p = 0;
				while (score_all_arr[p] != -2)
				{
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (score_all_shape[p][i][0] == max_score_shape[j][0] && score_all_shape[p][i][1] == max_score_shape[j][1])
								add_score += score_all_arr[p] + max_score;
						}
					}
					p++;
				}
				score_all_arr[p] = max_score;
				for (int i = 0; i < 5; i++)
				{
					score_all_shape[p][i][0] = max_score_shape[i][0];
					score_all_shape[p][i][1] = max_score_shape[i][1];
				}
				score_all_direct[p][0] = max_score_direct[0];
				score_all_direct[p][1] = max_score_direct[1];
			}
			else if (max_score_direct[1] != -2 && a == 2)
			{
				p = 0;
				while (score_all_arr[p] != -2)
				{
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							if (score_all_shape[p][i][0] == max_score_shape[j][0] && score_all_shape[p][i][1] == max_score_shape[j][1])
								add_score += score_all_arr[p] + max_score;
						}
					}
					p++;
				}
				score_all_arr[p] = max_score;
				for (int i = 0; i < 6; i++)
				{
					score_all_shape[p][i][0] = max_score_shape[i][0];
					score_all_shape[p][i][1] = max_score_shape[i][1];
				}
				score_all_direct[p][0] = max_score_direct[0];
				score_all_direct[p][1] = max_score_direct[1];
			}
			return add_score + max_score;
		}
		else
		{

			double add_score = 0; //�ӷ���
			//��һ�������ϣ� ֻȡ���ĵ÷���
			double max_score = 0;
			int max_score_shape[6][2] = { {-2,-2},{-2,-2},{-2,-2},{-2,-2},{-2,-2},{-2,-2} };
			int max_score_direct[2] = { -2,-2 };

			//����˷����ϣ��õ��Ѿ��е÷���״�����ظ�����
			int p = 0;
			while (score_all_enemy_arr[p] != -2)
			{
				for (int i = 0; i < 5; i++)
				{
					if (m == score_all_enemy_shape[p][i][0] && n == score_all_enemy_shape[p][i][1] && x_decrict == score_all_enemy_direct[p][0] && y_derice == score_all_enemy_direct[p][1])
						return 0;
				}
				p++;
			}
			int a = 1;
			for (int offset = -5; offset < 1; offset++)
			{

				int pos[6] = { -1,-1,-1,-1,-1,-1 };
				int t = 0; int c = 0;
				for (int i = 0; i < 6; i++, t++)
				{
					if (pos[t] == -1 && (m + (i + offset) * x_decrict) >= 0 && (n + (i + offset) * y_derice) >= 0)
					{
						if (calMap[m + (i + offset) * x_decrict][n + (i + offset) * y_derice] == 1)
						{
							pos[t] = 2;
							if (t != 5) {
								c++; break;
							}
						}
						else if (calMap[m + (i + offset) * x_decrict][n + (i + offset) * y_derice] == 2)
						{
							pos[t] = 1;
						}
						else
							pos[t] = calMap[m + (i + offset) * x_decrict][n + (i + offset) * y_derice];
					}
					if (pos[t] == -1)
					{
						c++; break;
					}
					
				}

				if (c != 0) continue;

				int lp = 0;
				int tmp_shap5[5] = { pos[0], pos[1], pos[2], pos[3], pos[4] };
				int tmp_shap6[6] = { pos[0], pos[1], pos[2], pos[3], pos[4], pos[5] };

				for (int i = 0; i < 16; i++)
				{
					a = 1;
					for (int j = 0; j < 5; j++)
					{
						if (shape_score[i][1][j] != tmp_shap5[j])
						{
							a = 0;
							goto trenemy5;
						}
					}
					if (a == 1) {
						goto trenemy5;
					}
					to15_6:a = 2;
					for (int j = 0; j < 6; j++)
					{
						if (shape_score[i][1][j] != tmp_shap6[j])
						{
							a = 0;
							goto trenemy6;
						}
					}
					if (a == 2) {
						goto trenemy6;
					}

		   trenemy5:if (shape_score[i][0][0] > max_score && a == 1)
				   {
						max_score = shape_score[i][0][0];
						for (int j = 0; j < 5; j++)
					    {
							max_score_shape[j][0] = (j + offset) * x_decrict + m;
							max_score_shape[j][1] = (j + offset) * y_derice + n;
						}
							max_score_direct[0] = x_decrict;
							max_score_direct[1] = y_derice;
					}
					if (a == 1) {
						goto to15_6;
					}
		   
		   trenemy6:if (shape_score[i][0][0] > max_score && a == 2)
				   {
						max_score = shape_score[i][0][0];
						for (int j = 0; j < 6; j++)
						{
							max_score_shape[j][0] = (j + offset) * x_decrict + m;
							max_score_shape[j][1] = (j + offset) * y_derice + n;
						}
						max_score_direct[0] = x_decrict;
						max_score_direct[1] = y_derice;
					}

				}

			}
			//����������״�ཻ�� ������3�� �ཻ�� �÷����� һ���ӵĳ���

			if (max_score_direct[1] != -2 && a == 1)
			{
				p = 0;
				while (score_all_enemy_arr[p] != -2)
				{
					for (int i = 0; i < 5; i++)
					{
						for (int j = 0; j < 5; j++)
						{
							if (score_all_enemy_shape[p][i][0] == max_score_shape[j][0] && score_all_enemy_shape[p][i][1] == max_score_shape[j][1])
								add_score += score_all_enemy_arr[p] + max_score;
						}
					}
					p++;
				}
				score_all_enemy_arr[p] = max_score;
				for (int i = 0; i < 5; i++)
				{
					score_all_enemy_shape[p][i][0] = max_score_shape[i][0];
					score_all_enemy_shape[p][i][1] = max_score_shape[i][1];
				}
				score_all_enemy_direct[p][0] = max_score_direct[0];
				score_all_enemy_direct[p][1] = max_score_direct[1];
			}
			else if (max_score_direct[1] != -2 && a == 2)
			{
				p = 0;
				while (score_all_enemy_arr[p] != -2)
				{
					for (int i = 0; i < 6; i++)
					{
						for (int j = 0; j < 6; j++)
						{
							if (score_all_enemy_shape[p][i][0] == max_score_shape[j][0] && score_all_enemy_shape[p][i][1] == max_score_shape[j][1])
								add_score += score_all_enemy_arr[p] + max_score;
						}
					}
					p++;
				}
				score_all_enemy_arr[p] = max_score;
				for (int i = 0; i < 6; i++)
				{
					score_all_enemy_shape[p][i][0] = max_score_shape[i][0];
					score_all_enemy_shape[p][i][1] = max_score_shape[i][1];
				}
				score_all_enemy_direct[p][0] = max_score_direct[0];
				score_all_enemy_direct[p][1] = max_score_direct[1];
			}
			
			return add_score + max_score;
		}
	}

	double evaluation(bool is_ai)
	{
		double total_score = 0;

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				calMap[i][j] = 0;
				scoreMap[i][j] = 0;
			}
		}
		// �ж��Ƿ�Ϊ ai ��
		if (is_ai)
		{
			for (int i = 0; i < 250; i++)
			{
				//if (list1[i][0] == -1)break;
				my_list[i][0] = list1[i][0];
				my_list[i][1] = list1[i][1];
				if (list1[i][0] != -1)calMap[list1[i][0]][list1[i][1]] = 1;
			}
			for (int i = 0; i < 250; i++)
			{
				//if (list2[i][0] == -1)break;
				enemy_list[i][0] = list2[i][0];
				enemy_list[i][1] = list2[i][1];
				if (list2[i][0] != -1)calMap[list2[i][0]][list2[i][1]] = 2;
			}
		}
		else
		{
			for (int i = 0; i < 250; i++)
			{
				//if (list2[i][0] == -1)break;
				my_list[i][0] = list2[i][0];
				my_list[i][1] = list2[i][1];
				if (list2[i][0] != -1)calMap[list2[i][0]][list2[i][1]] = 1;
			}
			for (int i = 0; i < 250; i++)
			{
				//if (list1[i][0] == -1)break;
				enemy_list[i][0] = list1[i][0];
				enemy_list[i][1] = list1[i][1];
				if (list1[i][0] != -1)calMap[list1[i][0]][list1[i][1]] = 2;
			}
		}

		pt[0] = -1;
		pt[1] = -1;
		//���Լ��ĵ÷�
		bool is_mine = true;
		//double score_all_arr[250] = { 0 };  //�÷���״��λ�� ���ڼ���������ཻ �÷ַ���  �Լ�
		for (int i = 0; i < 250; i++) {
			score_all_arr[i] = -2;
		}
		for (int i = 0; i < 250; i++) {
			for (int j = 0; j < 5; j++) {
				score_all_shape[i][j][0] = -2;
				score_all_shape[i][j][1] = -2;
			}
		}
		for (int i = 0; i < 250; i++) {
			score_all_direct[i][0] = -2;
			score_all_direct[i][1] = -2;
		}

		my_score = 0;
		double my_lastscore = 0;
		for (int m = 0; m < 250; m++)
		{
			if (my_list[m][0] == -1)break;
			for (int n = 0; n < 2; n++)
			{
				pt[n] = my_list[m][n];
			}
			double pos_score = 0;
			my_score += cal_score(pt[0], pt[1], 0, 1, is_mine);
			my_score += cal_score(pt[0], pt[1], 1, 0, is_mine);
			my_score += cal_score(pt[0], pt[1], 1, 1, is_mine);
			my_score += cal_score(pt[0], pt[1], -1, 1, is_mine);

			//pos_score += cal_score(pt[0], pt[1], 0, 1, is_mine);
			//pos_score += cal_score(pt[0], pt[1], 1, 0, is_mine);
			//pos_score += cal_score(pt[0], pt[1], 1, 1, is_mine);
			//pos_score += cal_score(pt[0], pt[1], -1, 1, is_mine);
			//scoreMap[pt[0]][pt[1]] = pos_score;
			//my_lastscore = pos_score;
		}

		//����˵ĵ÷֣� ����ȥ

		for (int i = 0; i < 250; i++) {
			score_all_enemy_arr[i] = -2;
		}
		for (int i = 0; i < 250; i++) {
			for (int j = 0; j < 5; j++) {
				score_all_enemy_shape[i][j][0] = -2;
				score_all_enemy_shape[i][j][1] = -2;
			}
		}
		for (int i = 0; i < 250; i++) {
			score_all_enemy_direct[i][0] = -2;
			score_all_enemy_direct[i][1] = -2;
		}

		enemy_score = 0;
		double enemy_lastscore = 0;
		for (int m = 0; m < 250; m++)
		{
			if (enemy_list[m][0] == -1)break;
			for (int n = 0; n < 2; n++)
			{
				pt[n] = enemy_list[m][n];
			}
			double pos_score = 0;
			//is_mine = false;
			enemy_score += cal_score(pt[0], pt[1], 0, 1, !is_mine);
			enemy_score += cal_score(pt[0], pt[1], 1, 0, !is_mine);
			enemy_score += cal_score(pt[0], pt[1], 1, 1, !is_mine);
			enemy_score += cal_score(pt[0], pt[1], -1, 1, !is_mine);

			//pos_score += cal_score(pt[0], pt[1], 0, 1, !is_mine);
			//pos_score += cal_score(pt[0], pt[1], 1, 0, !is_mine);
			//pos_score += cal_score(pt[0], pt[1], 1, 1, !is_mine);
			//pos_score += cal_score(pt[0], pt[1], -1, 1, !is_mine);
			//scoreMap[pt[0]][pt[1]] = pos_score;
			//if (enemy_lastscore <= pos_score) {
			//	enemy_lastscore = pos_score;
			//}
		}

		//�������� ��ȥ �з�����
		total_score = my_score - enemy_score * ratio * 0.11;

		return total_score;
	}


	bool has_neightnor()
	{
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (i == 0 and j == 0) continue;
				else
				{
					int k = 0;
					while (list3[k][0] != -1)
					{
						if (next_step[0] + i == list3[k][0] && next_step[1] + j == list3[k][1]) return true;
						k++;
					}
				}
			}
		}
		return false;
	}

	double negamax(bool is_AI, int depth, double alpha, double beta)
	{

		if (Judge1(1) || Judge1(2) || depth == 0)
			return evaluation(is_AI);
		//list_all - list3 = { �����ӵĵ㼯 }

		update_list3();

		update_blank();

		order();  // ������˳������  ��߼�֦Ч��

			//����ÿһ����ѡ��
		int i = 0; search_count = 0;
		while (blank_list[i][0] != -1)
		{
			i++;
		}

		for (int next = 0; next < i; next++)
		{
			search_count += 1;
			next_step[0] = blank_list[next][0];
			next_step[1] = blank_list[next][1];
			//i++;
			if (has_neightnor() == false) continue;
			else if (is_AI)
			{
				int j = 0;
				while (list1[j][0] != -1)
				{
					j++;
				}
				list1[j][0] = next_step[0];
				list1[j][1] = next_step[1];
			}
			else if (!is_AI)
			{
				int j = 0;
				while (list2[j][0] != -1)
				{
					j++;
				}
				list2[j][0] = next_step[0];
				list2[j][1] = next_step[1];
			}

			int j = 0;
			while (list3[j][0] != -1)
			{
				j++;
			}
			list3[j][0] = next_step[0];
			list3[j][1] = next_step[1];
			//update_blank();

					//���ص���һ��ڵ�ʱ��������������෴��(��Ϊ���ص�ֵ�൱�����ڶ��ֵ�ѡ���¶��ֶԵ�ǰ���̵���������, ����Ϊ���Ķ�����, Ҫ�ѷ���ȡ��)
					//alpha������Ϊ��ǰ����£���ǰ���ֿ��Եõ������ֵ����ǰ���ֵõ����ֵ == ���ֲ�Ը����ܵ����ֵ����Ϊ������Ҫ�������
			value = -negamax(!is_AI, depth - 1, -beta, -alpha);
			//���ղ������Ƴ�
			if (is_AI)
			{
				int j = 0;
				while (list1[j + 1][0] != -1)
				{
					j++;
				}
				list1[j][0] = -1;
				list1[j][1] = -1;
			}
			else
			{
				int j = 0;
				while (list2[j + 1][0] != -1)
				{
					j++;
				}
				list2[j][0] = -1;
				list2[j][1] = -1;
			}


			j = 0;
			while (list3[j + 1][0] != -1)
			{
				j++;
			}
			next_step[0] = list3[j][0];
			next_step[1] = list3[j][1];

			

			list3[j][0] = -1;
			list3[j][1] = -1;


			int sum = 0;
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					blank_list[sum][0] = i;
					blank_list[sum][1] = j;
					sum++;
				}
			}

			update_blank();
			//order();


			if (value > alpha)
			{//��depth == DEPTHʱ, ������ѭ���ڲ��ϵ���, �ܻ��ڿ��Ǻ����������������ҵ���õ����ӷ�ʽ;
				if (depth == 5)
				{
					next_point[0] = next_step[0];
					next_point[1] = next_step[1];
				}
				if (value >= beta)
				{//alpha + beta��֦��
				//����ǰvalue > beta ʱ�൱�� ���ֵ� value < -alpha, ���ֿ϶����ῼ�����ѡ��
					cut_count += 1;
					return beta;
				}
				alpha = value;
			}

		}
		return alpha;
	}

	void AI()
	{
		//Move move;
		cut_count = 0;
		search_count = 0;
		fill_list();
		update_list3();
		negamax(true, 5, -99999999, 99999999);//��ʼ�� ��ֵ�����㷨
		//move.x = next_point[0];
		//move.y = next_point[1];
		last_pos[0] = next_point[0];
		last_pos[1] = next_point[1];
		cout << "���ι���֦������" << cut_count << endl;
		cout << "���ι�����������" << search_count << endl;
		//return move;
	}

	void PlayPVE() //�˻���ս
	{
		initmap();
		play_board();
		gg = true;
		bool turn;
		black = 0; white = 0;
		initlist();
		while (gg)
		{
			turn = is_ai();
			if (turn)
			{
				if (black + white == 0)
				{
					last_pos[0] = 7;
					last_pos[1] = 7;
					list11[0][0] = last_pos[0];
					list11[0][1] = last_pos[1];
					update_list33();
					//update_blank();
					map[7][7] = 1;
					black++; turn = is_ai();
					Drawmap(7, 7);//���µ�ͼ

					Judge_ending();
					if (!gg)break;
				}
				else
				{
					//Move nextmove;
					AI();
					xpos = last_pos[0];
					ypos = last_pos[1];

					int j = 0;
					while (list11[j][0] != -1)
					{
						j++;
					}
					list11[j][0] = last_pos[0];
					list11[j][1] = last_pos[1];
					update_list33();
					//update_blank();
					if (flag)
					{//AI���� ����
						map[xpos][ypos] = 1;
						black++; turn = is_ai();
						Drawmap(xpos, ypos);//���µ�ͼ
						Judge_ending();
						if (!gg)break;

					}
					else if (!flag)
					{//AI���� ����
						map[xpos][ypos] = 2;
						white++; turn = is_ai();
						Drawmap(xpos, ypos);//���µ�ͼ
						Judge_ending();
						if (!gg)break;
					}

				}

			}
			else if (!turn)
			{
				int c = 0;

				//Drawmap();//���µ�ͼ
				Judge_ending();
				if (!gg)break;

				ExMessage m;//��Ϣ����
				flushmessage(EX_MOUSE);
				while (1)
				{
					m = getmessage(EX_MOUSE);//�õ������Ϣ
					if (m.message == WM_LBUTTONDOWN) {
						ipos = (int)(((double)m.x) / SIZE);//�������λ��
						jpos = (int)(((double)m.y) / SIZE);
						if (map[ipos][jpos] == 0)
							break;
					}
				}

				last_pos[0] = ipos;
				last_pos[1] = jpos;
				if (map[ipos][jpos] == 0 && !flag && c == 0 && !turn)
				{//human���� ����
					map[ipos][jpos] = 1;
					black++; turn = is_ai();
					c++;
					Drawmap(ipos, jpos);//���µ�ͼ
					Judge_ending();
					if (!gg)break;

				}
				else if (map[ipos][jpos] == 0 && !turn && c == 0)
				{//human���� ����
					map[ipos][jpos] = 2;
					white++; c++; turn = is_ai();
					Drawmap(ipos, jpos);//���µ�ͼ
					Judge_ending();
					if (!gg)break;
				}
				int j = 0;
				while (list22[j][0] != -1)
				{
					j++;
				}
				list22[j][0] = ipos;
				list22[j][1] = jpos;
				update_list33();
			}
			
		}
		end_board();
	}

};


void Click3() //�˻���սѡ��˭����
{
	gg = true;
	while (gg)
	{
		ExMessage m;
		flushmessage(EX_MOUSE);
		//ExMessage getmessage(BYTE filter = EX_MOUSE);
		m = getmessage(EX_MOUSE);//�õ������Ϣ
		if (m.message == WM_LBUTTONDOWN)//����������
		{
			if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 125 && (int)m.y <= 235)                 // RECT r = { 120, 120, 360, 240 };RECT t = { 120, 240, 360, 360 };
			{
				flag = 1;//ai��
				gg = false;
			}
			else if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 245 && (int)m.y <= 355)
			{
				flag = 0;
				gg = false;
			}
		}
	}
}

void Click1() //PVP or PVE
{
	gg = true;
	while (gg)
	{
		ExMessage m;
		flushmessage(EX_MOUSE);
		//ExMessage m;
		//ExMessage getmessage(BYTE filter = EX_MOUSE);
		m = getmessage(EX_MOUSE);//�õ������Ϣ
		if (m.message == WM_LBUTTONDOWN)//����������
		{
			if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 125 && (int)m.y <= 235)                  // RECT r = { 120, 120, 360, 240 };RECT t = { 120, 240, 360, 360 };
			{
				PlayPVP();
				//end_board();

			}
			else if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 245 && (int)m.y <= 355)
			{
				chose_board();
				Click3();
				Gobang_AI PVE;
				PVE.PlayPVE();
				//end_board();

			}
		}
	}
}

void Click2() // again or exit
{
	gg = true;
	while (gg)
	{
		ExMessage m;
		flushmessage(EX_MOUSE);
		//ExMessage getmessage(BYTE filter = EX_MOUSE);
		m = getmessage(EX_MOUSE);//�õ������Ϣ
		if (m.message == WM_LBUTTONDOWN)//����������
		{
			if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 125 && (int)m.y <= 235)                 // RECT r = { 120, 120, 360, 240 };RECT t = { 120, 240, 360, 360 };
			{
				gg = false;

			}
			else if ((int)m.x >= 125 && (int)m.x <= 355 && (int)m.y >= 245 && (int)m.y <= 355)
			{
				ff = false;
				gg = false;
				//break;
			}
		}
	}

}




int main()
{
	ff = true;
	while (ff)
	{
		begin_board();
		Click1();
		Click2();
	}
	//system("pause");
	return 0;
}


