#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct product {
    char id[10];        // 商品コード
    char name[50];      // 商品名
    int stock;       // 商品の残り数量。元の数量から購入数量を引く
    int numSold;        // 初期値はゼロ、まだ購入されていない場合。
    float price;        // 商品1個の価格
    int discount;       // 商品の割引
    float sales;        // 累積販売額、商品の総売上
};

// グローバル変数
struct product prod[50];    //最大の配列要素。
int count = 0;              // 新しい商品がある場合、これが増加します。
FILE *f;                    // ファイルポインタ
int z = 0;

//Global
void addProd();
void IDChecker();
void editProd();
void deleteProd();
void purchaseProd();
void displayHighestSale();
void displayProd();


void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int writeFile() {           // ファイル書き込み関数
    int i;
    f = fopen("inventory.txt", "w");
    if (f == NULL)
        return -1;
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; ++i) {
        fprintf(f, "%s\n", prod[i].id);
        fprintf(f, "%s\n", prod[i].name);
        fprintf(f, "%d\n", prod[i].stock);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%d\n", prod[i].discount);
        fprintf(f, "%f\n", prod[i].sales);
    }
    fclose(f);
    return 0;
}

int readFile() {    // ファイル読み込み関数
    int n = 0;
    int i;
    f = fopen("inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; ++i) {
        fgets(prod[i].id, 10, f);
        strtok(prod[i].id, "\n");
        fgets(prod[i].name, 50, f);
        strtok(prod[i].name, "\n");
        fscanf(f, "%d", &prod[i].stock);
        fscanf(f, "%d", &prod[i].numSold);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%d", &prod[i].discount);
        fscanf(f, "%f\n", &prod[i].sales);
    }
    fclose(f);
    return n;
}

void displayZeroQuant() {
    int i;
    count = readFile();    // 読み込み関数を呼び出す
    printf("\nProducts with zero Quantity:\n");
    for (i = 0; i < count; i++) {
        if (prod[i].stock == 0) {
            printf("Name of the product: %s\nProduct Id: %s\nQuantity left: %d\nNumber of product sold: %d\nPrice of the product: %.2f\nDiscount of the product: %d%%\n",
                prod[i].name, prod[i].id, prod[i].stock, prod[i].numSold, prod[i].price, prod[i].discount);
        }
    }
}

void menu() {
    int choice;
    do {
        printf("\n1. 新商品の追加");
        printf("\n2. 商品の編集");
        printf("\n3. 商品の削除");
        printf("\n4. 商品の購入");
        printf("\n5. 在庫がゼロの商品を表示");
        printf("\n6. 最も高い売上の商品を表示");
        printf("\n7. すべての商品を表示");
        printf("\n8. 終了");
        printf("\n\n選択は数字で入力してください: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProd();
                break;
            case 2:
                editProd();
                break;
            case 3:
                deleteProd();
                break;
            case 4:
                purchaseProd();
                break;
            case 5:
                displayZeroQuant();
                break;
            case 6:
                displayHighestSale();
                break;
            case 7:
                displayProd();
                break;
            case 8:
                printf("プログラムを終了します。\n");
                break;
            default:
                printf("選択が正しくありません！もう一度選択してください。\n");
                break;
        }
    } while (choice != 8);
}

int main() {
    count = readFile();    // 読み込み関数を呼び出す
    menu();
    return 0;
}

void addProd() {
    printf("新しい商品を追加します！\n");
    count = readFile(); // ファイルから既存の商品数を読み込む

    if (count > 0) {
        count = readFile(); // ファイルから既存の商品数を再度読み込む
        IDChecker(0, count); // 商品コードが既に使用されているかをチェック
    } else {
        printf("\n商品コード: ");
        fflush(stdin);
        fgets(prod[count].id, 10, stdin); // ユーザーに商品コードを入力させる
    }

    printf("商品名: ");
    fgets(prod[count].name, 20, stdin); // ユーザーに商品名を入力させる
    printf("数量: ");
    scanf("%d", &prod[count].stock); // ユーザーに数量を入力させる
    printf("価格: ");
    scanf("%f", &prod[count].price); // ユーザーに価格を入力させる
    printf("割引: ");
    scanf("%d", &prod[count].discount); // ユーザーに割引を入力させる
    count++; // 商品数を増やす

    writeFile(); // 変更をファイルに書き込む
}
void IDChecker(int start, int end) {
    int i;
    char tempID[10];

    printf("商品コードを入力してください: ");
    fflush(stdin);
    fgets(tempID, 10, stdin); // ユーザーに商品コードを入力させる

    for (i = start; i < end; i++) {
        if (strcmp(tempID, prod[i].id) == 0) {
            printf("入力された商品コードは既に使用されています。別の商品コードを入力してください。\n");
            IDChecker(start, end); // 再帰的に関数を呼び出し、新しい商品コードをチェックする
            return;
        }
    }

    strncpy(prod[count].id, tempID, 10); // 商品コードをコピーする
}

