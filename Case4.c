#include "common.h"

// �˻�ȭ�� �Լ�

void adjustMemberInfo(Member_t *id)
{
	int choice = 0;	                    // �˻��ɼ� ���� ����
	int studentid, i;                   // �˻����� �Է��� studentid�� �޴� ����, �˻����� �޴� �迭�� ���� ���� i
	char name[NAME_MAXCHAR];            // �˻����� �Է��� name�� �޴� ����
	char cellphone[CELLPHONE_MAXCHAR] ; // �˻����� �Է��� cellphone�� �޴� ����
	while (choice != -1){
		case4SearchOptionUI();
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
					choice = adjustInfo(id, i);
				}
				break;
			case '2':
				textColor(16 * 10);	gotoxy(7, 6);  printf("2. �̸�    "); textColor(7);
				studentid = searchName(name);
				if (studentid != -1){
					i = searchInfoName(id, name);
					choice = adjustInfo(id, i);
				}
				break;
			case '3':
				textColor(16 * 10);	gotoxy(7, 7);  printf("3. ��ȭ��ȣ"); textColor(7);
				studentid = searchCellphone(cellphone);
				if (studentid == -2) studentid = -1;
				if (studentid != -1){
					i = searchInfoCellphone(id, cellphone);
					choice = adjustInfo(id, i);
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

int searchInfoIDnum(Member_t *id, int idnum)
{
	int i;
	for (i = 1; id[i].Studentnum != 0; i++){
		if (idnum == id[i].Studentnum) break;
	}
	if (id[i].Studentnum == 0) i = -1;
	curtainEffect();
	case4PrintInfo(id, i);
	return i;
}

int searchCellphone(char *cellphone)
{
	int valid = -1, count = 0;    // valid�� ��ȭ��ȣ�� ��ȿ���� Ȯ��, count�� �����޼����� �ʿ����� Ȯ��
	while (valid == -1){
		if (count != 0) textColor(12);
		else textColor(10);
		gotoxy(4, 14);  printf("            ������������������������");
		gotoxy(16, 15); printf("��     -      -       ��");
		gotoxy(4, 16);  printf("            ������������������������ ");
		textColor(7);
		gotoxy(4, 15);  printf("�˻��� ��ȣ:");
		gotoxy(19, 15); 
		valid = insertCellphone(19, 15, cellphone, 0);
		if (valid == -1){
			case4SearchOptionUI();
			textColor(12 * 16); gotoxy(0, 28); printf("               Warning: ��ȭ��ȣ�� 11�� �̳� ���ڸ� �Է��ϼ���             ");
		}
		count++;
	}

	gotoxy(0, 26); lineClear();
	gotoxy(0, 28); lineClear();

	return valid;
}

int insertCellphone(int line, int row, char *cellphone, int menu)
{
	int valid, i, j, count = 0;
	gotoxy(line, row);

	for (i = 0, j = 0; i < 13;){
		if (i == 3 || i == 8){
			cellphone[i] = '-'; i++; j += 2;
		}
		else {
			gotoxy(line + i + j, row);
			cellphone[i] = getche();
			if (i != 0 && cellphone[i] == 8){
				if (i == 4 || i == 9){
					printf("  \b\b");
					i -= 2;
					j -= 2;
					gotoxy(line + i + j, row);
					printf("  \b\b");
				}
				else{
					i--;
					printf("  \b\b");
				}
			}
			else{
				valid = validCellphone(cellphone[i]);
				if (valid == 0) i++;
				else return -1;
			}
		}
	}
	validCellphoneErrorOff();

	if (valid != -1){
		valid = inputInfoYesOrNo(menu);
		if (valid == 0) cellphone[i] = '\0';
		else valid = -2;

		gotoxy(0, 26); lineClear();
		gotoxy(0, 28); lineClear();
	}
	return valid;
}

int searchInfoCellphone(Member_t *id, char *cellphone)
{
	int i, j;

	for (i = 1, j = 0; id[i-1].next != NULL; i++){
		if (!strcmp(cellphone, id[i].Cellphone)) {
			j++;
			break;
		}
	}
	if (j == 0) i = -1;
	curtainEffect();
	case4PrintInfo(id, i);

	return i;
}

int searchStudentID(void)
{
	int studentidnum;  // studentidnum�� �й� ����
	textColor(10);
	gotoxy(4, 14);  printf("            ������������������");
	gotoxy(16, 15); printf("��              ��");
	gotoxy(4, 16);  printf("            ������������������ ");
	textColor(7);
	gotoxy(4, 15);  printf("�˻��� �й�:");
	gotoxy(19, 15);
	studentidnum = insertStudentNum(19, 15, 0);
	return studentidnum;
}

int insertStudentNum(int line, int row, int menu)
{
	char studentid[STUDENTID_MAXCHAR];  // �Է¹��� �й� ����
	int i, studentidnum = 0;  // for���� ���� ���� i, studentidnum�� �Է¹��� char�� int�� �޴� ����
	int valid = 0;            // �Է� ������ valid üũ �� ���� �޴� ����
	while (valid != -1){
		for (i = 0; i < STUDENTID_MAXCHAR - 1; i++){
			gotoxy(line + i, row);
			studentid[i] = getche();
			if (i != 0 && studentid[i] == 8){  // �齺���̽� �Է� �� �ٷ� �� ���� ����
				gotoxy(line + i - 1, row); printf(" ");
				i -= 2;
			}
			else validStudentID(studentid[i], &i, line, row, menu);
		}
		studentid[i] = '\0';
		valid = inputInfoYesOrNo(menu);
		if (valid == 0) {
			studentidnum = atoi(studentid);
			return studentidnum;
		}
		gotoxy(0, 16); lineClear();
		gotoxy(0, 17); lineClear();
		gotoxy(0, 18); lineClear();
		gotoxy(0, 26); lineClear();
		gotoxy(0, 28); lineClear();
	}
	return -1;
}

int searchName(char *name)
{
	int valid = -1, count = 0;    // valid�� �̸��� ��ȿ���� Ȯ��, count�� �����޼����� �ʿ����� Ȯ��
	while (valid == -1){
		if (count != 0) textColor(12);
		else textColor(10);
		gotoxy(4, 14);  printf("            ������������������");
		gotoxy(16, 15); printf("��              ��");
		gotoxy(4, 16);  printf("            ������������������ ");
		textColor(7);
		gotoxy(4, 15);  printf("�˻��� �̸�:");
		gotoxy(19, 15);
		valid = insertName(19, 15, name, 0);
		if (valid == -1){
			case4SearchOptionUI();
			textColor(12*16); gotoxy(0, 28); printf("       Warning: �̸��� ���� ���� 4���̳��� �ѱ۸� �Է��ϼ���           ");
		}
		count++;
	}
	gotoxy(0, 16); lineClear();
	gotoxy(0, 17); lineClear();
	gotoxy(0, 18); lineClear();
	gotoxy(0, 26); lineClear();
	gotoxy(0, 28); lineClear();

	if (valid == 0) return 0;
	return -1;
}

int searchInfoName(Member_t *id, char *name)
{
	int i, j;
	int sameName[50];
	for (i = 0; i < 50; i++) sameName[i] = 0;

	for (i = 1, j = 0; id[i-1].next != NULL; i++){
		if (StringComp(name, id[i].Name)) {
			sameName[j] = i;
			j++;
		}
	}
	if (j == 0){
		curtainEffect();
		case4PrintInfo(id, -1);
		return -1;
	}

	else if (j == 1){
		curtainEffect();
		case4PrintInfo(id, sameName[j-1]);
		return sameName[j-1];
	}
	else if (j > 1){
		j = printSameNameMember(id, sameName, j);
		j--;
		curtainEffect();
		case4PrintInfo(id, sameName[j]);
		return sameName[j];
	}
	return -1;
}

int insertName(int line, int row, char *name, int menu)
{
	int valid;
	char temp[1000];
	gotoxy(line, row);
	gets(temp);

	valid = validName(temp, 2);
	if (valid != -1){
		valid = inputInfoYesOrNo(menu);
		if (valid == 0){
			strcpy(name, temp);
			return 0;
		}
		else if (valid == -1) return -2;
		gotoxy(0, 16); lineClear();
		gotoxy(0, 17); lineClear();
		gotoxy(0, 18); lineClear();
		gotoxy(0, 26); lineClear();
		gotoxy(0, 28); lineClear();
	}
	return valid;
}

int printSameNameMember(Member_t *id, int *sameName, int j)
{
	int i, valid = -1;
	textColor(10);
	gotoxy(0, 14); printf("��������������������������������������������������������������������������");
	gotoxy(0, 15); lineClear();
	gotoxy(0, 15); printf("��                                                                      ��");
	gotoxy(0, 16); printf("��                                                                      ��");
	gotoxy(0, 17); printf("��                                                                      ��");
	gotoxy(0, 18); printf("��                                                                      ��");
	gotoxy(0, 19); printf("��                                                                      ��");
	gotoxy(0, 20); printf("��                                                                      ��");
	gotoxy(0, 21); printf("��                                                                      ��");
	gotoxy(0, 22); printf("��                                                                      ��");
	gotoxy(0, 23); printf("��                                                                      ��");
	gotoxy(0, 24); printf("��                                                                      ��");
	gotoxy(0, 25); printf("��������������������������������������������������������������������������");
	textColor(7);
	gotoxy(8, 14); printf(" < �˻���� > ");
	gotoxy(2, 16); printf("No  ID_NUM    NAME                ADDRESS                 CELL PHONE\n");
	gotoxy(2, 17); printf("��  ������  ��������  ��������������������������������  ��������������");
	for (i = 0; i < j; i++){
		gotoxy(2, i + 18); printf("%2d", i + 1);
		gotoxy(6, i + 18); printf("%6d", id[sameName[i]].Studentnum);
		gotoxy(14, i + 18); printf("%.8s", id[sameName[i]].Name);
		gotoxy(24, i + 18); printf("%.30s", id[sameName[i]].Address);
		gotoxy(59, i + 18); printf("%.14s", id[sameName[i]].Cellphone);
	}
	while (valid == -1){
		textColor(16 * 14);
		gotoxy(0, 26); printf("               �˻��� ȸ���� No��ȣ�� �Է��ϼ���  �� ��                   ");
		textColor(7);
		gotoxy(52, 26); i = getch();
		if (i > 48 && i <= j + 48) return i-48;
		else {
			textColor(12 * 16);
			gotoxy(0, 28); printf("                Warning: �˻������ �ִ� ���ڸ� �Է��ϼ���                ");
			textColor(7);
			valid = -1;
		}
	}
	return 0;
}

int insertAddress(int line, int row, char *address, int menu)
{
	int valid;
	char temp[1000];
	gotoxy(line, row);
	gets(temp);

	valid = validAddress(temp, 1);
	if (valid != -1){
		valid = inputInfoYesOrNo(menu);
		if (valid == 0){
			strcpy(address, temp);
			return 0;
		}
		else if (valid == -1) return -2;
		gotoxy(0, 16); lineClear();
		gotoxy(0, 17); lineClear();
		gotoxy(0, 18); lineClear();
		gotoxy(0, 26); lineClear();
		gotoxy(0, 28); lineClear();
	}
	return valid;
}

void errorSearchChoice(void)
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("                  Warning: 1 ~ 4�� ������ ���ڸ� �Է��ϼ���                ");
	textColor(7);
}

void searchCancel(void)
{
	cursorOff();
	textColor(16 * 10);
	gotoxy(0, 26); printf("         < ȸ������ ������ ��� �Ǿ����ϴ� > �ƹ� Ű�� ��������            ");
	textColor(7);
	getch();
	cursorOn();
}

void validStudentID(char studentID, int *i, int line, int row, int menu)
{
	if (studentID < 48 || studentID > 57){  // ���� �ƽ�Ű�ڵ� 48~57 �ܿ� �Է� �� Error
		validStudentIDError(menu);
		gotoxy(line + *i, row); printf(" ");
		*i-=1;
	}
}

void validStudentIDError(int menu)
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("                 Warning: �й��� 6�� �̳� ���ڸ� �Է��ϼ���                ");
	textColor(12);
	if (menu == 0){
		gotoxy(4, 14);  printf("            ������������������");
		gotoxy(16, 15); printf("��");
		gotoxy(32, 15); printf("��");
		gotoxy(4, 16);  printf("            ������������������ ");
	}
	else if (menu == 1) {
		gotoxy(0, 16); printf("                    ����������������������������������������������         ");
		gotoxy(20, 17); printf("��"); gotoxy(64, 17); printf("��");
		gotoxy(0, 18); printf("                    ����������������������������������������������         ");
	}
	textColor(7);
}

