#include "common.h"

int main(void)
{
	system("mode con lines=30 cols=75");  // 윈도우 창 화면 크기를 고정
	FILE *fp = NULL;
	Member_t id[NUM_OF_MEMBERS];

	unsigned int maxnum = inputInfo(fp, id); // maxnum는 현재 등록된 전체 회원 수
	                                         // InputInfo : data.txt파일을 열고 구조체에 저장
	unsigned int saveneed = 0;               // saveneed는 세이브 필요 유무를 체크하는 변수
	int menu_choice = 0;                     // menu_choice는 유저가 선택하는 메뉴값 변수
	int error = 0;                           // menu 선택 시 error 발생에 따른 error 메세지 출력을 위한 변수

	while (menu_choice != -1)                // -1 (종료) 일 때 프로그램 종료
	{
		menu_choice = mainMenu(&error);

		switch (menu_choice)
		{
		case '1': //회원정보보기    검색키 추가, 빠져나오기 추가 필요
			choiceButton(menu_choice);      // 메뉴 버튼 입력 시 클릭 효과
			printInfo(id, maxnum);          // 구조체에 저장된 회원정보를 화면에 출력
			break;

		case '2': // 회원등록       주소 error 추가 필요
			choiceButton(menu_choice);
			case2(fp, id, &maxnum); // 회원 입력 후 maxnum +1
			saveneed++;
			break;

		case '3': // 회원삭제
			choiceButton(menu_choice);
			saveneed++;
			break;

		case '4': // 정보수정
			choiceButton(menu_choice);
			adjustMemberInfo(id);
			saveneed++;
			break;

		case '5': // 검색하기
			choiceButton(menu_choice);
			break;

		case '6': // 저장하기  수정된 사항이 없을 때 저장버튼 누르면 Error 메세지 뜨기 필요
			choiceButton(menu_choice);
			menu_choice = saveCheck();
			if (menu_choice == 1)
			{
				saveFile(fp, id, maxnum);
				saveneed = 0;
			}
			break;

		case '7': // 종료
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

void mainmenuUI(void)  // 메인메뉴 UI 출력
{
	system("cls");
	gotoxy(0, 1);
	printf("                         ┌──────────┐\n");
	printf("                         │ 회원 관리 프로그램 │\n");
	printf("                         └──────────┘ \n");
	textColor(8);
	printf("                              made by YG & Kyung\n\n");
	textColor(7);
	printf("                      ┌─── < 주요기능 > ───┐\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      │                          │\n");
	printf("                      └─────────────┘\n");
	textColor(15);
	gotoxy(30, 8);  printf("①  회원 보기");
	gotoxy(30, 10); printf("②  회원 등록");
	gotoxy(30, 12); printf("③  회원 삭제");
	gotoxy(30, 14); printf("④  회원 수정");
	gotoxy(30, 16); printf("⑤  회원 검색");
	gotoxy(30, 18); printf("⑥  파일 저장");
	gotoxy(30, 20); printf("⑦  종 료");
	textColor(16 * 14);
	gotoxy(0, 26); printf("\t\t     원하는 기능의 번호를 입력하세요【 】                  ");
	textColor(7);
}