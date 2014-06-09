#include "common.h"

// 7. ���� �Լ�
int saveCheck(void)   // ���� �� ���� ���� ������ ���� (��ȯ��: �Է¿���)
{
	int inputkey, errorcheck = 0;
	while (1){
		if (errorcheck != -1){
			textColor(16 * 10);
			gotoxy(0, 24); printf("                  ������ ������ �����Ͻðڽ��ϱ�? (Y/N)�� ��               ");
			textColor(7);
			gotoxy(57, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
		else if (errorcheck == -1){
			textColor(16 * 10);
			gotoxy(0, 24); printf("                  ������ ������ �����Ͻðڽ��ϱ�? (Y/N)�� ��               ");
			textColor(12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(��) Ȥ�� N(�ƴϿ�) Ű�� �Է��ϼ���            ");
			textColor(7);
			gotoxy(57, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
	}

	return errorcheck;
}
int checkSaveValue(int key)   // ���� ���� ���� �� ������ �Է��� ���� ����
{
	if (key == 89 || key == 121) return 1;
	else if (key == 78 || key == 110) return 2;
	else						 return -1;
}

void programCloseUI(void)   // ���α׷� ���� UI
{
	cursorOff();
	system("cls");
	textColor(16 * 14);
	printf("                             < ���α׷� ���� >                             "); Sleep(TIME_OF_DELAY);
	textColor(15);
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
	textColor(7);
	gotoxy(4, 25); printf(" made by YG & Kyung");
	textColor(14);
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
	textColor(12);
	printf("��"); Sleep(TIME_OF_DELAY * 3);
	textColor(15);
	gotoxy(31, 18);
	printf("*.");
	textColor(12);
	gotoxy(25, 18);
	printf("\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b��"); Sleep(TIME_OF_DELAY);
	textColor(7);
	gotoxy(4, 28);
}