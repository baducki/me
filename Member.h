// ȸ������ ���α׷� �������

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#pragma warning (disable:4996)

// ȸ������ ���α׷� Define

#define NUM_OF_MEMBERS      200
#define NUM_OF_PRINT         20
#define TIME_OF_DELAY        77
#define NAME_MAXCHAR          9
#define ADDRESS_MAXCHAR      41
#define CELLPHONE_MAXCHAR    15

// ȸ������ ���α׷� ����ü

typedef struct Member {
	int Studentnum;      // int�� �й�
	char IDNum[7];       // char�� �й�(���Ͽ��� �о�� �� ���)
	char Name[NAME_MAXCHAR];
	char Address[ADDRESS_MAXCHAR];
	char Cellphone[CELLPHONE_MAXCHAR];
	struct Member *prev;    // Linked List �� ������
	struct Member *next;    // Linked List �� ������
} Member_t;

/*** ȸ������ ���α׷� �Լ� ***/

// Main�� ���Ե� �Լ�
int inputInfo(FILE*, Member_t*);        // data.txt ������ ����ü�� ����
int mainMenu(int* error);               // ���θ޴� ��� (�Է°�: ������, ��°�: ���� �޴����ð�)
void printMainMenu(void);               // ���θ޴� ���
int inputMenu(void);                    // �޴� ���ð� �Է�
int errorCheck(int check);              // �޴����� �� ���� üũ

// 1. ȸ�� ���� �Լ�
void headOfCase1(void);                  // ȸ�� ���� ����� ���
void printInfo(Member_t*, int);          // ����ü�� �ִ� ȸ�������� ���

// 2. ȸ�� ��� �Լ�
void headOfCase2(void);                                      // ȸ�� ��� ����� ���
int case2(FILE *fp, Member_t *id, int maxnum);               // 2. ȸ�� ��� ���� (ȸ���� ��ϵǸ� maxnum +1)
int findMaxStudentNum(Member_t *id, int maxnum);             // ���� ����� �л��� �� ���� ū �й� �˻�
int inputNewMember(FILE *fp, Member_t *id, int maxnum);      // ���ο� ȸ�� ������ �Է� (Maxnum ���� ���� ��ȯ)
int validName(char *str);                                    // �Էµ� �̸� valid ���� Ȯ��
void validNameErrorOn(void);                                 // �߸��� �̸� �Է½� ���� �޼��� On
void validNameErrorOff(void);                                // �߸��� �̸� �Է½� ���� �޼��� Off
int validAddress(char *str);                                 // �Էµ� �ּ� valid ���� Ȯ��
void validAddressErrorOn(void);                              // �߸��� �ּ� �Է½� ���� �޼��� On
void validAddressErrorOff(void);                             // �߸��� �ּ� �Է½� ���� �޼��� Off
int validCellphone(char a);                                  // �Էµ� ��ȭ��ȣ valid ���� Ȯ��
void validCellphoneErrorOn(void);                            // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
void validCellphoneErrorOff(void);                           // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
int repeatCellphone(Member_t *id, char *str, int maxnum);    // �Էµ� ��ȭ��ȣ �ߺ� ���� Ȯ��
void repeatCellphoneErrorOn(void);                           // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
void repeatCellphoneErrorOff(void);                          // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
void closeCase2(void);                                       // ȸ�� ��� ���� ȭ�� ���
int inputMemberSave(void);                                   // �Է��� ȸ���� ���� ���� ���� Ȯ��

// 6. ���� �Լ� 
void SaveFile(FILE *fp, Member_t *id, int maxnum);           // �޸𸮿� ����Ǿ� �ִ� ������ ���Ϸ� ����

// 7. ���� �Լ�
int saveCheck(void);                     // ���� �� ���� ���� ������ ���� (��ȯ��: �Է¿���)
int checkSaveValue(int key);             // ���� ���� ���� �� ������ �Է��� ���� ����
void programClose(void);                 // ���α׷� ���� �ȳ� �޼��� ���

// ��� �Լ�
void gotoxy(int x, int y);               // �Է� Ŀ�� ��ġ ����
int pauseWithLeftRight(void);            // ���� ������, ���� ������ ȭ�� ���
void pauseWithRight(void);               // ���� ������ ȭ�� ��� (���� ������ ����)
int pauseWithLeft(void);                 // ���� ������ ȭ�� ��� (���� ������ ����)
void choiceButton(int num);              // ���� �޴����� ��� ���ý� ��ư On
void previousPageButton(void);           // ���� ������ ��ư On
void nextPageButton(void);               // ���� ������ ��ư On
void homePageButton(void);               // ���� ������ ��ư On
void printfAllNodes(Member_t *head);     // Linked List�� �̿��ؼ� ȸ������ ���