#include "common.h"

// 기능 함수

void gotoxy(int x, int y)   // 입력 커서 위치 조정
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void cursorOn(void)              // 커서 켜기
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void cursorOff(void)
{
	CONSOLE_CURSOR_INFO CurInfo; // 커서 끄기
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void textColor(int color)  // 글자색 변경
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void warningYesOrNo(void)  // Yes 혹은 No를 누르세요 Error 메세지 
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("                  Warning: Y(예) 혹은 N(아니요) 키를 입력하세요            ");
	textColor(16 * 14);
}

void curtainEffect(void)
{
	gotoxy(0, 26); lineClear();
	gotoxy(0, 28); lineClear();
	textColor(15);
	gotoxy(0, 1);  printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 2);  printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 3);  printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 4);  printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 5);  printf(" ■■□□□■■□□□□■■□□□■■□□□□■■■■□□□■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 6);  printf(" ■□■■■□■□■■■■□■■■□■□■■■□■■□■■■■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 7);  printf(" ■■□■■■■□■■■■□■■■□■□■■■□■□■■■■■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 8);  printf(" ■■■□■■■□□□□■□□□□□■□■■□■■□■■■■■□□□□□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 9);  printf(" ■■■■□■■□■■■■□■■■□■□□□■■■□■■■■■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 10); printf(" ■□■■■□■□■■■■□■■■□■□■■□■■■□■■■■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 11); printf(" ■■□□□■■□□□□■□■■■□■□■■■□■■■□□□■□■■■□■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 12); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 13); printf(" ■■■■■■■■■■■■■■■■");
	textColor(10); printf("< 검 색 중 >"); textColor(15);
	printf("■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 14); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 15); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 16); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 17); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 18); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 19); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 20); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 21); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 22); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 23); printf(" ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■"); Sleep(CURTAIN_DELAY * 7); textColor(7);
	gotoxy(0, 23); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 22); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 21); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 20); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 19); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 18); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 17); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 16); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 15); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 14); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(0, 13); lineClear(); Sleep(CURTAIN_DELAY);
	gotoxy(8, 13); printf("└────────────────────────────┘");
	gotoxy(0, 12); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 12); printf("│                                                        │");
	gotoxy(0, 11); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 11); printf("│                                                        │");
	gotoxy(0, 10); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 10); printf("│                                                        │");
	gotoxy(0, 9);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 9);  printf("│                                                        │");
	gotoxy(0, 8);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 8);  printf("│                                                        │");
	gotoxy(0, 7);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 7);  printf("│                                                        │");
	gotoxy(0, 6);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 6);  printf("│                                                        │");
	gotoxy(0, 5);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 5);  printf("│                                                        │");
	gotoxy(0, 4);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 4);  printf("│                                                        │");
	gotoxy(0, 3);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 3);  printf("┌────────── < 회원정보 > ───────────┐");
	gotoxy(0, 2);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(0, 1);  lineClear(); Sleep(CURTAIN_DELAY - 10);
}

void lineClear(void)
{
	printf("                                                                           ");
}

void printfAllNodes(Member_t *head) // Linked List를 이용해서 회원정보 출력
{
	Member_t *curNode;
	curNode = head->next;
	while (curNode){
		printf(" %s ", curNode->Name);
		curNode = curNode->next;
	}
	printf("\n");
}

void screenClearUp()
{
	int i;
	cursorOff();
	gotoxy(0, 27);
	for (i = 0; i < 28; i++)
	{
		printf("\n"); Sleep(14);
	}
	gotoxy(0, 0);
	textColor(16 * 14);
	lineClear();
	textColor(7);
	Sleep(14);
	cursorOn();
}

void screenClearDelete()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	cursorOff();
	int i, j;
	for (i = 7; i <= csbi.dwSize.X; i += 21)
	{
		coordScreen.Y = i; Sleep(14);
		for (j = 0; j <= i; j++)
		{
			coordScreen.X = j;
			coordScreen.Y--;
			SetConsoleCursorPosition(hConsole, coordScreen);
			printf(" ");
		}
	}
	for (i = 2; i <= csbi.dwSize.X; i += 27)
	{
		coordScreen.Y = i; Sleep(14);
		for (j = 0; j <= i; j++)
		{
			coordScreen.X = j;
			coordScreen.Y--;
			SetConsoleCursorPosition(hConsole, coordScreen);
			printf(" ");
		}
	}

	for (i = 3; i <= csbi.dwSize.X; i += 20)
	{
		coordScreen.Y = i; Sleep(14);
		for (j = 0; j <= i; j++)
		{
			coordScreen.X = j;
			coordScreen.Y--;
			SetConsoleCursorPosition(hConsole, coordScreen);
			printf(" ");
		}
	}

	for (i = 1; i <= csbi.dwSize.X; i += 11)
	{
		coordScreen.Y = i; Sleep(14);
		for (j = 0; j <= i; j++)
		{
			coordScreen.X = j;
			coordScreen.Y--;
			SetConsoleCursorPosition(hConsole, coordScreen);
			printf(" ");
		}
	}

	for (i = 0; i <= csbi.dwSize.X + 28; i += 7)
	{
		coordScreen.Y = i;
		for (j = 0; j <= i; j++)
		{
			coordScreen.X = j;
			coordScreen.Y--;
			SetConsoleCursorPosition(hConsole, coordScreen);
			printf(" ");
		}
	}
	SetConsoleCursorPosition(hConsole, coordScreen);
	cursorOn();
}