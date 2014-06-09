// 프로그래밍 연습 기말과제 3주차 - 1분반 윤영기(141057), 송경(141044)
// *** 현재는 1. 회원보기 2. 회원등록 3. 회원수정 4. 회원삭제 6. 저장하기 7. 종료하기를 구현하였습니다 ***

#include "common.h"

// Main에 포함된 함수
int inputInfo(FILE *fp, Member_t *id)   // data.txt 파일을 구조체에 저장
{
	char idnum[11];
	if ((fp = fopen("data.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file <%s>", "data.txt");
		return -1;
	}
	int j, i = 0, maxnum = 0;
	while (1){
		fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\n]\n", idnum, id[i].Name, id[i].Address, id[i].Cellphone);
		id[i].Studentnum = atoi(idnum);
		i++, maxnum++;
		if (feof(fp)) break;
	}
	id[maxnum + 1].Studentnum = 0;
	j = i; i = 0;
	while (i<j){
		id[i].prev = &id[i - 1];
		id[i].next = &id[i + 1];
		i++;
	}
	id[i - 1].next = NULL;
	fclose(fp);
	return maxnum;
}
int mainMenu(int *error)  // 메인메뉴 기능 (입력값: 에러값, 출력값: 유저 메뉴선택값)
{
	int choice;
	if (*error == 0){
		mainmenuUI();                // 메인 페이지 출력
		choice = inputMenu();        // 메뉴 입력 받기
		*error = errorCheck(choice);
	}

	else if (*error == -1){          // 에러입력 시 에러메세지 출력, 에러해제 시 에러메세지 삭제
		mainmenuUI();                // 메인 페이지 출력
		textColor(12 * 16);
		gotoxy(0, 28); printf("                  Warning: 1 ~ 7번 사이의 숫자를 입력하세요                ");
		textColor(7);
		choice = inputMenu();        //  메뉴 입력 받기
		gotoxy(0, 28); lineClear();
		*error = errorCheck(choice);
	}

	else if (*error == -2){
		mainmenuUI();               // 메인 페이지 출력
		textColor(12 * 16);
		gotoxy(0, 28); printf("                  Warning: 5번 MENU는 아직 작업 중입니다                   ");
		textColor(7);
		choice = inputMenu();     //  메뉴 입력 받기
		gotoxy(0, 28); lineClear();
		*error = errorCheck(choice);
	}
	return choice;
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
	else if (check == 53) return -2;
	return 0;
}