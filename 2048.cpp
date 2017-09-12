#include <iostream>
#include<time.h>
#include<conio.h>
#include <Windows.h>
#include <string>

using namespace std;

HANDLE hOutput;//控制台屏幕缓冲区句柄
COORD coord = { 0,0 };
//双缓冲处理显示
DWORD bytes = 0;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

#define GAME_OVER 1
#define GAME_WIN 2
#define GAME_CONTINUE 3

const int ROW = 4, COL = 4;
int game[ROW][COL] = { 0 };


bool CreateNumber()
{
	int x = -1;
	int y = -1;
	int times = 0;
	int maxTimes = ROW *COL;
	int whitch = rand() % 4;
	for(int i =0;i<ROW;i++)
		for (int j = 0; j < COL; j++)
		{
			if (game[i][j] == 0)
			{
				do {
					x = rand() % ROW;
					y = rand() % COL;
				} while (game[x][y] != 0);
				int num;
				if (whitch == 0)
					num = 4;
				else
				{
					num = 2;
				}
				game[x][y] = 2;
				return true;
			}
			
		}
	return false;
	

}
void init()
{
	srand((unsigned)time(0));
	CreateNumber();
	CreateNumber();
	hOutput = CreateConsoleScreenBuffer(
		GENERIC_WRITE,//定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE,//定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
}

void Print()
{
	FillConsoleOutputCharacterA(hOutput, ' ', 3200, { 0,0 }, &bytes);
	string s1 = "*****************  2048 控 制 台 版  ******************";
	string s2 = "*****************  By zhfollow (xaut) ******************";
	int line=0;
	WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), coord, &bytes);
	WriteConsoleOutputCharacterA(hOutput, s2.c_str(), strlen(s2.c_str()), { 0,(short)++line }, &bytes);
	for (int i = 0; i < ROW; ++i)
	{
		s1 = " ---------------------------------";
		line = line + 2;
		WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { 0,(short)line }, &bytes);
		
		for (int j = 0; j < COL; ++j)
		{
			if (game[i][j] == 0)
			{
				s1 ="|  ";
				WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { (short)(j*8),(short)(line+1) }, &bytes);
			}
			else
			{
				s1 =  "|  " +to_string(game[i][j]) ;
				WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { (short)(j * 8),(short)(line+1) }, &bytes);

			}
		}
		s1 = "|" ;
		WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { 33,(short)(line +1)}, &bytes);

	}

	s1 = " ---------------------------------" ;
	WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { (short)(0),(short)(line + 2) }, &bytes);
	SetConsoleActiveScreenBuffer(hOutput);
	
}

int Input()
{
	_getch();
	char direction1 = _getch();
	int direction = 0;
	switch (direction1)
	{
	case 72:
		direction = UP;
		break;
	case 80:
		direction = DOWN;
		break;
	case 75:
		direction = LEFT;
		break;
	case 77:
		direction = RIGHT;
		break;
	default:
		break;
	}
	Sleep(100);
	return direction;
}

