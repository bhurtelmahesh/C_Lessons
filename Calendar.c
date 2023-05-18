#include <stdio.h>
#include <string.h>

// グローバル変数
int startDay; // 月の最初の曜日
int month, year, numDays;


// 関数のプロトタイプ宣言
int isLeapYear(int year);
int getStartDay(int month, int year);
int getNumDays(int month, int year);
void displayCalendar(int month, int year);
void printHeader();

int main() {
    int choice;

    printf("\n\n何を表示しますか？:\n");
    printf("1. 月間カレンダー\n");
    printf("2. 年間カレンダー\n");
    printf("選択してください (1-2):\t");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("月を入力してください (1-12):\t");
        scanf("%d", &month);
        printf("年を入力してください:\t");
        scanf("%d", &year);
        printHeader();
        displayCalendar(month, year);

    } else if (choice == 2) {
        printf("年を入力してください:\t");
        scanf("%d", &year);
        printHeader();

        for (month = 1; month <= 12; month++) {
            displayCalendar(month, year);
        }
    }

    return 0;
}

// 閏年かどうかをチェックする
int isLeapYear(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        return 1;
    }
    return 0;
}

// 月の最初の曜日を取得する
int getStartDay(int month, int year) {
    if (month < 3) {
        month += 12;
        year--;
    }
    int q = 1;
    int m = month;
    int k = year % 100;
    int j = year / 100;
    int h = (q + (13 * (m + 1)) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
    return (h + 6) % 7;
}

// 入力された月・年のカレンダーを出力する
void displayCalendar(int month, int year) {
    numDays = getNumDays(month, year);
    startDay = getStartDay(month, year);

    //月の配列
    char *months[] = {"1月", "2月", "3月", "4月", "5月", "6月", "7月", "8月", "9月", "10月", "11月", "12月"};

    // 曜日の配列
    char *daysOfWeek[] = {"日", "月", "火", "水", "木", "金", "土"};

    // 年と月を出力する
    printf("\n\n%d年 %s\n\n",year, months[month - 1]);

    // 曜日を出力する
    for (int i = 0; i < 7; i++) {
        printf("%s\t", daysOfWeek[i]);
    }
    printf("\n\n");

    // カレンダーを出力する
    int day = 1;
    for (int week = 0; week < 6; week++) {
        for (int weekday = 0; weekday < 7; weekday++) {
            if (week == 0 && weekday < startDay) {
                printf("\t");
            } else if (day <= numDays) {
                printf("%d\t", day);
                day++;
            }
        }
        printf("\n\n");
        if (day > numDays) {
            break;
        }
    }
    printf("\n");
}

// 月の日数をゲットする
int getNumDays(int month, int year) {
    int numDays;

    switch (month) {
        case 2:
            if (isLeapYear(year)) {
                numDays = 29;
            } else {
                numDays = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            numDays = 30;
            break;
        default:
            numDays = 31;
            break;
    }
    return numDays;
}

//ヘッダーでの飾り
void printHeader(){
    printf("\n\n＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
        printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
        printf("＝＝　　　　　　　　　　　　　　　　　　　　　　＝＝\n");
        printf("＝＝　　　　　　　　 カレンダー 　　　　　　　　＝＝\n");
        printf("＝＝　　　　　　　　　　　　　　　　　　　　　　＝＝\n");
        printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");
        printf("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝");
}
