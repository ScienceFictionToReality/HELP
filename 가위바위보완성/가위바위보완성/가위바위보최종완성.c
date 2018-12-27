#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>


void game();
void UserName();
void menu();
void record();
void ranking();
void reset();


struct data {
	char name[7];
	int win, lose, draw, percent, score;
	float per;
};

struct data DataArr[100] = { 0 };



int main(void) {

	printf("****���������� ����****\n");
	printf("������ �����Ϸ��� G��, ��ŷ�� ������ R�� ��������.\n( ������ ������ 0 )\n");
	menu();

	return 0;
}


void menu() {


	int input = getch(); //getch() �� �Է¹��� ���ڸ� ȭ�鿡 ������� �ʰ�, getche()�� �����
	if (input == 'g' || input == 'G') {  //(input == 'g'||'G')�ȵǳ�
		game();
		record();

	}
	else if (input == 'r' || input == 'R') {
		ranking();
	}
	else if (input == '0') {
		printf("�����͸� �����մϴ�.\n");
		reset();
		menu();
	}
	else {
		printf("�ٽ� �Է��ϼ���\n");
		menu();
	}
}

void UserName() {
	printf("******�̸��� �Է��ϼ���(������)******\n");
	scanf("%s", DataArr[0].name);
}

void game() {
	int i = 0;
	int round = 0;
	char player[100];
	int result;
	int computer;
	char com[3][5] = { "����","����","��" };

	UserName();

	printf("�ȳ��ϼ��� ' %s ' �� ���������� ������ �����մϴ�\n", DataArr[0].name);
	srand((unsigned)time(NULL)); //�̰� å �״�� ��.
	for (round = 0; round <5; round++) {
		printf("~~~~����������~~~\n");
		scanf("%s", player);

		if (!memcmp(player, "����", sizeof("����"))) { //������ 0
			result = 0;
		}
		else if (!memcmp(player, "����", sizeof("����"))) {
			result = 1;
		}
		else if (!memcmp(player, "��", sizeof("��"))) {
			result = 2;
		}
		else {
			result = 7;
		}


		computer = rand() % 3; // 0,1,2 ����

		switch (result - computer) { //strcmp(player,computer)
		case 1: case -2:
			printf("  ��ǻ�ʹ� < %s >, �¸�---%d ���� \n", com[computer], round + 1);
			DataArr[0].win++;
			DataArr[0].score += 500;
			break;
		case -1: case 2:
			printf("  ��ǻ�ʹ� < %s >, �й�---%d ���� \n", com[computer], round + 1);
			DataArr[0].lose++;
			DataArr[0].score -= 300;
			break;
		case 0:
			printf("  ��ǻ�ʹ� < %s >, ���º�---%d ���� \n", com[computer], round + 1);
			DataArr[0].draw++;

			break;
		default:
			printf("@@@@@@@@@@@@@@�ٽ�@@@@@@@@@@@@@@\n");
			round--;
			break;

		}

	}
	DataArr[0].per = (float)DataArr[0].win / (DataArr[0].win + DataArr[0].lose + DataArr[0].draw) * 100;

	printf("�¸� = %d , �й� = %d, ���º� = %d, �·� = %5.2f, ���� = %d\n\n", DataArr[0].win, DataArr[0].lose, DataArr[0].draw, DataArr[0].per, DataArr[0].score);

}


void record(void) {
	char* fname = "C:\\Users\\user\\Desktop\\RCPgame.txt";
	FILE* fp = fopen(fname, "a");

	if (fp == NULL) {
		printf("�̾����� ���� [%s] ���⿡ �����߽��ϴ�. \n", fname);
		printf("errno=%d\n", errno);
	}
	else {
		printf("������ ����Ǿ����ϴ�.\n");
	}

	char* outFormat = "%s  %d   %d   %d   %5.2f  %d \n";



	fprintf(fp, outFormat, DataArr[0].name, DataArr[0].win, DataArr[0].lose, DataArr[0].draw, DataArr[0].per, DataArr[0].score);

	fclose(fp);
}
////////////////////////

void reset(void) {
	char* fname = "C:\\Users\\user\\Desktop\\RCPgame.txt";
	FILE* fp = fopen(fname, "w");

	fclose(fp);
	menu();
}

////////////////////////////// �̻����

void ranking(void) {


	char* fname = "C:\\Users\\user\\Desktop\\RCPgame.txt";
	FILE* fp = fopen(fname, "r");
	char* inFormat = "%s  %d   %d   %d   %f  %d";


	if (fp == NULL) {
		printf("���� [%s] �� �������� �ʽ��ϴ�.\n", fname);
		exit(1);/////
	}

	printf("  ��ŷ  �̸�  ��   ��  ��   �·�  ����\n");
	int i = 0;
	int retu;
	int Num = 0;


	while (1) {
		retu = fscanf(fp, inFormat, &DataArr[i].name, &DataArr[i].win, &DataArr[i].lose, &DataArr[i].draw, &DataArr[i].per, &DataArr[i].score);
		if (retu<0) break; // fscanf�� EOF�� �� ������ ��ȯ�ϰ�, retu �� ����
		i++;
		Num++;

	}


	struct data tmp;

	int p, q, k = 0;
	for (p = 0; p < Num - 1; p++) {
		for (q = 0; q < Num - p - 1; q++) {
			if (DataArr[q].score < DataArr[q + 1].score) {
				tmp = DataArr[q];
				DataArr[q] = DataArr[q + 1];
				DataArr[q + 1] = tmp;
			}
		}
	}
	int rank = 1;
	for (k = 0; k< Num; k++) {

		printf(" %4d  %4s  %d   %d   %d   %5.2f  %d \n", rank, DataArr[k].name, DataArr[k].win, DataArr[k].lose, DataArr[k].draw, DataArr[k].per, DataArr[k].score);

		rank++;
	}



	fclose(fp);

}