int Judge()
{
	for(int i =0;i<ROW;i++)
		for (int j = 0; j < COL; j++)
		{
			if (game[i][j] == 2048)
				return GAME_WIN;
		}
	for (int i = 0; i < ROW; i++)
	{
		for (int j=0; j < COL-1; j++)
		{
			if (!game[i][j] || game[i][j] == game[i][j++])
				return GAME_CONTINUE;
		}
	}
	for (int i = 0; i < COL; i++)
	{
		for (int j=0; j < ROW - 1; j++)
		{
			if (!game[i][j] || game[i][j] == game[i][j++])
				return GAME_CONTINUE;
		}
	}
	return GAME_OVER;
}
void Process(int direction)
{
	int times = 0;
	switch (direction)
	{
	case UP:
		for (int col = 0; col < COL; col++)
		{
			int times = 0;
			for (int row = 0; row < ROW - times; row++)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int crow = row; crow < ROW - 1 - times; crow++)
					{
						game[crow][col] = game[crow + 1][col];
						game[crow + 1][col] = 0;
					}
					times++;
				}
			}
			for (int row = 0; row < ROW - 1; row++)
			{
				if (game[row][col] == game[row + 1][col])
				{
					game[row][col] += game[row + 1][col];
					game[row + 1][col] = 0;
				}
			}
			times = 0;
			for (int row = 0; row < ROW - times; row++)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int crow = row; crow < ROW - 1 - times; crow++)
					{
						game[crow][col] = game[crow + 1][col];
						game[crow + 1][col] = 0;
					}
					times++;
				}
			}
		}
		break;

	case DOWN:
		for (int col = 0; col < COL; col++)
		{
			int times = 0;
			for (int row = ROW-1; row >= 0 + times; row--)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int crow = row; crow >= 1 + times; crow--)
					{
						game[crow][col] = game[crow -1][col];
						game[crow - 1][col] = 0;
					}
					times++;
				}
			}
			for (int row = ROW - 1; row >=1; row--)
			{
				if (game[row][col] == game[row - 1][col])
				{
					game[row][col] += game[row - 1][col];
					game[row - 1][col] = 0;
				}
			}
			times = 0;
			for (int row = ROW - 1; row >= 0 + times; row--)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int crow = row; crow >= 1 + times; crow--)
					{
						game[crow][col] = game[crow - 1][col];
						game[crow - 1][col] = 0;
					}
					times++;
				}
			}
		}
		break;
	case LEFT:
		for (int row = 0; row < ROW; row++)
		{
			int times = 0;
			for (int col = 0; col <COL-times; col++)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int ccol = col; ccol < COL-1-times; ccol++)
					{
						game[row][ccol] = game[row][ccol + 1];
						game[row][ccol + 1] = 0;
					}
					times++;
				}
			}
			for (int col = 0; col<COL-1; col++)
			{
				if (game[row][col] == game[row][col + 1])
				{
					game[row][col] += game[row][col + 1];
					game[row][col + 1] = 0;
				}
			}
			times = 0;
			for (int col = 0; col <COL - times; col++)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int ccol = col; ccol < COL - 1 - times; ccol++)
					{
						game[row][ccol] = game[row][ccol + 1];
						game[row][ccol + 1] = 0;
					}
					times++;
				}
			}
		}
		break;
	case RIGHT:
		for (int row = 0; row < ROW; row++)
		{
			int times = 0;
			for (int col = COL - 1; col >= 0 + times; col--)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int ccol = col; ccol >=1 + times; ccol--)
					{
						game[row][ccol] = game[row ][ccol-1];
						game[row][ccol - 1] = 0;
					}
					times++;
				}
			}
			for (int col = COL - 1; col >= 1; col--)
			{
				if (game[row][col] == game[row][col-1])
				{
					game[row][col] += game[row][col-1];
					game[row][col - 1] = 0;
				}
			}
			times = 0;
			for (int col = COL - 1; col >= 0 + times; col--)
			{
				while (game[row][col] == 0 && times < 3)
				{
					for (int ccol = col; ccol >= 1 + times; ccol--)
					{
						game[row][ccol] = game[row][ccol - 1];
						game[row][ccol - 1] = 0;
					}
					times++;
				}
			}
		}
		break;
	default:
		break;
	}
}
int main()
{
	init();
	Print();
	int direction = 0;
	int gamestate = -1;
	int flag = 1;
	while (1)
	{
		direction = Input();
		gamestate = Judge();
		if (direction && (gamestate == GAME_CONTINUE) && flag)
		{
			Process(direction);
			flag = CreateNumber();
			if (flag == 0)
			{
				gamestate = GAME_OVER;
			}
			Print();
			Sleep(100);
		}
		if (gamestate == GAME_WIN)
		{
			string s1 = "GAME WIN!!!    input 0 eixt";
			WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { 0,18 }, &bytes);
			SetConsoleActiveScreenBuffer(hOutput);
			break;
		}
		else if (gamestate == GAME_OVER)
		{
			string s1 = "GAME OVER!!!   input 0 eixt";
			WriteConsoleOutputCharacterA(hOutput, s1.c_str(), strlen(s1.c_str()), { 0,18 }, &bytes);
			SetConsoleActiveScreenBuffer(hOutput);
			break;
		}
		
	}
	
	while (flag);
	{
		cin >> flag;
	}
	return 0;
}
