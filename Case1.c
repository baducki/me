#include "common.h"

// 1. ȸ�� ���� �Լ�
void headOfCase1(void)   // ȸ�� ���� ����� ���
{
	system("cls");
	gotoxy(0, 0);
	textColor(16 * 14);
	cursorOff();
	printf("                             < ȸ��  List >                                ");
	textColor(7);
	printf("\n  No  ID_NUM    NAME                ADDRESS                 CELL PHONE\n");
	printf("  ��  ������  ��������  ��������������������������������  ��������������");
}

void printInfo(Member_t *id)   // ����ü�� �ִ� ȸ�������� ���
{
	int i = 1, j = 1, check;    // i�� for���� ���� ����, j�� ��ġ ������ ���� ����, check�� �Է�Ű üũ
	int pre = 0, temp;      // pre�� ����, ���� ������ ��� Ȯ���� ���� ����, temp�� ����, ���� ������ ��� �� i�� ������ ���� ����

	headOfCase1();
	
	Member_t tempmember[10];
	Member_t *printmember = (Member_t *)malloc(sizeof(Member_t));
	printmember->next = id[0].next;
	tempmember[0].next = printmember->next;

	for (i = 1, j = 1; printmember->next != NULL; i++, j++){
		if (j > NUM_OF_PRINT) j -= NUM_OF_PRINT;  // gotoxy�� ��ġ ���� ����ϱ� ���� j ���� ���� �� j�� ��� �� ��ġ ����

		gotoxy(1, j + 3);  printf("%3d", i);
		gotoxy(6, j + 3);  printf("%6d", printmember->next->Studentnum);
		gotoxy(14, j + 3); printf("%.8s", printmember->next->Name);
		gotoxy(24, j + 3); printf("%.30s", printmember->next->Address);
		gotoxy(59, j + 3); printf("%.14s", printmember->next->Cellphone);

		printmember->next = printmember->next->next;

		if (printmember->next != NULL){
			if (i%NUM_OF_PRINT == 0 && pre == 0){
				check = pauseWithRight();
				if (check == 77){
					temp = i - NUM_OF_PRINT;
					headOfCase1();
					pre++;
					tempmember[pre].next = printmember->next;
				}
				else if (check == 72) break; // ����Ű �踦 ������ ���� �������� ����
			}
			else if (i%NUM_OF_PRINT == 0 && pre != 0){
				check = pauseWithLeftRight();
				temp = i - NUM_OF_PRINT;
				if (check == 75){
					i = i - NUM_OF_PRINT * 2;
					previousPageButton();
					pre--;
					printmember->next = tempmember[pre].next;
				}
				else {
					nextPageButton();
					pre++;
					tempmember[pre].next = printmember->next;
				}
				headOfCase1();
			}
		}

		else if (printmember->next == NULL){
			textColor(16 * 10);
			gotoxy(0, 24); printf("                       ��� ȸ�� ������ ����Ͽ����ϴ�                     ");
			textColor(7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp;
				j = 0;
				previousPageButton();
				pre--;
				printmember->next = tempmember[pre].next;
				headOfCase1();
			}
			else if (check == 72) break; // ����Ű �踦 ������ ���� �������� ����
		}
	}
	free(printmember);
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
				homePageButton(1); break;
			}
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                   Warning: �� Ȥ�� �����Ű�� �Է��ϼ���                  ");
		textColor(7);
	}
	return choice;
}

int pauseWithRight(void)  // ȭ���� ���߰� ����ȭ�鿡 ��� ���
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("  ���� ������ [��]     (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [��]    ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 77){
				nextPageButton();
				break;
			}
			else if (choice == 72){
				homePageButton(0);
				break;
			}
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                    Warning: �� Ȥ�� �� ����Ű�� �Է��ϼ���                ");
		textColor(7);
	}
	return choice;
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
		textColor(12 * 16);
		gotoxy(0, 28); printf("                    Warning: �� Ȥ�� �� ����Ű�� �Է��ϼ���                ");
		textColor(7);
	}
	return choice;
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

void homePageButton(int check)   // ���� ������ ��ư On
{
	textColor(16 * 10 + 14);

	if (check == 0)	gotoxy(0, 26);
	else gotoxy(55, 26);

	printf("  ���� ������ [��]  "); Sleep(77);
	textColor(7);
}