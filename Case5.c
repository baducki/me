#include "common.h"

void searchMemberInfo(Member_t *id)
{
	int choice = 0;	                    // �˻��ɼ� ���� ����
	int studentid;                   // �˻����� �Է��� studentid�� �޴� ����, �˻����� �޴� �迭�� ���� ���� i
	char name[NAME_MAXCHAR];            // �˻����� �Է��� name�� �޴� ����
	char cellphone[CELLPHONE_MAXCHAR];  // �˻����� �Է��� cellphone�� �޴� ����
	while (choice != -1){
		case5SearchOptionUI();
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
					choice = searchInfoIDnum(id, studentid);
					searchInfo(id, choice);
					choice = -1;
				}
				break;
			case '2':
				textColor(16 * 10);	gotoxy(7, 6);  printf("2. �̸�    "); textColor(7);
				studentid = searchName(name);
				if (studentid != -1){
					choice = searchInfoName(id, name);
					searchInfo(id, choice);
					choice = -1;
				}
				break;
			case '3':
				textColor(16 * 10);	gotoxy(7, 7);  printf("3. ��ȭ��ȣ"); textColor(7);
				studentid = searchCellphone(cellphone);
				if (studentid == -2) studentid = -1;
				if (studentid != -1){
					choice = searchInfoCellphone(id, cellphone);
					searchInfo(id, choice);
					choice = -1;
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

void case5SearchOptionUI(void)  // ȸ������ ���� �� �˻� �ɼ� UI
{
	system("cls");
	textColor(16 * 14);
	gotoxy(0, 0); printf("                             < ȸ�� ���� �˻� >                            ");
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

void searchInfo(Member_t *id, int i)
{
	if (i != -1){
		cursorOff();
		textColor(16 * 14);
		gotoxy(0, 0); printf("                             < ȸ�� ���� �˻� >                            ");
		textColor(7);
		gotoxy(8, 3);  printf("���������������������� < ȸ������ > ������������������������");
		gotoxy(8, 4);  printf("��                                                        ��");
		gotoxy(8, 5);  printf("��                                                        ��");
		gotoxy(8, 6);  printf("��                                                        ��");
		gotoxy(8, 7);  printf("��                                                        ��");
		gotoxy(8, 8);  printf("��                                                        ��");
		gotoxy(8, 9);  printf("��                                                        ��");
		gotoxy(8, 10); printf("��                                                        ��");
		gotoxy(8, 11); printf("��                                                        ��");
		gotoxy(8, 12); printf("��                                                        ��");
		gotoxy(8, 13); printf("������������������������������������������������������������");
		gotoxy(12, 5);  printf("��     �й� : %d", id[i].Studentnum);
		gotoxy(12, 7);  printf("��     �̸� : %s", id[i].Name);
		gotoxy(12, 9);  printf("��     �ּ� : %s", id[i].Address);
		gotoxy(12, 11); printf("�� ��ȭ��ȣ : %s", id[i].Cellphone);
		textColor(16 * 10);
		gotoxy(0, 26); printf("                 < ȸ�� �˻��� �Ϸ� �Ǿ����ϴ� >   �ƹ�Ű�� ��������       ");
		textColor(7); getch();
		cursorOn();
	}
	return -1;
}