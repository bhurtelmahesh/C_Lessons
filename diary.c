#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int password(); // パスワードを入力する関数
void addrecord(); // レコードを追加する関数
void viewrecord(); // レコードを表示する関数
void editrecord(); // レコードを編集する関数
void editpassword(); // パスワードを変更する関数
void deleterecord(); // レコードを削除する関数

struct record
{
    char time[6];
    char name[30];
    char place[25];
    char duration[10];
    char note[500];
};

int main()
{
    int ch;
    
    printf("\n\n\t***********************************\n");
    printf("\t* パスワード保護された個人用日記 *\n");
    printf("\t***********************************");
    
    while(1)
    {
        printf("\n\n\t\tメインメニュー:");
        printf("\n\n\tレコードを追加する\t[1]");
        printf("\n\tレコードを表示する\t[2]");
        printf("\n\tレコードを編集する\t[3]");
        printf("\n\tレコードを削除する\t[4]");
        printf("\n\tパスワードを変更する\t[5]");
        printf("\n\t終了\t\t\t[6]");
        printf("\n\n\t選択してください:");
        scanf("%d",&ch);
        
        switch(ch)
        {
            case 1:
                addrecord(); // レコード追加の関数を呼び出す
                break;
            case 2:
                viewrecord(); // レコード表示の関数を呼び出す
                break;
            case 3:
                editrecord(); // レコード編集の関数を呼び出す
                break;
            case 4:
                deleterecord(); // レコード削除の関数を呼び出す
                break;
            case 5:
                editpassword(); // パスワード変更の関数を呼び出す
                break;
            case 6:
                printf("\n\n\t\tソフトウェアをご利用いただきありがとうございます");
                exit(0);
            default:
                printf("\n選択が間違っています..");
                printf("\nキーを押してもう一度試してください");
                break;
        }
        
        system("cls"); // 画面をクリアする（Windows用のコマンド）
    }
    
    return 0;
}

void addrecord()
{
    system("cls");
    
    FILE *fp ;
    char another = 'Y', time[10];
    struct record e;
    char filename[15];
    int choice;
    
    printf("\n\n\t\t***************************\n");
    printf("\t\t* レコード追加メニュー *");
    printf("\n\t\t***************************\n\n");
    
    printf("\n\n\tレコードの日付を入力してください:[yyyy-mm-dd]:");
    fflush(stdin);
    gets(filename);
    
    fp = fopen (filename, "ab+");
    
    if (fp == NULL)
    {
        fp=fopen(filename,"wb+");
        if(fp==NULL)
        {
            printf("\nデータベースエラー");
            printf("\nキーを押してメニューに戻ります");
            getch();
            return ;
        }
    }
    
    while (another == 'Y'|| another=='y')
    {
        choice=0;
        fflush(stdin);
        
        printf("\n\tレコードの時刻を入力してください:[hh:mm]:");
        scanf("%s",time);
        
        rewind(fp);
        
        while(fread(&e,sizeof(e),1,fp)==1)
        {
            if(strcmp(e.time,time)==0)
            {
                printf("\nこの時刻のレコードは既に存在します");
                choice=1;
            }
        }
        
        if(choice==0)
        {
            strcpy(e.time,time);
            
            printf("\tイベント名を入力してください:");
            fflush(stdin);
            gets(e.name);
            
            printf("\t場所を入力してください:");
            gets(e.place);
            
            printf("\t期間を入力してください:");
            gets(e.duration);
            
            printf("\tノートを入力してください:");
            gets(e.note);
            
            fwrite(&e,sizeof(e),1,fp);
            
            printf("\n\n\tレコードが追加されました");
        }
        
        printf("\n\n\t続行しますか？ [Y/N]");
        fflush(stdin);
        another = getchar();
    }
    
    fclose(fp);
    printf("\n\n\tキーを押してメニューに戻ります");
    getch();
}