void editProd(int start, int end) {
    char tempID[10];
    int i, choice;

    printf("編集する商品コードを入力してください: ");
    fflush(stdin);
    fgets(tempID, 10, stdin); // ユーザーに編集する商品コードを入力させる

    for (i = start; i < end; i++) {
        if (strcmp(tempID, prod[i].id) == 0) {
            printf("\n1. 商品名を編集\n");
            printf("2. 価格を編集\n");
            printf("3. 在庫数を編集\n");
            printf("4. キャンセル\n");
            printf("選択してください: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("新しい商品名を入力してください: ");
                    fflush(stdin);
                    fgets(prod[i].name, 50, stdin);
                    break;
                case 2:
                    printf("新しい価格を入力してください: ");
                    scanf("%f", &prod[i].price);
                    break;
                case 3:
                    printf("新しい在庫数を入力してください: ");
                    scanf("%d", &prod[i].stock);
                    break;
                case 4:
                    return;
                default:
                    printf("無効な選択です。\n");
                    break;
            }

            printf("商品情報が更新されました。\n");
            return;
        }
    }

    printf("入力された商品コードが見つかりませんでした。\n");
}

void deleteProd(int start, int end) {
    char tempID[10];
    int i, j;

    printf("削除する商品コードを入力してください: ");
    fflush(stdin);
    fgets(tempID, 10, stdin); // ユーザーに削除する商品コードを入力させる

    for (i = start; i < end; i++) {
        if (strcmp(tempID, prod[i].id) == 0) {
            // 削除対象の商品を見つけた場合、その商品を削除し、配列を詰める
            for (j = i; j < end - 1; j++) {
                strcpy(prod[j].id, prod[j + 1].id);
                strcpy(prod[j].name, prod[j + 1].name);
                prod[j].price = prod[j + 1].price;
                prod[j].stock = prod[j + 1].stock;
            }

            // 最後の要素を初期化
            strcpy(prod[end - 1].id, "");
            strcpy(prod[end - 1].name, "");
            prod[end - 1].price = 0.0;
            prod[end - 1].stock = 0;

            printf("商品が削除されました。\n");
            return;
        }
    }

    printf("入力された商品コードが見つかりませんでした。\n");
}
void purchaseProd() {
    char tempID[10];
    int quantity;
    int i;

    printf("購入する商品コードを入力してください: ");
    fflush(stdin);
    fgets(tempID, 10, stdin); // ユーザーに購入する商品コードを入力させる

    printf("購入する数量を入力してください: ");
    scanf("%d", &quantity); // ユーザーに購入数量を入力させる

    for (i = 0; i < count; i++) {
        if (strcmp(tempID, prod[i].id) == 0) {
            if (prod[i].stock >= quantity) {
                // 在庫が十分にある場合、商品を購入し在庫数を更新する
                prod[i].stock -= quantity;
                printf("商品が購入されました。\n");
                return;
            } else {
                printf("在庫が不足しています。\n");
                return;
            }
        }
    }

    printf("入力された商品コードが見つかりませんでした。\n");
}

void displayHighestSale() {
    int highestIndex = -1;
    float highestSale = 0.0;

    // 最も高い売上金額を持つ商品を見つける
    for (int i = 0; i < count; i++) {
        if (prod[i].sales > highestSale) {
            highestIndex = i;
            highestSale = prod[i].sales;
        }
    }

    // 最も高い売上金額を持つ商品を表示する
    if (highestIndex != -1) {
        printf("最も高い売上金額を持つ商品:\n");
        printf("ID: %s\n", prod[highestIndex].id);
        printf("商品名: %s\n", prod[highestIndex].name);
        printf("売上金額: %.2f\n", prod[highestIndex].sales);
    } else {
        printf("商品が見つかりませんでした。\n");
    }
}


void displayProd() {
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("番号 |   商品名   |  商品コード  |  数量     | 購入済み  |   価格   | 割引     | 総売上 |\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-4d | %-10s | %-12s | %-9d | %-9d | %-8.2f | %-8d | %-6.2f |\n", i + 1, prod[i].name, prod[i].id, prod[i].stock, prod[i].numSold, prod[i].price, prod[i].discount, prod[i].sales);
    }

    printf("-----------------------------------------------------------------------------------------------\n");
}
