// 회원관리 프로그램 헤더파일

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

// 회원관리 프로그램 구조체

typedef struct Member {
	int Studentnum;
	char IDNum[7]; 
	char Name[9];
	char Address[41];
	char Cellphone[15];
	struct Member *prev;    // Linked List 앞 포인터
	struct Member *next;    // Linked List 뒤 포인터
} Member_t;

// 회원관리 프로그램 Define

#define NUM_OF_MEMBERS 200
#define NUM_OF_PRINT   20
#define TIME_OF_DELAY  77

// 회원관리 프로그램 함수

// Main에 포함된 함수
int InputInfo(FILE*, Member_t*);        // data.txt 파일을 구조체에 저장
int mainMenu(int* error);               // 메인메뉴 기능 (입력값: 에러값, 출력값: 유저 메뉴선택값)
void printMainMenu(void);               // 메인메뉴 출력
int inputMenu(void);                    // 메뉴 선택값 입력
int errorCheck(int check);              // 메뉴선택 시 에러 체크

// 1. 회원 보기 함수
void headOfCase1(void);                  // 회원 보기 헤드양식 출력
void PrintInfo(Member_t*, int);          // 구조체에 있는 회원정보를 출력

// 2. 회원 등록 함수
void headOfCase2(void);                                      // 회원 등록 헤드양식 출력
void case2(FILE *fp, Member_t *id, int maxnum);              // 2. 회원 등록 실행 (회원이 등록되면 maxnum +1)
int findMaxStudentNum(Member_t *id, int maxnum);             // 현재 저장된 학생들 중 가장 큰 학번 검색
void inputNewMember(FILE *fp, Member_t *id, int maxnum);     // 새로운 회원 정보를 입력
int validName(char *str);                                    // 입력된 이름 valid 유무 확인
void validNameErrorOn(void);                                 // 잘못된 이름 입력시 에러 메세지 On
void validNameErrorOff(void);                                // 잘못된 이름 입력시 에러 메세지 Off
int validAddress(char *str);                                 // 입력된 주소 valid 유무 확인
void validAddressErrorOn(void);                              // 잘못된 주소 입력시 에러 메세지 On
void validAddressErrorOff(void);                             // 잘못된 주소 입력시 에러 메세지 Off
int validCellphone(char a);                                  // 입력된 전화번호 valid 유무 확인
void validCellphoneErrorOn(void);                            // 잘못된 전화번호 입력시 에러 메세지 On
void validCellphoneErrorOff(void);                           // 잘못된 전화번호 입력시 에러 메세지 Off
int repeatCellphone(Member_t *id, char *str, int maxnum);    // 입력된 전화번호 중복 여부 확인
void repeatCellphoneErrorOn(void);                           // 잘못된 전화번호 입력시 에러 메세지 On
void repeatCellphoneErrorOff(void);                          // 잘못된 전화번호 입력시 에러 메세지 Off
void closeCase2(void);                                       // 회원 등록 종료 화면 출력

// 6. 저장 함수 
void SaveFile(FILE *fp, Member_t *id, int maxnum);           // 메모리에 저장되어 있는 내용을 파일로 저장

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
void printfAllNodes(Member_t *head);     // Linked List를 이용해서 회원정보 출력
