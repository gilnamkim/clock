// 시계만들기
// cmd에 #을 이용한 7세그먼트를 그려서 출력
// github에 푸시했는데 글자가 깨져서 저장고급옵션에서 인코딩 방식을 utf-8로 변경해 주었다.
// fnd문자열로 1에 해당하는 seg를 출력했다.
#include <stdio.h>

void dispFND(char fnd[])
{
    char seg[5][5];
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            seg[i][j] = ' ';
    if (fnd[0] == 1) for (i = 0; i < 5; i++) seg[0][i] = '#';
    if (fnd[1] == 1) for (i = 0; i < 3; i++) seg[i][4] = '#';
    if (fnd[2] == 1) for (i = 0; i < 3; i++) seg[i + 2][4] = '#';
    if (fnd[3] == 1) for (i = 0; i < 5; i++) seg[4][i] = '#';
    if (fnd[4] == 1) for (i = 0; i < 3; i++) seg[i + 2][0] = '#';
    if (fnd[5] == 1) for (i = 0; i < 3; i++) seg[i][0] = '#';
    if (fnd[6] == 1) for (i = 0; i < 5; i++) seg[2][i] = '#';
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c", seg[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
int main(void) {
    int i;
    char fnd[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,0,0,1,1}  // 9
    };
    for (i = 0; i < 10; i++) {
        dispFND(fnd[i]);
    }
    return 0;
}