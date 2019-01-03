#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>


#define size 25
#define lenth size*2
#define height size

//handler ã�ƺ���, ������� �����ϴ� �ڵ尡 ������ �� �־����. �۰� ���������� �������� �ڵ鸵 ã�ƺ��� �ڵ鸵����
//�ݺ����ε��� ������ �����ڵ� �ʿ�?? >> ���� ���α׷��� ������ ����

void gotoxy(int x, int y);
void WASD(void);
void MAP(void);
void Start_Snake(void);
void Make_Star(void);
void move(void);
void Body_Movement(void);
void Eat_Star(int j);
void Print_Body(void);
void GAME_OVER(void);
void removeCursor(void);
void setcolor(unsigned short text, unsigned short back);


int SPEED = 150; //���� �ӵ�. �������� ����
int score = 0;
int tail = 7; //������ ����

char Star[2]; //���� x, y ��ǥ



struct snake { // ������ x, y��ǥ
	int x;
	int y;
};

struct snake body[lenth*height] = { 0 }; // ������ x, y ��ǥ�� �ʱ�ȭ

										 ///
int mapXY[lenth][height]; // ȭ���� x,y��ǥ. ���⿡ 0 �Ǵ� 1�� ������ ����.
int a, b;



int main(void) {
	for (a = 0; a<lenth; a++) {
		for (b = 0; b<height; b++)
			mapXY[a][b] = 0; //ȭ���� x,y ��ǥ�� 0�� ����
	}

	//struct snake body[200] = { 0 }; �̷��� �ߴµ� �� body[]�ʱ�ȭ �ȵ�???
	int i;
	for (i = 0; i<lenth*height; i++) { // ������ x, y �� 0���� �ʱ�ȭ. �̰� ������ ������ �� ��������
		body[i].x = 0;
		body[i].y = 0;
	}
	SPEED = 300;
	score = 0;
	tail = 7;

	system("cls"); // ��üȭ�� �����
	removeCursor(); // Ŀ�� ������ �����
	MAP(); // �� ����
	Start_Snake(); // �� �ʱ⼳��

	Make_Star(); // ������
	move(); // ���� ������


	return 0;


}

void move(void) { // WASD �� ���� �Է¹ް� �� �������� �� �̵�
	int i;
	int ch = 'd'; // ó���� ���������� �̵���
	char way;//WASD �̿��� ���� ������ ���� ����� ch�� �� �����ص�.


	while (1) {
		Sleep(SPEED);
		if (kbhit()) { // �Է� �ޱ������� ����ȵ�
			ch = getch();
			getch();
		}


		if ((ch == 'd') || (ch == 'D')) { // D �Է�
			way = 'd';
			if ((body[0].x == lenth - 2) || (mapXY[body[0].x + 2][body[0].y] == 1)) { // ���� ��ų� ���뿡 ������ ���ӿ���

				GAME_OVER();

			}
			else {


				Body_Movement();

				body[0].x = body[0].x + 2; // �۰� x=2��ŭ ��ƸԾ +2
				body[0].y = body[0].y;
				mapXY[body[0].x][body[0].y] = 1; // �ش� x,y��ǥ�� 1�� ����

				Print_Body();

				if (((body[0].x == Star[0])) && (body[0].y == Star[1])) {
					for (i = 1; body[i].x; i++) {
					}
					Make_Star();

					Eat_Star(i);
				}


			}
		}


		else if ((ch == 's') || (ch == 'S')) {
			way = 's';
			if ((body[0].y == height - 1) || (mapXY[body[0].x][body[0].y + 1] == 1)) {
				GAME_OVER();

			}
			else {

				Body_Movement();

				body[0].x = body[0].x;
				body[0].y = body[0].y + 1; // �۰� y=1 ��ŭ �����ؼ� +1
				mapXY[body[0].x][body[0].y] = 1;

				Print_Body();

				if (((body[0].x == Star[0])) && (body[0].y == Star[1])) {
					for (i = 1; body[i].x; i++) {
					}
					Make_Star();

					Eat_Star(i);
				}


			}
		}


		else if ((ch == 'a') || (ch == 'A')) {
			way = 'a';
			if ((body[0].x == 2) || (mapXY[body[0].x - 2][body[0].y] == 1)) {
				GAME_OVER();

			}
			else {
				Body_Movement();

				body[0].x = body[0].x - 2;
				body[0].y = body[0].y;
				mapXY[body[0].x][body[0].y] = 1;

				Print_Body();


				if (((body[0].x == Star[0])) && (body[0].y == Star[1])) {
					for (i = 1; body[i].x; i++) {
					}
					Make_Star();

					Eat_Star(i);
				}

			}
		}

		else if ((ch == 'w') || (ch == 'W')) {
			way = 'w';
			if ((body[0].y == 1) || (mapXY[body[0].x][body[0].y - 1] == 1)) {
				GAME_OVER();

			}
			else {


				Body_Movement();

				body[0].x = body[0].x;
				body[0].y = body[0].y - 1;
				mapXY[body[0].x][body[0].y] = 1;

				Print_Body();


				if (((body[0].x == Star[0])) && (body[0].y == Star[1])) {
					for (i = 1; body[i].x; i++) {
					}
					Make_Star();

					Eat_Star(i);

				}
			}
		}
		else {
			ch = way;

		}
	}


}



