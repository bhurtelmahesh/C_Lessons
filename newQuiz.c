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
    system("clear");
    printf("\t\t\tCプログラムクイズゲーム\n");
    printf("\n\t\t________________________________________");
    printf("\n\t\t\t   ザ・ゲーム");
    printf("\n\t\t\t      へ");
    printf("\n\t\t\t   ようこそ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t   一億円の質問！！！！！！    ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t > ゲームを開始するには、Sを押してください");
    printf("\n\t\t > 最高得点を確認するには、Vを押してください");
    printf("\n\t\t > スコアをリセットするには、Rを押してください");
    printf("\n\t\t > ヘルプを表示するには、Hを押してください");
    printf("\n\t\t > 終了するには、Qを押してください");
    printf("\n\t\t________________________________________\n\n");
    choice = toupper(getchar());

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
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tあなたの名前を入力してください：");
        getchar();
        fgets(playername, sizeof(playername), stdin);
        playername[strlen(playername) - 1] = '\0';

        system("clear");
        printf("\n ------------------  %sさん、Cプログラムクイズゲームへようこそ --------------------------", playername);
        printf("\n\n ゲームをプレイする前に知っておくべきいくつかのヒントがあります：");
        printf("\n -------------------------------------------------------------------------");
        printf("\n >> このクイズゲームは、ウォームアップラウンドとチャレンジラウンドの2つのラウンドで構成されています。");
        printf("\n >> ウォームアップラウンドでは、あなたの一般的な知識をテストするために3つの質問が出題されます。");
        printf("\n    チャレンジラウンドに進むためには、少なくとも2つの質問に正解する必要があります。");
        printf("\n >> チャレンジラウンドでは、プログラミングに関連する10の質問が出題されます。");
        printf("\n    正解数に基づいてスコアが計算されます。すべての質問に正解すると、最高得点が表示されます。");
        printf("\n >> プログラムを終了する場合は、いつでもQを押してください。");
        printf("\n >> 準備ができたら、ゲームを開始するためにEnterキーを押してください...");
        printf("\n -------------------------------------------------------------------------");
        getchar();

        // Warm-up round
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tウォームアップラウンド\n");
        printf("\n\t\t  3つの一般的な知識の質問に答えましょう");
        printf("\n\t\t________________________________________");
        printf("\n\t\t________________________________________");
        printf("\n\t\t > 正解の数に応じてスコアが計算されます");
        printf("\n\t\t > 最低2つの質問に正解する必要があります");
        printf("\n\t\t________________________________________\n\n");
        getchar();
        count = 0;

        for (i = 1; i <= 3; i++)
        {
            system("clear");
            r1 = i;
            switch (r1)
            {
            case 1:
                printf("\n\n1.Cプログラミング言語の開発者は誰ですか？");
                printf("\n\nA.Dennis Ritchie\t\tB.Bill Gates");
                printf("\n\nC.Steve Jobs\t\tD.Mark Zuckerberg");
                if (toupper(getchar()) == 'A')
                {
                    printf("\n\n正解！！！ ");
                    count++;
                    getchar();
                    break;
                }
                else
                {
                    printf("\n\n不正解！！！ 正解はDennis Ritchieです");
                    getchar();
                    break;
                }

            case 2:
                printf("\n\n\n2.C言語はどのようなタイプの言語ですか？");
                printf("\n\nA.コンパイラ言語\t\tB.インタプリタ言語");
                printf("\n\nC.アセンブリ言語\t\tD.マシン言語");
                if (toupper(getchar()) == 'A')
                {
                    printf("\n\n正解！！！");
                    count++;
                    getchar();
                    break;
                }
                else
                {
                    printf("\n\n不正解！！！ 正解はコンパイラ言語です");
                    getchar();
                    break;
                }

            case 3:
                printf("\n\n\n3.C言語のデータ型intのサイズは？");
                printf("\n\nA.2バイト\t\tB.4バイト");
                printf("\n\nC.8バイト\t\tD.データ型に依存");
                if (toupper(getchar()) == 'B')
                {
                    printf("\n\n正解！！！");
                    count++;
                    getchar();
                    break;
                }
                else
                {
                    printf("\n\n不正解！！！ 正解は4バイトです");
                    getchar();
                    break;
                }
            }
        }

        if (count >= 2)
        {
            goto test;
        }
        else
        {
            system("clear");
            printf("\n\n\n\n\n\n\n\n\n\n\t\t\tゲームオーバー");
            printf("\n\t\t\tYou didn't make it to the Challenge round.");
            printf("\n\t\t\tThank you for playing the game!");
            printf("\n\t\t\tYour final score is $0.00\n");
            printf("\t\t\tBetter luck next time %sさん", playername);
            edit_score(score, playername);
            goto mainhome;
        }

    test:
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tチャレンジラウンド！！！");
        printf("\n\t\t\tLet's test your programming knowledge");
        printf("\n\t\t\t________________________________________");
        printf("\n\t\t\t________________________________________");
        printf("\n\t\t\t > 10の質問に答える");
        printf("\n\t\t\t > すべての質問に正解すると最高得点が表示されます");
        printf("\n\t\t\t________________________________________");

        getchar();
        countr = 0;
        for (i = 1; i <= 10; i++)
        {
            system("clear");
            r = i;

            switch (r)
            {
            case 1:
                printf("\n\n1. C言語でのコメントの始まりの記号は？");
                printf("\n\nA. //\t\tB. /*");
                printf("\n\nC. #\t\tD. --");
                if (toupper(getchar()) == 'B')
                {
                    printf("\n\n正解！！！");
                    countr++;
                    getchar();
                    break;
                }
                else
                {
                    printf("\n\n不正解！！！ 正解は/*です");
                    getchar();
                    break;
                }

          case 2:
                printf("\n\n\n2. 次のコードの出力は何ですか？\n\n\t\t#include <stdio.h>\n\t\tint main()\n\t\t{\n\t\t\tint x = 10;\n\t\t\tint y = x++ + ++x;\n\t\t\tprintf(\"％d\", y);\n\t\t\treturn 0;\n\t\t}");
                printf("\n\nA. 21\t\tB. 20");
                printf("\n\nC. 22\t\tD. 23");
    
                char answer;
                scanf(" %c", answer);  // Read a single character input
                getchar();
    
                if (toupper(answer) == 'C')
                {
                    printf("\n\n正解！！！");
                    countr++;
                }
                else
                {
                    printf("\n\n不正解！！！ 正解は22です");
                }
    
                getchar();  // Consume the newline character
    
                break;


            // 他の質問...

            default:
                break;
            }
        }

        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tゲーム終了");
        printf("\n\t\t\tCongrats %sさん, you made it to the end!", playername);
        printf("\n\t\t\tあなたのスコアは$%.2fです\n", (float)countr * 10000);
        edit_score((float)countr * 10000, playername);
        goto mainhome;
    }
    else
    {
        system("clear");
        printf("\n\n\n\n\n\n\n\n\n\n\t\t\tゲームオーバー");
        printf("\n\t\t\tThank you for playing the game!");
        printf("\n\t\t\tYour final score is $0.00\n");
        edit_score(score, playername);
        exit(1);
    }

    return 0;
}

