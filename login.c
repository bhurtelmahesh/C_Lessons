#include<stdio.h>
#include<conio.h>
#include<windows.h>

struct user{
    char fullName[50];
    char email[50];
    char password[50];
    char username[50];
    char phone[50];
};

void takeInput(char ch[50]){
    fgets(ch,50,stdin);
    ch[strlen(ch) -1] = 0;
}

generateUsername(char email[50], char username[50]){
    for(int i = 0; i<strlen(email); i++){
        if(email[i] == '@') break;
        else username[i] = email[i];
    }
}

int main(){
    int opt;

    printf("\n\t\t\t-------Welcome to authentication system--------");
    printf("\nPlease choose your operation");
    printf("\n1. Signup");
    printf("\n2. Login");
    printf("\n3. Exit");

    printf("\n\nYour Choice:\t");
    scanf("%d", &opt);
    fgetc(stdin); // \n
    

    return 0;
}