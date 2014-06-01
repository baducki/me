// 회원관리 프로그램 헤더파일

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// 회원관리 프로그램 구조체

typedef struct Member {
	int studentnum;
	char IDNum[7]; 
	char Name[10];
	char Address[30];
	char Cellphone[15];
	struct Member *prev;    // Linked List 앞 포인터
	struct Member *next;    // Linked List 뒤 포인터
} Member_t;

// List 구조체 (마지막 회원 정보 주소를 지정)

typedef struct list{
	Member_t *last;
} List_t;


// 회원관리 프로그램 Define

#define NUM_OF_MEMBERS 100
#define NUM_OF_PRINT   20
#define TIME_OF_DELAY  77

// 회원관리 프로그램 함수

// Main에 포함된 함수
int mainMenu(int* error);               // 메인메뉴 기능 (입력값: 에러값, 출력값: 유저 메뉴선택값)
void printMainMenu(void);               // 메인메뉴 출력
int inputMenu(void);                    // 메뉴 선택값 입력
int errorCheck(int check);              // 메뉴선택 시 에러 체크

// 1. 회원 보기 함수
void PrintInfo(Member_t*, int);          // 구조체에 있는 회원정보를 출력
void printfAllNodes(Member_t *head);     // Linked List를 이용해서 회원정보 출력
int InputInfo(FILE*, Member_t*);         // data.txt 파일을 구조체에 저장

// 2. 회원 등록 함수
void case2(FILE *fp, Member_t *id);      // 2. 회원 등록 실행
void JoinMember(FILE *fp, Member_t *id);
int Valid_IDNum(char *data);
int Valid_Name(char *data);
int Valid_cellphone(char *data);
int findMaxStudentNum(Member_t *id);     // 가장 큰 학번 검색

// 7. 종료 함수
int saveCheck(void);                     // 종료 전 파일 저장 유무를 질문 (반환값: 입력여부)
int checkSaveValue(int key);             // 파일 저장 유무 시 유저가 입력한 값을 검증
void programClose(void);                 // 프로그램 종료 안내 메세지 출력

// 기능 함수
void gotoxy(int x, int y);               // 입력 커서 위치 조정
int pauseWithLeftRight(void);            // 이젠 페이지, 다음 페이지 화면 출력
void pauseWithRight(void);               // 다음 페이지 화면 출력 (이전 페이지 없음)
int pauseWithLeft(void);                 // 이전 페이지 화면 출력 (다음 페이지 없음)
void choiceButton(int num);              // 메인 메뉴에서 기능 선택시 버튼 On
void previousPageButton(void);           // 이전 페이지 버튼 On
void nextPageButton(void);               // 다음 페이지 버튼 On
void homePageButton(void);               // 다음 페이지 버튼 On
