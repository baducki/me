#include "common.h"

// ��� �Լ�

void gotoxy(int x, int y)   // �Է� Ŀ�� ��ġ ����
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void cursorOn(void)              // Ŀ�� �ѱ�
{
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = TRUE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void cursorOff(void)
{
	CONSOLE_CURSOR_INFO CurInfo; // Ŀ�� ����
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void textColor(int color)  // ���ڻ� ����
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void warningYesOrNo(void)  // Yes Ȥ�� No�� �������� Error �޼��� 
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
	textColor(16 * 14);
}

void curtainEffect(void)
{
	gotoxy(0, 26); lineClear();
	gotoxy(0, 28); lineClear();
	textColor(15);
	gotoxy(0, 1);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 2);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 3);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 4);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 5);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 6);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 7);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 8);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 9);  printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 10); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 11); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 12); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 13); printf("�����������������");
	textColor(10); printf("< �� �� �� >"); textColor(15);
	printf("����������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 14); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 15); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 16); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 17); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 18); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 19); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 20); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 21); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 22); printf("��������������������������������������"); Sleep(CURTAIN_DELAY);
	gotoxy(0, 23); printf("��������������������������������������"); Sleep(CURTAIN_DELAY * 7); textColor(7);
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
	gotoxy(8, 13); printf("������������������������������������������������������������");
	gotoxy(0, 12); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 12); printf("��                                                        ��");
	gotoxy(0, 11); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 11); printf("��                                                        ��");
	gotoxy(0, 10); lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 10); printf("��                                                        ��");
	gotoxy(0, 9);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 9);  printf("��                                                        ��");
	gotoxy(0, 8);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 8);  printf("��                                                        ��");
	gotoxy(0, 7);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 7);  printf("��                                                        ��");
	gotoxy(0, 6);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 6);  printf("��                                                        ��");
	gotoxy(0, 5);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 5);  printf("��                                                        ��");
	gotoxy(0, 4);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 4);  printf("��                                                        ��");
	gotoxy(0, 3);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(8, 3);  printf("���������������������� < ȸ������ > ������������������������");
	gotoxy(0, 2);  lineClear(); Sleep(CURTAIN_DELAY - 10);
	gotoxy(0, 1);  lineClear(); Sleep(CURTAIN_DELAY - 10);
}

void lineClear(void)
{
	printf("                                                                           ");
}

void printfAllNodes(Member_t *head) // Linked List�� �̿��ؼ� ȸ������ ���
{
	Member_t *curNode;
	curNode = head->next;
	while (curNode){
		printf(" %s ", curNode->Name);
		curNode = curNode->next;
	}
	printf("\n");
}