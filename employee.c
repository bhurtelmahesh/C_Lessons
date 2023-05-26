#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/** 従業員を表す構造体 */
struct emp{
    char name[40]; /// 従業員の名前
    int age; /// 従業員の年齢
    float bs; /// 従業員の基本給与
};

struct emp e; /// 構造体変数の作成


FILE *fp, *ft; /// ファイルポインタ
char another, choice;
char empname[40]; /// 従業員の名前を格納する文字列
long int recsize; /// 1つの従業員のレコードのサイズ

//関数プロトタイプ
void gotoxy(int x,int y);
void prompt();
void add();
void show();
void edit();
void editAnother();
void delete();
void deleteAnother();
void fullFunctions();



/** メイン関数の開始 */
int main(){

   
    fullFunctions();
    return 0;

}

// void gotoxy(int x,int y)
// {
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
// }

void prompt(){
    system("clear"); /// コンソールウィンドウをクリアする
    printf("\n\n**Employee Record System**\n\n");
    // gotoxy(30,10); /// カーソルを左上から座標30, 10に移動する
    printf("1. レコードの追加\n"); /// レコードの追加オプション
    // gotoxy(30,12);
    printf("2. レコードの表示\n"); /// 既存のレコードを表示するオプション
    // gotoxy(30,14);
    printf("3. レコードの編集\n"); // レコードの編集オプション//
    // gotoxy(30,16);
    printf("4. レコードの削除\n"); // レコードの削除オプション//
    // gotoxy(30,18);
    printf("5. 終了\n"); // プログラムの終了//
    // gotoxy(30,20);
    printf("選択してください:\t"); // 1, 2, 3, 4, 5の選択肢を入力//
    scanf("%c",&choice); /// キーボードから入力を取得する
}

void add(){
    printf("\n名前を入力してください: ");
    scanf("%s",e.name);
    printf("\n年齢を入力してください: ");
    scanf("%d", &e.age);
    printf("\n基本給を入力してください: ");
    scanf("%f", &e.bs);
    fwrite(&e,recsize,1,fp); /// レコードをファイルに書き込む
    printf("\n別のレコードを追加しますか？(y/n): ");
    fflush(stdin);
    scanf("%c",&another);

}

void show() {
    system("clear");
    rewind(fp);
    while (fread(&e, recsize, 1, fp) == 1) {
        printf("\n%s %d %.2f", e.name, e.age, e.bs);
    }
    getchar();

    printf("\n\nPress any key to go back to the main menu...");
    getchar();
    fullFunctions();
}



void edit(){
    system("clear");
    another = 'y';
    while(another == 'y'){
        editAnother();
    }
    fullFunctions();

}
void editAnother(){
    // char empname[40];
    printf("編集する従業員の名前を入力してください: ");
    scanf("%s", empname);
    rewind(fp);
    while (fread(&e, recsize, 1, fp) == 1) {
        if (strcmp(e.name, empname) == 0) {
            printf("\n新しい名前を入力してください: ");
            scanf("%s", e.name);

            printf("新しい年齢を入力してください: ");
            scanf("%d", &e.age);

            printf("新しい給与を入力してください: ");
            scanf("%f", &e.bs);

            fseek(fp, -recsize, SEEK_CUR);
            fwrite(&e, recsize, 1, fp);
            break;
        }
    }
    printf("\n別のレコードを編集しますか？(y/n):\t");
    fflush(stdin);
    scanf("%c",&another);
}

void delete() {
    system("clear");
    char choice = 'y';
    while (choice == 'y'){
        deleteAnother();
        printf("\n\n続行しますか？ [y/n]:\t");
        scanf(" %c", &choice);
    }
    fullFunctions(); // Go back to the main menu
}





void deleteAnother() {
    printf("\n削除する従業員の名前を入力してください: ");
    scanf("%s", empname);
    int found = 0; // レコードが見つかったかどうかを示すフラグ

    rewind(fp);
    while (fread(&e, recsize, 1, fp) == 1) {
        if (strcmp(e.name, empname) == 0) {
            found = 1; // レコードが見つかった
            break;
        }
    }

    if (found) {
        ft = fopen("Temp.dat", "wb");
        rewind(fp);
        while (fread(&e, recsize, 1, fp) == 1) {
            if (strcmp(e.name, empname) != 0) {
                fwrite(&e, recsize, 1, ft);
            }
        }
        fclose(fp);
        fclose(ft);
        remove("EMP.DAT");
        rename("Temp.dat", "EMP.DAT");
        fp = fopen("EMP.DAT", "rb+");
        printf("\nレコードを削除しました！");
    } else {
        printf("\nレコードが見つかりませんでした！");
    }
}


void fullFunctions(){
 /** ファイルをバイナリ読み書きモードで開く
    * もしEMP.DATというファイルが既に存在していれば、読み書きモードでそのファイルを開く
    * もしファイルが存在しなければ、新しいファイルを作成する
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("ファイルを開けません");
            exit(1);
        }
    }

    /// 各レコードのサイズ、つまり構造体変数eのサイズ
    recsize = sizeof(e);
    prompt();
    another = 'y';
    switch(choice){
        case '1': /// もしユーザが1を押した場合
            system("clear");
            fseek(fp,0,SEEK_END); /// ファイル内を検索し、カーソルをファイルの末尾に移動する
            /// ここで0はファイルの末尾から0の距離に移動することを示す
            another = 'y';
            while(another == 'y'){  /// もしユーザが別のレコードを追加する場合
                add();
            }
        break;
        case '2': // もしユーザが2を押した場合、レコードを表示する//
            show();
        break;
        case '3':  /// もしユーザが3を押した場合、既存のレコードを編集する
            edit();
        break;
        case '4'://この場合、従業員を削除できる//
            delete();
        break;
        case '5':
        fclose(fp); /// ファイルを閉じる
        exit(0); /// プログラムを終了する
    }
}