int inputInfoYesOrNo(int i) // �Է����� ���� ���� Ȯ�� (�Է°� i: �˻� or ���� ���� ����)
{
	int key;  // key: Yes or No ���� ����
	char input[2][5] = { "�˻�", "����" };
	while (1){
		textColor(16 * 10);
		gotoxy(0, 26); printf("                  �� ������ %s�Ͻðڽ��ϱ�? (Y/N) �� ��                  ", input[i]);
		textColor(7);
		gotoxy(54, 26);
		key = getche();
		if (key == 89 || key == 121) return 0;
		else if (key == 78 || key == 110) return -1;
		else warningYesOrNo();
	}
	return 0;
}

void case4PrintInfo(Member_t *id, int i)
{
	if (i == -1){
		textColor(12);
		gotoxy(21, 7);  printf("�˻��� ������ �������� �ʽ��ϴ�!");
		cursorOff();
		textColor(12 * 16);
		gotoxy(0, 28); printf("    Warning: �������� �ʴ� ȸ�������� �˻��߽��ϴ� (�ƹ�Ű�� ��������)     ");
		textColor(7); getch();
		cursorOn();
	}
	else{
		textColor(15);
		gotoxy(12, 5);  printf("��     �й� : %d", id[i].Studentnum);
		gotoxy(12, 7);  printf("��     �̸� : %s", id[i].Name);
		gotoxy(12, 9);  printf("��     �ּ� : %s", id[i].Address);
		gotoxy(12, 11); printf("�� ��ȭ��ȣ : %s", id[i].Cellphone);
		textColor(7);
	}
}

