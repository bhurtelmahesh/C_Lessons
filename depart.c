#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define ANS 15
#define ACS 4
COORD coord= {0,0}; // Global変数
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

/*チェック関数宣言*/
void c_code(char[]);
int check(char[]);

/*struct宣言*/
typedef struct
{
    char name[ANS],code[ACS];
    float rate;
    int quantity;
} rec;
rec item;

/*表示する関数宣言*/
void curser(int);
void dbill();
void d_mainmenu();
void display(rec *,int,int);
void window(int,int,int,int);
void dis_con();
void d_search();
void highlight(int,int);

/*メインメニュー関数宣言*/
void bill() ;
void edit();
void add();
void del();
void exit();

/*サブメニュー表示関数宣言*/
void d_code();
void d_rate();
void d_quan();
void d_all();

/*Main関数開始*/
int main()
{
    d_mainmenu();
    return 0;
}

void d_mainmenu()
{
    int i;
    char ch;
    const char *menu[]= {"   会計","   商品を追加","   商品を編集","   全て表示  ","   商品検索", "   商品削除","   戻る"};
    system("cls");
//textbackground(11);
//textcolor(0);
//_setcursortype(_NOCURSOR);
    window(25,50,20,32);
    gotoxy(33,18);
    printf("メインメニュー");
    for (i=0; i<=6; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(7);
}

void d_search()
{
    char ch;
    int i;
    const char *menu[]= {"   コードで","   価格で","   数量で","   戻る"};
    system("cls");
//textbackground(11);
//textcolor(0);
    window(25,50,20,32);
    gotoxy(33,18);
    printf("検索メニュー");
    for (i=0; i<=3; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    curser(4);
}

/*カーサー移動の関数*/
void curser(int no)
{
    int count=1;
    char ch='0';
    gotoxy(30,23);
    while(1)
    {
        switch(ch)
        {
        case 80:
            count++;
            if (count==no+1) count=1;
            break;
        case 72:
            count--;
            if(count==0) count=no;
            break;
        }
        highlight(no,count);
        ch=getch();
        if(ch=='\r')
        {
            if(no==7)
            {
                if (count==1) bill() ;
                else if(count==2) add();
                else if(count==3) edit();
                else if (count==4) d_all();
                else if (count==5) d_search();
                else if (count==6) del();
                else   exit(0);
            }
            if(no==4)
            {
                if (count==1) d_code();
                else if (count==2)d_rate();
                else if (count==3) d_quan();
                else d_mainmenu();
            }
        }
    }
}

void highlight(int no,int count)
{
    if (no==4)
    {
        //textbackground(11);
        //textcolor(0);
        gotoxy(30,23);
        printf("   コードで          ");
        gotoxy(30,24);
        printf("   価格で          ");
        gotoxy(30,25);
        printf("   数量で      ");
        gotoxy(30,26);
        printf("   戻る");
        //textcolor(0);
        //textbackground(2);
        switch (count)
        {
        case 1:
            gotoxy(30,23);
            printf(" - コードで          ");
            break;
        case 2:
            gotoxy(30,24);
            printf(" - 価格で          ");
            break;
        case 3:
            gotoxy(30,25);
            printf(" - 数量で     ");
            break;
        case 4:
            gotoxy(30,26);
            printf(" - 終了");
            break;
        }
    }

    if(no==7)
    {
        //textbackground(11);
        //textcolor(0);
        gotoxy (30,23);
        printf("   会計 ");
        gotoxy (30,24);
        printf("   商品を追加      ");
        gotoxy (30,25);
        printf("   商品を編集    ");
        gotoxy (30,26);
        printf("   全て表示    ");
        gotoxy (30,27);
        printf("   検索         ");
        gotoxy (30,28);
        printf("   商品を削除   ");
        gotoxy (30,29);
        printf("   終了           ");
        //textcolor(0);
        //textbackground(2);
        switch(count)
        {
        case 1:
            gotoxy (30,23);
            printf(" - 会計 ");
            break;
        case 2:
            gotoxy (30,24);
            printf(" - 商品を追加      ");
            break;
        case 3:
            gotoxy (30,25);
            printf(" - 商品を編集     ");
            break;
        case 4:
            gotoxy (30,26);
            printf(" - 全て表示    ");
            break;
        case 5:
            gotoxy (30,27);
            printf(" - 検索         ");
            break;
        case 6:
            gotoxy (30,28);
            printf(" - 商品を削除   ");
            break;
        case 7:
            gotoxy (30,29);
            printf(" - 終了           ");
            break;
        }
    }
}

void bill()
{
    char x[4]= {0};
    int j=29,q=0,size=0,i=1;
    float total=0,gtotal=0;
    FILE *file;
    file=fopen("record.txt","r+b");
    rewind(file);
    system("cls");
    dbill();
    gotoxy(26,15);
    printf("入力できたら\"end\" を入力してください");
    while(1)
    {
        gotoxy(25,18);
        printf("                    ");
        gotoxy(25,19);
        printf("                    ");
        gotoxy(25,18);
        printf("商品コードを入力してください:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        gotoxy(25,19);
        printf("量を入力してください:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
                total=item.rate*q;
                gotoxy(11,j);
                printf("%4d",i);
                printf("%9s",item.name);
                printf("%13d",q);
                printf("%15.2f",item.rate);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoxy(30,j+5);
        printf("合計 = ￥ %6.2f",gtotal);
    }
    fclose(file);
    getch();
    d_mainmenu();
}
/*レシートウィンドウ表示関数*/
void dbill()
{
    int i;
    gotoxy(20,10);
//;
    for (i=1; i<=10; i++)
        printf("-");
    printf(" DPT ");
    for (i=1; i<=10; i++)
        printf("-");
    printf("\n\n");
    gotoxy(30,11);
    printf("デパートストア");
//textcolor(1);
    gotoxy(32,25);
    printf("お客様控") ;
//textcolor(8);
    gotoxy(13,27);
    printf("SN.   商品名     数量     価格          合計");

}
/*レコードを追加する関数*/
void add ()
{
    FILE *file;
    char y[ACS],x[12];
    system("cls");
//textbackground(11);
//textcolor(0);
    gotoxy(25,25);
    printf("レコードを追加する？　Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","ab");
        c_code(y);
        strcpy(item.code,y);
        gotoxy(22,28);
        printf("表品の価格を入力してください:");
        scanf("%f",&item.rate);
        gotoxy(22,30);
        printf("数量を入力してください:");
        scanf("%d",&item.quantity);
        gotoxy(22,32);
        printf("商品名を入力してください:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        gotoxy(22,34);
        printf("新しい商品を追加する？　(Y/N)?");

    }
    d_mainmenu();
}

/*コードの可用性をチェックする関数*/
void c_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("record.txt","rb");
    while(1)
    {
        system("cls");
        window(20,58,23,36);
        gotoxy(32,18);
        printf(" 新しい商品追加 ")  ;
        flag=1;
        rewind(file);
        gotoxy(22,25);
        printf("新しい商品コード:");
        scanf(" %[^\n]",y);
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;
                gotoxy(26,30);
                printf("既に存在します");
                gotoxy(29,32);
                printf("もう一度入力してください");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
}

/*編集する関数*/
void edit()
{
    int flag=0,choice;
    char x[ACS],y[ACS];
    FILE *file;
    int size;
    system("cls");
//textcolor(0);
//textbackground(11);
    window(20,63,20,46);
    gotoxy(35,18);
    printf("商品を編集");
    ;
    gotoxy(25,23);
    printf("商品コード: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {
                //textcolor(0);
                gotoxy(25,27);
                printf("商品名       = %s",item.name);
                gotoxy(25,28);
                printf("商品コード       = %s",item.code);
                gotoxy(25,29);
                printf("価格       = %g",item.rate);
                gotoxy(25,30);
                printf("量   = %d",item.quantity);
                gotoxy(25,32);;
                printf("商品を編集する?　(y/n):");
                fflush(file);
                if(toupper(getche())=='Y')
                {
                    //textcolor(0);
                    gotoxy(25,34);
                    printf("1- 名前を変更 ");
                    gotoxy(25,35);
                    printf("2- コードを変更 ");
                    gotoxy(25,36);
                    printf("3- 価格を変更 ");
                    gotoxy(25,37);
                    printf("4- 量を変更 ");
                    gotoxy(25,39);  ;
                    printf(" 選択肢(1, 2, 3, 4)：");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        system("cls");
                        window(23,48,20,40);
                        gotoxy(35,18);
                        printf("商品編集");
                        gotoxy(25,24);
                        printf(" 新しい商品名: ");
                        scanf("%s",item.name);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("商品編集");
                        gotoxy(25,24);
                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("商品編集");
                        gotoxy(25,24);
                        printf(" 新しい価格: ");
                        scanf("%f",&item.rate);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("商品編集");
                        gotoxy(25,24);
                        printf(" 新しい量: ");
                        scanf("%d",&item.quantity);
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }
                    gotoxy(27,30);
                    printf("---編集が完了しました---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoxy(32,30);
        printf("商品が存在しない！");
        gotoxy(36,32);
        printf("もう一度試してください！");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*全てのレコードを表示する関数*/
void d_all()
{
    int i,j=1;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        display(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoxy(27,47);/*textcolor(0)*/;
            printf("もっと見るにはどちらかのキーを押してください...........");
            getch();
            system("cls");
            dis_con();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(24,30);
        printf("-- 商品が見つかりませんでした --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*数量で表示する関数*/
void d_quan()
{
    int i,j=1;
    int a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("最小の価格: ");
    scanf("%d",&a);
    gotoxy(16,21);
    printf("最大の価格:");
    scanf("%d",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.quantity>=a)&&(item.quantity<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("もっと見るにはどちらかのキーを押してください......");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" 商品は見つかりませんでした！");
    }
    getch();
    d_search();
    fclose(file);
}

/*価格で表示する関数*/
void d_rate()
{
    int i,j=1;
    float a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("最小価格: ");
    scanf("%f",&a);
    gotoxy(16,21);
    printf("最大価格: ");
    scanf("%f",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.rate>=a)&&(item.rate<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("もっと見るにはどちらかのキーを押してください.....");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" 商品は見つかりませんでした ");
    }
    getch();
    fclose(file);
    d_search();
}

/*コードで表示する関数*/
void d_code()
{
    int i,j=1;
    char x[4]= {0};
    FILE *file;
    dis_con();
    file=fopen("record.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("商品コード: ");
    scanf("%s",x);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((strcmp(item.code,x)==0))
        {
            display(&item,i,j);
            i++;
            j++;
            break;
        }
    }
    if (i==26)
    {
        gotoxy(28,30);
        printf("見つかりませんでした！");
    }
    getch();
    fclose(file);
    d_search();
}

/*商品を表示するウィンドウを表示する関数*/
void dis_con()
{
    int i;
    system("cls");
    gotoxy(20,10);
    ;
    for (i=1; i<=10; i++)
        printf("-");
    printf(" DPT ");
    for (i=1; i<=10; i++)
        printf("-");
    printf("\n\n");
    gotoxy(30,11);
    printf("デパートストア");
//textcolor(1);
    gotoxy(32,17);
    printf("レコード") ;
//textcolor(8);
    gotoxy(18,23);
    printf ("SN.   商品名   商品コード      価格     量");
}

/*スクリーンを表示する関数*/
void display(rec *item,int i,int j)
{
    gotoxy(16,i);//textcolor(13);
    printf("%4d",j);
    printf("%9s",item->name);
    printf("%12s",item->code);
    printf("%14.2f",item->rate);
    printf("%11d",item->quantity);
}

/*レコードを削除する関数*/
void del()
{
    int flag;
    char x[ANS];
    FILE *file,*file1;
    system("cls");
//textbackground(11);
//textcolor(0);
    window(23,51,25,34);
    gotoxy(29,18);
    printf("削除");
    gotoxy(27,27);
    printf("商品コード: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","ab");
        file=fopen("record.txt","rb");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        gotoxy(27,29);
        printf("---削除しました---");
        remove("record.txt");
        rename("record1.txt","record.txt");
    }
    if (flag==1)
    {
        gotoxy(25,29);
        printf("---商品が見つかりませんでした！---");
        gotoxy(30,31);
        printf("もう一度試してください！");
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}

/*編集や削除する際、コードをチェックする関数*/
int check(char x[ANS])
{
    FILE *file;
    int flag=1;
    file=fopen("record.txt","rb");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}

/*ボックスを表示する関数*/
void window(int a,int b,int c,int d)
{
    int i;
    system("cls");
    gotoxy(20,10);
//textcolor(1);
    for (i=1; i<=10; i++)
        printf("-");
    printf(" DPT ");
    for (i=1; i<=10; i++)
        printf("-");
    printf("\n\n");
    gotoxy(30,11);
    printf("デパートストア");
//textcolor(4);
    for (i=a; i<=b; i++)
    {
        gotoxy(i,17);
        printf("\xcd");
        gotoxy(i,19);
        printf("\xcd");
        gotoxy(i,c);
        printf("\xcd");
        gotoxy(i,d);
        printf("\xcd");
    }

    gotoxy(a,17);
    printf("\xc9");
    gotoxy(a,18);
    printf("\xba");
    gotoxy(a,19);
    printf("\xc8");
    gotoxy(b,17);
    printf("\xbb");
    gotoxy(b,18);
    printf("\xba");
    gotoxy(b,19);
    printf("\xbc");
//textcolor(4);
    for(i=c; i<=d; i++)
    {
        gotoxy(a,i);
        printf("\xba");
        gotoxy(b,i);
        printf("\xba");
    }
    gotoxy(a,c);
    printf("\xc9");
    gotoxy(a,d);
    printf("\xc8");
    gotoxy(b,c);
    printf("\xbb");
    gotoxy(b,d);
    printf("\xbc");
//textbackground(11);
//textcolor(0);
}
