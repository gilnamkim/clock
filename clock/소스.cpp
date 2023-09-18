// 시계만들기
// cmd에 #을 이용한 7세그먼트를 그려서 출력
// github에 푸시했는데 글자가 깨져서 저장고급옵션에서 인코딩 방식을 utf-8로 변경해 주었다.
// fnd문자열로 1에 해당하는 seg를 출력했다.
// ttl7447함수 생성
// ttl7490함수 생성

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

#define MAX_X   40
#define MAX_Y   5
#define MODE_CLOCK      0
#define MODE_ALARM      1
#define MODE_ALARM_SET  2

char screen[MAX_Y][MAX_X];
char al_en = 0;

void dispScreen(void)
{
    int i, j;
    for (i = 0; i < MAX_Y; i++) {
        for (j = 0; j < MAX_X; j++) {
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
}
void dispFND(char x, char y, char fnd[])
{
    char seg[5][5];
    char ch = '#';
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            seg[i][j] = ' ';
    if (al_en == 1) ch = '@';
    if (fnd[0] == 1) for (i = 0; i < 5; i++) seg[0][i] = ch;
    if (fnd[1] == 1) for (i = 0; i < 3; i++) seg[i][4] = ch;
    if (fnd[2] == 1) for (i = 0; i < 3; i++) seg[i + 2][4] = ch;
    if (fnd[3] == 1) for (i = 0; i < 5; i++) seg[4][i] = ch;
    if (fnd[4] == 1) for (i = 0; i < 3; i++) seg[i + 2][0] = ch;
    if (fnd[5] == 1) for (i = 0; i < 3; i++) seg[i][0] = ch;
    if (fnd[6] == 1) for (i = 0; i < 5; i++) seg[2][i] = ch;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            screen[y + i][x + j] = seg[i][j];
        }
    }
}
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
    for (i = 0; i < 4; i++)
        num |= (input[i] << i);
    for (i = 0; i < 7; i++) output[i] = fnd[num][i];
}
void ttl7490(char dev, char clk, char r0, char r1, char output[])
{
    static char oldclk[6] = { 0, }, num[6] = { 0, };
    int i;
    if (r0 == 1 && r1 == 1) {
        num[dev] = 0;
        for (i = 0; i < 4; i++)
            num[dev] |= (output[i] << i);
    }
    else if (r0 == 1 && r1 == 0) num[dev] = 0;
    else if (r0 == 0 && r1 == 1) num[dev] = 1;
    else if (r0 == 0 && r1 == 0) {
        if (oldclk[dev] == 1 && clk == 0) {
            if (++num[dev] == 10) num[dev] = 0;
        }
        oldclk[dev] = clk;
    }
    for (i = 0; i < 4; i++)
        output[i] = ((num[dev] >> i) & 0x01);
}
void cnvt(char num, char output[])
{
    int i;
    for (i = 0; i < 4; i++)
        output[i] = (num >> i) & 0x01;
}
char cnvt1(char num[])
{
    int i;
    char val = 0;
    for (i = 0; i < 4; i++)
        val |= (num[i] << i);
    return val;
}
void dispAlarm(char hour, char min)
{
    char num[4], fnd[7];
    cnvt(hour / 10, num);
    ttl7447(num, fnd);
    dispFND(0, 0, fnd);
    cnvt(hour % 10, num);
    ttl7447(num, fnd);
    dispFND(6, 0, fnd);
    cnvt(min / 10, num);
    ttl7447(num, fnd);
    dispFND(14, 0, fnd);
    cnvt(min % 10, num);
    ttl7447(num, fnd);
    dispFND(20, 0, fnd);
    cnvt(0, num);
    ttl7447(num, fnd);
    dispFND(28, 0, fnd);
    dispFND(34, 0, fnd);
    dispScreen();
}

