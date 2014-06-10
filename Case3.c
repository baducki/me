#include "common.h"

void deleteMemberInfo(Member_t *id)
{
	int choice = 0;	                    // �˻��ɼ� ���� ����
	int studentid, i;                   // �˻����� �Է��� studentid�� �޴� ����, �˻����� �޴� �迭�� ���� ���� i
	char name[NAME_MAXCHAR];            // �˻����� �Է��� name�� �޴� ����
	char cellphone[CELLPHONE_MAXCHAR];  // �˻����� �Է��� cellphone�� �޴� ����
	while (choice != -1){
		case3DeleteSearchOptionUI();
		gotoxy(20, 12); choice = getche();
		if (choice < 49 || choice > 52)
			errorSearchChoice();
		else {
			switch (choice)
			{
			case '1':
				textColor(16 * 10);	gotoxy(7, 5);  printf("1. �й�    "); textColor(7);
				studentid = searchStudentID();
				if (studentid != -1){
					i = searchInfoIDnum(id, studentid);
					choice = deleteInfo(id, i);
				}
				break;
			case '2':
				textColor(16 * 10);	gotoxy(7, 6);  printf("2. �̸�    "); textColor(7);
				studentid = searchName(name);
				if (studentid != -1){
					i = searchInfoName(id, name);
					choice = deleteInfo(id, i);
				}
				break;
			case '3':
				textColor(16 * 10);	gotoxy(7, 7);  printf("3. ��ȭ��ȣ"); textColor(7);
				studentid = searchCellphone(cellphone);
				if (studentid == -2) studentid = -1;
				if (studentid != -1){
					i = searchInfoCellphone(id, cellphone);
					choice = deleteInfo(id, i);
				}
				break;
			case '4':
				textColor(16 * 10);	gotoxy(7, 8);  printf("4. ���    "); textColor(7);
				searchCancel();
				choice = -1;
				break;
			}
		}
	}
}

int deleteInfo(Member_t *id, int i)
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("        �� ȸ�������� �����Ͻðڽ��ϱ�? (Y/N) �� ��     ���� ������ [��]   ");
	textColor(7);
	while (1){
		gotoxy(48, 26); textColor(16 * 14); printf(" "); textColor(7);
		gotoxy(48, 26); choice = getche();
		if (choice == 224){
			choice = getch();
			if (choice == 72){
				homePageButton();
				return -1;
			}
		}
		else if (choice == 89 || choice == 121) {
			deleteLinkedList(id, i);
			cursorOff();
			textColor(16 * 10);
			gotoxy(0, 26); printf("           < ȸ�� ������ �����Ǿ����ϴ� >   �ƹ� Ű�� ��������             ");
			textColor(7);
			getch();
			cursorOn();
			return -1;
		}
		else if (choice == 78 || choice == 110){
			cursorOff();
			textColor(16 * 10);
			gotoxy(0, 26); printf("        < ȸ�� ���� ������ ��ҵǾ����ϴ� >    �ƹ� Ű�� ��������           ");
			textColor(7);
			getch();
			cursorOn();
			return -1;
		}
		else {
			textColor(12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
			textColor(7);
		}
	}
	return 0;
}

void deleteLinkedList(Member_t *id, int i)
{
	Member_t *temp = (Member_t*)malloc(sizeof(Member_t));

	temp->prev = id[i].prev;
	temp->next = id[i].next;
	
	if (id[i].next != NULL){
		id[i].prev->next = temp->next;
		id[i].next->prev = temp->prev;
	}
	else id[i].prev->next = NULL;

	id[i].Address[0] = '\0';
	id[i].Cellphone[0] = '\0';
	id[i].Name[0] = '\0';
	id[i].Studentnum = 0;

	free(temp);
}

void case3DeleteSearchOptionUI(void)  // ȸ������ ���� �� �˻� �ɼ� UI
{
	system("cls");
	textColor(16 * 14);
	gotoxy(0, 0); printf("                             < ȸ�� ���� ���� >                            ");
	textColor(7);
	gotoxy(3, 3);  printf("�� < ȸ��  �˻� > ��");
	gotoxy(3, 4);  printf("��                ��");
	gotoxy(3, 5);  printf("��                ��");
	gotoxy(3, 6);  printf("��                ��");
	gotoxy(3, 7);  printf("��                ��");
	gotoxy(3, 8);  printf("��                ��");
	gotoxy(3, 9);  printf("��                ��");
	gotoxy(3, 10); printf("��������������������");
	textColor(15);
	gotoxy(7, 5);  printf("1. �й�");
	gotoxy(7, 6);  printf("2. �̸�");
	gotoxy(7, 7);  printf("3. ��ȭ��ȣ");
	gotoxy(7, 8);  printf("4. ���");
	textColor(7);
	gotoxy(4, 12); printf("�˻� �ɼ� ���á� ��");
}