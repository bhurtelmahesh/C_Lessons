#include<stdio.h>

#define CANDIDATE_COUNT 4

#define CANDIDATE1 "デビッド・ハル"
#define CANDIDATE2 "クリスティン・カネラ"
#define CANDIDATE3 "ジム・ブラー"
#define CANDIDATE4 "ドナルド・トライアンフ"

int votesCount1 = 0, votesCount2 = 0, votesCount3 = 0, votesCount4 = 0, spoiledVotes = 0;

void castVote(){
    int choice;    
    printf("\n\n ### 候補者を選んでください ###\n\n");
    printf("\n 1. %s", CANDIDATE1);
    printf("\n 2. %s", CANDIDATE2);
    printf("\n 3. %s", CANDIDATE3);
    printf("\n 4. %s", CANDIDATE4);
    printf("\n 5. %s", "どれにも該当しない");

    printf("\n\n 選択してください (1 - 4) : ");
    scanf("%d", &choice);

    switch(choice){
        case 1: votesCount1++; break;
        case 2: votesCount2++; break;
        case 3: votesCount3++; break;
        case 4: votesCount4++; break;
        case 5: spoiledVotes++; break;
        default: printf("\n エラー: 間違った選択です！もう一度試してください");
                 // 画面を停止
                 getchar();
    }
    printf("\n 投票ありがとうございました！");
}

void votesCount(){
    printf("\n\n ##### 投票統計情報 #####");
    printf("\n %s - %d 票", CANDIDATE1, votesCount1);
    printf("\n %s - %d 票", CANDIDATE2, votesCount2);
    printf("\n %s - %d 票", CANDIDATE3, votesCount3);
    printf("\n %s - %d 票", CANDIDATE4, votesCount4);
    printf("\n %s - %d 票", "無効票", spoiledVotes); 
}

void getLeadingCandidate(){
    printf("\n\n  #### 最多得票者 ####\n\n");
    if(votesCount1 > votesCount2 && votesCount1 > votesCount3 && votesCount1 > votesCount4)
        printf("[%s]", CANDIDATE1);
    else if (votesCount2 > votesCount3 && votesCount2 > votesCount4 && votesCount2 > votesCount1)
        printf("[%s]", CANDIDATE2);
    else if(votesCount3 > votesCount4 && votesCount3 > votesCount2 && votesCount3 > votesCount1)
        printf("[%s]", CANDIDATE3);
    else if(votesCount4 > votesCount1 && votesCount4 > votesCount2 && votesCount4 > votesCount3)
        printf("[%s]", CANDIDATE4);
    else
        printf("----- 警告！どの候補者も勝利できません ----");   
}

int main(){
    int choice;

    do{
        printf("\n\n ###### 選挙 / 投票 2019 へようこそ #####");
        printf("\n\n 1. 投票する");
        printf("\n 2. 投票数を確認する");
        printf("\n 3. 最多得票者を確認する");
        printf("\n 0. 終了する");

        printf("\n\n 選択してください : ");
        scanf("%d", &choice);

        switch(choice){
            case 1: castVote(); break;
            case 2: votesCount(); break;
            case 3: getLeadingCandidate(); break;
            default: printf("\n エラー: 無効な選択です");
        }
    } while(choice != 0);

    // 画面を停止
    getchar();

    return 0;
}
