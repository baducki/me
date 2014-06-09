#include "common.h"

// 2. ȸ�� ��� �Լ�
void case2(FILE *fp, Member_t *id, int *maxnum)   // 2. ȸ�� ��� ����
{
	system("cls");
	case2UI();
	inputNewMember(fp, id, maxnum); // ȸ������� �Ϸ�Ǹ� +1, ��ҵǸ� 0
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
void inputNewMember(FILE *fp, Member_t *id, int *maxnum)   // ���ο� ȸ�� ������ �Է�
{
	int i, j, valid = -1, repeatcheck = -1, count = 0;
	int maxstudentnum = findMaxStudentNum(id, *maxnum);
	maxstudentnum++; // �л� �й� �� ���� ū �й��� ã�� �� +1

	id[*maxnum].Studentnum = maxstudentnum;

	gotoxy(20, 4); printf("%d", maxstudentnum);
	gotoxy(63, 4); printf("(�ڵ�����)");

	while (valid)
	{
		if (count == 0){
			textColor(10);
			gotoxy(17, 6); printf("����������������������������������������������");
			gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
			gotoxy(17, 8); printf("����������������������������������������������");
			textColor(7);
		}
		gotoxy(20, 7);
		gets(id[*maxnum].Name);
		valid = validName(id[*maxnum].Name, 1);
		count++;
	}
	gotoxy(17, 6); printf("����������������������������������������������");
	gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
	gotoxy(17, 8); printf("����������������������������������������������");
	validNameErrorOff(); valid = -1; count = 0;

	while (valid){
		if (count == 0){
			textColor(10);
			gotoxy(17, 9); printf("����������������������������������������������");
			gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
			gotoxy(17, 11); printf("����������������������������������������������");
			textColor(7);
		}
		gotoxy(20, 10);
		gets(id[*maxnum].Address);
		valid = validAddress(id[*maxnum].Address, 0);
		count++;
	}
	gotoxy(17, 9); printf("����������������������������������������������");
	gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
	gotoxy(17, 11); printf("����������������������������������������������");
	validAddressErrorOff(); valid = -1; count = 0;

	while (repeatcheck){
		for (i = 0, j = 0; i < 13;){
			if (count == 0){
				textColor(10);
				gotoxy(17, 12); printf("����������������������������������������������");
				gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
				gotoxy(17, 14); printf("����������������������������������������������");
				textColor(7);
			}
			if (i == 3 || i == 8){
				id[*maxnum].Cellphone[i] = '-'; i++; j += 2;
			}
			else {
				gotoxy(22 + i + j, 13);
				id[*maxnum].Cellphone[i] = getche();
				if (i != 0 && id[*maxnum].Cellphone[i] == 8){
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
					valid = validCellphone(id[*maxnum].Cellphone[i]);
					if (valid == 0) i++;
					else {
						validCellphoneErrorOn();
						count++;
					}
				}
			}
		}
		id[*maxnum].Cellphone[i] = '\0';
		validCellphoneErrorOff(); valid = -1;
		repeatcheck = repeatCellphone(id, id[*maxnum].Cellphone, *maxnum);
		if (repeatcheck == -1) {
			repeatCellphoneErrorOn(0);
			count++;
		}
	}
	gotoxy(17, 12); printf("����������������������������������������������");
	gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
	gotoxy(17, 14); printf("����������������������������������������������");
	repeatCellphoneErrorOff();
	valid = inputMemberSave();
	cursorOff();
	if (valid == 0){
		id[*maxnum].Studentnum = 0;
		id[*maxnum].Name;
		id[*maxnum].Address;
		id[*maxnum].Cellphone;
		j = 0;
		textColor(16 * 10);
		gotoxy(0, 26); printf("                 < ȸ�� ����� ��� �Ǿ����ϴ� >   �ƹ�Ű�� ��������       ");
		textColor(7);
		gotoxy(74, 26); getche(); fflush(stdin);
	}
	else {
		id[*maxnum - 1].next = &id[*maxnum];
		id[*maxnum].prev = &id[*maxnum - 1];
		id[*maxnum].next = NULL;
		j = 1;
		closeCase2();
	}
	cursorOn();
	id[*maxnum + 1].Studentnum = 0;
	*maxnum += j;
}
int validName(char *str, int key)   // �̸��� �ѱ� �� �Է� ����
{
	int i = 0, len = strlen(str), check = 0;
	if (str[0] >= 0 && str[0] <128){
		validNameErrorOn(key); check = -1;
	}
	else if (len == 0 || str[0] == ' ') {
		validNameErrorOn(key); check = -1;
	}
	else if (len > 8) {
		validNameErrorOn(key); check = -1;
	}
	else {
		while (i < (len - 1)){
			if (str[i] <= -56 && str[i] >= -80){
				if (str[i] < 0)	{
					if (str[i + 1] <= -2 && str[i + 1] >= -95){
						i += 2;
					}
					else { validNameErrorOn(key); check = -1; break; }
				}
				else { validNameErrorOn(key); check = -1; break; }
			}
			else { validNameErrorOn(key); check = -1; break; }
		}
	}
	return check;
}
void validNameErrorOn(int key)   // �߸��� �̸� �Է½� ���� �޼��� On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("       Warning: �̸��� ���� ���� 4���̳��� �ѱ۸� �Է��ϼ���           ");
	textColor(7);
	if (key == 1){
		gotoxy(19, 7); printf("                                          ");
		gotoxy(19, 10); printf("                                          ");
		gotoxy(19, 13); printf(" (     -      -      )                    ");
		case2UI();
		textColor(12);
		gotoxy(17, 6); printf("����������������������������������������������");
		gotoxy(17, 7); printf("��"); gotoxy(61, 7); printf("��");
		gotoxy(17, 8); printf("����������������������������������������������");
		textColor(7);
	}
}
void validNameErrorOff(void)   // �߸��� �̸� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 7); printf("(�Է¿Ϸ�)");
}
int validAddress(char *str, int menu)   // �Էµ� �ּ� valid ���� Ȯ��
{
	int i = 0, len = strlen(str), check = 0;
	if (len > 40) {
		validAddressErrorOn(menu); check = -1;
	}
	return check;
}
void validAddressErrorOn(int menu)   // �߸��� �̸� �Է½� ���� �޼��� On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("           Warning: �ּҴ� ���� ���� 20���̳��� �Է��ϼ���             ");
	textColor(7);
	if (menu == 0){
		gotoxy(19, 10); printf("                                         ");
		gotoxy(19, 13); printf(" (     -      -      )                    ��");
		case2UI();
		textColor(12);
		gotoxy(17, 9); printf("����������������������������������������������");
		gotoxy(17, 10); printf("��"); gotoxy(61, 10); printf("��");
		gotoxy(17, 11); printf("����������������������������������������������");
		textColor(7);
		gotoxy(63, 7); printf("(�Է¿Ϸ�)");
	}
}
void validAddressErrorOff(void)   // �߸��� �ּ� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 10); printf("(�Է¿Ϸ�)");
}
int validCellphone(char a)   // �̸��� �ѱ� �� �Է� ����
{
	int check = 0;
	if (a < 48 || a > 57)    // ���� �ƽ�Ű�ڵ�=48~57 �ܿ� �Է� �� Error
		check = -1;
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
	textColor(12 * 16);
	gotoxy(0, 28); printf("               Warning: ��ȭ��ȣ�� 11�� �̳� ���ڸ� �Է��ϼ���             ");
	textColor(7);
	textColor(12);
	gotoxy(17, 12); printf("����������������������������������������������");
	gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
	gotoxy(17, 14); printf("����������������������������������������������");
	textColor(7);
}
void validCellphoneErrorOff(void)   // �߸��� �ּ� �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); lineClear();
}
void repeatCellphoneErrorOn(int menu)   // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("         Warning: ���� ȸ���� ������ ��ȭ��ȣ�Դϴ�! �ٽ� �Է��ϼ���       ");
	textColor(7);
	if (menu == 0){
		textColor(12);
		gotoxy(17, 12); printf("����������������������������������������������");
		gotoxy(17, 13); printf("��"); gotoxy(61, 13); printf("��");
		gotoxy(17, 14); printf("����������������������������������������������");
		textColor(7);
		gotoxy(19, 13); printf(" (     -      -      )                    ");
	}
}
void repeatCellphoneErrorOff(void)   // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 13); printf("(�Է¿Ϸ�)");
}
void closeCase2(void)
{
	int inputkey;
	textColor(16 * 10);
	gotoxy(0, 26); printf("                 < ȸ�� ����� �Ϸ� �Ǿ����ϴ� >   �ƹ�Ű�� ��������       ");
	textColor(7);
	gotoxy(74, 26); inputkey = getche();
}
int inputMemberSave(void)   // �Է��� ȸ���� ���� ���� ���� Ȯ��
{
	int key = -1, check = -1;
	textColor(16 * 14);
	gotoxy(0, 26); printf("                < ȸ�� ��� �Ϸ� > �����Ͻðڽ��ϱ�? (Y/N) �� ��           ");
	textColor(7);
	while (check != 1 || check != 0){
		gotoxy(61, 26); key = getche();
		if (key == 89 || key == 121){
			check = 1; break;
		}
		else if (key == 78 || key == 110){
			check = 0; break;
		}
		else{
			textColor(12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
			textColor(16 * 14);
			gotoxy(0, 26); printf("                < ȸ�� ��� �Ϸ� > �����Ͻðڽ��ϱ�? (Y/N) �� ��           ");
			textColor(7);
		}
	}
	gotoxy(0, 28); lineClear();
	return check;
}

void case2UI(void)   // ȸ����� UI ���
{
	gotoxy(0, 0);
	textColor(16 * 14);
	printf("                                < ȸ�� ��� >                              ");
	textColor(7);
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
	lineClear();
	lineClear();
	textColor(14);
	printf("              ����������������< �Է½� ���� ���� >����������������         ");
	printf("              ��                                                ��         ");
	printf("              ��  "); textColor(15);
	printf("1. �й�: �ڵ����� ����"); textColor(14);
	printf("                        ��         ");
	printf("              ��  "); textColor(15);
	printf("2. �̸�: ���� ���� 4���̳� �ѱ۸� �Է�"); textColor(14);
	printf("    ��         ");
	printf("              ��  "); textColor(15);
	printf("3. �ּ�: ���� ���� 20�� �̳� �Է�"); textColor(14);
	printf("         ��         ");
	printf("              ��  "); textColor(15);
	printf("4. ��ȭ��ȣ: 11�ڸ� �̳� ���� �Է�"); textColor(14);
	printf("            ��         ");
	printf("              ��  "); textColor(12);
	printf("5. ���α׷� ���� �� TXT���� ���� �ʿ�"); textColor(14);
	printf("         ��         ");
	printf("              ����������������������������������������������������         ");
	textColor(7);
}