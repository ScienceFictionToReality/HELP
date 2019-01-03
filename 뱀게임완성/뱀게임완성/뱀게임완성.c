#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>


#define size 25
#define lenth size*2
#define height size

//handler 찾아보고, 쓰레드는 종료하는 코드가 쌍으로 꼭 있어야함. 글고 전역변수로 하지말고 핸들링 찾아보고 핸들링으로
//반복문인데도 쓰레드 종료코드 필요?? >> ㅇㅇ 프로그램이 끝나기 전에

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


int SPEED = 150; //게임 속도. 낮을수록 빠름
int score = 0;
int tail = 7; //몸통의 개수

char Star[2]; //☆의 x, y 좌표



struct snake { // 몸통의 x, y좌표
	int x;
	int y;
};

struct snake body[lenth*height] = { 0 }; // 몸통의 x, y 좌표값 초기화

										 ///
int mapXY[lenth][height]; // 화면의 x,y좌표. 여기에 0 또는 1을 저장할 것임.
int a, b;



int main(void) {
	for (a = 0; a<lenth; a++) {
		for (b = 0; b<height; b++)
			mapXY[a][b] = 0; //화면의 x,y 좌표에 0을 넣음
	}

	//struct snake body[200] = { 0 }; 이렇게 했는데 왜 body[]초기화 안됨???
	int i;
	for (i = 0; i<lenth*height; i++) { // 몸통의 x, y 값 0으로 초기화. 이거 없으면 리겜할 때 문제생김
		body[i].x = 0;
		body[i].y = 0;
	}
	SPEED = 300;
	score = 0;
	tail = 7;

	system("cls"); // 전체화면 지우기
	removeCursor(); // 커서 깜빡임 지우기
	MAP(); // 맵 생성
	Start_Snake(); // 뱀 초기설정

	Make_Star(); // 별생성
	move(); // 뱀의 움직임


	return 0;


}

