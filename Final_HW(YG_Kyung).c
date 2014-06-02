// 프로그래밍 연습 기말과제 1주차 (회원정보 보기) - 1분반 윤영기(141057), 송경(141044)
// *** 현재는 1. 회원보기 2. 회원등록 3. 저장하기 7. 종료하기를 구현하였습니다 ***

#include "Member.h"

int main(void)
{
	int maxnum;                             // maxnum 변수는 현재 등록된 전체 회원 수를 저장
	system("mode con lines=30 cols=75");    // 윈도우 창 화면 크기를 고정
	FILE *fp = NULL;
	Member_t id[NUM_OF_MEMBERS];

	maxnum = InputInfo(fp, id);             // 프로그램 실행 후 data.txt파일을 열고 구조체에 저장
	int menu_choice = 0;                    // 변수 menu_choice는 유저가 선택하는 메뉴값
	int error = 0; int *perror = &error;    // 메인메뉴 에러 종류를 파악하기 위한 변수 (포인터도 함께 선언)

	while (menu_choice != '8')              // 변수 7(아스키코드 55) 일 때 프로그램 종료 + 아름다운 종료 그림
	{
		menu_choice = mainMenu(perror);

		switch (menu_choice)
		{
		case '1': //회원정보보기
			choiceButton(menu_choice);      // 메뉴 버튼 입력 시 클릭 효과
			PrintInfo(id, maxnum);          // 구조체에 저장된 회원정보를 화면에 출력
			break;

		case '2': // 회원등록
			choiceButton(menu_choice);
			case2(fp, id, maxnum); maxnum++; // 회원 입력 후 maxnum +1
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

// Main에 포함된 함수
int InputInfo(FILE *fp, Member_t *id)   // data.txt 파일을 구조체에 저장
{
	if ((fp = fopen("data.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file %s.", "data.txt");
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
int mainMenu(int* error)  // 메인메뉴 기능 (입력값: 에러값, 출력값: 유저 메뉴선택값)
{
	int choice;
	if (*error == 0){
		printMainMenu();               // 메인 페이지 출력
		choice = inputMenu();          // 메뉴 입력 받기
		*error = errorCheck(choice);
	}

	else if (*error == -1){            // 에러입력 시 에러메세지 출력, 에러해제 시 에러메세지 삭제
		printMainMenu();               // 메인 페이지 출력
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 1 ~ 7번 사이의 숫자를 입력하세요                ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();          //  메뉴 입력 받기
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}

	else if (*error == -2){
		printMainMenu();               // 메인 페이지 출력
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
		gotoxy(0, 28); printf("                  Warning: 3 ~ 5번 MENU는 아직 작업 중입니다               ");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		choice = inputMenu();     //  메뉴 입력 받기
		gotoxy(0, 28); printf("                                                                           ");
		*error = errorCheck(choice);
	}
	return choice;
}
void printMainMenu(void)  // 메인메뉴 출력
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	gotoxy(0, 26); printf("\t\t     원하는 기능의 번호를 입력하세요【 】                  ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
int inputMenu(void)   // 메뉴 선택값 입력
{
	int choice;
	gotoxy(54, 26);
	choice = getche();
	return choice;
}
int errorCheck(int check)   // 메뉴선택 시 에러 체크
{
	if (check < 49 || check > 55) return -1;
	else if (check > 50 && check < 54) return -2;
	return 0;
}

// 1. 회원 보기 함수
void headOfCase1(void)   // 회원 보기 헤드양식 출력
{
	system("cls"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                             < 회원  List >                                ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n  No  ID_NUM    NAME \t            ADDRESS \t\t    CELL PHONE\n");
	printf("  ─  ───  ────  ────────────────  ───────");
}
void PrintInfo(Member_t *id, int maxnum)   // 구조체에 있는 회원정보를 출력
{
	int i, j, check, temp, pre = 0;   // 변수: i는 for문을 위한 변수, j는 위치 지정을 위한 변수, check는 입력키 체크
	// temp는 이전 페이지로 돌아가기 위한 변수, pre는 이전, 다음 페이지 출력 확인을 위한 변수
	headOfCase1();
	for (i = 1, j = 1; i < maxnum; i++, j++){
		if (j>NUM_OF_PRINT) j -= NUM_OF_PRINT;  // gotoxy로 위치 지정 출력하기 위해 j 변수 선언 후 j로 출력 열 위치 조정
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
			gotoxy(0, 24); printf("                       모든 회원 정보를 출력하였습니다                     ");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp; j = 0;
				pre--;
				previousPageButton();
				headOfCase1();
			}
			else if (check == 72 || check == 104) break; // H키를 누르면 메인 페이지로 복귀
		}
	}
}

// 2. 회원 등록 함수
void headOfCase2(void)
{
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 14);
	printf("                                < 회원 등록 >                              ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n                 ┌─────────────────────┐            ");
	gotoxy(11, 4); printf("학번 : ");
	gotoxy(17, 4); printf("│"); gotoxy(61, 4); printf("│");
	printf("\n                 └─────────────────────┘            ");
	printf("                 ┌─────────────────────┐            ");
	printf("   ①      이름 :│");
	gotoxy(61, 7); printf("│            ");
	printf("                 └─────────────────────┘            ");
	printf("                 ┌─────────────────────┐            ");
	printf("   ②      주소 :│");
	gotoxy(61, 10); printf("│            ");
	printf("                 └─────────────────────┘            ");
	printf("                 ┌─────────────────────┐            ");
	printf("   ③  전화번호 :│ (     -      -      )                    │            ");
	printf("                 └─────────────────────┘            ");
	printf("                                                                           ");
	printf("                                                                           ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("              ┌───────< 입력시 주의 사항 >───────┐         ");
	printf("              │                                                │         ");
	printf("              │  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("1. 학번: 자동으로 생성"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("                        │         ");
	printf("              │  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("2. 이름: 띄어쓰기 없이 4자이내 한글만 입력"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("    │         ");
	printf("              │  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("3. 주소: 띄어쓰기 포함 20자 이내 입력"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         │         ");
	printf("              │  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("4. 전화번호: 11자리 이내 숫자 입력"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("            │         ");
	printf("              │  "); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("5. 프로그램 종료 전 TXT파일 저장 필요"); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("         │         ");
	printf("              └────────────────────────┘         ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void case2(FILE *fp, Member_t *id, int maxnum)   // 2. 회원 등록 실행
{
	if ((fp = fopen("data.txt", "r")) == NULL)
		fprintf(stderr, "Error opening file %s.", "data.txt");
	system("cls");
	headOfCase2();
	inputNewMember(fp, id, maxnum);
	
	fp = fopen("data.txt", "a+");
	fprintf(fp, "\n%s\t%s\t%s\t%s", id[maxnum].IDNum, id[maxnum].Name, id[maxnum].Address, id[maxnum].Cellphone);
	fclose(fp);
}
int findMaxStudentNum(Member_t *id, int maxnum)   // 현재 저장된 학생들 중 가장 큰 학번 검색
{
	int i, maxstudentnum;
	for (i = 2; i <= maxnum; i++){
		if (id[i - 1].Studentnum < id[i].Studentnum)
			maxstudentnum = id[i].Studentnum;
	}
	return maxstudentnum;
}
void inputNewMember(FILE *fp, Member_t *id, int maxnum)   // 새로운 회원 정보를 입력
{
	int i, j, valid = -1, repeatcheck = -1;
	int maxstudentnum = findMaxStudentNum(id, maxnum); maxstudentnum++; // 학생 학번 중 가장 큰 학번을 찾은 후 +1

	id[maxnum].Studentnum = maxstudentnum;
	itoa(maxstudentnum, id[maxnum].IDNum, 10);

	gotoxy(20, 4); printf("%d", maxstudentnum);
	gotoxy(63, 4); printf("(자동생성)");
	
	while (valid)
	{
		gotoxy(20, 7);
		gets(id[maxnum].Name);
		valid = validName(id[maxnum].Name);
	}
	validNameErrorOff(); valid = -1;

	while (valid){
		gotoxy(20, 10);
		gets(id[maxnum].Address);
		valid = validAddress(id[maxnum].Address);
	}
	validAddressErrorOff(); valid = -1;

	while (repeatcheck){
		for (i = 0, j = 0; i < 13;){
			if (i == 3 || i == 8){
				id[maxnum].Cellphone[i] = '-'; i++; j += 2;
			}
			else {
				gotoxy(22 + i + j, 13);
				id[maxnum].Cellphone[i] = getche();
				if (id[maxnum].Cellphone[i] == 8 && i != 0){
					printf(" "); i--;
				}
				else {
					valid = validCellphone(id[maxnum].Cellphone[i]);
					if (valid == 0) i++;
					else validCellphoneErrorOn();
				}
			}
		}
		id[maxnum].Cellphone[i] = '\0';
		validCellphoneErrorOff(); valid = -1;
		repeatcheck = repeatCellphone(id, id[maxnum].Cellphone, maxnum);
		if (repeatcheck == -1) repeatCellphoneErrorOn();
	}
	repeatCellphoneErrorOff();
	closeCase2();
}
int validName(char *str)   // 이름에 한글 외 입력 금지
{
	int i = 0, len = strlen(str), check = 0;
	if (len == 0 || str[0] == ' ') {
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
void validNameErrorOn(void)   // 잘못된 이름 입력시 에러 메세지 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("       Warning: 이름은 띄어쓰기 없이 4자이내로 한글만 입력하세요           ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(19, 7); printf("                                         │");
	gotoxy(19, 10); printf("                                         │");
	gotoxy(19, 13); printf(" (     -      -      )                    │");
	headOfCase2();
}
void validNameErrorOff(void)   // 잘못된 이름 입력시 에러 메세지 Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 7); printf("(입력완료)");
}
int validAddress(char *str)   // 입력된 주소 valid 유무 확인
{
	int i = 0, len = strlen(str), check = 0;
	if (len > 40) {
		validAddressErrorOn(); check = -1;
	}
	return check;
}
void validAddressErrorOn(void)   // 잘못된 이름 입력시 에러 메세지 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("           Warning: 주소는 띄어쓰기 포함 20자이내로 입력하세요             ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(19, 10); printf("                                         │");
	gotoxy(19, 13); printf(" (     -      -      )                    │");
	headOfCase2();	gotoxy(63, 7); printf("(입력완료)");
}
void validAddressErrorOff(void)   // 잘못된 주소 입력시 에러 메세지 Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 10); printf("(입력완료)");
}
int validCellphone(char a)   // 이름에 한글 외 입력 금지
{
	int check = 0;
	if (a < 48 || a > 57){    // 숫자 아스키코드=48~57 외에 입력 시 Error
		check = -1;
		return check;
	}
	return check;
}
int repeatCellphone(Member_t *id, char *str, int maxnum)
{
	for (int i = 1; i < maxnum; i++){
		if (strcmp(id[i].Cellphone, id[maxnum].Cellphone) == 0)  // 전화 번호가 같다면 -1을 반환
			return -1;
	}
	return 0;
}
void validCellphoneErrorOn(void)   // 잘못된 전화번호 입력시 에러 메세지 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("               Warning: 전화번호는 11자 이내 숫자만 입력하세요             ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void validCellphoneErrorOff(void)   // 잘못된 주소 입력시 에러 메세지 Off
{
	gotoxy(0, 28); printf("                                                                           ");
}
void repeatCellphoneErrorOn(void)   // 잘못된 전화번호 입력시 에러 메세지 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12 * 16);
	gotoxy(0, 28); printf("         Warning: 기존 회원과 동일한 전화번호입니다! 다시 입력하세요       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void repeatCellphoneErrorOff(void)   // 잘못된 전화번호 입력시 에러 메세지 Off
{
	gotoxy(0, 28); printf("                                                                           ");
	gotoxy(63, 13); printf("(입력완료)");
}
void closeCase2(void)
{
	int inputkey;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10);
	gotoxy(0, 26); printf("                 < 회원 등록이 완료 되었습니다 >   아무키나 누르세요       ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	gotoxy(74, 26); inputkey = getche();
}

// 7. 종료 함수
int saveCheck(void)   // 종료 전 파일 저장 유무를 질문 (반환값: 입력여부)
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
int checkSaveValue(int key)   // 파일 저장 유무 시 유저가 입력한 값을 검증
{
	if (key == 89 || key == 121)
		return 56;
	if (key == 78 || key == 110)
		return 0;
	else
		return -1;
}
void programClose(void)   // 프로그램 종료 안내 메세지 출력
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
	gotoxy(25, 18);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	printf("♡"); Sleep(TIME_OF_DELAY*3);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	printf("\b\b\b♥"); Sleep(TIME_OF_DELAY);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); gotoxy(4, 28);
}

// 기능 함수
void gotoxy(int x, int y)   // 입력 커서 위치 조정
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
void choiceButton(int num)   // 메인 메뉴에서 기능 선택시 버튼 On
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
void previousPageButton(void)   // 이전 페이지 버튼 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void nextPageButton(void)   // 다음 페이지 버튼 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf("  다음 페이지 [→]  "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void homePageButton(void)   // 다음 페이지 버튼 On
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * 10 + 14);
	gotoxy(55, 26); printf(" 메인 페이지 [H] 키 "); Sleep(77);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void printfAllNodes(Member_t *head) // Linked List를 이용해서 회원정보 출력
{
	Member_t *curNode;
	curNode = head->next;
	while (curNode){
		printf(" %s ", curNode->Name);
		curNode = curNode->next;
	}
	printf("\n");
}
