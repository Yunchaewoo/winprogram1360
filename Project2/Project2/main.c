#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // _kbhit(), _getch() 함수 사용을 위해


#define SCREEN_WIDTH 40  // 화면 너비
#define INIT_POSITION 20  // *의 초기 위치 (중앙)

// 화면을 지우는 함수 (반환값 없음)
int showmenu();
void clearScreen() {
    system("cls");  // 콘솔 화면 지우기
}

// 화면을 그리는 함수 (반환값 없음)
void drawScreen(int position) {
    clearScreen();  // 화면 지우기

    // 화면의 각 위치에 '*'을 출력
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (i == position) {
            printf("0");  // '*'을 현재 위치에 출력
        }
        else {
            printf("_");  // 그 외에는 공백
        }
    }
    printf("\n");
}

int main() {
    int position = INIT_POSITION;  // '*'의 초기 위치
    char key;

    // 게임 루프
    while (1) {
        drawScreen(position);  // 화면 그리기

        // 키 입력 받기 (사용자가 키를 누를 때까지 대기)
        if (_kbhit()) {
            key = _getch();  // 키 입력 받기

            // 'A' 키로 왼쪽으로 이동
            if (key == 'a' || key == 'A') {
                if (position > 0) {
                    position--;  // 위치를 왼쪽으로
                }
            }
            // 'D' 키로 오른쪽으로 이동
            else if (key == 'd' || key == 'D') {
                if (position < SCREEN_WIDTH - 1) {
                    position++;  // 위치를 오른쪽으로
                }
            }
            // 'Q' 키를 누르면 게임 종료
            else if (key == 'q' || key == 'Q') {
                break;  // 게임 종료
            }
        }
    }

    return 0;  // main 함수는 항상 int를 반환해야 하므로 0 반환
}