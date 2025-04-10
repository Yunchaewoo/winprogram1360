#include <windows.h>
#include <stdio.h>

int main() {
    char letter = 'O';
    POINT mousePos;
    int letterX = 10, letterY = 5;

    HWND consoleWnd = GetConsoleWindow();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 폰트 크기 안전하게 가져오기
    CONSOLE_FONT_INFO fontInfo;
    GetCurrentConsoleFont(hConsole, FALSE, &fontInfo);
    int fontWidth = fontInfo.dwFontSize.X > 0 ? fontInfo.dwFontSize.X : 8;
    int fontHeight = fontInfo.dwFontSize.Y > 0 ? fontInfo.dwFontSize.Y : 16;

    while (1) {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            printf("\n프로그램 종료\n");
            break;
        }

        GetCursorPos(&mousePos);
        ScreenToClient(consoleWnd, &mousePos);

        // 콘솔 좌표 보정 (커서 중심 기준)
        int mouseX = (mousePos.x + fontWidth / 2) / fontWidth;
        int mouseY = (mousePos.y + fontHeight / 2) / fontHeight;

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            letterX = mouseX;
            letterY = mouseY;
        }

        system("cls");
        printf("마우스를 누르고 있으면 알파벳 '%c'이 커서를 따라갑니다. (ESC로 종료)\n", letter);
        printf("현재 위치: (%d, %d)\n", letterX, letterY);
        SetConsoleCursorPosition(hConsole, (COORD) { (SHORT)letterX, (SHORT)letterY });
        printf("%c", letter);

        Sleep(10);
    }

    return 0;
}
