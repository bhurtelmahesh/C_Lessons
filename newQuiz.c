#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void show_record();
void reset_score();
void help();
void edit_score(float, char[]);

int main()
{
    int countr, r, r1, count, i, n;
    float score;
    char choice;
    char playername[20];

mainhome:
    system("clear"); // Clear the console screen
    printf("\t\t\tC PROGRAM QUIZ GAME\n");
    printf("\n\t\t________________________________________");
    printf("\n\t\t\t   WELCOME ");
    printf("\n\t\t\t      to ");
    printf("\n\t\t\t   THE GAME ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t   一億円の質問！！！！！！    "); 
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t > Sキーを押してゲームを開始します");
    printf("\n\t\t > Vキーを押して最高得点を表示します");
    printf("\n\t\t > Rキーを押して得点をリセットします");
    printf("\n\t\t > Hキーを押してヘルプを表示します");
    printf("\n\t\t > Qキーを押して終了します");
    printf("\n\t\t________________________________________\n\n");
    choice = toupper((getchar()));

    if (choice == 'V')
    {
        show_record();
        goto mainhome;
    }
    else if (choice == 'H')
    {
        help();
        getchar();
        goto mainhome;
    }
    else if (choice == 'R')
    {
        reset_score();
        getchar();
        goto mainhome;
    }
    else if (choice == 'Q')
        exit(1);
    else if (choice == 'S')
    {
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tあなたの名前を登録してください：");
        getchar();
        fgets(playername, sizeof(playername), stdin);
        playername[strlen(playername) - 1] = '\0';

        system("clear");
        printf("\n ------------------  ようこそ %s さん、Cプログラムクイズゲームへ --------------------------", playername);
        printf("\n\n ここではプレイ前に知っておきたいいくつかのヒントがあります：");
        printf("\n -------------------------------------------------------------------------");
        printf("\n >> このクイズゲームにはウォームアップラウンドとチャレンジラウンドの2つのラウンドがあります");
        printf("\n >> ウォームアップラウンドでは、あなたの一般知識をテストするために合計3つの質問が出されます。少なくとも2つの正解を出すとゲームをプレイすることができます。");
        printf("\n    それ以外の場合、チャレンジラウンドには進めません。");
        printf("\n >> チャレンジラウンドでは、あなたのプログラミングスキルをテストするために合計10の質問が出されます。");
        printf("\n    これらの質問に答えるためにプログラミングの知識と経験が必要です。");
        printf("\n >> 各正解には1ポイントが与えられます。");
        printf("\n >> チャレンジラウンドで最大スコアを獲得することを目指してください！\n");
        printf("\n >> プレイするにはEnterキーを押してください！");
        if (toupper(getchar()) == '\n')
            goto home;
    }

home:
    system("clear");
    count = 0;
    for (i = 1; i <= 3; i++)
    {
        system("clear");
        r1 = i;
        switch (r1)
        {
        case 1:
            printf("\n\nWho is the Prime Minister of Japan?\n");
            printf("\nA. Shinzo Abe\t\tB. Yoshihide Suga\n");
            printf("\nC. Naoto Kan\t\tD. Junichiro Koizumi\n");
            if (toupper(getchar()) == 'B')
            {
                printf("\n\nCorrect!!!\n");
                count++;
                getchar();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is B\n");
                getchar();
                break;
            }

        case 2:
            printf("\n\n\nWhich is the capital city of Japan?\n");
            printf("\nA. Kyoto\t\tB. Hiroshima\n");
            printf("\nC. Osaka\t\tD. Tokyo\n");
            if (toupper(getchar()) == 'D')
            {
                printf("\n\nCorrect!!!\n");
                count++;
                getchar();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is D\n");
                getchar();
                break;
            }

        case 3:
            printf("\n\n\nWhat is the currency of Japan?\n");
            printf("\nA. Yen\t\tB. Dollar\n");
            printf("\nC. Euro\t\tD. Pound\n");
            if (toupper(getchar()) == 'A')
            {
                printf("\n\nCorrect!!!\n");
                count++;
                getchar();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is A\n");
                getchar();
                break;
            }
        }
    }
    score = (float)count;
    if (score >= 2)
    {
        printf("\n\n\nCongratulations!!! You are eligible to play the Game");
        printf("\n\n\nPress any key to Start the Game!!");
        getchar();
        goto game;
    }
    else
    {
        printf("\n\n\nSorry! You are not eligible to play the Game. Please try again...");
        getchar();
        goto mainhome;
    }
game:
    system("clear");
    count = 0;
    for (i = 1; i <= 10; i++)
    {
        system("clear");
        r = i;
        switch (r)
        {
        case 1:
            printf("\n\nWhat is the output of the following code?\n\n");
            printf("#include <stdio.h>\n\nint main()\n{\n\tint x = 5;\n\tint y = x++;\n\tprintf(\"%%d %%d\", x, y);\n\treturn 0;\n}");
            printf("\n\nA. 5 5\t\tB. 6 5\n");
            printf("\nC. 6 6\t\tD. 5 6\n");
            if (toupper(getchar()) == 'B')
            {
                printf("\n\nCorrect!!!\n");
                count++;
                getchar();
                break;
            }
            else
            {
                printf("\n\nWrong!!! The correct answer is B\n");
                getchar();
                break;
            }
        }

    }

    score = (float)count;
    system("clear");
    printf("\n\n\n\t\t**************** CONGRATULATIONS *****************");
    printf("\n\n\t\t       You scored %.2f points!", score);
    if (score > 5.0)
    {
        printf("\n\n\t\t You have demonstrated excellent programming knowledge.");
        printf("\n\t\t     Keep up the good work!");
    }
    else if (score > 3.0)
    {
        printf("\n\n\t\t    You have a decent programming knowledge.");
        printf("\n\t\t  Practice more to improve your skills.");
    }
    else
    {
        printf("\n\n\t\t     You need to work on your programming knowledge.");
        printf("\n\t\t  Study more and keep practicing.");
    }
    printf("\n\n\n\t\t***************************************************");
    printf("\n\n\t\t\t Thanks for playing the Game!");
    printf("\n\n\t\t***************************************************");
    printf("\n\n\n\nEnter 'Y' to save your score or any other key to exit: ");
    if (toupper(getchar()) == 'Y')
    {
        printf("\n\n\n\t\t\tEnter your name: ");
        getchar();
        fgets(playername, sizeof(playername), stdin);
        playername[strlen(playername) - 1] = '\0';
        edit_score(score, playername);
        getchar();
    }
    else
        exit(1);
    return 0;
}

