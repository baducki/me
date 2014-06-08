#pragma warning(disable:4996)
// ���α׷��� ���� �⸻���� 1���� (ȸ������ ����) - 1�й� ������(141057), �۰�(141044)
// *** ����� 1. ȸ������ 2. ȸ����� 6. �����ϱ� 7. �����ϱ⸦ �����Ͽ����ϴ� ***

#include "member.h"

int main(void)
{
	system("mode con lines=30 cols=75");    // ������ â ȭ�� ũ�⸦ ����
	FILE *fp = NULL;
	Member_t id[NUM_OF_MEMBERS];

	int maxnum = inputInfo(fp, id);         // maxnum�� ���� ��ϵ� ��ü ȸ�� ��
	// InputInfo : data.txt������ ���� ����ü�� ����
	int menu_choice = 0;                    // ���� menu_choice�� ������ �����ϴ� �޴���
	int error = 0; int *perror = &error;    // ���θ޴� ���� ������ �ľ��ϱ� ���� ���� (�����͵� �Բ� ����)
	int dataIndex; // ���� ������ �ʿ��� �ε���

	while (menu_choice != -2)               // return -2 (���� �� ���� ���� Y) �� �� ���α׷� ���� + �Ƹ��ٿ� ���� �׸�
	{
		menu_choice = mainMenu(perror);

		switch (menu_choice)
		{
		case '1': //ȸ����������
			choiceButton(menu_choice);      // �޴� ��ư �Է� �� Ŭ�� ȿ��
			printInfo(id, maxnum);          // ����ü�� ����� ȸ�������� ȭ�鿡 ���
			break;

		case '2': // ȸ�����
			choiceButton(menu_choice);
			maxnum = case2(fp, id, maxnum); // ȸ�� �Է� �� maxnum +1
			break;

		case '3': // ȸ������
			choiceButton(menu_choice);
			dataIndex = findDataIndex(id, maxnum);
			//system("pause");
			deleteData(id, dataIndex);
			break;

		case '4': // ��������
			choiceButton(menu_choice);
			break;

		case '5': // �˻��ϱ�
			choiceButton(menu_choice);
			break;

		case '6': // �����ϱ�
			choiceButton(menu_choice);
			SaveFile(fp, id, maxnum);
			break;

		case '7': // ����
			choiceButton(menu_choice);
			menu_choice = saveCheck();
			break;
		}
	}
	programClose();
	return 0;
}

