#include <stdio.h>
#include <errno.h>

int main(void) {
	char* filename = "C:\\Users\\user\\Desktop\\work";
	FILE* fp	= fopen(filename, "r"); // ����ü* fp

	if(fp == NULL) {
		printf("�б���� ���� [%s] ���⿡ �����Ͽ����ϴ�.\n", filename);
		printf("errno=%d\n", errno);//  
	} else {
		printf("�б���� ���� [%s] ���⿡ �����߽��ϴ�. \n", filename);
	}

	fp = fopen(filename, "w");
	errno = 0;
	
	if(fp == NULL) {
		printf("������� ���� [%s] ���⿡ �����߽��ϴ�.\n", filename);
		printf("errno = %d\n", errno);
	}else {
		printf("������� ���� [%s] ���⿡ �����߽��ϴ�.\n", filename);
	}

	printf("FOPEN_MAX=%d\n", FOPEN_MAX);
	/////////
	fclose(fp);
	printf("���� [%s]�� �ݽ��ϴ�.\n", filename);

	return 0;
}