void GAME_OVER(void) {
	int ch;
	gotoxy(2, 9);
	printf("�������������������������");
	gotoxy(2, 10);
	printf("�������������������������");
	gotoxy(2, 11);
	printf("�������������������������");
	gotoxy(2, 12);
	printf("�������������������������");
	gotoxy(2, 13);
	printf("�������������������������");
	gotoxy(2, 14);
	printf("�������������������������");
	gotoxy(2, 15);
	printf("�������������������������");
	gotoxy(2, 16);
	printf("�������������������������");
	gotoxy(2, 17);
	printf("�������������������������");
	gotoxy(0, height + 2);
	printf("�ٽ� �÷����Ϸ��� 'R'�� ��������\n");
	printf("������ �����Ϸ��� 'X'�� ��������\n");


	ch = getch();
	getch();

	if ((ch == 'r') || (ch == 'R')) { // 'R' �Է½� 3 �� �� main�Լ��� ���ư��� ���� �ٽý���, 'X' �Է½� ���� ����
		int SPEED = 0;
		int score = 0;
		int tail = 0;
		gotoxy(2, 9);
		printf("�������������������������");
		gotoxy(2, 10);
		printf("�������������������������");
		gotoxy(2, 11);
		printf("������������������������");
		gotoxy(2, 12);
		printf("�������������������������");
		gotoxy(2, 13);
		printf("�������������������������");
		gotoxy(2, 14);
		printf("�������������������������");
		gotoxy(2, 15);
		printf("�������������������������");
		gotoxy(2, 16);
		printf("�������������������������");
		gotoxy(2, 17);
		printf("�������������������������");
		Sleep(1000);
		//3 
		gotoxy(2, 9);
		printf("�������������������������");
		gotoxy(2, 10);
		printf("�������������������������");
		gotoxy(2, 11);
		printf("�������������������������");
		gotoxy(2, 12);
		printf("�������������������������");
		gotoxy(2, 13);
		printf("�������������������������");
		gotoxy(2, 14);
		printf("�������������������������");
		gotoxy(2, 15);
		printf("�������������������������");
		gotoxy(2, 16);
		printf("�������������������������");
		gotoxy(2, 17);
		printf("�������������������������");
		Sleep(1000);
		//2���
		gotoxy(2, 9);
		printf("�������������������������");
		gotoxy(2, 10);
		printf("�������������������������");
		gotoxy(2, 11);
		printf("�������������������������");
		gotoxy(2, 12);
		printf("�������������������������");
		gotoxy(2, 13);
		printf("�������������������������");
		gotoxy(2, 14);
		printf("�������������������������");
		gotoxy(2, 15);
		printf("�������������������������");
		gotoxy(2, 16);
		printf("�������������������������");
		gotoxy(2, 17);
		printf("�������������������������");
		Sleep(1000);
		//1

		main();
	}
	else if ((ch == 'x') || (ch == 'X')) {
		exit(1);
	}

	else {
		GAME_OVER();
	}


}