// ����ȭ�� �Լ�

int adjustInfo(Member_t *id, int i)
{
	int j, IDnum = 0, valid = -1, count = 0;
	int choice = 0;
	char tempname[NAME_MAXCHAR];           // �̸� ���� ������ �ǵ����� ���� temp ����
	char tempaddress[ADDRESS_MAXCHAR];     // �ּ� ���� ������ �ǵ����� ���� temp ����
	char tempcellphone[CELLPHONE_MAXCHAR]; // ��ȭ��ȣ ���� ������ �ǵ����� ���� temp ����

	if (i != -1){
		while (choice != -1){
			choice = adjustInfoMenuChoice();
			switch (choice)
			{
			case '1':
				adjustCell(count);
				gotoxy(6, 17); printf("��     �й� : ");
				IDnum = insertStudentNum(23, 17, 1);
				if (IDnum > -1)
					IDnum = repeatStudentIDCheck(id, IDnum);
				if (IDnum > -1)
					adjustInfoInputStudentID(id, IDnum, i);
				break;
			case '2':
				while (valid == -1){
					adjustCell(count);
					gotoxy(6, 17); printf("��     �̸� : ");
					strcpy(tempname, id[i].Name);
					valid = insertName(23, 17, id[i].Name, 1);
					if (valid > -1)
						adjustInfoInputName(id, i);
					else strcpy(id[i].Name, tempname);
					count++;
				}
				valid = -1; count = 0;
				break;
			case '3':
				while (valid == -1){
					adjustCell(count);
					gotoxy(6, 17); printf("��     �ּ� : ");
					strcpy(tempaddress, id[i].Address);
					valid = insertAddress(23, 17, id[i].Address, 1);
					if (valid > -1)	adjustInfoInputAddress(id, i);
					else strcpy(id[i].Address, tempaddress);
					count++;
				}
				valid = -1; count = 0;
				break;
			case '4':
				while (valid == -1){
					adjustCell(count);
					gotoxy(6, 17); printf("�� ��ȭ��ȣ : ");
					gotoxy(26, 17); printf(" -      -     ");
					strcpy(tempcellphone, id[i].Cellphone);
					valid = insertCellphone(23, 17, id[i].Cellphone, 1);
					if (valid > -1){  // ��ȭ��ȣ �ߺ� Check
						for (j = 1; id[j].Studentnum != 0; j++){
							if (i == j);
							else if (strcmp(id[j].Cellphone, id[i].Cellphone) == 0) {  // ��ȭ ��ȣ�� ���ٸ� -1�� ��ȯ
								repeatCellphoneErrorOn(1);
								valid = -1;
								break;
							}
						}
					}
					if (valid != -1) {
						adjustInfoInputCellphone(id, i);
						break;
					}
					else strcpy(id[i].Cellphone, tempcellphone);
					count++;
				}
				break;
			}
			gotoxy(0, 16); lineClear(); gotoxy(0, 17); lineClear(); gotoxy(0, 18); lineClear();
		}
	}
	return -1;
}

