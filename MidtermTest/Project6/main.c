#include <stdio.h>

// 5. PassOrFail 함수 정의
int PassOrFail(int score) {
    if (score >= 50) {
        return 1;  // 50점 이상이면 합격
    }
    else {
        return 0;  // 50점 미만이면 불합격
    }
}

// 6. main 함수
int main() {
    int myScore = 1; // <- 여기에 본인의 예상 점수를 넣으세요
    int result = PassOrFail(myScore);

    if (result == 1) {
        printf("재시험 없습니다!\n");
    }
    else {
        printf("우리는 망했다… 재시험이다…\n");
    }

    return 0;
}