int main(void) {
    int i, j, cnt = 0;
    char num[4], num1[4], fnd[7], ch;
    char mode = MODE_CLOCK;
    char al_hour = 12, al_min = 0;
    char hour, min, sec;
    char order, alarm_call = 0;
    time_t timer = time(NULL);
    struct tm* t = localtime(&timer);

    cnvt(t->tm_sec % 10, num);
    ttl7490(0, 0, 1, 1, num);
    cnvt(t->tm_sec / 10, num);
    ttl7490(1, 0, 1, 1, num);
    cnvt(t->tm_min % 10, num);
    ttl7490(2, 0, 1, 1, num);
    cnvt(t->tm_min / 10, num);
    ttl7490(3, 0, 1, 1, num);
    cnvt(t->tm_hour % 10, num);
    ttl7490(4, 0, 1, 1, num);
    cnvt(t->tm_hour / 10, num);
    ttl7490(5, 0, 1, 1, num);

    for (i = 0; i < MAX_Y; i++)
        for (j = 0; j < MAX_X; j++)
            screen[i][j] = ' ';
    i = 0;

    for (;;) {
        if (_kbhit()) {
            ch = _getch();
            if (ch == ' ') {
                mode = MODE_ALARM_SET;
                order = 0;
                system("cls");
                dispAlarm(al_hour, al_min);
            }
            else if (ch == '\r') {
                if (mode == MODE_ALARM_SET)
                    mode = MODE_CLOCK;
            }
            else if (ch == 'a') {
                if (al_en == 0) al_en = 1;
                else al_en = 0;
            }
            else if (ch == 's') {
                alarm_call = 0;
            }
            else if (mode == MODE_ALARM_SET) {
                if (order == 0)
                    al_hour = (ch - '0') * 10;
                else if (order == 1)
                    al_hour += (ch - '0');
                else if (order == 2)
                    al_min = (ch - '0') * 10;
                else if (order == 3)
                    al_min += (ch - '0');
                if (++order == 4) order = 0;
                system("cls");
                dispAlarm(al_hour, al_min);
            }
        }
        if (++cnt == 5) {
            i++;
            ttl7490(0, i % 2, 0, 0, num);

            if (i % 2 == 0) {
                ttl7447(num, fnd);
                dispFND(34, 0, fnd);
                sec = cnvt1(num);
                ttl7490(1, num[3], 0, 0, num);
                if (num[2] == 1 && num[1] == 1)
                    ttl7490(1, num[3], 1, 0, num);
                ttl7447(num, fnd);
                dispFND(28, 0, fnd);
                sec += cnvt1(num) * 10;
                ttl7490(2, num[2], 0, 0, num);
                ttl7447(num, fnd);
                dispFND(20, 0, fnd);
                min = cnvt1(num);
                ttl7490(3, num[3], 0, 0, num);
                if (num[2] == 1 && num[1] == 1)
                    ttl7490(3, num[3], 1, 0, num);
                ttl7447(num, fnd);
                dispFND(14, 0, fnd);
                min += cnvt1(num) * 10;
                ttl7490(4, num[2], 0, 0, num);
                ttl7447(num, fnd);
                dispFND(6, 0, fnd);
                hour = cnvt1(num);
                ttl7490(5, num[3], 0, 0, num1);
                if (num[2] == 1 && num[1] == 0 && num[0] == 0 && num1[1] == 1) {
                    ttl7490(4, num[2], 1, 0, num);
                    ttl7447(num, fnd);
                    dispFND(6, 0, fnd);
                    ttl7490(5, num[3], 1, 0, num1);
                }
                ttl7447(num1, fnd);
                dispFND(0, 0, fnd);
                hour += cnvt1(num1) * 10;

                if (mode == MODE_CLOCK) {
                    system("cls");
                    dispScreen();
                    printf("\n\n");
                }
            }
            cnt = 0;
            if (al_en == 1) {
                if (sec == 0 && min == al_min && hour == al_hour) {
                    alarm_call = 1;
                }
                if (alarm_call == 1)
                    printf("%c", 7);
            }
        }
        Sleep(100);
    }
    return 0;
}