void move(void) { // WASD 로 방향 입력받고 그 방향으로 쭉 이동
	int i;
	int ch = 'd'; // 처음엔 오른쪽으로 이동함
	char way;//WASD 이외의 값을 눌렀을 때를 대비해 ch의 값 저장해둠.


	while (1) {
		Sleep(SPEED);
		if (kbhit()) { // 입력 받기전까진 실행안됨
			ch = getch();
			getch();
		}


		if ((ch == 'd') || (ch == 'D')) { // D 입력
			way = 'd';
			if ((body[0].x == lenth - 2) || (mapXY[body[0].x + 2][body[0].y] == 1)) { // 벽에 닿거나 몸통에 닿으면 게임오버

				GAME_OVER();

			}
			else {


				Body_Movement();

				body[0].x = body[0].x + 2; // ○가 x=2만큼 잡아먹어서 +2
				body[0].y = body[0].y;
				mapXY[body[0].x][body[0].y] = 1; // 해당 x,y좌표에 1을 저장

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
				body[0].y = body[0].y + 1; // ○가 y=1 만큼 차지해서 +1
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
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, 10);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, 11);
	printf("■■■□□■■□■■■□■□□□□■□□□■■■");
	gotoxy(2, 12);
	printf("■■□■■□■□■■■□■□■■■■□■■□■■");
	gotoxy(2, 13);
	printf("■■□■■□■■□■□■■□□□□■□□□□■■");
	gotoxy(2, 14);
	printf("■■□■■□■■□■□■■□■■■■□■□■■■");
	gotoxy(2, 15);
	printf("■■■□□■■■■□■■■□□□□■□■■□■■");
	gotoxy(2, 16);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(2, 17);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(0, height + 2);
	printf("다시 플레이하려면 'R'을 누르세요\n");
	printf("게임을 종료하려면 'X'를 누르세요\n");


	ch = getch();
	getch();

	if ((ch == 'r') || (ch == 'R')) { // 'R' 입력시 3 초 후 main함수로 돌아가서 게임 다시시작, 'X' 입력시 게임 종료
		int SPEED = 0;
		int score = 0;
		int tail = 0;
		gotoxy(2, 9);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(2, 10);
		printf("■■■■■■■■□□□□□□□■■■■■■■■■");
		gotoxy(2, 11);
		printf("■■■■■■■□□■■■■■□□■■■■■■■");
		gotoxy(2, 12);
		printf("■■■■■■■■■■■■■□□□■■■■■■■■");
		gotoxy(2, 13);
		printf("■■■■■■■■■■□□□□□■■■■■■■■■");
		gotoxy(2, 14);
		printf("■■■■■■■■■■■■■□□□■■■■■■■■");
		gotoxy(2, 15);
		printf("■■■■■■■□□■■■■■□□■■■■■■■■");
		gotoxy(2, 16);
		printf("■■■■■■■■□□□□□□□■■■■■■■■■");
		gotoxy(2, 17);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
		Sleep(1000);
		//3 
		gotoxy(2, 9);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(2, 10);
		printf("■■■■■■■■■■□□□□■■■■■■■■■■");
		gotoxy(2, 11);
		printf("■■■■■■■■□□■■■□□■■■■■■■■■");
		gotoxy(2, 12);
		printf("■■■■■■■■□□■■■□□■■■■■■■■■");
		gotoxy(2, 13);
		printf("■■■■■■■■■■■■□□■■■■■■■■■■");
		gotoxy(2, 14);
		printf("■■■■■■■■■■□□■■■■■■■■■■■■");
		gotoxy(2, 15);
		printf("■■■■■■■■■□□■■■■■■■■■■■■■");
		gotoxy(2, 16);
		printf("■■■■■■■■□□□□□□□■■■■■■■■■");
		gotoxy(2, 17);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
		Sleep(1000);
		//2□□
		gotoxy(2, 9);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
		gotoxy(2, 10);
		printf("■■■■■■■■■■■□□■■■■■■■■■■■");
		gotoxy(2, 11);
		printf("■■■■■■■■■□□□□■■■■■■■■■■■");
		gotoxy(2, 12);
		printf("■■■■■■■■■■■□□■■■■■■■■■■■");
		gotoxy(2, 13);
		printf("■■■■■■■■■■■□□■■■■■■■■■■■");
		gotoxy(2, 14);
		printf("■■■■■■■■■■■□□■■■■■■■■■■■");
		gotoxy(2, 15);
		printf("■■■■■■■■■■■□□■■■■■■■■■■■");
		gotoxy(2, 16);
		printf("■■■■■■■■■□□□□□□■■■■■■■■■");
		gotoxy(2, 17);
		printf("■■■■■■■■■■■■■■■■■■■■■■■■");
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



void Eat_Star(int j) {// 별을 먹으면 몸통이 하나 늘어나고 속도 증가

	body[j].x = lenth + 6; // 이거 1, 1 로 두면 벽이 깨지던데 왜지
	body[j].y = height + 4;
	gotoxy(lenth + 10, 5);
	score += 100;
	printf("점수 :  %d 점", score);
	gotoxy(lenth + 10, 7);
	tail++;
	printf("몸통 :  %d 개", tail);
	gotoxy(lenth + 10, 9);
	if (SPEED > 60) {
		SPEED -= 10;
	}
	printf("속도 :  %d", SPEED);

}



void Make_Star() { //별 생성. 몸통과 안겹치게.
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

	printf("♥");
	setcolor(15, 0);


}



void Body_Movement(void) { // 몸통 움직임
	int i, j;

	for (i = 1; body[i].x; i++) {
	}

	//i는 몸통의 길이 +1이 됨
	body[i].x = body[i - 1].x;
	body[i].y = body[i - 1].y;
	gotoxy(body[i].x, body[i].y);
	printf("  "); // 마지막 몸통이 있던 자리 지움
	mapXY[body[i].x][body[i].y] = 0; // 마지막 몸통이 있던 좌표에 0 저장
	body[i].x = 0;
	body[i].y = 0;


	j = i - 1;
	for (j; j>0; j--) { // 몸통 한칸씩 이동
		body[j].x = body[j - 1].x;
		body[j].y = body[j - 1].y;
		mapXY[body[j].x][body[j].y] = 1; // 몸통이 있는 좌표에 1 저장
	}
}



void Print_Body(void) { // 몸통 출력
	int i;
	setcolor(2, 0);
	gotoxy(body[0].x, body[0].y);
	printf("●");
	for (i = 1; body[i].x; i++) {
		gotoxy(body[i].x, body[i].y);
		printf("○");
	}
	setcolor(15, 0);
}




void Start_Snake(void) { // 뱀 초기세팅. 몸통7개.


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
		printf("●");
		mapXY[body[0].x][body[0].y] = 1;
		gotoxy(body[i].x, body[i].y);
		printf("○");
		mapXY[body[i].x][body[i].y] = 1;
	}
	setcolor(15, 0);
}




void MAP(void) { // 지도생성
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

	gotoxy(lenth + 10, 5);
	printf("점수 :  %d 점", score);
	gotoxy(lenth + 10, 7);
	printf("몸통 :  %d 개", tail);
	gotoxy(lenth + 10, 9);
	printf("속도 :  %d", SPEED);



}





void gotoxy(int x, int y) {
	COORD Pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos); //SetConsoleCursorPosition 함수 호출은 필수
																	//WinCon.h 안에 들어있고, 이 헤더파일은 Windows.h에 들어있음
}

void removeCursor(void) //베낀 코드. 나중에 이해

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