int adjustInfoMenuChoice(void)
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("             ������ ������ ��ȣ�� �Է��ϼ���  �� ��     ���� ������ [��]   ");
	textColor(7);
	while (1){
		gotoxy(48, 26); textColor(16 * 14); printf(" "); textColor(7);
		gotoxy(48, 26); choice = getche();
		if (choice == 224){
			choice = getch();
			if (choice == 72){
				homePageButton(1);
				return -1;
			}
		}
		else if (choice < '0' || choice > '4'){
			textColor(12 * 16);
			gotoxy(0, 28); printf("                  Warning: 1 ~ 4�� ������ ���ڸ� �Է��ϼ���                ");
			textColor(7);
		}
		else {
			gotoxy(0, 26); lineClear();
			break;
		}
	}
	return choice;
}

void adjustCell(int count)
{
	if (count == 0)	textColor(10);
	else textColor(12);
	gotoxy(0, 16); printf("                    ����������������������������������������������         ");
	gotoxy(0, 17); lineClear();
	gotoxy(20, 17); printf("��"); gotoxy(64, 17); printf("��");
	gotoxy(0, 18); printf("                    ����������������������������������������������         ");
	textColor(7);
}

 void adjustInfoInputStudentID(Member_t *id, int IDnum, int i)
{
	id[i].Studentnum = IDnum;
	cursorOff();
	textColor(16 * 10);
	gotoxy(0, 26); printf("          < �й� ������ �Ϸ� �Ǿ����ϴ� > �ƹ� Ű�� ��������             ");
	textColor(7);
	getch();
	cursorOn();
	gotoxy(0, 16); lineClear();
	gotoxy(0, 17); lineClear();
	gotoxy(0, 18); lineClear();
	gotoxy(0, 26); lineClear();
	gotoxy(0, 28); lineClear();
	case4PrintInfo(id, i);
}

 void adjustInfoInputName(Member_t *id, int i)
{
	 cursorOff();
	 textColor(16 * 10);
	 gotoxy(0, 26); printf("          < �̸� ������ �Ϸ� �Ǿ����ϴ� > �ƹ� Ű�� ��������             ");
	 textColor(7);
	 getch();
	 cursorOn();
	 gotoxy(22, 7); printf("          ");
	 gotoxy(0, 16); lineClear();
	 gotoxy(0, 17); lineClear();
	 gotoxy(0, 18); lineClear();
	 gotoxy(0, 26); lineClear();
	 gotoxy(0, 28); lineClear();
	 case4PrintInfo(id, i);
 }
 
 void adjustInfoInputAddress(Member_t *id, int i)
 {
	 cursorOff();
	 textColor(16 * 10);
	 gotoxy(0, 26); printf("          < �ּ� ������ �Ϸ� �Ǿ����ϴ� > �ƹ� Ű�� ��������             ");
	 textColor(7);
	 getch();
	 cursorOn();
	 gotoxy(22, 9); printf("                                            ");
	 gotoxy(0, 16); lineClear();
	 gotoxy(0, 17); lineClear();
	 gotoxy(0, 18); lineClear();
	 gotoxy(0, 26); lineClear();
	 gotoxy(0, 28); lineClear();
	 case4PrintInfo(id, i);
 }

 void adjustInfoInputCellphone(Member_t *id, int i)
 {
	 cursorOff();
	 textColor(16 * 10);
	 gotoxy(0, 26); printf("           < ��ȭ��ȣ ������ �Ϸ� �Ǿ����ϴ� > �ƹ� Ű�� ��������          ");
	 textColor(7);
	 getch();
	 cursorOn();
	 gotoxy(0, 16); lineClear();
	 gotoxy(0, 17); lineClear();
	 gotoxy(0, 18); lineClear();
	 gotoxy(0, 26); lineClear();
	 gotoxy(0, 28); lineClear();
	 case4PrintInfo(id, i);
 }

 int repeatStudentIDCheck(Member_t *id, int IDnum)
 {
	 int i;  // for ���� ���� ���� i
	 for (i = 1; id[i].Studentnum != 0; i++){
		 if (id[i].Studentnum == IDnum){
			 cursorOff();
			 textColor(12 * 16);
			 gotoxy(0, 28); printf("      Warning: ���� ȸ���� �ߺ��Ǵ� �й��Դϴ� (�ƹ�Ű�� ��������)         ");
			 textColor(7); getch();
			 cursorOn();
			 gotoxy(0, 16); lineClear();
			 gotoxy(0, 17); lineClear();
			 gotoxy(0, 18); lineClear();
			 gotoxy(0, 26); lineClear();
			 gotoxy(0, 28); lineClear();
			 IDnum = -1;
			 break;
		 }
	 }
	 return IDnum;
 }

 void case4SearchOptionUI(void)  // ȸ������ ���� �� �˻� �ɼ� UI
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