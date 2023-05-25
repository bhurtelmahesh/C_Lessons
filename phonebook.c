/*
説明：このファイルを使用することで、連絡先を保存し、以下の操作を行うことができます。
1) すべての連絡先を表示する。
2) 連絡先を追加する。
3) 任意の連絡先番号の詳細を検索する。
4) 連絡先を削除する。
5) 任意の連絡先の詳細を更新する。
6) 電話帳全体を削除する（電話帳に存在するすべての連絡先を削除する）。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct person
{
    char name[30];
    char country_code[4];
    long int mble_no;
    char sex[8];
    char mail[100];
};

// personデータ型の定義。
typedef struct person person;

// すべての関数の宣言。
void start();
void remove_all();
void print_menu();
void add_person();
void list_record();
void search_person();
void remove_person();
void update_person();
void take_input(person *p);


// プログラムはここから開始します。
int main()
{
    start();
    return 0;
}

// この関数はプログラムを開始します。
void start()
{
    int choice;
    while(1)
    {
        print_menu();
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                list_record();
                getchar();
                getchar();
                break;
            case 2:
                add_person();
                getchar();
                getchar();
                break;
            case 3:
                search_person();
                getchar();
                getchar();
                break;
            case 4:
                remove_person();
                getchar();
                getchar();
                break;
            case 5:
                update_person();
                getchar();
                getchar();
                break;
            case 6:
                remove_all();
                getchar();
                getchar();
                break;
            default :
                system("clear");
                printf("電話帳をご利用いただき、ありがとうございました :)\n");
                getchar();
                getchar();
                exit(1);
        }
    }
}

//  これはメインメニューを表示します。
void print_menu()
{
    system("clear");
    printf("\t\t****************************************************************\n");
    printf("\t\t*                  Welcome To Phone Book                    *\n");
    printf("\t\t****************************************************************\n\n");
    printf("\t\t\t1) 連絡先一覧\n\n");
    printf("\t\t\t2) 連絡先の追加\n\n");
    printf("\t\t\t3) 連絡先の詳細検索\n\n");
    printf("\t\t\t4) 連絡先の削除\n\n");
    printf("\t\t\t5) 連絡先の更新\n\n");
    printf("\t\t\t6) 全ての連絡先を削除\n\n");
    printf("\t\t\t7) 電話帳を終了\n\n");

    printf("\t\t\t\t選択してください : ");
}

// この関数は電話帳に連絡先を追加します。
void add_person()
{
    system("clear");
    FILE *fp;
    fp = fopen("phonebook_db", "ab+");
    if (fp == NULL)
    {
        printf("エラーが発生しました。もう一度試してください!\n");
        printf("続行するには何かキーを押してください....\n");
        return;
    }
    else
    {
        person p;
        take_input(&p);
        fwrite(&p, sizeof(p), 1, fp);
        fflush(stdin);
        fclose(fp);
        system("clear");
        printf("連絡先が正常に追加されました。\n");
        printf("続行するには何かキーを押してください....\n");

    }
}

//  連絡先情報を取得します。
void take_input(person *p)
{
    system("clear");
    // これは前の関数で発生した改行文字（\n）を取得するためです。
    // これにより、scanfのスキャンセットが正常に機能します。

    getchar();
    printf("名前を入力してください : ");


    // scanset '^' - >  until get
    // ここではスキャンセット '^' -> 改行まで

    scanf("%[^\n]s",p->name);

    printf("国コードを入力してください : ");
    scanf("%s",p->country_code); 
    
    printf("電話番号を入力してください : ");
    scanf("%ld",&p->mble_no); 

    printf("性別を入力してください : ");
    scanf("%s",p->sex); 
    
    printf("メールアドレスを入力してください : ");
    scanf("%s",p->mail); 
}

// この関数は電話帳にある連絡先をリスト表示します。
void list_record()
{
    system("clear");
    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("エラーが発生しました。もう一度試してください！\n");
        printf("続行するには何かキーを押してください....\n");
        return;
    }
    else
    {
        person p;
        printf("\n\t\t\t\t******************************************************************************\n");
        printf("\t\t\t\t*                  電話帳に記載されているすべてのレコード                    *\n");
        printf("\t\t\t\t******************************************************************************\n\n\n");
        printf("  名前\t\t\t\t   国コード\t\t    電話番号\t\t    性別\t\t             EMAIL\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
        // fseek(fp,-(sizeof(p)*2L),2);
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            int i;
            int len1 = 40 - strlen(p.name);
            int len2 = 19 - strlen(p.country_code);
            int len3 = 15;
            int len4 = 21 - strlen(p.sex);
            printf("%s",p.name);
            for(i=0;i<len1;i++) printf(" ");

            printf("%s",p.country_code);
            for(i=0;i<len2;i++) printf(" ");

            printf("%ld",p.mble_no);
            for(i=0;i<len3;i++) printf(" ");

            printf("%s",p.sex);
            for(i=0;i<len4;i++) printf(" ");

            printf("%s",p.mail);
            printf("\n");
            fflush(stdin);
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\n続行するには何かキーを押してください....\n");
        
    }
}

// この関数は電話帳で連絡先を検索します。
void search_person()
{
    system("clear");
    long int phone;
    printf("検索したい電話番号を入力してください : ");
    scanf("%ld",&phone);

    FILE *fp;
    fp = fopen("phonebook_db", "rb");
    if (fp == NULL)
    {
        printf("ファイルのオープンにエラーが発生しました。もう一度試してください！\n");
        printf("続行するには何かキーを押してください....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                printf("  名前\t\t\t\t   国コード\t\t    電話番号\t\t    性別\t\t             EMAIL\n");
                printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
                int i;
                int len1 = 40 - strlen(p.name);
                int len2 = 19 - strlen(p.country_code);
                int len3 = 15;
                int len4 = 21 - strlen(p.sex);
                printf("%s",p.name);
                for(i=0;i<len1;i++) printf(" ");

                printf("%s",p.country_code);
                for(i=0;i<len2;i++) printf(" ");

                printf("%ld",p.mble_no);
                for(i=0;i<len3;i++) printf(" ");

                printf("%s",p.sex);
                for(i=0;i<len4;i++) printf(" ");

                printf("%s",p.mail);
                printf("\n");

                flag = 1;
                break;
            }
            else continue;
            // fflush(stdin);
        }
        if(flag == 0) 
        {
            system("clear");
            printf("レコードは存在しません！\n");
        }
        fflush(stdin);
        fclose(fp);
        printf("\n\n続行するには何かキーを押してください....\n");
    }

}

// この関数は電話帳から連絡先を削除します。
void remove_person()
{
    system("clear");
    long int phone;
    printf("電話帳から削除する電話番号を入力してください  : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("ファイルのオープンにエラーが発生しました。もう一度試してください！\n");
        printf("続行するには何かキーを押してください....\n");
        return;
    } else {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                flag = 1;
                continue;
            }
            else
            {
                fwrite(&p,sizeof(p),1,temp);
            }
        }
        fclose(fp);
        fclose(temp);
        if(flag == 0) 
        {
            system("clear");
            printf("電話帳からその人物を削除することはできませんでした\n");
        }
        else
        {
            fp = fopen("phonebook_db", "wb");
            temp = fopen("temp","rb");
            while (fread(&p, sizeof(p), 1, temp) == 1)
            {
                fwrite(&p,sizeof(p),1,fp);
            }
            fclose(fp);
            fclose(temp);
            system("clear");
            printf("連絡先が正常に削除されました\n");
        }
        printf("\n\n続行するには何かキーを押してください....\n");
    }

}

//  この関数は電話帳の連絡先情報を更新します。
void update_person()
{

    system("clear");
    long int phone;
    printf("更新する連絡先の電話番号を入力してください : ");
    scanf("%ld",&phone);

    FILE *fp,*temp;
    fp = fopen("phonebook_db", "rb");
    temp = fopen("temp","wb+");
    if (fp == NULL)
    {
        printf("エラーが発生しました。もう一度試してください！\n");
        printf("続行するには何かキーを押してください....\n");
        return;
    }
    else
    {
        int flag = 0;
        person p;
        while (fread(&p, sizeof(p), 1, fp) == 1)
        {
            if(p.mble_no == phone)
            {
                printf("以下の情報で連絡先を更新します\n");
                printf("新しい情報を入力してください\n");
                take_input(&p);
                fwrite(&p,sizeof(p),1,temp);
                flag = 1;
            }
            else
            {
                fwrite(&p,sizeof(p),1,temp);
            }
        }
        fclose(fp);
        fclose(temp);
        if(flag == 0) 
        {
            system("clear");
            printf("電話帳からその人物を更新することはできませんでした\n");
        }
        else
        {
            fp = fopen("phonebook_db", "wb");
            temp = fopen("temp","rb");
            while (fread(&p, sizeof(p), 1, temp) == 1)
            {
                fwrite(&p,sizeof(p),1,fp);
            }
            fclose(fp);
            fclose(temp);
            system("clear");
            printf("連絡先が正常に更新されました\n");
        }
        printf("\n\n続行するには何かキーを押してください....\n");
    }
}


// この関数は電話帳全体を削除します
void remove_all()
{
    char choice;
    system("clear");
    remove("./phonebook_db");
    printf("電話帳全体を削除しました！\n");
    printf("続行するには何かキーを押してください ... \n");
}