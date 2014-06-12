#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* int main(void)
{
	char *p, msg[] = "Some of THESE letters are Capitals";
	puts(msg);

	for (p = msg; p < msg + strlen(msg); p++)
	{
		if (islower(*p))
			putchar(toupper(*p));
		else if (isupper(*p))
			putchar(tolower(*p));
		else
			putchar(*p);
	}
	printf("\n");
	return 0;
} */

/* int mystrlen(char *);
char* mystrcpy(char *, char *);
char* mystrcat(char *, char *);
int mystrcmp(char *, char *);

int main(void)
{
	char *str = "hello, World";
	char *dest = NULL;
	char str1[30] = "first";
	char str2[30] = "second";
	char str3[30] = "My String";
	char str4[30] = "My String";

	int len = mystrlen(str);
	char *p;
	int result;
	// strlen
	printf("길이: %d, 내용: %s %d \n", mystrlen(str), str, sizeof(str));
	// strcpy
	dest = (char*)malloc(len + 1);
	mystrcpy(dest, str);
	printf("sourse: %s, dest: %s \n", str, dest);
	// strcat
	mystrcat(str1, str2);
	printf("sourse: %s, dest: %s \n", str, dest);
	// strcmp
	result = mystrcmp(str3, str4);
	printf("%d \n", result);
	return 0;
}

int mystrlen(char *dest)
{
	int count = 0;
	while (*dest != '\0'){
		count++;
		dest++;
	}
	return count;
}

char* mystrcpy(char *dest, char *src)
{
	// int len = strlen(src);

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = *src;
	return dest;
}

char* mystrcat(char *dest, char *src)
{
	while (*dest != '\0') dest++;
	while (*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return dest;
}

int mystrcmp(char *str1, char *str2)
{
	while (*str1 == *str2){
		if (*str1 == '\0' && *str2 == '\0')
			return 0;
		str1++; str2++;
	}
	if (*str1 > *str2) return 1;
	return 0;
} */

/* int main(void)
{
	char *src = " I am a student";
	char *reverse;
	int i, j;

	reverse = (char*)malloc(strlen(src) + 1);
	if (reverse == NULL){
		printf("Failure of allocation of memory");
		return -1;
	}

	for (i = strlen(src) - 1, j = 0; i >= 0; i--, j++)
		reverse[j] = src[i];
	reverse[j] = '\0';
	printf("reverse String is %s\n", reverse);
	return 0;
} */

/* int main(void)
{
	char str[] = "lazy";
	char string[] = "The quick brown dog jumps over the lazy fox";
	char *pdest;
	int result;

	printf("String to be searched:\n\t%s\n", string);
	pdest = strstr(string, str);
	result = pdest - string + 1;

	if (pdest != NULL)
		printf("%s found at position %d\n\n", str, result);
	else
		printf("%s not found\n", str);

	return 0;
} */

/* int main(void)
{
	int ch1, ch2;
	ch1 = getchar();
	ch2 = fgetc(stdin);

	putchar(ch1);
	fputc(ch2, stdout);
	return 0;
} */

/* int main(void)
{
	char perID[7];
	char name[10];

	fputs("주민번호 6자리: ", stdout);
	fgets(perID, sizeof(perID), stdin); // 'n'이 입력버퍼에 남음
	
	while (getchar() != '\n');

	fputs("이름입력: ", stdout);
	fgets(name, sizeof(name), stdin);

	printf("주민번호: %s \n", perID);
	printf("이름: %s \n", name);

	return 0;
} */

void removeNewLine(char str[]){
	int len = strlen(str);
	str[len - 1] = 0;
}

/* int main(void)
{
	char str[100];
	printf("문자열 입력: ");
	fgets(str, sizeof(str), stdin);
	printf("길이 %d, 내용 %s\n", strlen(str), str);
	
	removeNewLine(str);
	printf("길이 %d, 내용 %s\n", strlen(str), str);
	return 0;
} */

/* int main(void)
{
	FILE *fin, *fout;
	char ch;
	int num;
	char buf[256];
	char buf2[10];

	if ((fin = fopen("input.txt", "r")) == NULL){
		printf("file open error\n");
		exit(0);
	}

	fout = fopen("output.txt", "w");
	fscanf(fin, "%d %s %s", &num, buf, buf2);
	fprintf(fout, "%8d\n", num);
	fclose(fin);
	fclose(fout);
	return 0;
} */

/* void file_print(char *p, int n)
{
	while (n--) putchar(*p++);
	putchar('\n');
} */

/* int main(void)
{
	FILE *fp;
	char str[100];
	fp = fopen("test.dat", "wb");
	fprintf(fp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	fclose(fp);
	fp = fopen("test.dat", "rb");
	fscanf(fp, "%26c", str);
	file_print(str, 26);

	fseek(fp, 3L, SEEK_SET);
	fscanf(fp, "%5c", str);
	file_print(str, 5);

	fseek(fp, -10L, SEEK_END);
	fscanf(fp, "%5c", str);
	file_print(str, 10);
	fclose(fp);

	return 0;
} */

int main(void)
{
	FILE *fp;
	char str[256];
	int count = 0;

	if ((fp = fopen("name1.txt", "r")) == NULL){
		fprintf(stderr, "Error opening file %s.", "name.txt");
		return -1;
	}

	str[0] = 0;
	while ((fgets(str, sizeof(str), fp)) != NULL){
		removeNewLine(str);
		if (strlen(str) > 0){
			printf("%03d %s \n", count, str);
			count++;
			str[0] = 0;
		}
		else printf("\n");
	}
	fclose(fp);
	return 0;
}