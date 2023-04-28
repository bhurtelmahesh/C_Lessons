#include <stdio.h>
#include <ctype.h>

int main(){

    char questions[][100] = {"問１．英語で\"事実\"は何と言いますか。",
                             "問２．1日は何秒になりますか。",
                             "問３．\"凡例\"の読み方は何ですか。",
                             "問４．\"しょうわじだい\"の漢字はどれですか。",
                             "問５．\"疾病\"の読み方は何ですか。"};

    char options[][100] = {"A. Fact", "B．Truth", "C．Subject", "D．Matter",
                           "A. 12460", "B．3600", "C．36000", "D．86400",
                           "A. ぼんれつ", "B．ぼんれい", "C．はんれい", "D．ばんれい",
                           "A. 昭和寺大", "B．昭和時代", "C．小話時代", "D．宗和時代",
                           "A. しつびょう", "B．しっぺい", "C．しつぺい", "D．しっぴょう"};
    char answers[5] = {'A','D','C','B','B'};

    int noOfQuestions = sizeof(questions)/sizeof(questions[0]);

    char guess;
    int score = 0;

    printf("QUIZ GAME!\n");

    for(int i = 0; i < noOfQuestions; i++){
        printf("%s \n", questions[i]);

        for(int j = i * 4; j < (i * 4) + 4; j++){
            printf("%s\n", options[j]);
        }

    printf("A、B、C、Dの中から最も正しい答えを選んでください：　");
    scanf("%c", &guess);
    getchar();
    guess = toupper(guess);

    if(guess == answers[i]){
        printf("正解！\n");
        score++;
    } else {
        printf("不正解！\n");
        
    }
    }
    printf("****************\n");
    printf("\n");
    printf("最終スコア：%d/%d\n",score, noOfQuestions);
    printf("\n");
    printf("****************\n");

    return 0;
}