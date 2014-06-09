// ���α׷��� ���� �⸻���� 3���� - 1�й� ������(141057), �۰�(141044)
// *** ����� 1. ȸ������ 2. ȸ����� 3. ȸ������ 4. ȸ������ 6. �����ϱ� 7. �����ϱ⸦ �����Ͽ����ϴ� ***

#include "common.h"

int main(void)
{
	system("mode con lines=30 cols=75");  // ������ â ȭ�� ũ�⸦ ����
	FILE *fp = NULL;
	Member_t id[NUM_OF_MEMBERS];

	unsigned int maxnum = inputInfo(fp, id); // maxnum�� ���� ��ϵ� ��ü ȸ�� ��
	                                         // InputInfo : data.txt������ ���� ����ü�� ����
	unsigned int saveneed = 0;               // saveneed�� ���̺� �ʿ� ������ üũ�ϴ� ����
	int menu_choice = 0;                     // menu_choice�� ������ �����ϴ� �޴��� ����
	int error = 0;                           // menu ���� �� error �߻��� ���� error �޼��� ����� ���� ����

	while (menu_choice != -1)                // -1 (����) �� �� ���α׷� ����
	{
		menu_choice = mainMenu(&error);

		switch (menu_choice)
		{
		case '1': //ȸ���������� 
			choiceButton(menu_choice);      // �޴� ��ư �Է� �� Ŭ�� ȿ��
			printInfo(id, maxnum);          // ����ü�� ����� ȸ�������� ȭ�鿡 ���
			break;

		case '2': // ȸ�����
			choiceButton(menu_choice);
			case2(fp, id, &maxnum); // ȸ�� �Է� �� maxnum +1
			saveneed++;
			break;

		case '3': // ȸ������
			choiceButton(menu_choice);
			deleteMemberInfo(id);
			saveneed++;
			break;

		case '4': // ��������
			choiceButton(menu_choice);
			adjustMemberInfo(id);
			saveneed++;
			break;

		case '5': // �˻��ϱ�
			choiceButton(menu_choice);
			break;

		case '6': // �����ϱ�
			choiceButton(menu_choice);
			menu_choice = saveCheck();
			if (menu_choice == 1)
			{
				saveFile(fp, id, maxnum);
				saveneed = 0;
			}
			break;

		case '7': // ����
			choiceButton(menu_choice);
			if (saveneed > 0) menu_choice = saveCheck();
			if (menu_choice == 1) saveFile(fp, id, maxnum);
			menu_choice = -1;
			break;
		}
	}
	programCloseUI();
	return 0;
}

// Main�� ���Ե� �Լ�
int inputInfo(FILE *fp, Member_t *id)   // data.txt ������ ����ü�� ����
{
	char idnum[11];
	if ((fp = fopen("data.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file <%s>", "data.txt");
		return -1;
	}
	int j, i = 0, maxnum = 0;
	while (1){
		fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", idnum, id[i].Name, id[i].Address, id[i].Cellphone);
		id[i].Studentnum = atoi(idnum);
		if (i != 0 && id[i].Studentnum == 0);
		else {
			i++, maxnum++;
		}
		if (feof(fp)) break;
	}
	id[maxnum + 1].Studentnum = 0;
	j = i; i = 0;
	while (i<j){
		id[i].prev = &id[i - 1];
		id[i].next = &id[i + 1];
		i++;
	}
	id[i - 1].next = NULL;
	fclose(fp);
	return maxnum;
}
int mainMenu(int *error)  // ���θ޴� ��� (�Է°�: ������, ��°�: ���� �޴����ð�)
{
	int choice;
	if (*error == 0){
		mainmenuUI();                // ���� ������ ���
		choice = inputMenu();        // �޴� �Է� �ޱ�
		*error = errorCheck(choice);
	}

	else if (*error == -1){          // �����Է� �� �����޼��� ���, �������� �� �����޼��� ����
		mainmenuUI();                // ���� ������ ���
		textColor(12 * 16);
		gotoxy(0, 28); printf("                  Warning: 1 ~ 7�� ������ ���ڸ� �Է��ϼ���                ");
		textColor(7);
		choice = inputMenu();        //  �޴� �Է� �ޱ�
		gotoxy(0, 28); lineClear();
		*error = errorCheck(choice);
	}

	else if (*error == -2){
		mainmenuUI();               // ���� ������ ���
		textColor(12 * 16);
		gotoxy(0, 28); printf("                  Warning: 5�� MENU�� ���� �۾� ���Դϴ�                   ");
		textColor(7);
		choice = inputMenu();     //  �޴� �Է� �ޱ�
		gotoxy(0, 28); lineClear();
		*error = errorCheck(choice);
	}
	return choice;
}
int inputMenu(void)   // �޴� ���ð� �Է�
{
	int choice;
	gotoxy(54, 26);
	choice = getche();
	return choice;
}
int errorCheck(int check)   // �޴����� �� ���� üũ
{
	if (check < 49 || check > 55) return -1;
	else if (check == 53) return -2;
	return 0;
}

void mainmenuUI(void)  // ���θ޴� UI ���
{
	system("cls");
	gotoxy(0, 1);
	printf("                         ������������������������\n");
	printf("                         �� ȸ�� ���� ���α׷� ��\n");
	printf("                         ������������������������ \n");
	textColor(8);
	printf("                              made by YG & Kyung\n\n");
	textColor(7);
	printf("                      �������� < �ֿ��� > ��������\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ��                          ��\n");
	printf("                      ������������������������������\n");
	textColor(15);
	gotoxy(30, 8);  printf("��  ȸ�� ����");
	gotoxy(30, 10); printf("��  ȸ�� ���");
	gotoxy(30, 12); printf("��  ȸ�� ����");
	gotoxy(30, 14); printf("��  ȸ�� ����");
	gotoxy(30, 16); printf("��  ȸ�� �˻�");
	gotoxy(30, 18); printf("��  ���� ����");
	gotoxy(30, 20); printf("��  �� ��");
	textColor(16 * 14);
	gotoxy(0, 26); printf("\t\t     ���ϴ� ����� ��ȣ�� �Է��ϼ��䡼 ��                  ");
	textColor(7);
}