void show_record()
{
    char name[20];
    float scr;
    FILE *f;
    f = fopen("score.txt", "r");
    fscanf(f, "%s%f", name, &scr);
    printf("\n\n\t\t*************************************************************");
    printf("\n\n\t\t %s has secured the Highest Score %.2f", name, scr);
    printf("\n\n\t\t*************************************************************");
    fclose(f);
    getchar();
}

void reset_score()
{
    FILE *f;
    f = fopen("score.txt", "w");
    fprintf(f, "%s %.2f", "no one", 0.0);
    fclose(f);
    printf("\n\n\t\t*************************************************************");
    printf("\n\n\t\t\t     Score reset successfully!!");
    printf("\n\n\t\t*************************************************************");
    getchar();
}

void help()
{
    system("clear");
    printf("\n\n\n\t\t\tHELP");
    printf("\n\n----------------------------------------------------------------------------");
    printf("\n >> このゲームは一億円の質問（Become a millionaire）のクイズゲームです。");
    printf("\n >> ゲームを開始するためにSキーを押してください。");
    printf("\n >> ウォームアップラウンドでは、合計3つの質問が出されます。少なくとも2つの正解が必要です。");
    printf("\n    そうでない場合、ゲームは終了されます。");
    printf("\n >> チャレンジラウンドでは、合計10のプログラミング質問が出されます。");
    printf("\n    これらの質問に答えるためにプログラミングの知識が必要です。");
    printf("\n >> 各正解には1ポイントが与えられます。");
    printf("\n >> チャレンジラウンドで最高スコアを獲得しましょう！");
    printf("\n >> Enterキーを押すと質問が表示されます。答えを選んだらEnterキーを押してください。");
    printf("\n >> ゲームが終了したら、スコアが表示されます。スコアを保存する場合はYキーを押してください。");
    printf("\n >> スコアをリセットするにはRキーを押してください。");
    printf("\n >> 最高スコアを表示するにはVキーを押してください。");
    printf("\n >> ヘルプを表示するにはHキーを押してください。");
    printf("\n >> ゲームを終了するにはQキーを押してください。");
    printf("\n----------------------------------------------------------------------------");
    printf("\n\n\n Press any key to continue...");
    getchar();
}

void edit_score(float score, char plnm[20])
{
    system("clear");
    float sc;
    char nm[20];
    FILE *f;
    f = fopen("score.txt", "r");
    fscanf(f, "%s%f", nm, &sc);
    if (score >= sc)
    {
        sc = score;
        fclose(f);
        f = fopen("score.txt", "w");
        fprintf(f, "%s\n%.2f", plnm, sc);
        fclose(f);
    }
}
