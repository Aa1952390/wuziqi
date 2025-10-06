#include<stdio.h>
#include<math.h>//引入数学符号绝对值
#include<graphics.h>//载入图片和音乐

int flag = 0;//记录回合数
int ChessPlace[25][25] = { 0 };//记录棋子数组

//初始化游戏：
void initGame() {
	initgraph(474, 711);//创建画面
	loadimage(NULL, "bg.jpg");//载入背景图片
	//绘制棋盘，以450*450以18为间隔，棋盘25*25
	setlinecolor(BLACK);
	for (int i = 1; i < 25; i++) {
		line(0, 18 * i, 450, 18 * i);//横线
		line(18 * i, 0, 18 * i, 450);//竖线
	}
	setlinestyle(PS_SOLID, 2);//加粗边界线
	line(450, 0, 450, 450);//绘制边界线
	setbkmode(0);//设置背景图为透明
	settextcolor(BLACK);//设置字体颜色,
	outtext(460, 250, "玩家1:黑棋");
	outtext(460, 500, "玩家2:白棋");
	return 0;
}
//游戏的判断
int judge(int MapX,int MapY) {
	int temp = 2 - flag % 2;//
	//判定竖直方向
	for (int i = MapX - 4, j = MapY; i <= MapX; i++) {
		if (i >= 1 && i < 21 && temp == ChessPlace[i][j] && temp == ChessPlace[i + 1][j] &&
			temp == ChessPlace[i + 2][j] && temp == ChessPlace[i + 3][j]
			&& temp == ChessPlace[i + 4][j]) {
			return 1;
		}
	}
	//判定横的方向
	for (int i = MapX, j = MapY - 4; j <= MapY; j++) {
		if (i >= 1 && i < 21 && temp == ChessPlace[i][j] && temp == ChessPlace[i][j+1] &&
			temp == ChessPlace[i][j+2] && temp == ChessPlace[i][j+3]
			&& temp == ChessPlace[i][j+4]) {
			return 1;
		}
	}
	//判定左斜线方向
	for (int i = MapX-4, j = MapY - 4; i<=MapX,j <= MapY; i++,j++) {
		if (i >= 1 && i < 21 && temp == ChessPlace[i][j] && temp == ChessPlace[i+1][j + 1] &&
			temp == ChessPlace[i+2][j + 2] && temp == ChessPlace[i+3][j + 3]
			&& temp == ChessPlace[i+4][j + 4]) {
			return 1;
		}
	}
	//判定右斜线方向
	for (int i = MapX-4, j = MapY + 4; i<=MapX,j >= MapY;i++ j--) {
		if (i >= 1 && i < 21 && temp == ChessPlace[i][j] && temp == ChessPlace[i+1][j - 1] &&
			temp == ChessPlace[i+2][j - 2] && temp == ChessPlace[i+3][j - 3]
			&& temp == ChessPlace[i+4][j - 4]) {
			return 1;
		}
	}
	return 0;
		
		
	
}

//开始游戏
void playGame() {
	int ChessX = 0, ChessY = 0;//记录棋子的坐标
	int MapX = 0, MapY = 0;//记录棋盘地图下标
	MOUSEMSG Msg;//定义一个变量（存储库）存储鼠标信息

	HWND hwnd = GetHWnd();//获取窗口，在表面

	while (1) {
		Msg = GetMouseMsg();//获取鼠标信息
		//优化鼠标位置使其被认定在线条交汇处
		for (int i = 1; i < 25; i++) {
			for (int j = 1; j < 25; j++) {
				if (abs(Msg.x - j * 18) <= 9 && abs(Msg.y - i * 18) <= 9) {
					ChessX = j * 18;//记录x坐标
					ChessY = i * 18;//记录y坐标
					MapX = i;
					MapY = j;
				}
			}
		}if (Msg.uMsg == WM_LBUTTONDOWN) {
		//如果鼠标左键按下
			if (ChessPlace[MapX][MapY] != 0) {
				MessageBox(hwnd, "这里有棋子了！请重新选择。", "五子棋", MB_OK);
				continue;
			}
			if (flag % 2 == 0) {
				setfillcolor(BLACK);//设置圆的颜色
				solidcircle(ChessX, ChessY, 8);
				ChessPlace[MapX][MapY] = 1;//黑棋为1
			}
			else {
				setfillcolor(WHILE);//设置圆的颜色
				solidcircle(ChessX, ChessY, 8);
				ChessPlace[MapX][MapY] = 2;//白棋为2
			}
			flag++;//更换下棋者
		}
		if (judge(MapX, MapY)) {
			if (1 == flag % 2) {
				MessageBox(hwnd, "玩家1;黑棋dictory", "Game Over", MB_OK);
				return;
			}
			else {
				MessageBox(hwnd, "玩家2;白棋dictory", "Game Over", MB_OK);
				return;
			}
		}
	}
}

int main() {
	mciSendString("play bgm2.mp3", 0, 0, 0);载入哈基米音乐

	intGame();
	playGame();
	closegraph();
	return 0;

}

