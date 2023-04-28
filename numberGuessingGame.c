#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main () {
    const int MIN = 1000;
    const int MAX = 9999;
    int guess;
    int guesses = 0;
    int answer;

    srand(time(0)); //use the current time as seed 

    answer = (rand() % MAX) + MIN; // generate a random number between min and max

    do{
    printf("%d と %dの間の数値を想像して下さい: ",MIN, MAX);
    scanf("%d", &guess);
    if(guess < answer){
        printf("ヒント：%d より大きいです! \n", guess);
    }else if(guess > answer) {
        printf("ヒント：%d より小さいです! \n", guess);
    }else{
        printf("**********\n");
        printf("当たりです! \n");
    }
    guesses++;
    }while(guess != answer);
    printf("正解: %d\n", answer);
    printf("トライ: %d 回\n", guesses);
    printf("**********\n");

    return 0;
}