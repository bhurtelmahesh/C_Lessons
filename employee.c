#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h> //Windows上で利用するため
#include <string.h>

/** グローバル変数のリスト */
COORD coord = {0,0}; /// ウィンドウの左上隅の座標


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



/** メイン関数の開始 */
int main(){
    system("color 3f");

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

    while(1){
        prompt();
        switch(choice){
            case '1': /// もしユーザが1を押した場合
                system("cls");
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
    }//メインループの終了//

    return 0;

}

void gotoxy(int x,int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void prompt(){
    system("cls"); /// コンソールウィンドウをクリアする
    printf("**Knowledge 360**");
    gotoxy(30,10); /// カーソルを左上から座標30, 10に移動する
    printf("1. レコードの追加"); /// レコードの追加オプション
    gotoxy(30,12);
    printf("2. レコードの表示"); /// 既存のレコードを表示するオプション
    gotoxy(30,14);
    printf("3. レコードの編集"); // レコードの編集オプション//
    gotoxy(30,16);
    printf("4. レコードの削除"); // レコードの削除オプション//
    gotoxy(30,18);
    printf("5. 終了"); // プログラムの終了//
    gotoxy(30,20);
    printf("選択してください: "); // 1, 2, 3, 4, 5の選択肢を入力//
    fflush(stdin); /// 入力バッファをクリアする
    choice = getche(); /// キーボードから入力を取得する
}

void add(){
    printf("\n名前を入力してください: ");
    scanf("%s",e.name);
    printf("\n年齢を入力してください: ");
    scanf("%d", &e.age);
    printf("\n基本給を入力してください: ");
    scanf("%f", &e.bs);
    fwrite(&e,recsize,1,fp); /// レコードをファイルに書き込む
    printf("\n別のレコードを追加しますか？(y/n) ");
    fflush(stdin);
    another = getche();
}

void show(){
    system("cls");
    rewind(fp); /// ファイルカーソルをファイルの先頭に移動する
    while(fread(&e,recsize,1,fp)==1){  /// ファイルを読み込み、1つのレコードを1回の読み込みで取得する
        printf("\n%s %d %.2f",e.name,e.age,e.bs); /// 名前、年齢、基本給を表示する
    }
    getch();
}

void edit(){
    system("cls");
    another = 'y';
    while(another == 'y'){
        editAnother();
    }
}
void editAnother(){
    printf("\n編集する従業員の名前を入力してください: ");
    scanf("%s", empname);
    rewind(fp);
    while(fread(&e,recsize,1,fp)==1){  /// ファイルからすべてのレコードを取得する
        if(strcmp(e.name,empname) == 0){ /// 入力された名前がファイル内の名前と一致する場合
            printf("\n新しい名前、年齢、基本給を入力してください: ");
            scanf("%s%d%f",e.name,&e.age,&e.bs);
            fseek(fp,-recsize,SEEK_CUR); /// カーソルを現在位置から1つ前に移動する
            fwrite(&e,recsize,1,fp); /// レコードを上書きする
            break;
        }
    }
    printf("\n別のレコードを編集しますか？(y/n)");
    fflush(stdin);
    another = getche();
}

void delete(){
    system("cls");
    another = 'y';
    while(another == 'y'){
        deleteAnother();
    }
}

void deleteAnother(){
    printf("\n削除する従業員の名前を入力してください: ");
    scanf("%s",empname);
    ft = fopen("Temp.dat","wb"); /// 一時的なストレージのための中間ファイルを作成する
    rewind(fp); /// レコードをファイルの先頭に移動する
    while(fread(&e,recsize,1,fp) == 1){ /// ファイルからすべてのレコードを読み込む
        if(strcmp(e.name,empname) != 0){ /// 入力されたレコードが一致しない場合
            fwrite(&e,recsize,1,ft); /// 削除するレコード以外のすべてのレコードを一時ファイルに移動する
        }
    }
    fclose(fp);
    fclose(ft);
    remove("EMP.DAT"); /// 元のファイルを削除する
    rename("Temp.dat","EMP.DAT"); /// 一時ファイルを元のファイル名に変更する
    fp = fopen("EMP.DAT", "rb+");
    printf("\n別のレコードを削除しますか？(y/n)");
    fflush(stdin);
    another = getche();
}