void Eat_Star(int j) {// ���� ������ ������ �ϳ� �þ�� �ӵ� ����

	body[j].x = lenth + 6; // �̰� 1, 1 �� �θ� ���� �������� ����
	body[j].y = height + 4;
	gotoxy(lenth + 10, 5);
	score += 100;
	printf("���� :  %d ��", score);
	gotoxy(lenth + 10, 7);
	tail++;
	printf("���� :  %d ��", tail);
	gotoxy(lenth + 10, 9);
	if (SPEED > 60) {
		SPEED -= 10;
	}
	printf("�ӵ� :  %d", SPEED);

}



void Make_Star() { //�� ����. ����� �Ȱ�ġ��.
	int j;
	srand((unsigned)time(NULL));
	Star[0] = (rand() % (size - 1) + 1) * 2;
	Star[1] = rand() % (size - 1) + 1;
	for (j = 0; body[j].x; j++) {
		while ((body[j].x == Star[0]) && (body[j].y == Star[1])) {
			Star[0] = (rand() % (size - 1) + 1) * 2;
			Star[1] = rand() % (size - 1) + 1;
		}
	}
	gotoxy(Star[0], Star[1]);
	setcolor(12, 0);

	printf("��");
	setcolor(15, 0);


}



void Body_Movement(void) { // ���� ������
	int i, j;

	for (i = 1; body[i].x; i++) {
	}

	//i�� ������ ���� +1�� ��
	body[i].x = body[i - 1].x;
	body[i].y = body[i - 1].y;
	gotoxy(body[i].x, body[i].y);
	printf("  "); // ������ ������ �ִ� �ڸ� ����
	mapXY[body[i].x][body[i].y] = 0; // ������ ������ �ִ� ��ǥ�� 0 ����
	body[i].x = 0;
	body[i].y = 0;


	j = i - 1;
	for (j; j>0; j--) { // ���� ��ĭ�� �̵�
		body[j].x = body[j - 1].x;
		body[j].y = body[j - 1].y;
		mapXY[body[j].x][body[j].y] = 1; // ������ �ִ� ��ǥ�� 1 ����
	}
}



void Print_Body(void) { // ���� ���
	int i;
	setcolor(2, 0);
	gotoxy(body[0].x, body[0].y);
	printf("��");
	for (i = 1; body[i].x; i++) {
		gotoxy(body[i].x, body[i].y);
		printf("��");
	}
	setcolor(15, 0);
}




void Start_Snake(void) { // �� �ʱ⼼��. ����7��.


	int i;
	for (i = 1; i<7; i++) {
		body[0].x = 14;
		body[0].y = height - 1;

		body[i].x = body[i - 1].x - 2;
		body[i].y = height - 1;

	}
	setcolor(2, 0);
	for (i = 1; i<7; i++) {
		gotoxy(body[0].x, body[0].y);
		printf("��");
		mapXY[body[0].x][body[0].y] = 1;
		gotoxy(body[i].x, body[i].y);
		printf("��");
		mapXY[body[i].x][body[i].y] = 1;
	}
	setcolor(15, 0);
}




void MAP(void) { // ��������
	int x;
	int y;

	gotoxy(0, 0);
	printf("��");
	for (x = 1; x<lenth; x++) {
		gotoxy(x, 0);
		printf("��");
	}
	gotoxy(lenth, 0);
	printf("��");

	for (y = 1; y<height; y++) {
		gotoxy(0, y);
		printf("��");

	}
	for (y = 1; y < height; y++) {
		gotoxy(lenth, y);
		printf("��");

	}
	gotoxy(0, height);
	printf("��");
	for (x = 1; x<lenth; x++) {
		gotoxy(x, height);
		printf("��");
	}
	gotoxy(lenth, height);
	printf("��");

	gotoxy(lenth + 10, 5);
	printf("���� :  %d ��", score);
	gotoxy(lenth + 10, 7);
	printf("���� :  %d ��", tail);
	gotoxy(lenth + 10, 9);
	printf("�ӵ� :  %d", SPEED);



}





void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //SetConsoleCursorPosition �Լ� ȣ���� �ʼ�
																	//WinCon.h �ȿ� ����ְ�, �� ��������� Windows.h�� �������
}

void removeCursor(void) //���� �ڵ�. ���߿� ����

{

	CONSOLE_CURSOR_INFO cur;

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);

	cur.bVisible = 0;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);

}

void setcolor(unsigned short text, unsigned short back)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}