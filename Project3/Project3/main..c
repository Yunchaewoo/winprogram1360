#include <windows.h>
#include <stdio.h>

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
    printf("\033[%d;%dH", y + 1, x + 1); // ANSI 이스케이프 코드 방식으로 커서 이동
}

// 창의 속성을 저장하는 구조체
typedef struct {
    int width;      // 가로 크기
    int height;     // 세로 크기
    int x;          // X 좌표
    int y;          // Y 좌표
    char borderColor[10]; // 테두리 색상 (ANSI 코드)
    char bgColor[10];     // 내부 배경 색상 (ANSI 코드)
    char name[100];  // 창 이름
} Window;

// 콘솔 배경을 초록색으로 채우는 함수 (printf 방식)
void FillBackgroundWithGreen(int width, int height)
{
    printf("\033[42m"); // 초록색 배경 설정

    for (int y = 0; y < height; y++)
    {
        gotoxy(0, y);
        for (int x = 0; x < width; x++)
        {
            printf(" "); // 공백 출력하여 배경 적용
        }
    }

    printf("\033[0m"); // 색상 초기화
}

// 네모 창을 그리는 함수
void DrawWindow(Window win)
{
    // 테두리 색상 적용
    printf("%s", win.borderColor);

    // 윗부분 그리기
    for (int x = 0; x < win.width; x++) {
        gotoxy(x + win.x, win.y);
        printf("#");
    }

    // 아랫부분 그리기
    for (int x = 0; x < win.width; x++) {
        gotoxy(x + win.x, win.y + win.height - 1);
        printf("#");
    }

    // 왼쪽과 오른쪽 경계 그리기
    for (int y = 1; y < win.height - 1; y++) {
        gotoxy(win.x, win.y + y);
        printf("#");
        gotoxy(win.x + win.width - 1, win.y + y);
        printf("#");
    }

    // 내부 색상 적용
    printf("%s", win.bgColor);
    for (int y = 1; y < win.height - 1; y++) {
        gotoxy(win.x + 1, win.y + y);
        for (int x = 1; x < win.width - 1; x++) {
            printf(" "); // 내부를 채움
        }
    }
    printf("\033[0m"); // 색상 초기화
}

// 콘솔 크기를 감지하고 화면을 다시 그리는 함수
void UpdateScreen(Window windows[], int windowCount)
{
    // 현재 콘솔 크기 가져오기
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int prevWidth = 0, prevHeight = 0;

    while (1) {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // 콘솔 크기가 변경되었는지 확인
        if (consoleWidth != prevWidth || consoleHeight != prevHeight) {
            system("cls"); // 화면 지우기

            // 초록색 배경 채우기
            FillBackgroundWithGreen(consoleWidth, consoleHeight);

            // 저장된 창 다시 그리기
            for (int i = 0; i < windowCount; i++) {
                DrawWindow(windows[i]);
            }

            // 값 업데이트
            prevWidth = consoleWidth;
            prevHeight = consoleHeight;
        }

        Sleep(100); // CPU 사용량 절약을 위해 잠시 대기
    }
}

int main()
{
    // ANSI 이스케이프 코드 활성화 (Windows에서 필요)
    EnableANSI();

    // 네모 창 설정 (고정된 크기와 위치)
    Window windows[] = {
        { 20, 7, 10, 3, "\033[37m", "\033[44m", "Window1" },
        { 15, 6, 15, 5, "\033[33m", "\033[41m", "Window2" }
    };

    // 콘솔 크기를 감지하며 화면 갱신
    UpdateScreen(windows, sizeof(windows) / sizeof(windows[0]));

    return 0;
}