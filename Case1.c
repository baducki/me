#include "common.h"

// 1. ȸ�� ���� �Լ�
void headOfCase1(void)   // ȸ�� ���� ����� ���
{
	system("cls"); textColor(16 * 14);
	cursorOff();
	printf("                             < ȸ��  List >                                ");
	textColor(7);
	printf("\n  No  ID_NUM    NAME                ADDRESS                 CELL PHONE\n");
	printf("  ��  ������  ��������  ��������������������������������  ��������������");
}
void printInfo(Member_t *id, int maxnum)   // ����ü�� �ִ� ȸ�������� ���
{
	int i, j, check, temp, pre = 0;   // ����: i�� for���� ���� ����, j�� ��ġ ������ ���� ����, check�� �Է�Ű üũ
	// temp�� ���� �������� ���ư��� ���� ����, pre�� ����, ���� ������ ��� Ȯ���� ���� ����
	headOfCase1();
	for (i = 1, j = 1; i < maxnum; i++, j++){
		if (j>NUM_OF_PRINT) j -= NUM_OF_PRINT;  // gotoxy�� ��ġ ���� ����ϱ� ���� j ���� ���� �� j�� ��� �� ��ġ ����
		gotoxy(1, j + 3); printf("%3d", i);
		gotoxy(6, j + 3); printf("%6d", id[i].Studentnum);
		gotoxy(14, j + 3); printf("%.8s", id[i].Name);
		gotoxy(24, j + 3); printf("%.30s", id[i].Address);
		gotoxy(59, j + 3); printf("%.14s", id[i].Cellphone);

		if (i != (maxnum - 1)){
			if (i%NUM_OF_PRINT == 0 && pre == 0){
				pauseWithRight();
				temp = i - NUM_OF_PRINT;
				headOfCase1();
				pre++;
			}
			else if (i%NUM_OF_PRINT == 0 && pre != 0){
				check = pauseWithLeftRight();
				temp = i - NUM_OF_PRINT;
				if (check == 75){
					i = i - NUM_OF_PRINT * 2; pre--;
					previousPageButton();
				}
				else {
					nextPageButton();
					pre++;
				}
				headOfCase1();
			}
		}
		else if (i == (maxnum - 1)){
			textColor(16 * 10);
			gotoxy(0, 24); printf("                       ��� ȸ�� ������ ����Ͽ����ϴ�                     ");
			textColor(7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp; j = 0;
				pre--;
				previousPageButton();
				headOfCase1();
			}
			else if (check == 72) break; // ����Ű �踦 ������ ���� �������� ����
		}
	}
	cursorOn();
}


int pauseWithLeft(void)  // ȭ���� ���߰� ����ȭ�鿡 ��� ���
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("  ���� ������ [��]     (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [��]    ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75){
				previousPageButton(); break;
			}
			else if (choice == 72){
				homePageButton(); break;
			}
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                   Warning: �� Ȥ�� ��Ű�� �Է��ϼ���                      ");
		textColor(7);
	}
	return choice;
}

void pauseWithRight(void)  // ȭ���� ���߰� ����ȭ�鿡 ��� ���
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("                       (���Ͻô� Ű�� �Է��ϼ���)        ���� ������ [��]  ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 77) break;
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                    Warning: �� ����Ű�� �Է��ϼ���                        ");
		textColor(7);
	}
	nextPageButton();
}

int pauseWithLeftRight(void)    // ȭ���� ���߰� ����ȭ�鿡 ���, ����ȭ������ ���
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("  ���� ������ [��]     (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [��]    ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75) break;
			else if (choice == 77) break;
		}
		else{
			textColor(12 * 16);
			gotoxy(0, 28); printf("                    Warning: �� Ȥ�� �� ����Ű�� �Է��ϼ���                ");
			textColor(7);
		}
	}
	return choice;
}

void choiceButton(int num)   // ���� �޴����� ��� ���ý� ��ư On
{
	switch (num)
	{
	case '1':
		textColor(16 * 10);
		gotoxy(30, 8); printf("��  ȸ�� ����"); Sleep(77);
		textColor(7);
		break;
	case '2':
		textColor(16 * 10);
		gotoxy(30, 10); printf("��  ȸ�� ���"); Sleep(77);
		textColor(7);
		break;
	case '3':
		textColor(16 * 10);
		gotoxy(30, 12); printf("��  ȸ�� ����"); Sleep(77);
		textColor(7);
		break;
	case '4':
		textColor(16 * 10);
		gotoxy(30, 14); printf("��  ȸ�� ����"); Sleep(77);
		textColor(7);
		break;
	case '5':
		textColor(16 * 10);
		gotoxy(30, 16); printf("��  ȸ�� �˻�"); Sleep(77);
		textColor(7);
		break;
	case '6':
		textColor(16 * 10);
		gotoxy(30, 18); printf("��  ���� ����"); Sleep(77);
		textColor(7);
		break;
	case '7':
		textColor(16 * 10);
		gotoxy(30, 20); printf("��  �� ��    "); Sleep(77);
		textColor(7);
		break;
	}
}

void previousPageButton(void)   // ���� ������ ��ư On
{
	textColor(16 * 10 + 14);
	gotoxy(0, 26); printf("  ���� ������ [��]  "); Sleep(77);
	textColor(7);
}

void nextPageButton(void)   // ���� ������ ��ư On
{
	textColor(16 * 10 + 14);
	gotoxy(55, 26); printf("  ���� ������ [��]  "); Sleep(77);
	textColor(7);
}

void homePageButton(void)   // ���� ������ ��ư On
{
	textColor(16 * 10 + 14);
	gotoxy(55, 26); printf("  ���� ������ [��]  "); Sleep(77);
	textColor(7);
}