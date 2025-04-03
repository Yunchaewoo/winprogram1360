#include <windows.h>
#include <stdio.h>

// ANSI �̽������� �ڵ� Ȱ��ȭ �Լ�
void EnableANSI()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

// Ŀ�� ��ġ �̵� �Լ�
void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y + 1, x + 1); // ANSI �̽������� �ڵ� ������� Ŀ�� �̵�
}

// â�� �Ӽ��� �����ϴ� ����ü
typedef struct {
    int width;      // ���� ũ��
    int height;     // ���� ũ��
    int x;          // X ��ǥ
    int y;          // Y ��ǥ
    char borderColor[10]; // �׵θ� ���� (ANSI �ڵ�)
    char bgColor[10];     // ���� ��� ���� (ANSI �ڵ�)
    char name[100];  // â �̸�
} Window;

// �ܼ� ����� �ʷϻ����� ä��� �Լ� (printf ���)
void FillBackgroundWithGreen(int width, int height)
{
    printf("\033[42m"); // �ʷϻ� ��� ����

    for (int y = 0; y < height; y++)
    {
        gotoxy(0, y);
        for (int x = 0; x < width; x++)
        {
            printf(" "); // ���� ����Ͽ� ��� ����
        }
    }

    printf("\033[0m"); // ���� �ʱ�ȭ
}

// �׸� â�� �׸��� �Լ�
void DrawWindow(Window win)
{
    // �׵θ� ���� ����
    printf("%s", win.borderColor);

    // ���κ� �׸���
    for (int x = 0; x < win.width; x++) {
        gotoxy(x + win.x, win.y);
        printf("#");
    }

    // �Ʒ��κ� �׸���
    for (int x = 0; x < win.width; x++) {
        gotoxy(x + win.x, win.y + win.height - 1);
        printf("#");
    }

    // ���ʰ� ������ ��� �׸���
    for (int y = 1; y < win.height - 1; y++) {
        gotoxy(win.x, win.y + y);
        printf("#");
        gotoxy(win.x + win.width - 1, win.y + y);
        printf("#");
    }

    // ���� ���� ����
    printf("%s", win.bgColor);
    for (int y = 1; y < win.height - 1; y++) {
        gotoxy(win.x + 1, win.y + y);
        for (int x = 1; x < win.width - 1; x++) {
            printf(" "); // ���θ� ä��
        }
    }
    printf("\033[0m"); // ���� �ʱ�ȭ
}

// �ܼ� ũ�⸦ �����ϰ� ȭ���� �ٽ� �׸��� �Լ�
void UpdateScreen(Window windows[], int windowCount)
{
    // ���� �ܼ� ũ�� ��������
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int prevWidth = 0, prevHeight = 0;

    while (1) {
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        // �ܼ� ũ�Ⱑ ����Ǿ����� Ȯ��
        if (consoleWidth != prevWidth || consoleHeight != prevHeight) {
            system("cls"); // ȭ�� �����

            // �ʷϻ� ��� ä���
            FillBackgroundWithGreen(consoleWidth, consoleHeight);

            // ����� â �ٽ� �׸���
            for (int i = 0; i < windowCount; i++) {
                DrawWindow(windows[i]);
            }

            // �� ������Ʈ
            prevWidth = consoleWidth;
            prevHeight = consoleHeight;
        }

        Sleep(100); // CPU ��뷮 ������ ���� ��� ���
    }
}

int main()
{
    // ANSI �̽������� �ڵ� Ȱ��ȭ (Windows���� �ʿ�)
    EnableANSI();

    // �׸� â ���� (������ ũ��� ��ġ)
    Window windows[] = {
        { 20, 7, 10, 3, "\033[37m", "\033[44m", "Window1" },
        { 15, 6, 15, 5, "\033[33m", "\033[41m", "Window2" }
    };

    // �ܼ� ũ�⸦ �����ϸ� ȭ�� ����
    UpdateScreen(windows, sizeof(windows) / sizeof(windows[0]));

    return 0;
}