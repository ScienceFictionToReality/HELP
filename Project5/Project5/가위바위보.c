#include <stdio.h>

int PlayerNum(void);
void game(int Num);
void UserName(int i);
void ranking(int Num);



struct data {
	char name[7];
	int win, lose, draw, percent, score;
};

struct data DataArr[100] = { 0 };




int main(void) {
	int Num;
	printf("****가위바위보 게임****\n");
	Num = PlayerNum();
	game(Num);
	ranking(Num);
	return 0;
}




int PlayerNum(void) {
	int Num;//플레이어 숫자
	printf("플레이어 수를 입력하세요 > ");
	scanf("%d", &Num);
	printf("플레이어 : %d명\n", Num);

	return Num;
}




void UserName(int i) {
	printf("******이름을 입력하세요******\n");
	scanf("%s", DataArr[i].name);
}




void game(int Num) { // 플레이어 숫자 받아옴
	int i = 0;
	int round = 0;
	char player[100];
	int result;
	int computer;
	char com[3][5] = { "가위","바위","보" };

	for (i = 0; i<Num; i++) {

		UserName(i);

		printf("안녕하세요 ' %s ' 님 가위바위보 게임을 시작합니다\n", DataArr[i].name);

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

			srand((unsigned)time(NULL)); //이건 책 그대로 함.
			computer = rand() % 3; // 0,1,2 얻음

			switch (result - computer) { //strcmp(player,computer)
			case 1: case -2:
				printf("  컴퓨터는 < %s >, 승리---%d 라운드 \n", com[computer], round + 1);
				DataArr[i].win++;
				DataArr[i].score += 500;
				break;
			case -1: case 2:
				printf("  컴퓨터는 < %s >, 패배---%d 라운드 \n", com[computer], round + 1);
				DataArr[i].lose++;
				DataArr[i].score -= 300;
				break;
			case 0:
				printf("  컴퓨터는 < %s >, 무승부---%d 라운드 \n", com[computer], round + 1);
				DataArr[i].draw++;

				break;
			default:
				printf("@@@@@@@@@@@@@@다시@@@@@@@@@@@@@@\n");
				round--;
				break;

			}

		}
		printf("승리 = %d , 패배 = %d, 무승부 = %d, 승률 = %5.2f, 점수 = %d\n\n", DataArr[i].win, DataArr[i].lose, DataArr[i].draw, (float)DataArr[i].win / (DataArr[i].win + DataArr[i].lose + DataArr[i].draw) * 100, DataArr[i].score);

	}
}



void ranking(int Num) {
	printf("---------랭    킹--------\n");
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
	for (k = 0; k<Num; k++) {
		printf("%d등. %s :: 승리 = %d , 패배 = %d, 무승부 = %d, 승률 = %5.2f, 점수 = %d\n", rank, DataArr[k].name, DataArr[k].win, DataArr[k].lose, DataArr[k].draw, (float)DataArr[k].win / (DataArr[k].win + DataArr[k].lose + DataArr[k].draw) * 100, DataArr[k].score);
		rank++;
	}

}

