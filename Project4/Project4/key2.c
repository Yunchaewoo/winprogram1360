#include <windows.h>
#include <stdio.h>

int main()
{
    while (1)
    {
        // F2 Ű�� ���ȴ��� Ȯ�� (Key Down)
        if (GetAsyncKeyState(VK_F2) & 0x8000)
        {
            printf("F2 Ű ���� (Key Down)\n");
        }

        // S Ű�� ���ȴ��� Ȯ�� (Key Down)
        if (GetAsyncKeyState('S') & 0x8000)
        {
            printf("S Ű ���� (Key Down)\n");
        }

        // W Ű�� ���������� Ȯ�� (Key Up)
        if (!(GetAsyncKeyState('W') & 0x8000))
        {
            printf("W Ű ������ (Key Up)\n");
        }

        // S Ű�� ���������� Ȯ�� (Key Up)
        if (!(GetAsyncKeyState('S') & 0x8000))
        {
            printf("S Ű ������ (Key Up)\n");
        }

        // ���α׷� ���� ����
        if (GetAsyncKeyState('Q') & 0x8000)
        {
            printf("���� ����\n");
            break;  // Q Ű�� ������ ����
        }

        // ��� ��� (CPU ��� ����ȭ)
        Sleep(10);
    }

    return 0;
}