void show_record()
{
    system("clear");
    char playername[20];
    float score;
    FILE *fp;
    fp = fopen("score.txt", "r");
    fscanf(fp, "%s%f", playername, &score);
    printf("\n\n\n\n\n\t\t\t最高得点は%sさんのものです！", playername);
    printf("\n\n\t\t\t%sさんの最高得点は$%.2fです\n", playername, score);
    fclose(fp);
    getchar();
}

void reset_score()
{
    system("clear");
    float score;
    char playername[20];
    FILE *fp;
    fp = fopen("score.txt", "w");
    strcpy(playername, "No one");
    score = 0;
    fprintf(fp, "%s\n%.2f", playername, score);
    fclose(fp);
    printf("\n\n\n\n\n\t\t\tスコアがリセットされました！");
    getchar();
}

void help()
{
    system("clear");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\tルールとヘルプ");
    printf("\n\t\t\t________________________________________");
    printf("\n\t\t\t________________________________________");
    printf("\n\t\t\t > ゲームを開始するには、Sを押してください");
    printf("\n\t\t\t > 最高得点を確認するには、Vを押してください");
    printf("\n\t\t\t > スコアをリセットするには、Rを押してください");
    printf("\n\t\t\t > ヘルプを表示するには、Hを押してください");
    printf("\n\t\t\t > 終了するには、Qを押してください");
    printf("\n\t\t\t________________________________________");
    printf("\n\t\t\t________________________________________");
    printf("\n\t\t\t > ウォームアップラウンドでは、3つの質問が出題されます。");
    printf("\n\t\t\t > チャレンジラウンドでは、10の質問が出題されます。");
    printf("\n\t\t\t > 最低2つのウォームアップ質問に正解する必要があります。");
    printf("\n\t\t\t > ゲームの最後には、最高得点が表示されます。");
    printf("\n\t\t\t________________________________________");
    printf("\n\t\t\t________________________________________");
    getchar();
}

void edit_score(float score, char plnm[20])
{
    system("clear");
    float sc;
    char playername[20];
    FILE *fp;
    fp = fopen("score.txt", "r");
    fscanf(fp, "%s%f", playername, &sc);
    if (score >= sc)
    {
        sc = score;
        fclose(fp);
        fp = fopen("score.txt", "w");
        fprintf(fp, "%s\n%.2f", plnm, sc);
        fclose(fp);
    }
}
