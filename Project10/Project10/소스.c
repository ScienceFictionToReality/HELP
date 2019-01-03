
#include <stdio.h>
#include <Windows.h>
#define size 25
#define lenth size*2
#define height size
void gotoxy(int x, int y);
void map(void);
void snake(void);
void end(void);
void move(void);



int main(void) {
	map();

	snake();
	move();
	end();

	return 0;
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
	int future_x=0;
	int future_y=0;
	while (1) {
		int ch;
		ch = getch();
		
		if ((ch == 's') || (ch == 'S')) {
			if (head_y == height - 1) {
			}
			else{
				future_x = 0;
				future_y = 1;
			}
		}

		else if ((ch == 'a') || (ch == 'A')) {
			if (head_x == 2) {
			}
			else{
				future_x = -2;
				future_y = 0;
			}
		}
		else if ((ch == 'w') || (ch == 'W')) {
			if (head_y == 1) {
			}
			else {
				future_x = 0;
				future_y = -1;
			}
		}
		else if ((ch == 'd') || (ch == 'D')) {
			if (head_x == lenth - 2) {
			}
			else {
				future_x = 2;
				future_y = 0;
			}

		}
		
		head_x = head_x + future_x; // 14 + 2
		head_y = head_y + future_y;
		gotoxy(head_x, head_y);
		printf("●");
			
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
