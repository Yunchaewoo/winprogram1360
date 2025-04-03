#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // _kbhit(), _getch() �Լ� ����� ����


#define SCREEN_WIDTH 40  // ȭ�� �ʺ�
#define INIT_POSITION 20  // *�� �ʱ� ��ġ (�߾�)

// ȭ���� ����� �Լ� (��ȯ�� ����)
int showmenu();
void clearScreen() {
    system("cls");  // �ܼ� ȭ�� �����
}

// ȭ���� �׸��� �Լ� (��ȯ�� ����)
void drawScreen(int position) {
    clearScreen();  // ȭ�� �����

    // ȭ���� �� ��ġ�� '*'�� ���
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        if (i == position) {
            printf("0");  // '*'�� ���� ��ġ�� ���
        }
        else {
            printf("_");  // �� �ܿ��� ����
        }
    }
    printf("\n");
}

int main() {
    int position = INIT_POSITION;  // '*'�� �ʱ� ��ġ
    char key;

    // ���� ����
    while (1) {
        drawScreen(position);  // ȭ�� �׸���

        // Ű �Է� �ޱ� (����ڰ� Ű�� ���� ������ ���)
        if (_kbhit()) {
            key = _getch();  // Ű �Է� �ޱ�

            // 'A' Ű�� �������� �̵�
            if (key == 'a' || key == 'A') {
                if (position > 0) {
                    position--;  // ��ġ�� ��������
                }
            }
            // 'D' Ű�� ���������� �̵�
            else if (key == 'd' || key == 'D') {
                if (position < SCREEN_WIDTH - 1) {
                    position++;  // ��ġ�� ����������
                }
            }
            // 'Q' Ű�� ������ ���� ����
            else if (key == 'q' || key == 'Q') {
                break;  // ���� ����
            }
        }
    }

    return 0;  // main �Լ��� �׻� int�� ��ȯ�ؾ� �ϹǷ� 0 ��ȯ
}