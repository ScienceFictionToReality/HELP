
#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>


#define size 25
#define lenth size*2
#define height size

void gotoxy(int x, int y);
void map(void);
void snake(void);
void end(void);
void move(void);
int star_x(void);
int star_y(void);

int main(void) {
	map();
	snake();

	move();
	end();

	return 0;
}


int star_x(void) {
	int x = 0;
	srand((unsigned)time(NULL));
	x = (rand() % 24 + 1) * 2;

	return x;

}

int star_y(void) {
	int y = 0;
	srand((unsigned)time(NULL));

	y = rand() % 24 + 1;

	return y;

}

void move(void) {

	int head_x = 14;
	int head_y = height - 1;
	int body1_x = 12;
	int body1_y = height - 1;
	int body2_x = 10;
	int body2_y = height - 1;
	int body3_x = 8;
	int body3_y = height - 1;
	int body4_x = 6;
	int body4_y = height - 1;
	int body5_x = 4;
	int body5_y = height - 1;
	int body6_x = 2;
	int body6_y = height - 1;
	int starX;
	int starY;
	int score = 0;


	do {
		starX = star_x();

	} while ((starX == head_x) || (starX == body1_x) || (starX == body2_x) || (starX == body3_x) || (starX == body4_x) || (starX == body5_x) || (starX == body6_x));

	do {
		starY = star_y();

	} while ((starY == head_y) || (starY == body1_y) || (starY == body2_y) || (starY == body3_y) || (starY == body4_y) || (starY == body5_y) || (starY == body6_y));

	gotoxy(starX, starY);
	printf("★");



	while (1) {
		if ((starX == head_x) && (starY == head_y)) {
			score += 100;
			gotoxy(2, height + 2);
			printf("점수 : %d 점", score);
			do {
				starX = star_x();

			} while ((starX == head_x) || (starX == body1_x) || (starX == body2_x) || (starX == body3_x) || (starX == body4_x) || (starX == body5_x) || (starX == body6_x));

			do {
				starY = star_y();

			} while ((starY == head_y) || (starY == body1_y) || (starY == body2_y) || (starY == body3_y) || (starY == body4_y) || (starY == body5_y) || (starY == body6_y));

			gotoxy(starX, starY);
			printf("★");
		}


		int ch;
		ch = getch();

		if ((ch == 's') || (ch == 'S')) {
			if (head_y == height - 1) {
			}
			else if (((head_x == body1_x) && (head_y + 1 == body1_y)) ||
				((head_x == body2_x) && (head_y + 1 == body2_y)) ||
				((head_x == body3_x) && (head_y + 1 == body3_y)) ||
				((head_x == body4_x) && (head_y + 1 == body4_y)) ||
				((head_x == body5_x) && (head_y + 1 == body5_y)) ||
				((head_x == body6_x) && (head_y + 1 == body6_y))) {
			}

			else {
				gotoxy(body6_x, body6_y);
				printf(" ");
				body6_x = body5_x;
				body6_y = body5_y;
				gotoxy(body6_x, body6_y);
				printf("○");
				body5_x = body4_x;
				body5_y = body4_y;
				gotoxy(body5_x, body5_y);
				printf("○");
				body4_x = body3_x;
				body4_y = body3_y;
				gotoxy(body4_x, body4_y);
				printf("○");
				body3_x = body2_x;
				body3_y = body2_y;
				gotoxy(body3_x, body3_y);
				printf("○");
				body2_x = body1_x;
				body2_y = body1_y;
				gotoxy(body2_x, body2_y);
				printf("○");
				body1_x = head_x;
				body1_y = head_y;
				gotoxy(body1_x, body1_y);
				printf("○");
				head_x = head_x;
				head_y = head_y + 1;
				gotoxy(head_x, head_y);
				printf("●");
				gotoxy(lenth, height);
			}
		}

		if ((ch == 'a') || (ch == 'A')) {
			if (head_x == 2) {
			}
			else if (((head_x - 2 == body1_x) && (head_y == body1_y)) ||
				((head_x - 2 == body2_x) && (head_y == body2_y)) ||
				((head_x - 2 == body3_x) && (head_y == body3_y)) ||
				((head_x - 2 == body4_x) && (head_y == body4_y)) ||
				((head_x - 2 == body5_x) && (head_y == body5_y)) ||
				((head_x - 2 == body6_x) && (head_y == body6_y))) {
			}

			else {
				gotoxy(body6_x, body6_y);
				printf(" ");
				body6_x = body5_x;
				body6_y = body5_y;
				gotoxy(body6_x, body6_y);
				printf("○");
				body5_x = body4_x;
				body5_y = body4_y;
				gotoxy(body5_x, body5_y);
				printf("○");
				body4_x = body3_x;
				body4_y = body3_y;
				gotoxy(body4_x, body4_y);
				printf("○");
				body3_x = body2_x;
				body3_y = body2_y;
				gotoxy(body3_x, body3_y);
				printf("○");
				body2_x = body1_x;
				body2_y = body1_y;
				gotoxy(body2_x, body2_y);
				printf("○");
				body1_x = head_x;
				body1_y = head_y;
				gotoxy(body1_x, body1_y);
				printf("○");
				head_x = head_x - 2;
				head_y = head_y;
				gotoxy(head_x, head_y);
				printf("●");
				gotoxy(lenth, height);
			}
		}


		if ((ch == 'w') || (ch == 'W')) {
			if (head_y == 1) {
			}
			else if (((head_x == body1_x) && (head_y - 1 == body1_y)) ||
				((head_x == body2_x) && (head_y - 1 == body2_y)) ||
				((head_x == body3_x) && (head_y - 1 == body3_y)) ||
				((head_x == body4_x) && (head_y - 1 == body4_y)) ||
				((head_x == body5_x) && (head_y - 1 == body5_y)) ||
				((head_x == body6_x) && (head_y - 1 == body6_y))) {
			}

			else {
				gotoxy(body6_x, body6_y);
				printf(" ");
				body6_x = body5_x;
				body6_y = body5_y;
				gotoxy(body6_x, body6_y);
				printf("○");
				body5_x = body4_x;
				body5_y = body4_y;
				gotoxy(body5_x, body5_y);
				printf("○");
				body4_x = body3_x;
				body4_y = body3_y;
				gotoxy(body4_x, body4_y);
				printf("○");
				body3_x = body2_x;
				body3_y = body2_y;
				gotoxy(body3_x, body3_y);
				printf("○");
				body2_x = body1_x;
				body2_y = body1_y;
				gotoxy(body2_x, body2_y);
				printf("○");
				body1_x = head_x;
				body1_y = head_y;
				gotoxy(body1_x, body1_y);
				printf("○");
				head_x = head_x;
				head_y = head_y - 1;
				gotoxy(head_x, head_y);
				printf("●");
				gotoxy(lenth, height);
			}
		}

		if ((ch == 'd') || (ch == 'D')) {
			if (head_x == lenth - 2) {
			}
			else if (((head_x + 2 == body1_x) && (head_y == body1_y)) ||
				((head_x + 2 == body2_x) && (head_y == body2_y)) ||
				((head_x + 2 == body3_x) && (head_y == body3_y)) ||
				((head_x + 2 == body4_x) && (head_y == body4_y)) ||
				((head_x + 2 == body5_x) && (head_y == body5_y)) ||
				((head_x + 2 == body6_x) && (head_y == body6_y))) {
			}

			else {
				gotoxy(body6_x, body6_y);
				printf(" ");
				body6_x = body5_x;
				body6_y = body5_y;
				gotoxy(body6_x, body6_y);
				printf("○");
				body5_x = body4_x;
				body5_y = body4_y;
				gotoxy(body5_x, body5_y);
				printf("○");
				body4_x = body3_x;
				body4_y = body3_y;
				gotoxy(body4_x, body4_y);
				printf("○");
				body3_x = body2_x;
				body3_y = body2_y;
				gotoxy(body3_x, body3_y);
				printf("○");
				body2_x = body1_x;
				body2_y = body1_y;
				gotoxy(body2_x, body2_y);
				printf("○");
				body1_x = head_x;
				body1_y = head_y;
				gotoxy(body1_x, body1_y);
				printf("○");
				head_x = head_x + 2;
				head_y = head_y;
				gotoxy(head_x, head_y);
				printf("●");
				gotoxy(lenth, height);
			}
		}



	}
}




