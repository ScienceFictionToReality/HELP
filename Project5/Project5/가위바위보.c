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
	printf("****���������� ����****\n");
	Num = PlayerNum();
	game(Num);
	ranking(Num);
	return 0;
}




int PlayerNum(void) {
	int Num;//�÷��̾� ����
	printf("�÷��̾� ���� �Է��ϼ��� > ");
	scanf("%d", &Num);
	printf("�÷��̾� : %d��\n", Num);

	return Num;
}




void UserName(int i) {
	printf("******�̸��� �Է��ϼ���******\n");
	scanf("%s", DataArr[i].name);
}




void game(int Num) { // �÷��̾� ���� �޾ƿ�
	int i = 0;
	int round = 0;
	char player[100];
	int result;
	int computer;
	char com[3][5] = { "����","����","��" };

	for (i = 0; i<Num; i++) {

		UserName(i);

		printf("�ȳ��ϼ��� ' %s ' �� ���������� ������ �����մϴ�\n", DataArr[i].name);

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

			srand((unsigned)time(NULL)); //�̰� å �״�� ��.
			computer = rand() % 3; // 0,1,2 ����

			switch (result - computer) { //strcmp(player,computer)
			case 1: case -2:
				printf("  ��ǻ�ʹ� < %s >, �¸�---%d ���� \n", com[computer], round + 1);
				DataArr[i].win++;
				DataArr[i].score += 500;
				break;
			case -1: case 2:
				printf("  ��ǻ�ʹ� < %s >, �й�---%d ���� \n", com[computer], round + 1);
				DataArr[i].lose++;
				DataArr[i].score -= 300;
				break;
			case 0:
				printf("  ��ǻ�ʹ� < %s >, ���º�---%d ���� \n", com[computer], round + 1);
				DataArr[i].draw++;

				break;
			default:
				printf("@@@@@@@@@@@@@@�ٽ�@@@@@@@@@@@@@@\n");
				round--;
				break;

			}

		}
		printf("�¸� = %d , �й� = %d, ���º� = %d, �·� = %5.2f, ���� = %d\n\n", DataArr[i].win, DataArr[i].lose, DataArr[i].draw, (float)DataArr[i].win / (DataArr[i].win + DataArr[i].lose + DataArr[i].draw) * 100, DataArr[i].score);

	}
}



void ranking(int Num) {
	printf("---------��    ŷ--------\n");
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
		printf("%d��. %s :: �¸� = %d , �й� = %d, ���º� = %d, �·� = %5.2f, ���� = %d\n", rank, DataArr[k].name, DataArr[k].win, DataArr[k].lose, DataArr[k].draw, (float)DataArr[k].win / (DataArr[k].win + DataArr[k].lose + DataArr[k].draw) * 100, DataArr[k].score);
		rank++;
	}

}

