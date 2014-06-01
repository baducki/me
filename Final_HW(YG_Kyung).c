// 프로그래밍 연습 기말과제 1주차 (회원정보 보기) - 1분반 윤영기(141057), 송경(141044)
// *** 현재는 1. 회원보기 2. 회원등록 3. 저장하기 7. 종료하기를 구현하였습니다 ***

#include "Member.h"

List_t last;                              // Linked List의 마지막 회원 정보 주소 입력을 위한 변수 선언
int maxnum;                               // 현재 등록된 전체 회원 수

int main(void)
{
	system("mode con lines=30 cols=75");   // 윈도우 창 화면 크기를 고정
	FILE *fp = NULL;
	Member_t id[NUM_OF_MEMBERS];

	maxnum = InputInfo(fp, id);            // 프로그램 실행 후 data.txt파일을 열고 구조체에 저장
	int menu_choice = 0;                   // 변수 menu_choice는 유저가 선택하는 메뉴값
	int error = 0; int *perror = &error;   // 메인메뉴 에러 종류를 파악하기 위한 변수 (포인터도 함께 선언)
	
	while (menu_choice != '8')              // 변수 7(아스키코드 55) 일 때 프로그램 종료 + 아름다운 종료 그림
	{
		menu_choice = mainMenu(perror);

		switch (menu_choice)
		{
		case '1': //회원정보보기
			choiceButton(menu_choice);
			PrintInfo(id, maxnum);          // 구조체에 저장된 회원정보를 화면에 출력
			break;

		case '2': // 회원등록
			choiceButton(menu_choice);
			case2(fp, id);
			break;

		case '3': // 회원삭제
			choiceButton(menu_choice);
			break;

		case '4': // 정보수정
			choiceButton(menu_choice);
			break;

		case '5': // 검색하기
			choiceButton(menu_choice);
			break;

		case '6': // 저장하기
			choiceButton(menu_choice);
			break;

		case '7': // 종료
			choiceButton(menu_choice);
			menu_choice = saveCheck();
			break;
		}
	}
	programClose();
	return 0;
}

int mainMenu(int* error)
{
	int choice;
	if (*error == 0){
		printMainMenu();               // 메인메뉴 출력
		choice = inputMenu();          //  메뉴 입력 받기
		*error = errorCheck(choice);
	}

	else if (*error == -1){            // 에러입력 시 에러메세지 출력, 에러해제 시 에러메세지 삭제
		printMainMenu();               // 메인메뉴 출력
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 1 ~ 7번 사이의 숫자를 입력하세요                ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();          //  메뉴 입력 받기
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}

	else if (*error == -2){
		printMainMenu();               // 메인메뉴 출력
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 3 ~ 5번 MENU는 아직 작업 중입니다               ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();     //  메뉴 입력 받기
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}
	return choice;
}

void case2(FILE *fp, Member_t *id)
{
	if ((fp = fopen("data.txt", "r")) == NULL)
		fprintf(stderr, "Error opening file %s.", "data.txt");

	int maxstudentnum, valid;

	system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < 회원  등록 >                                ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	maxstudentnum = findMaxStudentNum(id);
	maxstudentnum++;
	gotoxy(17, 7);
	printf("학번 : %d", maxstudentnum);
	id[maxnum+1].studentnum = maxstudentnum;
	itoa(maxstudentnum, id[maxnum+1].IDNum, 10);

	gotoxy(17, 8); printf("이름 입력 : ");
	scanf("%s", id[maxnum+1].Name); fflush(stdin);//이름은 확인하지 않음

	gotoxy(17, 9); printf("주소 입력 : ");
	gets(id[maxnum + 1].Address);
	fflush(stdin);
	while (1){
		gotoxy(17, 10); printf("전화번호 입력(010-0000-0000형태) : ");
		scanf("%s", id[maxnum + 1].Cellphone);
		valid = 0;                               //valid값 초기화
		printf("%s\n", id[maxnum + 1].Cellphone);
		valid = Valid_cellphone(id[maxnum + 1].Cellphone); //전화번호 예외처리

		if (valid != -1)
			break;
	}
	fp = fopen("data.txt", "a+");
	fprintf(fp, "%s\t%s\t%s\t%s\n", id[maxnum + 1].IDNum, id[maxnum + 1].Name, id[maxnum + 1].Address, id[maxnum + 1].Cellphone);
	fclose(fp);
	printf("회원이 등록됬습니다.\n");
	maxnum++;
}

