// 시계만들기
// cmd에 #을 이용한 7세그먼트를 그려서 출력
// github에 푸시했는데 글자가 깨져서 저장고급옵션에서 인코딩 방식을 utf-8로 변경해 주었다.
// fnd문자열로 1에 해당하는 seg를 출력했다.
// ttl7447함수 생성
// ttl7490함수 생성

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

// ttl7447의 역할은 4비트의 2진수값을 받아 fnd배열7자리 숫자를 반환한다.
void ttl7447(char input[4], char output[7]) 
{
    int i;
    char num = 0;
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
    for (i = 0; i < 4; i++)  //input으로 받은 4비트의 값으로
        num |= (input[i] << i); // 비트연산으로 10진수 값을 만들어
    for (i = 0; i < 7; i++) 
        output[i] = fnd[num][i]; // 해당 10진수의 7자리 배열을 fnd에 넣어 반환한다
}


// ttl7490의 역할은 clk이 0일때 정수를 반환한다.
void ttl7490() {

}

// main에서 반복문을 돌려 0부터 9까지의 숫자를 4비트의 2진수값으로 ttl7447을 호출한다.
int main(void) {
    int i,j;
    char num[4], fnd[7];
    for (i = 0; i < 10; i++) { //반복문으로 0부터 9까지의 정수를 뽑고
        for (j = 0; j < 4; j++) { //비트연산을 통해 num배열에 4비트값을 넣는다.
            if ((i & (1 << j)) == 0)
                num[j] = 0;
            else
                num[j] = 1;
        }
        ttl7447(num, fnd);
        dispFND(fnd);
    }
    return 0;
}