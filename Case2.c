#include "common.h"

// 2. �蛾� 蛔煙 л熱
void case2(FILE *fp, Member_t *id, int *maxnum)   // 2. �蛾� 蛔煙 褒ч
{
	system("cls");
	case2UI();
	inputNewMember(fp, id, maxnum); // �蛾礸貔狨� 諫猿腎賊 +1, 鏃模腎賊 0
}

int findMaxStudentNum(Member_t *id, int maxnum)   // ⑷營 盪濰脹 з儅菟 醞 陛濰 贖 з廓 匐儀
{
	int i, maxstudentnum;
	for (i = 2; i <= maxnum; i++){
		if (id[i - 1].Studentnum < id[i].Studentnum)
			maxstudentnum = id[i].Studentnum;
	}
	return maxstudentnum;
}
void inputNewMember(FILE *fp, Member_t *id, int *maxnum)   // 億煎遴 �蛾� 薑爾蒂 殮溘
{
	int i, j, valid = -1, repeatcheck = -1, count = 0;
	int maxstudentnum = findMaxStudentNum(id, *maxnum);
	maxstudentnum++; // з儅 з廓 醞 陛濰 贖 з廓擊 瓊擎 �� +1

	id[*maxnum].Studentnum = maxstudentnum;

	gotoxy(20, 4); printf("%d", maxstudentnum);
	gotoxy(63, 4); printf("(濠翕儅撩)");

	while (valid)
	{
		if (count == 0){
			textColor(10);
			gotoxy(17, 6); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
			gotoxy(17, 7); printf("弛"); gotoxy(61, 7); printf("弛");
			gotoxy(17, 8); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
			textColor(7);
		}
		gotoxy(20, 7);
		gets(id[*maxnum].Name);
		valid = validName(id[*maxnum].Name, 1);
		count++;
	}
	gotoxy(17, 6); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(17, 7); printf("弛"); gotoxy(61, 7); printf("弛");
	gotoxy(17, 8); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
	validNameErrorOff(); valid = -1; count = 0;

	while (valid){
		if (count == 0){
			textColor(10);
			gotoxy(17, 9); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
			gotoxy(17, 10); printf("弛"); gotoxy(61, 10); printf("弛");
			gotoxy(17, 11); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
			textColor(7);
		}
		gotoxy(20, 10);
		gets(id[*maxnum].Address);
		valid = validAddress(id[*maxnum].Address, 0);
		count++;
	}
	gotoxy(17, 9); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(17, 10); printf("弛"); gotoxy(61, 10); printf("弛");
	gotoxy(17, 11); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
	validAddressErrorOff(); valid = -1; count = 0;

	while (repeatcheck){
		for (i = 0, j = 0; i < 13;){
			if (count == 0){
				textColor(10);
				gotoxy(17, 12); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
				gotoxy(17, 13); printf("弛"); gotoxy(61, 13); printf("弛");
				gotoxy(17, 14); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
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
	gotoxy(17, 12); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(17, 13); printf("弛"); gotoxy(61, 13); printf("弛");
	gotoxy(17, 14); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
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
		gotoxy(0, 26); printf("                 < �蛾� 蛔煙檜 鏃模 腎歷蝗棲棻 >   嬴鼠酈釭 援腦撮蹂       ");
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
int validName(char *str, int key)   // 檜葷縑 и旋 諼 殮溘 旎雖
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
void validNameErrorOn(int key)   // 澀跤脹 檜葷 殮溘衛 縑楝 詭撮雖 On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("       Warning: 檜葷擎 嗥橫噙晦 橈檜 4濠檜頂煎 и旋虜 殮溘ж撮蹂           ");
	textColor(7);
	if (key == 1){
		gotoxy(19, 7); printf("                                          ");
		gotoxy(19, 10); printf("                                          ");
		gotoxy(19, 13); printf(" (     -      -      )                    ");
		case2UI();
		textColor(12);
		gotoxy(17, 6); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
		gotoxy(17, 7); printf("弛"); gotoxy(61, 7); printf("弛");
		gotoxy(17, 8); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
		textColor(7);
	}
}
void validNameErrorOff(void)   // 澀跤脹 檜葷 殮溘衛 縑楝 詭撮雖 Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 7); printf("(殮溘諫猿)");
}
int validAddress(char *str, int menu)   // 殮溘脹 輿模 valid 嶸鼠 �挫�
{
	int i = 0, len = strlen(str), check = 0;
	if (len > 40) {
		validAddressErrorOn(menu); check = -1;
	}
	return check;
}
void validAddressErrorOn(int menu)   // 澀跤脹 檜葷 殮溘衛 縑楝 詭撮雖 On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("           Warning: 輿模朝 嗥橫噙晦 んл 20濠檜頂煎 殮溘ж撮蹂             ");
	textColor(7);
	if (menu == 0){
		gotoxy(19, 10); printf("                                         ");
		gotoxy(19, 13); printf(" (     -      -      )                    弛");
		case2UI();
		textColor(12);
		gotoxy(17, 9); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
		gotoxy(17, 10); printf("弛"); gotoxy(61, 10); printf("弛");
		gotoxy(17, 11); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
		textColor(7);
		gotoxy(63, 7); printf("(殮溘諫猿)");
	}
}
void validAddressErrorOff(void)   // 澀跤脹 輿模 殮溘衛 縑楝 詭撮雖 Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 10); printf("(殮溘諫猿)");
}
int validCellphone(char a)   // 檜葷縑 и旋 諼 殮溘 旎雖
{
	int check = 0;
	if (a < 48 || a > 57)    // 璋濠 嬴蝶酈囀萄=48~57 諼縑 殮溘 衛 Error
		check = -1;
	return check;
}
int repeatCellphone(Member_t *id, char *str, int maxnum)
{
	for (int i = 1; i < maxnum; i++){
		if (strcmp(id[i].Cellphone, id[maxnum].Cellphone) == 0)  // 瞪�� 廓�ㄟ� 偽棻賊 -1擊 奩��
			return -1;
	}
	return 0;
}
void validCellphoneErrorOn(void)   // 澀跤脹 瞪�食醽� 殮溘衛 縑楝 詭撮雖 On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("               Warning: 瞪�食醽ㄣ� 11濠 檜頂 璋濠虜 殮溘ж撮蹂             ");
	textColor(7);
	textColor(12);
	gotoxy(17, 12); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
	gotoxy(17, 13); printf("弛"); gotoxy(61, 13); printf("弛");
	gotoxy(17, 14); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
	textColor(7);
}
void validCellphoneErrorOff(void)   // 澀跤脹 輿模 殮溘衛 縑楝 詭撮雖 Off
{
	gotoxy(0, 28); lineClear();
}
void repeatCellphoneErrorOn(int menu)   // 澀跤脹 瞪�食醽� 殮溘衛 縑楝 詭撮雖 On
{
	textColor(12 * 16);
	gotoxy(0, 28); printf("         Warning: 晦襄 �蛾灠� 翕橾и 瞪�食醽�殮棲棻! 棻衛 殮溘ж撮蹂       ");
	textColor(7);
	if (menu == 0){
		textColor(12);
		gotoxy(17, 12); printf("忙式式式式式式式式式式式式式式式式式式式式式忖");
		gotoxy(17, 13); printf("弛"); gotoxy(61, 13); printf("弛");
		gotoxy(17, 14); printf("戌式式式式式式式式式式式式式式式式式式式式式戎");
		textColor(7);
		gotoxy(19, 13); printf(" (     -      -      )                    ");
	}
}
void repeatCellphoneErrorOff(void)   // 澀跤脹 瞪�食醽� 殮溘衛 縑楝 詭撮雖 Off
{
	gotoxy(0, 28); lineClear();
	gotoxy(63, 13); printf("(殮溘諫猿)");
}
void closeCase2(void)
{
	int inputkey;
	textColor(16 * 10);
	gotoxy(0, 26); printf("                 < �蛾� 蛔煙檜 諫猿 腎歷蝗棲棻 >   嬴鼠酈釭 援腦撮蹂       ");
	textColor(7);
	gotoxy(74, 26); inputkey = getche();
}
int inputMemberSave(void)   // 殮溘и �蛾衋� 薑爾 盪濰 嶸鼠 �挫�
{
	int key = -1, check = -1;
	textColor(16 * 14);
	gotoxy(0, 26); printf("                < �蛾� 蛔煙 諫猿 > 盪濰ж衛啊蝗棲梱? (Y/N) □ ■           ");
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
			gotoxy(0, 28); printf("                  Warning: Y(蕨) �分� N(嬴棲蹂) 酈蒂 殮溘ж撮蹂            ");
			textColor(16 * 14);
			gotoxy(0, 26); printf("                < �蛾� 蛔煙 諫猿 > 盪濰ж衛啊蝗棲梱? (Y/N) □ ■           ");
			textColor(7);
		}
	}
	gotoxy(0, 28); lineClear();
	return check;
}

