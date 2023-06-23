#include <stdio.h>

int main() {
    char questions[][100] = {
        "Q1. プログラミング言語Cの作者は誰でしょう？\n(a) デニス・リッチー\n(b) ケン・トンプソン\n(c) リンカス・トーバルズ\n(d) ジェームズ・ゴスリン\n",
        "Q2. C言語のsizeof演算子は何を返すでしょう？\n(a) 変数のアドレス\n(b) 変数の値\n(c) 変数のサイズ\n(d) 変数の型\n",
        "Q3. C言語での文字列を表すための終端文字は何でしょう？\n(a) '\\0'\n(b) '\\n'\n(c) '\\r'\n(d) '\\t'\n",
        "Q4. C言語での条件分岐に使われるキーワードは何でしょう？\n(a) for\n(b) while\n(c) if\n(d) switch\n",
        "Q5. C言語でのポインタ変数の宣言に使用する演算子は何でしょう？\n(a) &\n(b) *\n(c) #\n(d) $\n"
    };

    char answers[] = {'a', 'c', 'a', 'c', 'b'};
    int score = 0;
    int i;

    printf("***** クイズゲーム *****\n\n");

    for (i = 0; i < 5; i++) {
        printf("========== 質問 %d ==========\n\n", i + 1);
        printf("%s", questions[i]);

        char userAnswer;
        printf("回答を選択してください (a, b, c, d): ");
        scanf(" %c", &userAnswer);

        if (userAnswer == answers[i]) {
            printf("\n*** 正解です！ ***\n");
            score++;
        } else {
            printf("\n*** 不正解です。 ***\n");
        }

        printf("\n============================\n\n");
    }

    printf("***** クイズ終了！ *****\n\n");
    printf("あなたのスコアは %d / 5 です。\n\n", score);

    // スコアの記録と表示
    char playerName[50];
    printf("名前を入力してください: ");
    scanf("%s", playerName);

    printf("\n===== スコアボード =====\n");
    printf("プレーヤー: %s\n", playerName);
    printf("スコア: %d / 5\n", score);
    printf("=======================\n");

    return 0;
}
