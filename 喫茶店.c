#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items{
    char item[20];
    float price;
    int qty;
};

struct orders{
    char customer[50];
    char date[50];
    int noOfItems;
    struct items itm[50];
};

//関数
void billHeader(char name[50], char date[50]);
void billBody(char item[30], int qty, float price);
void billFooter(float total);
void print(); //レシート出力
void printAll(); //全てのレシート出力
void kensaku();


//Global 変数
int opt; //選択肢
int n; //注文の数
int found = 0; //レシート検索時、見つからなかった場合
FILE *fp;
float total;
struct orders ord; //case 1の時
struct orders order; //case 2の時
char saveBill = 'y', cont = 'y';
char name[50];


int main(){
    printf("\n\t==========DPT喫茶店==========\n");
    printf("\nメニューを数字で入力してください：\t");
    printf("\n\n１．レシートを出力");
    printf("\n２．全てのレシートを出力");
    printf("\n３．レシート検索");
    printf("\n４．終了\n");
    printf("\nあなたの選択：\t");
    scanf("%d", &opt);
    fgetc(stdin);

    switch(opt){
        case 1:
        system("clear");
        print();
        break;

        case 2:
        system("clear");
        printAll();
        break;

        case 3:
        system("clear");
        kensaku();
        break;

        case 4:
        printf("プログラム終了します！");
        exit(0);
        break;

        default:
        printf("選択肢は正しくありません！！！");
        break;
    }
    //続いてシステム利用したい時の処理
    //
    //
    //
    //
    //明日
    printf("\n\n");
    return 0;
}

void print(){
    printf("お客様のお名前を入力してください：");
    fgets(ord.customer,50,stdin);
    ord.customer[strlen(ord.customer)-1] = 0; //\nを切る
    strcpy(ord.date,__DATE__);
    printf("注文の数を入力してください：\t");
    scanf("%d", &n); //料理の数
    ord.noOfItems = n;

    for(int i = 0; i < n; i++){
        fgetc(stdin);
        printf("\n\n");
        printf("%d番目の料理名を入力してください：\t",i+1);
        fgets(ord.itm[i].item,20,stdin);
        ord.itm[i].item[strlen(ord.itm[i].item)-1] = 0; 
        printf("注文の数を入力してください：\t\t");
        scanf("%d", &ord.itm[i].qty);
        printf("料理の価格を入力してください：\t\t");
        scanf("%f",&ord.itm[i].price);
        total += ord.itm[i].qty * ord.itm[i].price;
    } 
    billHeader(ord.customer, ord.date);
    for(int i = 0; i < n; i++){
        billBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
    }
    billFooter(total);

    printf("\n レシートを保存しますか？[y/n]：\t");
    scanf("%s", &saveBill);

    if(saveBill == 'y'){
        fp = fopen("喫茶店.dat","a+");
        if(fwrite(&ord, sizeof(struct orders), 1, fp) == 1) {
            printf("\n保存しました！");
        } else {
            printf("\nエラーが発生しました、保存できませんでした！");
        }
        fclose(fp);
    }
}

void printAll(){
    fp = fopen("喫茶店.dat","r");
    printf("\n\t＊＊＊＊＊過去のレシート＊＊＊＊＊\n");
    while(fread(&order,sizeof(struct orders),1,fp)){
        float tot = 0;
        billHeader(order.customer,order.date);
        for(int i = 0; i < order.noOfItems; i++){
            billBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
            tot += order.itm[i].qty * order.itm[i].price;
        }
        billFooter(tot);
    }
    fclose(fp);

}

void kensaku(){
    printf("お客様の名前：\t");
    // fgetc(stdin);
    fgets(name,50,stdin);
    name[strlen(name)-1] = 0;
    system("clear");
    fp = fopen("喫茶店.dat","r");
    printf("\n\t＊＊＊＊＊%s 様のレシート＊＊＊＊＊",name);
    while(fread(&order,sizeof(struct orders),1,fp)){
        float tot = 0;
        if(!strcmp(order.customer,name)){
            billHeader(order.customer,order.date);
            for(int i = 0; i < order.noOfItems; i++){
                billBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                tot += order.itm[i].qty * order.itm[i].price;
            }
            billFooter(tot);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("%s 様のレシートは見つかりませんでした！",name);
    }
    fclose(fp);

}

void billHeader(char name[50],char date[50]){
    printf("\n\n");
    printf("\t   DPT喫茶店");
    printf("\n\t -------------");
    printf("\n年月日：%s",date);
    printf("\n\t%s 様",name);
    printf("\n");
    printf("----------------------------------------\n");
    printf("項目\t\t");
    printf("品数\t\t");
    printf("合計\t\t");
    printf("\n----------------------------------------\n");
    printf("\n\n");
}

void billBody(char item[30], int qty, float price){
    printf("%s\t\t", item); //料理
    printf("%d\t\t",qty); //量
    printf("%.2f\t\t", qty*price);
    printf("\n");
}

void billFooter(float total){
    printf("\n");
    float dis = 0.05*total; //5%割引
    float netTotal = total-dis; //割引後のprice
    float tax = 0.1*netTotal, grandTotal = netTotal+tax; //税金１０％、その後の最終的なprice
    printf("----------------------------------------\n");
    printf("小計\t\t\t\t%.2f",total);
    printf("\n割引　5%s\t\t\t-%.2f","%",dis);
    printf("\n\t\t\t\t-------\n");
    printf("割引後\t\t\t\t%.2f",netTotal);
    printf("\n税金 10%s\t\t\t+%.2f","%",tax);
    printf("\n----------------------------------------\n");
    printf("合計\t\t\t\t%.2f",grandTotal);
    printf("\n----------------------------------------\n");
    printf("\n\t＊＊***DPT喫茶店***＊＊\n");
}