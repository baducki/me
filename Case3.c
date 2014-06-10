#include "common.h"

void deleteMemberInfo(Member_t *id)
{
	int choice = 0;	                    // 검색옵션 선택 변수
	int studentid, i;                   // 검색에서 입력한 studentid를 받는 변수, 검색에서 받는 배열의 순서 변수 i
	char name[NAME_MAXCHAR];            // 검색에서 입력한 name을 받는 변수
	char cellphone[CELLPHONE_MAXCHAR];  // 검색에서 입력한 cellphone을 받는 변수
	while (choice != -1){
		case3DeleteSearchOptionUI();
		gotoxy(20, 12); choice = getche();
		if (choice < 49 || choice > 52)
			errorSearchChoice();
		else {
			switch (choice)
			{
			case '1':
				textColor(16 * 10);	gotoxy(7, 5);  printf("1. 학번    "); textColor(7);
				studentid = searchStudentID();
				if (studentid != -1){
					i = searchInfoIDnum(id, studentid);
					choice = deleteInfo(id, i);
				}
				break;
			case '2':
				textColor(16 * 10);	gotoxy(7, 6);  printf("2. 이름    "); textColor(7);
				studentid = searchName(name);
				if (studentid != -1){
					i = searchInfoName(id, name);
					choice = deleteInfo(id, i);
				}
				break;
			case '3':
				textColor(16 * 10);	gotoxy(7, 7);  printf("3. 전화번호"); textColor(7);
				studentid = searchCellphone(cellphone);
				if (studentid == -2) studentid = -1;
				if (studentid != -1){
					i = searchInfoCellphone(id, cellphone);
					choice = deleteInfo(id, i);
				}
				break;
			case '4':
				textColor(16 * 10);	gotoxy(7, 8);  printf("4. 취소    "); textColor(7);
				searchCancel();
				choice = -1;
				break;
			}
		}
	}
}

int deleteInfo(Member_t *id, int i)
{
	int choice;
	textColor(16 * 14);
	gotoxy(0, 26); printf("        위 회원정보를 삭제하시겠습니까? (Y/N) 【 】     메인 페이지 [↑]   ");
	textColor(7);
	while (1){
		gotoxy(48, 26); textColor(16 * 14); printf(" "); textColor(7);
		gotoxy(48, 26); choice = getche();
		if (choice == 224){
			choice = getch();
			if (choice == 72){
				homePageButton();
				return -1;
			}
		}
		else if (choice == 89 || choice == 121) {
			deleteLinkedList(id, i);
			cursorOff();
			textColor(16 * 10);
			gotoxy(0, 26); printf("           < 회원 정보가 삭제되었습니다 >   아무 키나 누르세요             ");
			textColor(7);
			getch();
			cursorOn();
			return -1;
		}
		else if (choice == 78 || choice == 110){
			cursorOff();
			textColor(16 * 10);
			gotoxy(0, 26); printf("        < 회원 정보 삭제가 취소되었습니다 >    아무 키나 누르세요           ");
			textColor(7);
			getch();
			cursorOn();
			return -1;
		}
		else {
			textColor(12 * 16);
			gotoxy(0, 28); printf("                  Warning: Y(예) 혹은 N(아니요) 키를 입력하세요            ");
			textColor(7);
		}
	}
	return 0;
}

void deleteLinkedList(Member_t *id, int i)
{
	Member_t *temp = (Member_t*)malloc(sizeof(Member_t));

	temp->prev = id[i].prev;
	temp->next = id[i].next;
	
	if (id[i].next != NULL){
		id[i].prev->next = temp->next;
		id[i].next->prev = temp->prev;
	}
	else id[i].prev->next = NULL;

	id[i].Address[0] = '\0';
	id[i].Cellphone[0] = '\0';
	id[i].Name[0] = '\0';
	id[i].Studentnum = 0;

	free(temp);
}

void case3DeleteSearchOptionUI(void)  // 회원정보 수정 중 검색 옵션 UI
{
	system("cls");
	textColor(16 * 14);
	gotoxy(0, 0); printf("                             < 회원 정보 삭제 >                            ");
	textColor(7);
	gotoxy(3, 3);  printf("┌ < 회원  검색 > ┐");
	gotoxy(3, 4);  printf("│                │");
	gotoxy(3, 5);  printf("│                │");
	gotoxy(3, 6);  printf("│                │");
	gotoxy(3, 7);  printf("│                │");
	gotoxy(3, 8);  printf("│                │");
	gotoxy(3, 9);  printf("│                │");
	gotoxy(3, 10); printf("└────────┘");
	textColor(15);
	gotoxy(7, 5);  printf("1. 학번");
	gotoxy(7, 6);  printf("2. 이름");
	gotoxy(7, 7);  printf("3. 전화번호");
	gotoxy(7, 8);  printf("4. 취소");
	textColor(7);
	gotoxy(4, 12); printf("검색 옵션 선택【 】");
}