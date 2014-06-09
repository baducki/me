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
		case '1': //ȸ����������    �˻�Ű �߰�, ���������� �߰� �ʿ�
			choiceButton(menu_choice);      // �޴� ��ư �Է� �� Ŭ�� ȿ��
			printInfo(id, maxnum);          // ����ü�� ����� ȸ�������� ȭ�鿡 ���
			break;

		case '2': // ȸ�����       �ּ� error �߰� �ʿ�
			choiceButton(menu_choice);
			case2(fp, id, &maxnum); // ȸ�� �Է� �� maxnum +1
			saveneed++;
			break;

		case '3': // ȸ������
			choiceButton(menu_choice);
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

		case '6': // �����ϱ�  ������ ������ ���� �� �����ư ������ Error �޼��� �߱� �ʿ�
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