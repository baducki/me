// ���α׷��� ���� �⸻���� 3���� - 1�й� ������(141057), �۰�(141044)
// *** ����� 1. ȸ������ 2. ȸ����� 3. ȸ������ 4. ȸ������ 6. �����ϱ� 7. �����ϱ⸦ �����Ͽ����ϴ� ***

#include "common.h"

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
		i++, maxnum++;
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