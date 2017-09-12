
//贪吃蛇 双缓冲去过闪烁

#include<iostream>
#include<time.h>
#include<conio.h>
#include <Windows.h>
#include<string>
using namespace std;
typedef struct { int x; int y; }Point;

HANDLE hOutput, hOutBuf;//控制台屏幕缓冲区句柄
COORD coord = { 0,0 };
//双缓冲处理显示
DWORD bytes = 0;
char map[22][22];
Point snake[400], food, Next;
int head, tail;
int grade, length, autotime;
char direction;

inline void Update(char map[][22], int grade, int length, int autotime)
{
	/*
	system("cls");
	int i, j;
	cout << endl;
	for (i= 0; i< 22; i++)
	{
		for (j = 0; j < 22; j++)
			cout << map[i][j]<<' ';
		if (i == 0)
			cout << "\t等级为：" << grade;
		if (i == 2)
			cout << "\t长度为：" << length;
		if (i == 6)
			cout << "\t自动前进时间：" << autotime;
		cout << endl;
	}
	*/
	
	
	for (int i = 0; i < 22; i++)
	{
		coord.Y = i;
		char map1[44];
		for (int k = 0; k < 22; k++)
		{
			map1[2 * k] = map[i][k];
			map1[2 * k + 1] = ' ';
		}
		WriteConsoleOutputCharacterA(hOutBuf, map1, 43, coord, &bytes);
	}
	COORD coord1 = { 48,2 };
	COORD coord2 = { 48,4 };
	COORD coord3 = { 48,6 };
	string s1 = "等级为：";
	string s2 = "长度为：";
	string s3 = "自动前进时间：";
	WriteConsoleOutputCharacterA(hOutBuf,s1.c_str(), strlen(s1.c_str()), coord1, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, s2.c_str(), strlen(s2.c_str()), coord2, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf,s3.c_str() , strlen(s3.c_str()), coord3, &bytes);
	COORD coord11 = { 58,2 };
	COORD coord22 = { 58,4 };
	COORD coord33 = { 64,6 };
	WriteConsoleOutputCharacterA(hOutBuf, to_string(grade).c_str(), strlen(to_string(grade).c_str()), coord11, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, to_string(length).c_str(), strlen(to_string(length).c_str()), coord22, &bytes);
	WriteConsoleOutputCharacterA(hOutBuf, to_string(autotime).c_str(), strlen(to_string(autotime).c_str()), coord33, &bytes);

	SetConsoleActiveScreenBuffer(hOutBuf);
}

inline void hello()
{
	cout << "贪吃蛇游戏即将开始" << endl;
	double start;
	for (int i = 1; i >= 0; i--)
	{
		start = (double)clock() / CLOCKS_PER_SEC;
		while ((double)clock() / CLOCKS_PER_SEC - start <= 1);
		if (i > 0)
		{
			system("cls");
			cout << "倒计时" << i;
		}
		else
			Update(map, grade, length, autotime);
	}

}

inline void f()
{
	srand(time(0));
	do {
		food.x = rand() % 20 + 1;
		food.y= rand() % 20 + 1;
	} while (map[food.x][food.y] != ' ');
		map[food.x][food.y] = '!';
}

inline void init()
{
	int i, j;
	for (i = 1; i <= 20; i++)
	{
		for (j = 1; j <= 20; j++)
			map[i][j] = ' ';
	}
	for (i = 0; i <= 21; i++) {
		map[0][i] = map[21][i] = map[i][0] = map[i][21] = '*';
	}
	map[1][1] = map[1][2] = 'o';
	map[1][3] = '@';
	head = 2;
	tail = 0;
	snake[head].x = 1; snake[head].y = 3;
	snake[tail].x = 1; snake[tail].y = 1;
	snake[1].x = 1; snake[1].y = 2;
	f();
	grade = 1;
	length = 3;
	autotime = 500;
	direction = 77;
	//创建新的控制台缓冲区
	hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_WRITE,//定义进程可以往缓冲区写数据
		FILE_SHARE_WRITE,//定义缓冲区可共享写权限
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);
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
	SetConsoleCursorInfo(hOutBuf, &cci);
}
inline int GO()
{
	bool timeover = true;
	double start = (double)clock() / CLOCKS_PER_SEC;
	while ((timeover = ((double)clock() / CLOCKS_PER_SEC - start <= autotime / 1000.0)) && !_kbhit());
	if (timeover)
	{
		_getch();
		direction = _getch();
	}
	switch (direction)
	{
	case 72:
		Next.x = snake[head].x - 1;
		Next.y = snake[head].y;
		break;
	case 80:
		Next.x = snake[head].x + 1;
		Next.y = snake[head].y;
		break;
	case 75:
		Next.x = snake[head].x ;
		Next.y = snake[head].y-1;
		break;
	case 77:
		Next.x = snake[head].x;
		Next.y = snake[head].y+1;
		break;
	default:
		cout << "game over";
		return 0;
	}
	if (Next.x == 0 || Next.x == 21 || Next.y == 0 || Next.y == 21)
	{
		cout << "game over";
		return 0;
	}
	if (map[Next.x][Next.y] != ' ' && !(Next.x == food.x &&Next.y == food.y))
	{
		cout << "game over";
		return 0;
	}
	if (length == 400)
	{
		cout << "good game";
		return 0;
	}
	return 1;
}

inline void Eat()
{
	length++;
	int _grade = length / 10 + 1;
	if (_grade != grade)
	{
		grade = _grade;
		if (autotime >= 100)
			autotime = 550 - grade * 50;
	}
	map[Next.x][Next.y] = '@';
	map[snake[head].x][snake[head].y] = 'o';
	head = (head + 1) % 400;
	snake[head].x = Next.x;
	snake[head].y = Next.y;
	f();
	Update(map, grade, length, autotime);
}

inline void Failture()
{
	map[snake[tail].x][snake[tail].y] = ' ';
	tail = (tail + 1) % 400;
	map[Next.x][Next.y] = '@';
	map[snake[head].x][snake[head].y] = 'O';
	head = (head + 1) % 400;
	snake[head].x = Next.x;
	snake[head].y = Next.y;
	Update(map, grade, length, autotime);
}
int main()
{
	init();
	hello();
	while (1)
	{
		if (GO())
		{
			if (Next.x == food.x&&Next.y == food.y)
				Eat();
			else
				Failture();
		}
		else
			return 0;
	}
	return 0;
}