void case2UI(void)   // �蛾礸貔� UI 轎溘
{
	gotoxy(0, 0);
	textColor(16 * 14);
	printf("                                < �蛾� 蛔煙 >                              ");
	textColor(7);
	printf("\n\n                 忙式式式式式式式式式式式式式式式式式式式式式忖            ");
	gotoxy(11, 4); printf("з廓 : ");
	gotoxy(17, 4); printf("弛"); gotoxy(61, 4); printf("弛");
	printf("\n                 戌式式式式式式式式式式式式式式式式式式式式式戎            ");
	printf("                 忙式式式式式式式式式式式式式式式式式式式式式忖            ");
	printf("   函      檜葷 :弛");
	gotoxy(61, 7); printf("弛            ");
	printf("                 戌式式式式式式式式式式式式式式式式式式式式式戎            ");
	printf("                 忙式式式式式式式式式式式式式式式式式式式式式忖            ");
	printf("   刻      輿模 :弛");
	gotoxy(61, 10); printf("弛            ");
	printf("                 戌式式式式式式式式式式式式式式式式式式式式式戎            ");
	printf("                 忙式式式式式式式式式式式式式式式式式式式式式忖            ");
	printf("   券  瞪�食醽� :弛 (     -      -      )                    弛            ");
	printf("                 戌式式式式式式式式式式式式式式式式式式式式式戎            ");
	lineClear();
	lineClear();
	textColor(14);
	printf("              忙式式式式式式式< 殮溘衛 輿曖 餌о >式式式式式式式忖         ");
	printf("              弛                                                弛         ");
	printf("              弛  "); textColor(15);
	printf("1. з廓: 濠翕戲煎 儅撩"); textColor(14);
	printf("                        弛         ");
	printf("              弛  "); textColor(15);
	printf("2. 檜葷: 嗥橫噙晦 橈檜 4濠檜頂 и旋虜 殮溘"); textColor(14);
	printf("    弛         ");
	printf("              弛  "); textColor(15);
	printf("3. 輿模: 嗥橫噙晦 んл 20濠 檜頂 殮溘"); textColor(14);
	printf("         弛         ");
	printf("              弛  "); textColor(15);
	printf("4. 瞪�食醽�: 11濠葬 檜頂 璋濠 殮溘"); textColor(14);
	printf("            弛         ");
	printf("              弛  "); textColor(12);
	printf("5. Щ煎斜極 謙猿 瞪 TXTだ橾 盪濰 в蹂"); textColor(14);
	printf("         弛         ");
	printf("              戌式式式式式式式式式式式式式式式式式式式式式式式式戎         ");
	textColor(7);
}