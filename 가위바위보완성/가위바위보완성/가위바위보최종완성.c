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

	printf("****가위바위보 게임****\n");
	printf("게임을 실행하려면 G를, 랭킹을 보려면 R을 누르세요.\n( 데이터 리셋은 0 )\n");
	menu();

	return 0;
}


void menu() {


	int input = getch(); //getch() 는 입력받은 문자를 화면에 출력하지 않고, getche()는 출력함
	if (input == 'g' || input == 'G') {  //(input == 'g'||'G')안되나
		game();
		record();

	}
	else if (input == 'r' || input == 'R') {
		ranking();
	}
	else if (input == '0') {
		printf("데이터를 리셋합니다.\n");
		reset();
		menu();
	}
	else {
		printf("다시 입력하세요\n");
		menu();
	}
}

void UserName() {
	printf("******이름을 입력하세요(세글자)******\n");
	scanf("%s", DataArr[0].name);
}

void game() {
	int i = 0;
	int round = 0;
	char player[100];
	int result;
	int computer;
	char com[3][5] = { "가위","바위","보" };

	UserName();

	printf("안녕하세요 ' %s ' 님 가위바위보 게임을 시작합니다\n", DataArr[0].name);
	srand((unsigned)time(NULL)); //이건 책 그대로 함.
	for (round = 0; round <5; round++) {
		printf("~~~~가위바위보~~~\n");
		scanf("%s", player);

		if (!memcmp(player, "가위", sizeof("가위"))) { //같으면 0
			result = 0;
		}
		else if (!memcmp(player, "바위", sizeof("바위"))) {
			result = 1;
		}
		else if (!memcmp(player, "보", sizeof("보"))) {
			result = 2;
		}
		else {
			result = 7;
		}


		computer = rand() % 3; // 0,1,2 얻음

		switch (result - computer) { //strcmp(player,computer)
		case 1: case -2:
			printf("  컴퓨터는 < %s >, 승리---%d 라운드 \n", com[computer], round + 1);
			DataArr[0].win++;
			DataArr[0].score += 500;
			break;
		case -1: case 2:
			printf("  컴퓨터는 < %s >, 패배---%d 라운드 \n", com[computer], round + 1);
			DataArr[0].lose++;
			DataArr[0].score -= 300;
			break;
		case 0:
			printf("  컴퓨터는 < %s >, 무승부---%d 라운드 \n", com[computer], round + 1);
			DataArr[0].draw++;

			break;
		default:
			printf("@@@@@@@@@@@@@@다시@@@@@@@@@@@@@@\n");
			round--;
			break;

		}

	}
	DataArr[0].per = (float)DataArr[0].win / (DataArr[0].win + DataArr[0].lose + DataArr[0].draw) * 100;

	printf("승리 = %d , 패배 = %d, 무승부 = %d, 승률 = %5.2f, 점수 = %d\n\n", DataArr[0].win, DataArr[0].lose, DataArr[0].draw, DataArr[0].per, DataArr[0].score);

}


void record(void) {
	char* fname = "C:\\Users\\user\\Desktop\\RCPgame.txt";
	FILE* fp = fopen(fname, "a");

	if (fp == NULL) {
		printf("이어쓰기모드로 파일 [%s] 열기에 실패했습니다. \n", fname);
		printf("errno=%d\n", errno);
	}
	else {
		printf("게임이 종료되었습니다.\n");
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

////////////////////////////// 이상없음

void ranking(void) {


	char* fname = "C:\\Users\\user\\Desktop\\RCPgame.txt";
	FILE* fp = fopen(fname, "r");
	char* inFormat = "%s  %d   %d   %d   %f  %d";


	if (fp == NULL) {
		printf("파일 [%s] 가 존재하지 않습니다.\n", fname);
		exit(1);/////
	}

	printf("  랭킹  이름  승   패  무   승률  점수\n");
	int i = 0;
	int retu;
	int Num = 0;


	while (1) {
		retu = fscanf(fp, inFormat, &DataArr[i].name, &DataArr[i].win, &DataArr[i].lose, &DataArr[i].draw, &DataArr[i].per, &DataArr[i].score);
		if (retu<0) break; // fscanf은 EOF일 때 음수를 반환하고, retu 에 저장
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