void printMainMenu(void)
{
	system("cls");  // 전 화면 삭제
	printf("\n\t\t         ┌──────────┐ \n\t\t         │ 회원 관리 프로그램 │ \n");
	printf("\t\t         └──────────┘ \n\t\t\t      made by YG & Kyung\n\n");
	printf("\t\t      ┌─── < 주요기능 > ───┐\n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("①  회원 보기"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        │\n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("②  회원 등록"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        │ \n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("③  회원 삭제"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        │ \n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("④  회원 수정"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        │\n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("⑤  회원 검색"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("        │\n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("⑥  저 장"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("            │\n\t\t      │                          │\n");
	printf("\t\t      │     "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("⑦  종 료"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("            │\n\t\t      │                          │\n");
	printf("\t\t      └─────────────┘\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16*14);
	gotoxy(0, 26); printf("\t\t     원하는 기능의 번호를 입력하세요【 】                  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int inputMenu(void)
{
	int choice;
	gotoxy(54, 26);
	choice = getche();
	return choice;
}

int errorCheck(int check)
{
	if (check < 49 || check > 55) return -1;
	else if (check > 50 && check < 54) return -2;
	return 0;
}

int InputInfo(FILE *fp, Member_t *id)
{
	if ((fp = fopen("data.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file %s.", "data.txt");
		return -1;
	}
	int j, i = 0, maxnum = 0;
	while (1){
		fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", id[i].IDNum, id[i].Name, id[i].Address, id[i].Cellphone);
		id[i].studentnum = atoi(id[i].IDNum);
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
	id[i-1].next = NULL;
	last.last = &id[i - 1];
	return maxnum;
}

void PrintInfo(Member_t *id, int maxnum)
{
	int i, check, temp, pre = 0;
	system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < 회원  List >                                ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n   No  ID_NUM    NAME \t           ADDRESS \t\t   CELL PHONE\n");
	printf("   ─  ───   ─── \t   ────────────\t ─────── \n");
	for (i = 1; i < maxnum; i++){
		printf("  %3d  %s   %s\t    %s\t  %s\n", i, id[i].IDNum, id[i].Name, id[i].Address, id[i].Cellphone);
		if (i != (maxnum - 1)){
			if (i%NUM_OF_PRINT == 0 && pre == 0){
				pauseWithRight();
				temp = i - NUM_OF_PRINT;
				system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
				printf("                             < 회원  List >                                ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n   No  ID_NUM    NAME \t           ADDRESS \t\t   CELL PHONE\n");
				printf("   ─  ───   ─── \t   ────────────\t ─────── \n");
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
					nextPageButton(); pre++;
				}
				system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
				printf("                             < 회원  List >                                ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n   No  ID_NUM    NAME \t           ADDRESS \t\t   CELL PHONE\n");
				printf("   ─  ───   ─── \t   ────────────\t ─────── \n");
			}
		}
		else if (i == (maxnum-1)){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16*10);
			gotoxy(0, 24); printf("                       모든 회원 정보를 출력하였습니다                     ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp; pre--;
				previousPageButton();
				system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
				printf("                             < 회원  List >                                ");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				printf("\n   No  ID_NUM    NAME \t           ADDRESS \t\t   CELL PHONE\n");
				printf("   ─  ───   ─── \t   ────────────\t ─────── \n");
			}
			else if (check == 72 || check == 104) break;
		}
	}
	printf("\n");
}

void printfAllNodes(Member_t *head)
{
	Member_t *curNode;
	curNode = head->next;
	while (curNode){
		printf(" %s ", curNode->Name);
		curNode = curNode->next;
	}
	printf("\n");
}

int Valid_IDNum(char *data) //학번 확인
{
	if (strlen(data) != 6) //학번은 6자리
	{
		printf("다시 입력하세요\n");
		return -1;
	}

	for (int i = 0; i < (int)strlen(data); i++)
	{
		if (*data<48 || *data>57)
		{
			printf("다시 입력하세요\n");
			return -1;
		}
		data++;
	}
	return 0;
}

int Valid_Name(char *data) // 이름 확인
{
	for (int i = 0; i < (int)strlen(data); i++)
	{
		if (*data<44032 || *data>55203)//code >= 44032 && code <= 55203
		{
			printf("다시 입력하세요\n");
			return -1;
		}
		data++;
	}
	return 0;
}

int Valid_cellphone(char *data)//전화번호 확인
{
	if ((strlen(data) != 12 && strlen(data) != 13)) // 전화번호는 12~13자리 (-포함)
	{
		printf("다시 입력하세요\n");
		return -1;
	}
	for (int i = 0; i < (int)strlen(data); i++)
	{

		if ((*data<45) || ((45< *data) && (*data <48)) || (*data>57)) //숫자의 아스키코드=48~57 , -의 아스키코드=45
		{
			printf("다시 입력하세요\n");
			return -1;
		}
		data++;
	}
	return 0;
}

int saveCheck(void)
{
	int inputkey, errorcheck = 0;
	while (1){
		if (errorcheck != -1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
			gotoxy(0, 24); printf("               종료 전에 수정한 내용을 저장하셨습니까? (Y/N)【 】          ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(62, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
		else if (errorcheck == -1){
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
			gotoxy(0, 24); printf("               종료 전에 수정한 내용을 저장하셨습니까? (Y/N)【 】          ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(예) 혹은 N(아니요) 키를 입력하세요            ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			gotoxy(62, 24); inputkey = getche();
			errorcheck = checkSaveValue(inputkey);
			if (errorcheck != -1) break;
		}
	}

	return errorcheck;
}

int checkSaveValue(int key)
{
	if (key == 89 || key == 121)
		return 56;
	if (key == 78 || key == 110)
		return 0;
	else
		return -1;
}

void programClose(void)
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < 프로그램 종료 >                             "); Sleep(TIME_OF_DELAY);
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
	printf("                          *@*@@*.***...*                  ............   .\n"); Sleep(TIME_OF_DELAY);
	printf("                           .@@@*.*...                 ....   .......     .\n"); Sleep(TIME_OF_DELAY);
	printf("                            .@@*....               .....        .        .\n"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         G"); Sleep(TIME_OF_DELAY);
	printf("O"); Sleep(TIME_OF_DELAY); printf("O"); Sleep(TIME_OF_DELAY); printf("D "); Sleep(TIME_OF_DELAY);
	printf("B"); Sleep(TIME_OF_DELAY); printf("Y"); Sleep(TIME_OF_DELAY); printf("E"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("              *@..             ...........              .\n"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         S"); Sleep(TIME_OF_DELAY);
	printf("E"); Sleep(TIME_OF_DELAY); printf("E "); Sleep(TIME_OF_DELAY);
	printf("Y"); Sleep(TIME_OF_DELAY); printf("O"); Sleep(TIME_OF_DELAY); printf("U "); Sleep(TIME_OF_DELAY);
	printf("L"); Sleep(TIME_OF_DELAY); printf("A"); Sleep(TIME_OF_DELAY); printf("T"); Sleep(TIME_OF_DELAY); 
	printf("E"); Sleep(TIME_OF_DELAY); printf("R"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); printf("♥"); Sleep(TIME_OF_DELAY);
	printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY); printf("\b♥"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("\b.@*..     ...****..........  ..          .\n"); Sleep(TIME_OF_DELAY);
	printf("                                  ........   .@@****.........            .\n"); Sleep(TIME_OF_DELAY);
	printf("                                               *******...**              .\n"); Sleep(TIME_OF_DELAY);
	printf("         "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(" made by YG & Kyung"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("                    .*@@**@@@*           .  ..\n"); Sleep(TIME_OF_DELAY);
	printf("    ..........................................@@@@@@@@*             .   ..\n\n"); Sleep(TIME_OF_DELAY);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int pauseWithLeft(void)  // 화면을 멈추고 다음화면에 계속 출력
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]     (원하시는 키를 입력하세요)      메인 페이지 [H] 키  ");
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
		gotoxy(0, 28); printf("                   Warning: ← 혹은 H 키를 입력하세요                      ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	return choice;
}

void pauseWithRight(void)  // 화면을 멈추고 다음화면에 계속 출력
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("                       (원하시는 키를 입력하세요)      다음 페이지 [→]키  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 77) break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                    Warning: → 방향키를 입력하세요                        ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	nextPageButton();
}

int pauseWithLeftRight(void)    // 화면을 멈추고 다음화면에 계속, 이전화면으로 출력
{
	int choice;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]     (원하시는 키를 입력하세요)      다음 페이지 [→]키  ");
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
			gotoxy(0, 28); printf("                    Warning: ← 혹은 → 방향키를 입력하세요                ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
	}
	return choice;
}

void choiceButton(int num)
{
	switch (num)
	{
	case '1':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 8); printf("①  회원 보기"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '2':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 10); printf("②  회원 등록"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '3':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 12); printf("③  회원 삭제"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '4':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 14); printf("④  회원 수정"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '5':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 16); printf("⑤  회원 검색"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '6':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 18); printf("⑥  저 장"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case '7':
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
		gotoxy(29, 20); printf("⑦  종 료"); Sleep(77);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	}
}

void previousPageButton(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void nextPageButton(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf("  다음 페이지 [→]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void homePageButton(void)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf(" 메인 페이지 [H] 키 "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int findMaxStudentNum(Member_t *id)
{
	int i, maxstudentnum;
	for (i = 2; i <= maxnum; i++){
		if (id[i - 1].studentnum < id[i].studentnum)
			maxstudentnum = id[i].studentnum;
	}
	return maxstudentnum;
}
