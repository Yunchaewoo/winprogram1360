#include <GLFW/glfw3.h>
#include <cmath>

#pragma comment(lib, "Opengl32.lib")

const float PI = 3.14159265358979323846;

// 직선을 그리기 위한 함수
void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawHorizontalLine(float startX, float endX, float y) {
    drawLine(startX, y, endX, y);
}

// 다각형을 그리기 위한 함수
void drawPolygon(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// 원을 그리기 위한 함수
void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * PI / 180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// 시계의 시간을 나타내는 선들을 그리는 함수
void drawClock() {
    // 각 시간대에 해당하는 선을 그립니다.
    for (int i = 0; i < 12; i++) {
        float angle = i * 30.0f * PI / 180.0f; // 각도 계산 (12시 기준)

        // 원의 반지름이 0.8일 때, 선의 길이는 원의 3/1로 설정 (0.8 * 1/3 = 0.267)
        float length = 0.267f;

        // 선의 시작점을 원의 테두리로 이동 (원 밖으로 나가는 것이 아니라 원 안쪽으로 향하게 하기 위해)
        float x1 = 0.8f * cos(angle);
        float y1 = 0.8f * sin(angle);

        // 선의 끝점은 원 안쪽으로 향하게 (선이 원 안쪽으로 향하도록 길이를 조정)
        float x2 = (0.8f - length) * cos(angle);  // 원의 테두리보다 0.267만큼 길이를 줄임
        float y2 = (0.8f - length) * sin(angle);

        drawLine(x1, y1, x2, y2);
    }
}

// 시침과 분침을 그리는 함수
void drawHands() {
    // 시침 (짧은 선, 원의 2/3 크기)
    float hourLength = 0.5f;  // 시침 길이는 0.5 (원 크기의 2/3)

    // 시침은 11시와 12시 사이를 향함 (330도)
    float hourAngle = 330.0f * PI / 180.0f;  // 11시와 12시 사이의 각도 (330도)

    float hourX1 = 0.0f;
    float hourY1 = 0.0f;
    float hourX2 = hourLength * cos(hourAngle);
    float hourY2 = hourLength * sin(hourAngle);
    drawLine(hourX1, hourY1, hourX2, hourY2);

    // 분침 (긴 선, 원의 3/4 크기)
    float minuteLength = 0.6f;  // 분침 길이는 0.6 (원 크기의 3/4)

    // 분침은 1시와 2시 사이를 향함 (45도)
    float minuteAngle = 45.0f * PI / 180.0f;  // 1시와 2시 사이의 각도 (45도)

    float minuteX1 = 0.0f;
    float minuteY1 = 0.0f;
    float minuteX2 = minuteLength * cos(minuteAngle);
    float minuteY2 = minuteLength * sin(minuteAngle);
    drawLine(minuteX1, minuteY1, minuteX2, minuteY2);
}

// 초침을 그리는 함수
void drawSecondHand() {
    // 초침 (가장 긴 선, 원의 3/4 크기)
    float secondLength = 0.4f;  // 초침 길이는 0.4 (원 크기의 1/2보다 약간 짧음)

    // 초침은 8시와 9시 사이를 향함 (240도)
    float secondAngle = 240.0f * PI / 180.0f;  // 8시와 9시 사이의 각도 (240도)

    float secondX1 = 0.0f;
    float secondY1 = 0.0f;
    float secondX2 = secondLength * cos(secondAngle);
    float secondY2 = secondLength * sin(secondAngle);
    drawLine(secondX1, secondY1, secondX2, secondY2);
}

// 시침, 분침, 초침 끝에 삼각형을 추가하는 함수
void addArrowhead(float x, float y, float angle, float length) {
    // 삼각형의 크기 (화살촉 부분)
    float arrowSize = 0.05f;

    // 삼각형의 3개의 꼭짓점 계산
    float x1 = x + length * cos(angle);
    float y1 = y + length * sin(angle);

    float x2 = x1 - arrowSize * cos(angle - PI / 6);
    float y2 = y1 - arrowSize * sin(angle - PI / 6);

    float x3 = x1 - arrowSize * cos(angle + PI / 6);
    float y3 = y1 - arrowSize * sin(angle + PI / 6);

    // 삼각형을 그립니다.
    drawPolygon(x1, y1, x2, y2, x3, y3);
}

// [추가] drawLine 함수로 세로 긴 직사각형을 그리는 함수
void drawRectangle(float x, float y, float width, float height) {
    float halfWidth = width / 2.0f;
    float halfHeight = height / 3.0f;

    float left = x - halfWidth;
    float right = x + halfWidth;
    float top = y + halfHeight;
    float bottom = y - halfHeight;

    // 좌측 세로선
    drawLine(left, bottom, left, top);

    // 우측 세로선
    drawLine(right, bottom, right, top);

    // 아래 가로선
    drawLine(left, bottom, right, bottom);

    // 위 가로선
    drawLine(left, top, right, top);
}

int main(void) {
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Clock with Polygon Hands and Rectangles", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 2D 직교 투영을 설정하면서 비율을 동일하게 유지하기 위해 좌표 범위를 -1.0 ~ 1.0으로 설정
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 좌표계를 동일하게 맞춰줍니다.

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        // 시계의 원을 그리기 (반지름: 0.8)
        drawCircle(0.8f);

        // 시계의 각 시간을 나타내는 선들을 그리기
        drawClock();

        // [추가] 세로로 긴 직사각형 6개 그리기
        float startX = -0.25f;  // 시작 x 위치
        float spacing = 0.1f;  // 직사각형 간 간격
        float rectWidth = 0.1f;
        float rectHeight = 0.4f;
        for (int i = 0; i < 6; ++i) {
            float x = startX + i * spacing;
            drawRectangle(x, -0.3f, rectWidth, rectHeight);  // y 위치는 -0.9f 고정
        }

        drawHorizontalLine(-0.3f, 0.3f, -0.3f);

        // 시침과 분침을 그리기
        drawHands();

        // 초침을 그리기
        drawSecondHand();

        // 시침, 분침, 초침 끝에 삼각형을 추가하기
        addArrowhead(0.0f, 0.0f, 330.0f * PI / 180.0f, 0.5f);  // 시침 끝에 삼각형
        addArrowhead(0.0f, 0.0f, 45.0f * PI / 180.0f, 0.6f);   // 분침 끝에 삼각형
        addArrowhead(0.0f, 0.0f, 240.0f * PI / 180.0f, 0.4f);  // 초침 끝에 삼각형

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}











