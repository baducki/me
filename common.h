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
#define CURTAIN_DELAY        37
#define STUDENTID_MAXCHAR     7
#define NAME_MAXCHAR          9
#define ADDRESS_MAXCHAR      41
#define CELLPHONE_MAXCHAR    15

// ȸ������ ���α׷� ����ü

typedef struct Member {
	int Studentnum;         // �й�
	char IDNum[7];
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
int inputMenu(void);                    // �޴� ���ð� �Է�
int errorCheck(int check);              // �޴����� �� ���� üũ

// 1. ȸ�� ���� �Լ�
void headOfCase1(void);                  // ȸ�� ���� ����� ���
void printInfo(Member_t*, int);          // ����ü�� �ִ� ȸ�������� ���
int pauseWithLeftRight(void);            // ���� ������, ���� ������ ȭ�� ���
int pauseWithLeft(void);                 // ���� ������ ȭ�� ��� (���� ������ ����)
void pauseWithRight(void);               // ���� ������ ȭ�� ��� (���� ������ ����)
void choiceButton(int num);              // ���� �޴����� ��� ���ý� ��ư On
void previousPageButton(void);           // ���� ������ ��ư On
void nextPageButton(void);               // ���� ������ ��ư On
void homePageButton(void);               // ���� ������ ��ư On

// 2. ȸ�� ��� �Լ�
void case2(FILE *fp, Member_t *id, int *maxnum);             // 2. ȸ�� ��� ���� (ȸ���� ��ϵǸ� maxnum +1)
int findMaxStudentNum(Member_t *id, int maxnum);             // ���� ����� �л��� �� ���� ū �й� �˻�
void inputNewMember(FILE *fp, Member_t *id, int *maxnum);    // ���ο� ȸ�� ������ �Է� (Maxnum ���� ���� ��ȯ)
int validName(char *str, int key);                           // �Էµ� �̸� valid ���� Ȯ��
void validNameErrorOn(int key);                              // �߸��� �̸� �Է½� ���� �޼��� On
void validNameErrorOff(void);                                // �߸��� �̸� �Է½� ���� �޼��� Off
int validAddress(char *str, int menu);                       // �Էµ� �ּ� valid ���� Ȯ��
void validAddressErrorOn(int menu);                          // �߸��� �ּ� �Է½� ���� �޼��� On
void validAddressErrorOff(void);                             // �߸��� �ּ� �Է½� ���� �޼��� Off
int validCellphone(char a);                                  // �Էµ� ��ȭ��ȣ valid ���� Ȯ��
void validCellphoneErrorOn(void);                            // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
void validCellphoneErrorOff(void);                           // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
int repeatCellphone(Member_t *id, char *str, int maxnum);    // �Էµ� ��ȭ��ȣ �ߺ� ���� Ȯ��
void repeatCellphoneErrorOn(int menu);                       // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� On
void repeatCellphoneErrorOff(void);                          // �߸��� ��ȭ��ȣ �Է½� ���� �޼��� Off
void closeCase2(void);                                       // ȸ�� ��� ���� ȭ�� ���
int inputMemberSave(void);                                   // �Է��� ȸ���� ���� ���� ���� Ȯ��
void case2UI(void);                                          // ȸ����� UI

// 4. ȸ�� ���� ���� �Լ�
void adjustMemberInfo(Member_t *id);   // ȸ�� ���� ����
int searchStudentID(void);             // ȸ�� ���� �˻� �ɼ� �� �й� �˻�
int searchName(char *name);            // ȸ�� ���� �˻� �ɼ� �� �̸� �˻�
int searchCellphone(char *cellphone);  // ȸ�� ���� �˻� �ɼ� �� ��ȭ��ȣ �˻�
void errorSearchChoice(void);          // ȸ�� ���� �˻� �� �����޼���
void searchCancel(void);               // ȸ�� ���� �˻� ���
void validStudentID(char studentID, int *i, int line, int row, int menu);  // �й� valid Check
void validStudentIDError(int menu);                       // �й� valid Error On
int inputInfoYesOrNo(int i);                              // �Է����� ���� ���� Ȯ�� (�Է°� i: �˻� or ���� ���� ����)
int searchInfoIDnum(Member_t *id, int idnum);             // ȸ�� �й����� �˻� (�Է°�: idnum�� �й�)
int searchInfoName(Member_t *id, char *name);             // ȸ�� �̸����� �˻�
void case4PrintInfo(Member_t *id, int i);                 // �˻��� ȸ�� ���� ���
int adjustInfo(Member_t *id, int i);                      // ȸ�� ���� ����
int adjustInfoMenuChoice(void);                           // ȸ������ ���� �� �ɼ� ����
void adjustCell(int count);                               // ȸ������ ���� �� �Է�â ��� (�Է°�: ������ ���� ����)
int insertStudentNum(int line, int row, int menu);        // �й� �Է� �� Valid Check (�Է°�: �࿭�� �Է��Ͽ� ��ġ�� ������)
int insertName(int line, int row, char *name, int menu);  // �̸� �Է� �� Valid Check
void adjustInfoInputStudentID(Member_t *id, int INDnum, int i); // ������ �й� ������ ����
int repeatStudentIDCheck(Member_t *id, int IDnum);              // �й� �ߺ� Check
int printSameNameMember(Member_t *id, int *sameName, int j);    // ������ �̸��� ���� ȸ�� ���� ���
void adjustInfoInputName(Member_t *id, int i);                  // ������ �̸� ������ ����
int insertCellphone(int line, int row, char *name, int menu);   // ��ȭ��ȣ �Է� �� valid Check
int searchInfoCellphone(Member_t *id, char *cellphone);         // ��ȭ��ȣ�� �˻�
void adjustInfoInputAddress(Member_t *id, int i);               // ������ �ּ� ������ ����
void adjustInfoInputCellphone(Member_t *id, int i);             // ������ ��ȭ��ȣ ������ ����

// 6. ���� �Լ� 
void saveFile(FILE *fp, Member_t *id, int maxnum);  // �޸𸮿� ����Ǿ� �ִ� ������ ���Ϸ� ����
void fileSaveUI(void);                              // �������� UI

// 7. ���� �Լ�
int saveCheck(void);                     // ���� �� ���� ���� ������ ���� (��ȯ��: �Է¿���)
int checkSaveValue(int key);             // ���� ���� ���� �� ������ �Է��� ���� ����
void programCloseUI(void);               // ���α׷� ���� UI

// ����Լ� (consoleFuntion.c)
void gotoxy(int x, int y);               // �Է� Ŀ�� ��ġ ����
void cursorOn(void);                     // Ŀ�� On
void cursorOff(void);                    // Ŀ�� Off
void textColor(int color);               // ���ڻ� ����
void warningYesOrNo(void);               // Yes Ȥ�� No�� �������� Error �޼��� 
void curtainEffect(void);                // ȸ������ �˻� �� Ŀư ȭ�� ȿ��
void lineClear(void);                    // �� �� �޼��� ����
void printfAllNodes(Member_t *head);     // Linked List�� �̿��ؼ� ȸ������ ���

// UI (UI.c)
void mainmenuUI(void);                   // ���θ޴� UI
void case4SearchOptionUI(void);          // ȸ������ �� �˻� �ɼ� UI