void viewrecord()
{
    FILE *fpte ;
    system("cls");
    struct record customer ;
    char time[6],choice,filename[14];
    int ch;
    
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* レコード表示メニュー *");
    printf("\n\t\t*******************************\n\n");
    
    choice='Y';
    while(choice=='Y'||choice=='y')
    {
        printf("\n\n\tレコードの日付を入力してください:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);
        
        fpte = fopen ( filename, "rb" ) ;
        if ( fpte == NULL )
        {
            puts ( "\nデータベースが見つかりません" ) ;
            printf("\nキーを押してメニューに戻ります");
            getch();
            return ;
        }
        system("cls");
        
        printf("\n\t\tレコード: %s\n\n",filename);
        printf("---------------------------------------------------------------------------------\n");
        printf("\t時間\t\tイベント名\t場所\t\t期間\t\tノート\n");
        printf("---------------------------------------------------------------------------------\n");
        
        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
        {
            printf("\t%s\t",customer.time);
            printf("%s\t\t",customer.name);
            printf("%s\t\t",customer.place);
            printf("%s\t\t",customer.duration);
            printf("%s\t",customer.note);
            printf("\n");
        }
        
        printf("\n\n\n\tキーを押してメニューに戻ります");
        
        fclose ( fpte ) ;
        
        getch();
        printf("\n\n\tレコードを続けますか？ [Y/N]");
        fflush(stdin);
        choice=getchar();
    }
}

void editrecord()
{
    system("cls");
    FILE *fpte ;
    struct record customer ;
    char time[6],choice,filename[14];
    int num,count=0;
    
    printf("\n\n\t\t*******************************\n");
    printf("\t\t* レコード編集メニュー *");
    printf("\n\t\t*******************************\n\n");
    
    choice='Y';
    while(choice=='Y'||choice=='y')
    {
        printf("\n\n\t編集するレコードの日付を入力してください:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);
        
        printf("\n\t編集するレコードの時刻を入力してください:[hh:mm]:");
        fflush(stdin);
        gets(time);
        
        fpte = fopen ( filename, "rb+" ) ;
        if ( fpte == NULL )
        {
            printf( "\nデータベースが見つかりません" ) ;
            printf("\nキーを押してメニューに戻ります");
            getch();
            return;
        }
        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
        {
            if(strcmp(customer.time,time)==0)
            {
                printf("\nこのレコードを編集しますか? [Y/N]");
                fflush(stdin);
                choice=getchar();
                if(choice=='Y'||choice=='y')
                {
                    printf("\n時間\t\tイベント名\t場所\t\t期間\t\tノート\n");
                    printf("---------------------------------------------------------------------------------\n");
                    printf("\n%s\t",customer.time);
                    printf("%s\t\t",customer.name);
                    printf("%s\t\t",customer.place);
                    printf("%s\t\t",customer.duration);
                    printf("%s\t",customer.note);
                    printf("\n\n新しい詳細を入力してください\n");
                    printf("時間\t\tイベント名\t場所\t\t期間\t\tノート\n");
                    printf("---------------------------------------------------------------------------------\n");
                    fflush(stdin);
                    scanf("\n%s\t%s\t\t%s\t\t%s\t\t%s",customer.time,customer.name,customer.place,customer.duration,customer.note);
                    fseek(fpte,-sizeof(customer),SEEK_CUR);
                    fwrite(&customer,sizeof(customer),1,fpte);
                    break;
                }
            }
        }
        printf("\n\n\n\tキーを押してメニューに戻ります");
        
        fclose ( fpte ) ;
        
        getch();
        printf("\n\n\tレコードを続けますか？ [Y/N]");
        fflush(stdin);
        choice=getchar();
    }
}

void deleterecord()
{
    system("cls");
    FILE *fp,*fptr ;
    struct record file ;
    char filename[15],another = 'Y' ,time[10];;
    int choice,check;
    
    printf("\n\n\t\t*************************\n");
    printf("\t\t* レコード削除メニュー *");
    printf("\n\t\t*************************\n\n");
    
    while ( another == 'Y' )
    {
        printf("\n\n\tレコードの日付を入力してください:[yyyy-mm-dd]:");
        fflush(stdin);
        gets(filename);
        
        fp = fopen ( filename, "rb" ) ;
        if ( fp == NULL )
        {
            printf( "\nデータベースが見つかりません" ) ;
            printf("\nキーを押してメニューに戻ります");
            getch();
            return ;
        }
        
        fptr=fopen("temp","wb");
        
        if(fptr==NULL)
        {
            printf("\nデータベースエラー");
            printf("\nキーを押してメニューに戻ります");
            getch();
            return ;
        }
        
        printf("\n\t削除するレコードの時刻を入力してください:[hh:mm]:");
        fflush(stdin);
        gets(time);
        
        while(fread(&file,sizeof(file),1,fp)==1)
        {
            if(strcmp(file.time,time)!=0)
                fwrite(&file,sizeof(file),1,fptr);
        }
        
        fclose(fp);
        fclose(fptr);
        remove(filename);
        rename("temp",filename);
        
        fp=fopen(filename,"rb+");
        
        if(fp==NULL)
        {
            printf("\nデータベースエラー");
            printf("\nキーを押してメニューに戻ります");
            getch();
            return ;
        }
        
        printf("\n\n\tレコードが削除されました");
        
        printf("\n\n\t他のレコードを削除しますか？ [Y/N]");
        fflush(stdin);
        another=getchar();
    }
    
    printf("\n\n\tキーを押してメニューに戻ります");
    getch();
}

void editpassword()
{
    system("cls");
    printf("\n\n\t\t***************************\n");
    printf("\t\t* パスワード変更メニュー *");
    printf("\n\t\t***************************\n\n");
    printf("\n\n\tこの機能はまだ実装されていません");
    printf("\n\n\tキーを押してメニューに戻ります");
    getch();
}

int password()
{
    // パスワードの確認に使用する関数
    // 実装はまだされていません
    return 1;
}
