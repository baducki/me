#include "common.h"

// 1. 회원 보기 함수
void headOfCase1(void)   // 회원 보기 헤드양식 출력
{
	system("cls"); textColor(16 * 14);
	cursorOff();
	printf("                             < 회원  List >                                ");
	textColor(7);
	printf("\n  No  ID_NUM    NAME                ADDRESS                 CELL PHONE\n");
	printf("  ─  ───  ────  ────────────────  ───────");
}
void printInfo(Member_t *id, int maxnum)   // 구조체에 있는 회원정보를 출력
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
			textColor(16 * 10);
			gotoxy(0, 24); printf("                       모든 회원 정보를 출력하였습니다                     ");
			textColor(7);
			check = pauseWithLeft();
			if (check == 75){
				i = temp; j = 0;
				pre--;
				previousPageButton();
				headOfCase1();
			}
			else if (check == 72) break; // 방항키 ↑를 누르면 메인 페이지로 복귀
		}
	}
	cursorOn();
}


int pauseWithLeft(void)  // 화면을 멈추고 다음화면에 계속 출력
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]     (원하시는 키를 입력하세요)      메인 페이지 [↑]    ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75){
				previousPageButton(); break;
			}
			else if (choice == 72){
				homePageButton(); break;
			}
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                   Warning: ← 혹은 ↑키를 입력하세요                      ");
		textColor(7);
	}
	return choice;
}

void pauseWithRight(void)  // 화면을 멈추고 다음화면에 계속 출력
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("                       (원하시는 키를 입력하세요)        다음 페이지 [→]  ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 77) break;
		}
		textColor(12 * 16);
		gotoxy(0, 28); printf("                    Warning: → 방향키를 입력하세요                        ");
		textColor(7);
	}
	nextPageButton();
}

int pauseWithLeftRight(void)    // 화면을 멈추고 다음화면에 계속, 이전화면으로 출력
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]     (원하시는 키를 입력하세요)      다음 페이지 [→]    ");
	textColor(7);
	while (1){
		gotoxy(37, 26); choice = getch();
		if (choice == 224){
			choice = getch();
			if (choice == 75) break;
			else if (choice == 77) break;
		}
		else{
			textColor(12 * 16);
			gotoxy(0, 28); printf("                    Warning: ← 혹은 → 방향키를 입력하세요                ");
			textColor(7);
		}
	}
	return choice;
}

void choiceButton(int num)   // 메인 메뉴에서 기능 선택시 버튼 On
{
	switch (num)
	{
	case '1':
		textColor(16 * 10);
		gotoxy(30, 8); printf("①  회원 보기"); Sleep(77);
		textColor(7);
		break;
	case '2':
		textColor(16 * 10);
		gotoxy(30, 10); printf("②  회원 등록"); Sleep(77);
		textColor(7);
		break;
	case '3':
		textColor(16 * 10);
		gotoxy(30, 12); printf("③  회원 삭제"); Sleep(77);
		textColor(7);
		break;
	case '4':
		textColor(16 * 10);
		gotoxy(30, 14); printf("④  회원 수정"); Sleep(77);
		textColor(7);
		break;
	case '5':
		textColor(16 * 10);
		gotoxy(30, 16); printf("⑤  회원 검색"); Sleep(77);
		textColor(7);
		break;
	case '6':
		textColor(16 * 10);
		gotoxy(30, 18); printf("⑥  파일 저장"); Sleep(77);
		textColor(7);
		break;
	case '7':
		textColor(16 * 10);
		gotoxy(30, 20); printf("⑦  종 료    "); Sleep(77);
		textColor(7);
		break;
	}
}

void previousPageButton(void)   // 이전 페이지 버튼 On
{
	textColor(16 * 10 + 14);
	gotoxy(0, 26); printf("  이전 페이지 [←]  "); Sleep(77);
	textColor(7);
}

void nextPageButton(void)   // 다음 페이지 버튼 On
{
	textColor(16 * 10 + 14);
	gotoxy(55, 26); printf("  다음 페이지 [→]  "); Sleep(77);
	textColor(7);
}

void homePageButton(void)   // 다음 페이지 버튼 On
{
	textColor(16 * 10 + 14);
	gotoxy(55, 26); printf("  메인 페이지 [↑]  "); Sleep(77);
	textColor(7);
}