void snake(void) {

	gotoxy(14, height - 1);
	printf("●");
	gotoxy(12, height - 1);
	printf("○");
	gotoxy(10, height - 1);
	printf("○");
	gotoxy(8, height - 1);
	printf("○");
	gotoxy(6, height - 1);
	printf("○");
	gotoxy(4, height - 1);
	printf("○");
	gotoxy(2, height - 1);
	printf("○");




}




void map(void) {
	int x;
	int y;
	gotoxy(0, 0);
	printf("┌");
	for (x = 1; x<lenth; x++) {
		gotoxy(x, 0);
		printf("─");
	}
	gotoxy(lenth, 0);
	printf("┐");
	for (y = 1; y<height; y++) {
		gotoxy(0, y);
		printf("│");
	}
	for (y = 1; y < height; y++) {
		gotoxy(lenth, y);
		printf("│");
	}
	gotoxy(0, height);
	printf("└");
	for (x = 1; x<lenth; x++) {
		gotoxy(x, height);
		printf("─");
	}
	gotoxy(lenth, height);
	printf("┘");
}


void end(void) {
	gotoxy(lenth + 1, height + 1);
	printf("\n");
}


void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //SetConsoleCursorPosition 함수 호출은 필수
																	//WinCon.h 안에 들어있고, 이 헤더파일은 Windows.h에 들어있음
}
