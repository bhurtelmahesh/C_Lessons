// 私はこのプログラムをMacBookで書いてあるため、Windowsで動かない可能性があります。

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct user {
    char phone[50];
    char ac[50];
    char password[50];
    float balance;
};

//関数
//ログイン
void login();

//新規登録
void registerUser();

//残高照会
void getBalance();

//入金
void deposit();

//出金
void withdraw();

//送金
void transfer();

//パスワード変更
void changePassword();

//スタート
void start();

//変数
struct user user;
char filename[50], phone[50], password[50], phone2[50];
FILE *fp, *fptr;
int opt, choice;
int amount;
char cont = 'y';

int main() {
    start();
    return 0;
}

void start(){
	printf("\nご希望の取り引きを選択してください");
    printf("\n\n1.講座新規登録");
    printf("\n2.既存の口座へログイン");
    printf("\n\n取り引きを番号で入力ください:\t");
    scanf("%d", &opt);
    if (opt == 1) {
        registerUser();
    } else if (opt == 2) {
        login();
    }
}

void login() {
    printf("\n電話番号:\t");
    scanf("%s", phone);
    printf("パスワード:\t");
    scanf("%s", password);
    fp = fopen(strcat(phone, ".dat"), "r");
    if (fp == NULL){
        printf("\n:::::::::::::::::::::::\n");
        printf("アカウントが見つかりませんでした！");
        printf("\n::::::::::::::::::::\n");
    } else {
        fread(&user, sizeof(struct user), 1, fp);
        fclose(fp);
        if (!strcmp(password, user.password)) {
            do {
                system("clear"); //system("cls") on windows
                printf("\n\tようこそ %s", user.phone);
                printf("\n１　残高照会");
                printf("\n２　入金");
                printf("\n３　出金");
                printf("\n４　送金");
                printf("\n５　パスワード変更\n\n");
                scanf("%d", &choice);
                switch (choice) {
                    case 1:
                        getBalance();
                        break;

                    case 2:
                        deposit();
                        break;

                    case 3:
                        withdraw();
                        break;

                    case 4:
                        transfer();
                        break;

                    case 5:
                        changePassword();
                        break;

                    default:
                        break;
                }
                printf("\n別のサービスをご利用ですか?[y/n]:\t");
                scanf(" %c", &cont);
            } while (cont == 'y');
        } else {
            printf("\n:::::::::::::::::::::::\n");
            printf("パスワードは正しくありません！");
            printf("\n::::::::::::::::\n");
        }
    }
    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::\n");
    printf("***いつもDPT銀行をご利用いただきありがとうございます***");
    printf("\n::::::::::::::::::::::::::::::::::::::::::::::::::\n");
}

void registerUser() {
    printf("\n口座番号を入力してください:\t");
    scanf("%s", user.ac);
    printf("電話番号を入力してください:\t");
    scanf("%s", user.phone);
    printf("パスワードを入力してください:\t");
    scanf("%s", user.password);
    user.balance = 0;
    strcpy(filename, user.phone);
    fp = fopen(strcat(filename, ".dat"), "w");
    if(fwrite(&user,sizeof(struct user),1,fp) != 0){
        printf("\n:::::::::::::::::::::::\n");
        printf("登録が完了しました！");
        printf("\n:::::::::::::::::::::::\n");
    }
    fclose(fp);
}

void getBalance() {
    printf("残高： %.2f円", user.balance);
}

void deposit() {

    printf("入金額を入力してください:\t");
    scanf("%d", &amount);

    if (amount < 0) {
		printf("\n:::::::::::::::::::::::\n");
        printf("金額は正しくありません！");
        printf("\n:::::::::::::::::::::::\n");
        return;
    }

    user.balance += amount;

    char filename[20];
    sprintf(filename, "%s.dat", user.phone);
    fp = fopen(filename, "w");
    fwrite(&user, sizeof(struct user), 1, fp);
    fclose(fp);
	printf("\n:::::::::::::::::::::::\n");
    printf("%d円、入金完了しました！", amount);
    printf("\n:::::::::::::::::::::::\n");

}
void withdraw(){
	printf("出金額を入力してください:\t");
	scanf("%d",&amount);
    //小銭の出金禁止
	if(amount % 1000 != 0) printf("\n千円未満の金額の取引ができません！");
	else if(amount>user.balance) printf("\n残高不足しております！");
	else {
		user.balance -= amount;
		fp = fopen(user.phone,"w");
		fwrite(&user,sizeof(struct user),1,fp);
		if(fwrite(&user,sizeof(struct user),1,fp) != 0){
			printf("\n:::::::::::::::::::::::\n");
    		printf("%d円の出金が完了しました！",amount);
        printf("\n:::::::::::::::::::::::\n");
		}
		fclose(fp);

	}
}

void transfer(){
	printf("送金先の電話番号を入力してください:\t");
	scanf("%s",phone);
	printf("送金額を入力してください:\t");
	scanf("%d",&amount);
	if(amount > user.balance){
		printf("\n:::::::::::::::::::::::\n");
		printf("残高不足しております！");
        printf("\n:::::::::::::::::::::::\n");
	}else{
		strcpy(phone2, phone);
		fptr = fopen(strcat(phone2,".dat"),"r");
		if(fptr==NULL){
			printf("\n:::::::::::::::::::::::\n");
			printf("入力いただいた電話番号が存在しません！");
        	printf("\n:::::::::::::::::::::::\n");
		}else{
			fread(&user,sizeof(struct user),1,fptr);
			fclose(fptr);			
			user.balance += amount;		
			fp = fopen(phone,"w");
			fwrite(&user,sizeof(struct user),1,fp);
			if (fwrite(&user, sizeof(struct user), 1, fp) == 1) {
				printf("\n:::::::::::::::::::::::\n");
    			printf("送金が完了しました。%sへ%dを送金しました！", user.ac, amount);
        		printf("\n:::::::::::::::::::::::\n");

    			fclose(fp);
    			user.balance -= amount;
    			strcpy(filename, user.phone);
    			fp = fopen(strcat(filename, ".dat"), "w");
    			fwrite(&user, sizeof(struct user), 1, fp);
    			fclose(fp);
            }
		}
	}
}

void changePassword(){
	printf("\n\n現在のパスワードを入力してください:\t");
	scanf("%s",password);
	if(!strcmp(password,user.password)){
		printf("\n\n新しいパスワードを入力してください:\t");
		scanf("%s",password);
		strcpy(user.password,password);
		strcpy(filename,user.phone);
		fp = fopen(strcat(filename,".dat"),"w");
		fwrite(&user,sizeof(struct user),1,fp);
		fclose(fp);	
		printf("\n:::::::::::::::::::::::\n");
		printf("パスワードの変更が完了しました！");
        printf("\n:::::::::::::::::::::::\n");
	}else{
        printf("\n:::::::::::::::::::::::\n");
		printf("\nパスワードは正しくありません！");
	}
}