// Main�� ���Ե� �Լ�
int inputInfo(FILE *fp, Member_t *id)   // data.txt ������ ����ü�� ����
{
	if ((fp = fopen("data.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file <%s>", "data.txt");
		return -1;
	}
	int j, i = 0, maxnum = 0;
	while (1){
		fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", id[i].IDNum, id[i].Name, id[i].Address, id[i].Cellphone);
		id[i].Studentnum = atoi(id[i].IDNum);
		i++, maxnum++;
		if (feof(fp)) break;
	}
	j = i;
	i = 0;
	while (i<j){
		id[i].prev = &id[i - 1];
		id[i].next = &id[i + 1];
		i++;
	}
	id[i - 1].next = NULL;
	fclose(fp);
	return maxnum;
}
int mainMenu(int* error)  // ���θ޴� ��� (�Է°�: ������, ��°�: ���� �޴����ð�)
{
	int choice;
	if (*error == 0){
		printMainMenu();               // ���� ������ ���
		choice = inputMenu();          // �޴� �Է� �ޱ�
		*error = errorCheck(choice);
	}

	else if (*error == -1){            // �����Է� �� �����޼��� ���, �������� �� �����޼��� ����
		printMainMenu();               // ���� ������ ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 1 ~ 7�� ������ ���ڸ� �Է��ϼ���                ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();          //  �޴� �Է� �ޱ�
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}

	else if (*error == -2){
		printMainMenu();               // ���� ������ ���
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 5�� MENU�� ���� �۾� ���Դϴ�               ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();     //  �޴� �Է� �ޱ�
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}
	return choice;
}
void printMainMenu(void)  // ���θ޴� ���
{
	system("cls");  // �� ȭ�� ����
	printf("\n\t\t         ������������������������ \n\t\t         �� ȸ�� ���� ���α׷� �� \n");
	printf("\t\t         ������������������������ \n\t\t\t      made by YG & Kyung\n\n");
	printf("\t\t      �������� < �ֿ��� > ��������\n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  ȸ�� ����"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        ��\n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  ȸ�� ���"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        �� \n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  ȸ�� ����"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        �� \n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  ȸ�� ����"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        ��\n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  ȸ�� �˻�"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        ��\n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  �� ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("            ��\n\t\t      ��                          ��\n");
	printf("\t\t      ��     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("��  �� ��"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("            ��\n\t\t      ��                          ��\n");
	printf("\t\t      ������������������������������\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("\t\t     ���ϴ� ����� ��ȣ�� �Է��ϼ��䡼 ��                  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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

// 1. ȸ�� ���� �Լ�
void headOfCase1(void)   // ȸ�� ���� ����� ���
{
	system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < ȸ��  List >                                ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n  No  ID_NUM    NAME \t            ADDRESS \t\t    CELL PHONE\n");
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
			gotoxy(0, 24); printf("                       ��� ȸ�� ������ ����Ͽ����ϴ�                     ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp; j = 0;
				pre--;
				previousPageButton();
				headOfCase1();
			}
			else if (check == 72 || check == 104) break; // HŰ�� ������ ���� �������� ����
		}
	}
}

// 2. ȸ�� ��� �Լ�
void headOfCase2(void)
{
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                                < ȸ�� ��� >                              ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n                 ����������������������������������������������            ");
	gotoxy(11, 4); printf("�й� : ");
	gotoxy(17, 4); printf("��"); gotoxy(61, 4); printf("��");
	printf("\n                 ����������������������������������������������            ");
	printf("                 ����������������������������������������������            ");
	printf("   ��      �̸� :��");
	gotoxy(61, 7); printf("��            ");
	printf("                 ����������������������������������������������            ");
	printf("                 ����������������������������������������������            ");
	printf("   ��      �ּ� :��");
	gotoxy(61, 10); printf("��            ");
	printf("                 ����������������������������������������������            ");
	printf("                 ����������������������������������������������            ");
	printf("   ��  ��ȭ��ȣ :�� (     -      -      )                    ��            ");
	printf("                 ����������������������������������������������            ");
	printf("                                                                           ");
	printf("                                                                           ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("              ����������������< �Է½� ���� ���� >����������������         ");
	printf("              ��                                                ��         ");
	printf("              ��  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("1. �й�: �ڵ����� ����"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                        ��         ");
	printf("              ��  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("2. �̸�: ���� ���� 4���̳� �ѱ۸� �Է�"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("    ��         ");
	printf("              ��  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("3. �ּ�: ���� ���� 20�� �̳� �Է�"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         ��         ");
	printf("              ��  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("4. ��ȭ��ȣ: 11�ڸ� �̳� ���� �Է�"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("            ��         ");
	printf("              ��  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("5. ���α׷� ���� �� TXT���� ���� �ʿ�"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         ��         ");
	printf("              ����������������������������������������������������         ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int case2(FILE *fp, Member_t *id, int maxnum)   // 2. ȸ�� ��� ����
{
	system("cls");
	headOfCase2();
	maxnum += inputNewMember(fp, id, maxnum); // ȸ������� �Ϸ�Ǹ� +1, ��ҵǸ� 0
	return maxnum;
}
int findMaxStudentNum(Member_t *id, int maxnum)   // ���� ����� �л��� �� ���� ū �й� �˻�
{
	int i, maxstudentnum;
	for (i = 2; i <= maxnum; i++){
		if (id[i - 1].Studentnum < id[i].Studentnum)
			maxstudentnum = id[i].Studentnum;
	}
	return maxstudentnum;
}
int inputNewMember(FILE *fp, Member_t *id, int maxnum)   // ���ο� ȸ�� ������ �Է�
{
	int i, j, valid = -1, repeatcheck = -1, count = 0;
	int maxstudentnum = findMaxStudentNum(id, maxnum); maxstudentnum++; // �л� �й� �� ���� ū �й��� ã�� �� +1

	id[maxnum].Studentnum = maxstudentnum;
	itoa(maxstudentnum, id[maxnum].IDNum, 10);

	gotoxy(20, 4); printf("%d", maxstudentnum);
	gotoxy(63, 4); printf("(�ڵ�����)");

	while (valid)
	{
		if (count == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(17, 6); printf("����������������������������������������������");
			gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
			gotoxy(17, 8); printf("����������������������������������������������");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		gotoxy(20, 7);
		gets(id[maxnum].Name);
		valid = validName(id[maxnum].Name);
		count++;
	}
	gotoxy(17, 6); printf("����������������������������������������������");
	gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
	gotoxy(17, 8); printf("����������������������������������������������");
	validNameErrorOff(); valid = -1; count = 0;

	while (valid){
		if (count == 0){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			gotoxy(17, 9); printf("����������������������������������������������");
			gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
			gotoxy(17, 11); printf("����������������������������������������������");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		gotoxy(20, 10);
		gets(id[maxnum].Address);
		valid = validAddress(id[maxnum].Address);
		count++;
	}
	gotoxy(17, 9); printf("����������������������������������������������");
	gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
	gotoxy(17, 11); printf("����������������������������������������������");
	validAddressErrorOff(); valid = -1; count = 0;

	while (repeatcheck){
		for (i = 0, j = 0; i < 13;){
			if (count == 0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				gotoxy(17, 12); printf("����������������������������������������������");
				gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
				gotoxy(17, 14); printf("����������������������������������������������");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			if (i == 3 || i == 8){
				id[maxnum].Cellphone[i] = '-'; i++; j += 2;
			}
			else {
				gotoxy(22 + i + j, 13);
				id[maxnum].Cellphone[i] = getche();
				if (i != 0 && id[maxnum].Cellphone[i] == 8){
					if (i == 4 || i == 9){
						printf("  \b\b");
						i -= 2;
						j -= 2;
						gotoxy(22 + i + j, 13);
						printf("  \b\b");
					}
					else{
						i--;
						printf("  \b\b");
					}
				}
				else{
					valid = validCellphone(id[maxnum].Cellphone[i]);
					if (valid == 0) i++;
					else {
						validCellphoneErrorOn();
						count++;
					}
				}
			}
		}
		id[maxnum].Cellphone[i] = '\0';
		validCellphoneErrorOff(); valid = -1;
		repeatcheck = repeatCellphone(id, id[maxnum].Cellphone, maxnum);
		if (repeatcheck == -1) {
			repeatCellphoneErrorOn();
			count++;
		}
	}
	gotoxy(17, 12); printf("����������������������������������������������");
	gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
	gotoxy(17, 14); printf("����������������������������������������������");
	repeatCellphoneErrorOff();
	valid = inputMemberSave();
	if (valid == 0){
		id[maxnum].Studentnum;
		id[maxnum].IDNum;
		id[maxnum].Name;
		id[maxnum].Address;
		id[maxnum].Cellphone;
		j = 0;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(0, 26); printf("                 < ȸ�� ����� ��� �Ǿ����ϴ� >   �ƹ�Ű�� ��������       ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		gotoxy(74, 26); getche(); fflush(stdin);
	}
	else {
		id[maxnum - 1].next = &id[maxnum];
		id[maxnum].prev = &id[maxnum - 1];
		id[maxnum].next = NULL;
		j = 1;
		closeCase2();
	}
	return j;
}
int validName(char *str)   // �̸��� �ѱ� �� �Է� ����
{
	int i = 0, len = strlen(str), check = 0;
	if (str[0] >= 0 && str[0] <128){
		validNameErrorOn(); check = -1;
	}
	else if (len == 0 || str[0] == ' ') {
		validNameErrorOn(); check = -1;
	}
	else if (len > 8) {
		validNameErrorOn(); check = -1;
	}
	else {
		while (i < (len - 1)){
			if (str[i] <= -56 && str[i] >= -80){
				if (str[i] < 0)	{
					if (str[i + 1] <= -2 && str[i + 1] >= -95){
						i += 2;
					}
					else { validNameErrorOn(); check = -1; break; }
				}
				else { validNameErrorOn(); check = -1; break; }
			}
			else { validNameErrorOn(); check = -1; break; }
		}
	}
	return check;
}
void validNameErrorOn(void)   // �߸��� �̸� �Է½� ���� �޼��� On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("       Warning: �̸��� ���� ���� 4���̳��� �ѱ۸� �Է��ϼ���           ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(19, 7); printf("                                          ");
	gotoxy(19, 10); printf("                                          ");
	gotoxy(19, 13); printf(" (     -      -      )                    ");
	headOfCase2();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(17, 6); printf("����������������������������������������������");
	gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
	gotoxy(17, 8); printf("����������������������������������������������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void validNameErrorOff(void)   // �߸��� �̸� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 7); printf("(�Է¿Ϸ�)");
}
int validAddress(char *str)   // �Էµ� �ּ� valid ���� Ȯ��
{
	int i = 0, len = strlen(str), check = 0;
	if (len > 40) {
		validAddressErrorOn(); check = -1;
	}
	return check;
}
void validAddressErrorOn(void)   // �߸��� �̸� �Է½� ���� �޼��� On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("           Warning: �ּҴ� ���� ���� 20���̳��� �Է��ϼ���             ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(19, 10); printf("                                         ");
	gotoxy(19, 13); printf(" (     -      -      )                    ��");
	headOfCase2();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(17, 9); printf("����������������������������������������������");
	gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
	gotoxy(17, 11); printf("����������������������������������������������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(63, 7); printf("(�Է¿Ϸ�)");
}
void validAddressErrorOff(void)   // �߸��� �ּ� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 10); printf("(�Է¿Ϸ�)");
}
int validCellphone(char a)   // �̸��� �ѱ� �� �Է� ����
{
	int check = 0;
	if (a < 48 || a > 57){    // ���� �ƽ�Ű�ڵ�=48~57 �ܿ� �Է� �� Error
		check = -1;
		return check;
	}
	return check;
}
int repeatCellphone(Member_t *id, char *str, int maxnum)
{
	for (int i = 1; i < maxnum; i++){
		if (strcmp(id[i].Cellphone, id[maxnum].Cellphone) == 0)  // ��ȭ ��ȣ�� ���ٸ� -1�� ��ȯ
			return -1;
	}
	return 0;
}
void validCellphoneErrorOn(void)   // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("               Warning: ��ȭ��ȣ�� 11�� �̳� ���ڸ� �Է��ϼ���             ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(17, 12); printf("����������������������������������������������");
	gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
	gotoxy(17, 14); printf("����������������������������������������������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void validCellphoneErrorOff(void)   // �߸��� �ּ� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); printf("                                                                           ");
}
void repeatCellphoneErrorOn(void)   // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("         Warning: ���� ȸ���� ������ ��ȭ��ȣ�Դϴ�! �ٽ� �Է��ϼ���       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(17, 12); printf("����������������������������������������������");
	gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
	gotoxy(17, 14); printf("����������������������������������������������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(19, 13); printf(" (     -      -      )                    ");
}
void repeatCellphoneErrorOff(void)   // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 13); printf("(�Է¿Ϸ�)");
}
void closeCase2(void)
{
	int inputkey;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
	gotoxy(0, 26); printf("                 < ȸ�� ����� �Ϸ� �Ǿ����ϴ� >   �ƹ�Ű�� ��������       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(74, 26); inputkey = getche();
}
int inputMemberSave(void)   // �Է��� ȸ���� ���� ���� ���� Ȯ��
{
	int key = -1, check = -1;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("                < ȸ�� ��� �Ϸ� > �����Ͻðڽ��ϱ�? (Y/N) �� ��           ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (check != 1 || check != 0){
		gotoxy(61, 26); key = getche();
		if (key == 89 || key == 121){
			check = 1; break;
		}
		else if (key == 78 || key == 110){
			check = 0; break;
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
			gotoxy(0, 26); printf("                < ȸ�� ��� �Ϸ� > �����Ͻðڽ��ϱ�? (Y/N) �� ��           ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
	gotoxy(0, 28); printf("                                                                           ");
	return check;
}

// 6. ���� �Լ�
void SaveFile(FILE *fp, Member_t *id, int maxnum)   // �޸𸮿� ����Ǿ� �ִ� ������ ���Ϸ� ����
{
	fp = fopen("data.txt", "wt");
	fprintf(fp, "ȸ�����̵�\tȸ���̸�\tȸ���ּ�\t�ڵ�����ȣ\n");     //��ù�� ����

	for (int i = 1; i < maxnum; i++)
		fprintf(fp, "%s\t%s\t%s\t%s\n", id[i].IDNum, id[i].Name, id[i].Address, id[i].Cellphone);

	fclose(fp);
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                                < ���� ���� >                              ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n\n\n\n\n\n");
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("               �����������������������\n"); Sleep(TIME_OF_DELAY);
	printf("\n\n\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
	printf("              <���� ������ �Ϸ�Ǿ����ϴ� > �ƹ� Ű�� ��������             ");
	getch(); fflush(stdin);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// 7. ���� �Լ�
int saveCheck(void)   // ���� �� ���� ���� ������ ���� (��ȯ��: �Է¿���)
{
	int inputkey, errorcheck = 0;
	while (1){
		if (errorcheck != -1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
			gotoxy(0, 24); printf("               ���� ���� ������ ������ �����ϼ̽��ϱ�? (Y/N)�� ��          ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(62, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
		else if (errorcheck == -1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
			gotoxy(0, 24); printf("               ���� ���� ������ ������ �����ϼ̽��ϱ�? (Y/N)�� ��          ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(62, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
	}

	return errorcheck;
}
int checkSaveValue(int key)   // ���� ���� ���� �� ������ �Է��� ���� ����
{
	if (key == 89 || key == 121)
		return -2;
	if (key == 78 || key == 110)
		return 0;
	else
		return -1;
}
void programClose(void)   // ���α׷� ���� �ȳ� �޼��� ���
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < ���α׷� ���� >                             "); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("               @@@@@@@@@@@@@@@@@***.....*@@@@@@*@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("              @@@@@@@@@@@***...           ..****@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("              *@*@@@@@@@*....                 .**. *@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                 @@@@@@*....       ...........     .@@@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                *@@@@@@*..     ..*********......    .*@@@@@@@@@@@@@@@@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                ****@@@@@@*..    ....                  .@@@@@@@**.   ..@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                     @@******..    ...*.****..          .@@@@*.       ..@@\n"); Sleep(TIME_OF_DELAY);
	printf("                      ***.*..**    ..*..***.            .*@@*.. ...   ..@@\n"); Sleep(TIME_OF_DELAY);
	printf("                      ***.****.       ..                 .*@*.     ..  *@@\n"); Sleep(TIME_OF_DELAY);
	printf("                      ***...**                           .**.      .  .@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                      *....**                            .*.         *@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                       *..**                             ... ..    ..@@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                        **@@*.   .                          ..........@@@@\n"); Sleep(TIME_OF_DELAY);
	printf("                         @***@. .                          ...    ....***@\n"); Sleep(TIME_OF_DELAY);
	printf("                          @*@*....                         ... ...........\n"); Sleep(TIME_OF_DELAY);
	printf("                           @*@@*.***...*                  ............   .\n"); Sleep(TIME_OF_DELAY);
	printf("                            @@@*.*...                 ....   .......     .\n"); Sleep(TIME_OF_DELAY);
	printf("                             @@*....               .....        .        .\n"); Sleep(TIME_OF_DELAY);
	printf("                               *@..             ...........              .\n"); Sleep(TIME_OF_DELAY);
	printf("                                .@*..     ...****..........  ..          .\n"); Sleep(TIME_OF_DELAY);
	printf("                                  ........   .@@****.........            .\n"); Sleep(TIME_OF_DELAY);
	printf("                                               *******...**              .\n"); Sleep(TIME_OF_DELAY);
	printf("                                                .*@@**@@@*           .  ..\n"); Sleep(TIME_OF_DELAY);
	printf("    ..........................................@@@@@@@@*             .   ..\n"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(4, 25); printf(" made by YG & Kyung");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	gotoxy(4, 17);
	printf("G"); Sleep(TIME_OF_DELAY);
	printf("O"); Sleep(TIME_OF_DELAY);
	printf("O"); Sleep(TIME_OF_DELAY);
	printf("D"); Sleep(TIME_OF_DELAY);
	gotoxy(9, 17);
	printf("B"); Sleep(TIME_OF_DELAY);
	printf("Y"); Sleep(TIME_OF_DELAY);
	printf("E"); Sleep(TIME_OF_DELAY);
	gotoxy(4, 18);
	printf("S"); Sleep(TIME_OF_DELAY);
	printf("E"); Sleep(TIME_OF_DELAY);
	printf("E"); Sleep(TIME_OF_DELAY);
	gotoxy(8, 18);
	printf("Y"); Sleep(TIME_OF_DELAY);
	printf("O"); Sleep(TIME_OF_DELAY);
	printf("U"); Sleep(TIME_OF_DELAY);
	gotoxy(12, 18);
	printf("L"); Sleep(TIME_OF_DELAY);
	printf("A"); Sleep(TIME_OF_DELAY);
	printf("T"); Sleep(TIME_OF_DELAY);
	printf("E"); Sleep(TIME_OF_DELAY);
	printf("R"); Sleep(TIME_OF_DELAY);
	gotoxy(31, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("��"); Sleep(TIME_OF_DELAY * 3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(31, 18); printf("*.");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	gotoxy(25, 18);
	printf("\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); gotoxy(4, 28);
}

// ��� �Լ�
void gotoxy(int x, int y)   // �Է� Ŀ�� ��ġ ����
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
int pauseWithLeft(void)  // ȭ���� ���߰� ����ȭ�鿡 ��� ���
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("  ���� ������ [��]     (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [H] Ű  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75){
				previousPageButton(); break;
			}
		}
		else if (choice == 72 || choice == 104){
			homePageButton(); break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                   Warning: �� Ȥ�� H Ű�� �Է��ϼ���                      ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	return choice;
}
void pauseWithRight(void)  // ȭ���� ���߰� ����ȭ�鿡 ��� ���
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("                       (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [��]Ű  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 77) break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                    Warning: �� ����Ű�� �Է��ϼ���                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	nextPageButton();
}
int pauseWithLeftRight(void)    // ȭ���� ���߰� ����ȭ�鿡 ���, ����ȭ������ ���
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("  ���� ������ [��]     (���Ͻô� Ű�� �Է��ϼ���)      ���� ������ [��]Ű  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75) break;
			else if (choice == 77) break;
		}
		else{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
			gotoxy(0, 28); printf("                    Warning: �� Ȥ�� �� ����Ű�� �Է��ϼ���                ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
	return choice;
}
void choiceButton(int num)   // ���� �޴����� ��� ���ý� ��ư On
{
	switch (num)
	{
	case '1':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 8); printf("��  ȸ�� ����"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '2':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 10); printf("��  ȸ�� ���"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '3':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 12); printf("��  ȸ�� ����"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '4':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 14); printf("��  ȸ�� ����"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '5':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 16); printf("��  ȸ�� �˻�"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '6':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 18); printf("��  �� ��"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '7':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 20); printf("��  �� ��"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	}
}
void previousPageButton(void)   // ���� ������ ��ư On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(0, 26); printf("  ���� ������ [��]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void nextPageButton(void)   // ���� ������ ��ư On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf("  ���� ������ [��]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void homePageButton(void)   // ���� ������ ��ư On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf(" ���� ������ [H] Ű "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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

int findDataIndex(Member_t *id, int maxnum)
{

	while (1)
	{
		int choice;// �˻� ���ð�
		int valid;  // ��ȿ�� �ڷ����� üũ�Լ� -1�� ��ȿ���� ����
		char inputData[50];
		int dataIndex;// �˻��� data�� ��ġ
		system("cls");

		printf("������� �˻��ϰڽ��ϱ�?\n");
		printf("1. �й�\n");
		printf("2. �̸�\n");
		printf("3. ��ȭ��ȣ\n");


		choice = getche();

		switch (choice)
		{
		case '1':
			while (1)
			{

				printf("�й��� �Է����ּ���\n");
				printf("�й� :  ");
				gets(inputData);

				valid = validIDNum(inputData); //��ȿ�� üũ

				if (valid == -1)
				{
					continue;
				}
				//��ȿ�� üũ ��

				for (int i = 0; i < maxnum; i++)
				{
					if (strcmp(inputData, id[i].IDNum) == 0)   // IDNum�� ������ ��ȯ���� �˻�
					{
						printf("If���Դ�");
						dataIndex = i;
					}
				}
				printSearchedData(id, dataIndex); // �˻� �ڷ� ���
				return dataIndex;
			}

		case '2':
			system("cls");
			while (1){
				printf("�̸��� �Է����ּ���\n");
				printf("�̸� :  ");
				gets(inputData);

				valid = validName(inputData); //��ȿ�� üũ = ~ing  // �ٽ��Է� ����

				if (valid == -1)
				{
					printf("�ٽ� �Է����ּ���\n");
					continue;
				}

				for (int i = 0; i < maxnum; i++){ // data_idx ����
					if (strcmp(inputData, id[i].Name) == 0)
						dataIndex = i;
				}

				printSearchedData(id, dataIndex); // �˻� �ڷ� ���
				return;
			}

		case '3':
			system("cls");
			while (1)
			{
				printf("��ȭ��ȣ�� �Է����ּ���\n");
				printf("��ȭ��ȣ :  ");
				gets(inputData);

				valid = validCellphone(inputData); //��ȿ�� üũ  - ~ing // �ٽ��Է¹���

				if (valid == -1)
				{
					printf("�ٽ� �Է����ּ���\n");
					continue;
				}

				for (int i = 0; i < maxnum; i++)
				{
					if (strcmp(inputData, id[i].Cellphone) == 0)
						dataIndex = i;
				}

				printSearchedData(id, dataIndex); // �˻� �ڷ� ���
				break;

			}

		default:

			printf("1~3 ������ ���� �Է��ϼ���\n");
			break;
		}

	}
}

int validIDNum(char *data) //�й� Ȯ��
{

	if (strlen(data) != 6) //�й��� 6�ڸ�
	{
		//printf("if ���Դ�1\n");
		printf("6�ڸ��� �ٽ� �Է��ϼ���\n");
		return -1;
	}

	for (int i = 0; i < strlen(data); i++)
	{
		if (*data<48 || *data>57)
		{
			//printf("if ���Դ�2\n");
			printf("���ڸ� �Է��ϼ���. �ٽ� �Է��ϼ���\n");
			return -1;
		}
		data++;
	}

	return 1;
}



void printSearchedData(Member_t *id, int dataIndex)
{
	printf("%6s %.8s %.30s %.80s\n", id[dataIndex].IDNum, id[dataIndex].Name, id[dataIndex].Address, id[dataIndex].Cellphone);
}

void deleteData(Member_t *id, int *dataIndex)
{

	int choice;
	printf("�� ȸ���� ���� �Ͻðڽ��ϱ�?\n");
	system("pause");



}