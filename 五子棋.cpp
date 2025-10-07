#pragma comment(lib, "winmm.lib")
#include<stdio.h>
#include<windows.h>
#include<math.h>//������ѧ���ž���ֵ
#include<graphics.h>//����ͼƬ������

int flag = 0;
int ChessMap[25][25] = { 0 };//��¼��������

//��ʼ����Ϸ��
void initGame() {
	initgraph(474, 711);//��������
	loadimage(NULL, L"bg.jpg");//���뱳��ͼƬ
	//�������̣���450*450��18Ϊ���������25*25
	setlinecolor(BLACK);
	for (int i = 1; i < 25; i++) {
		line(0, 18 * i, 450, 18 * i);//����
		line(18 * i, 0, 18 * i, 450);//����
	}
	setlinestyle(PS_SOLID, 2);//�Ӵֱ߽���
	line(450, 0, 450, 450);//���Ʊ߽���
	line(0, 450, 450, 450);
	setbkmode(0);//���ñ���ͼΪ͸��
	settextcolor(BLACK);//����������ɫ,
	outtextxy(270, 500, L"���1:����");
	outtextxy(130, 500, L"���2:����");

}
//��Ϸ���ж�
int judge(int MapX,int MapY) {
	int temp = 2 - flag % 2;//
	//�ж���ֱ����
	for (int i = MapX - 4, j = MapY; i <= MapX; i++) {
		if (i >= 1 && i < 21 && temp == ChessMap[i][j] && temp == ChessMap[i + 1][j] &&
			temp == ChessMap[i + 2][j] && temp == ChessMap[i + 3][j]
			&& temp == ChessMap[i + 4][j]) {
			return 1;
		}
	}
	//�ж���ķ���
	for (int i = MapX, j = MapY - 4; j <= MapY; j++) {
		if (i >= 1 && i < 21 && temp == ChessMap[i][j] && temp == ChessMap[i][j+1] &&
			temp == ChessMap[i][j+2] && temp == ChessMap[i][j+3]
			&& temp == ChessMap[i][j+4]) {
			return 1;
		}
	}
	//�ж���б�߷���
	for (int i = MapX-4, j = MapY - 4; i<=MapX &&j <= MapY; i++,j++) {
		if (i >= 1 && i < 21 && temp == ChessMap[i][j] && temp == ChessMap[i+1][j + 1] &&
			temp == ChessMap[i+2][j + 2] && temp == ChessMap[i+3][j + 3]
			&& temp == ChessMap[i+4][j + 4]) {
			return 1;
		}
	}
	//�ж���б�߷���
	for (int i = MapX-4, j = MapY + 4; i<=MapX &&j >= MapY;i++ ,j--) {
		if (i >= 1 && i < 21 && temp == ChessMap[i][j] && temp == ChessMap[i+1][j - 1] &&
			temp == ChessMap[i+2][j - 2] && temp == ChessMap[i+3][j - 3]
			&& temp == ChessMap[i+4][j - 4]) {
			return 1;
		}
	}
	return 0;
		
		
	
}

//��ʼ��Ϸ
void playGame() {
	int ChessX = 0, ChessY = 0;//��¼���ӵ�����
	int MapX = 0, MapY = 0;//��¼���̵�ͼ�±�
	MOUSEMSG Msg;//����һ���������洢�⣩�洢�����Ϣ

	HWND hwnd = GetHWnd();//��ȡ���ڣ��ڱ���

	while (1) {
		Msg = GetMouseMsg();//��ȡ�����Ϣ
		//�Ż����λ��ʹ�䱻�϶����������㴦
		for (int i = 1; i < 25; i++) {
			for (int j = 1; j < 25; j++) {
				if (abs(Msg.x - j * 18) <= 9 && abs(Msg.y - i * 18) <= 9) {
					ChessX = j * 18;//��¼x����
					ChessY = i * 18;//��¼y����
					MapX = i;
					MapY = j;
				}
			}
		}if (Msg.uMsg == WM_LBUTTONDOWN) {
		//�������������
			if (ChessMap[MapX][MapY] != 0) {
				MessageBox(hwnd, L"�����������ˣ�������ѡ��", L"������", MB_OK);
				continue;
			}
			if (flag % 2 == 0) {
				setfillcolor(BLACK);//����Բ����ɫ
				solidcircle(ChessX, ChessY, 8);
				ChessMap[MapX][MapY] = 1;//����Ϊ1
			}
			else {
				setfillcolor(WHITE);//����Բ����ɫ
				solidcircle(ChessX, ChessY, 8);
				ChessMap[MapX][MapY] = 2;//����Ϊ2
			}
			flag++;//����������
		}
		if (judge(MapX, MapY)) {
			if (1 == flag % 2) {
				MessageBox(hwnd, L"���1;����ʤ��", L"Game Over", MB_OK);
				return;
			}
			else {
				MessageBox(hwnd, L"���2;����ʤ��", L"Game Over", MB_OK);
				return;
			}
		}
	}
}

int main() {
	mciSendString(L"play bgm2.mp3", 0, 0, 0);

	initGame();
	playGame();
	closegraph();
	return 0;
}