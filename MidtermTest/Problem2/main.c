#include <windows.h>
#include <stdio.h>
#include <string.h>

// ANSI 이스케이프 코드 활성화 함수
void EnableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// 커서 위치 이동 함수
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1);
}

// 윈도우를 그리는 함수
void drawConsoleWindow(int startX, int startY, int width, int height, const char* title, int color)
{
    // 1. 창 테두리 및 내부
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            gotoxy(startX + x, startY + y);

            if (y == 0 || y == height - 1) {
                printf("\033[48;5;%dm\033[30m-\033[0m", color);
            }
            else if (x == 0 || x == width - 1) {
                printf("\033[48;5;%dm\033[30m|\033[0m", color);
            }
            else {
                printf("\033[48;5;%dm \033[0m", color);
            }
        }
    }

    // 2. X 버튼
    gotoxy(startX + width - 3, startY + 1);
    printf("\033[48;5;1m\033[97mX\033[0m");

    // 3. 제목 (왼쪽으로 5칸, 위로 4칸)
    int centerX = (width - (int)strlen(title)) / 2;
    int titleX = startX + centerX - 5;
    int titleY = startY + height / 2 - 4;  // 한 칸 더 위로
    gotoxy(titleX, titleY);
    printf("\033[48;5;%dm\033[30m%s\033[0m", color, title);

    // 4. 커서를 창 밑으로 보내기 (겹침 방지)
    gotoxy(0, startY + height + 0);
}

int main()
{
    EnableANSI();

    drawConsoleWindow(5, 1, 30, 10, "나의 멋진 윈도우", 11);

    return 0;
}


