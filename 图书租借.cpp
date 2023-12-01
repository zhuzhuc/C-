#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Multimedia {
    char code[10];
    char name[100];
    float price;
    int originalQuantity;
    int remainingQuantity;
};

struct Renter {
    char code[10];
    char name[100];
    char rentDate[20];
    float deposit;
    int rentDays;
    float rentFee;
};

struct Renter renterArray[100]; // 结构体数组用于保存租借者信息
int renterCount = 0; // 记录当前租借者数量

void createMultimediaLibrary() {
    // 实现音像图书库的创建
    // 保存到文件中
    FILE *file = fopen("multimedia_library.txt", "w");
    if (file == NULL) {
        printf("无法打开文件\n");
    } else {
        // 随机生成多个示例音像图书并保存到文件中
        for (int i = 0; i < 5; i++) {
            struct Multimedia item;
            sprintf(item.code, "M%d", i + 1);
            sprintf(item.name, "Multimedia %d", i + 1);
            item.price = ((float)rand() / RAND_MAX) * 100.0;
            item.originalQuantity = rand() % 100;
            item.remainingQuantity = item.originalQuantity;
            fprintf(file, "%s %s %.2f %d %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
        }
        fclose(file);
        printf("音像图书库创建成功\n");
    }
}

void rentMultimedia() {
    // 实现音像图书的租借
    // 修改文件中的剩余数量
    // 添加租借者信息到结构体数组
    // 读取并打印音像图书库中的信息
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    printf("当前音像图书库中的信息：\n");
    printf("编号  名称  价格 原数量 剩余数量\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // 选择要租借的音像图书
    char code[10];
    printf("请输入要租借的音像图书编号：");
    scanf("%s", code);

    // 找到要租借的音像图书并修改文件中的剩余数量
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            if (item.remainingQuantity > 0) {
                item.remainingQuantity--;
                fseek(file, -((int)sizeof(struct Multimedia)), SEEK_CUR);
                fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
                printf("音像图书 %s 租借成功\n", item.name);
            } else {
                printf("音像图书 %s 库存不足，无法租借\n", item.name);
            }
            break;
        }
    }
    fclose(file);

    // 添加租借者信息到结构体数组
    struct Renter renter;
    strcpy(renter.code, code);
    printf("请输入您的姓名：");
    scanf("%s", renter.name);
    printf("请输入租借日期：");
    scanf("%s", renter.rentDate);
    renterArray[renterCount++] = renter;
}

void returnMultimedia() {
    // 实现音像图书的归还
    // 修改文件中的剩余数量
    // 根据租借日期和归还日期计算租金
    // 删除租借者信息
    // 读取并打印音像图书库中的信息
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    printf("当前音像图书库中的信息：\n");
    printf("编号  名称  价格 原数量 剩余数量\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // 选择要归还的音像图书
    char code[10];
    printf("请输入要归还的音像图书编号：");
    scanf("%s", code);

    // 找到要归还的音像图书并修改文件中的剩余数量
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            item.remainingQuantity++;
            fseek(file, -((int)sizeof(struct Multimedia)), SEEK_CUR);
            fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
            printf("音像图书 %s 归还成功\n", item.name);
            break;
        }
    }
    fclose(file);

    // 根据租借日期和归还日期计算租金
    for (int i = 0; i < renterCount; i++) {
        if (strcmp(renterArray[i].code, code) == 0) {
            printf("请输入归还日期：");
            char returnDate[20];
            scanf("%s", returnDate);
            // 这里可以根据租借日期和归还日期计算租金
            // 假设租金为每天5元
            int rentDays = 0; // 计算租借天数
            // 计算租金
            float rent = 5 * rentDays;
            printf("租金为：%.2f 元\n", rent);
            // 删除租借者信息
            for (int j = i; j < renterCount - 1; j++) {
                renterArray[j] = renterArray[j + 1];
            }
            renterCount--;
            break;
        }
    }
}

void purchaseMultimedia() {
    // 实现音像图书的购进
    // 修改文件中的原数量
    // 读取并打印音像图书库中的信息
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    printf("当前音像图书库中的信息：\n");
    printf("编号  名称  价格 原数量 剩余数量\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // 输入新购进的音像图书信息
    printf("请输入新购进的音像图书信息：\n");
    struct Multimedia newItem;
    printf("编号：");
    scanf("%s", newItem.code);
    printf("名称：");
    scanf("%s", newItem.name);
    printf("价格：");
    scanf("%f", &newItem.price);
    printf("数量：");
    scanf("%d", &newItem.originalQuantity);
    newItem.remainingQuantity = newItem.originalQuantity;

    // 将新购进的音像图书信息写入文件
    file = fopen("multimedia_library.txt", "a");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    fprintf(file, "%s %s %.2f %d %d\n", newItem.code, newItem.name, newItem.price, newItem.originalQuantity, newItem.remainingQuantity);
    fclose(file);

    printf("音像图书 %s 已成功购入\n", newItem.name);
}

void scrapMultimedia() {
    // 实现音像图书的报废
    // 修改文件中的剩余数量
    // 读取并打印音像图书库中的信息
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    printf("当前音像图书库中的信息：\n");
    printf("编号  名称  价格 原数量 剩余数量\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // 输入要报废的音像图书编号和数量
    char code[10];
    int quantity;
    printf("请输入要报废的音像图书编号：");
    scanf("%s", code);
    printf("请输入要报废的音像图书数量：");
    scanf("%d", &quantity);

    // 更新文件中对应音像图书的剩余数量
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            if (quantity <= item.remainingQuantity) {
                item.remainingQuantity -= quantity;
                fseek(file, -sizeof(item), SEEK_CUR);
                fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
                printf("音像图书 %s 已成功报废\n", item.name);
            } else {
                printf("报废数量超过剩余数量，无法报废\n");
            }
            break;
        }
    }
    fclose(file);
}

// 比较函数，用于排序
int compare(const void *a, const void *b) {
    const struct Multimedia *multimediaA = (struct Multimedia *)a;
    const struct Multimedia *multimediaB = (struct Multimedia *)b;
    return multimediaA->remainingQuantity - multimediaB->remainingQuantity;
}

void searchMultimedia() {
    // 实现音像图书的查询
    // 按编号和剩余数量查询图书库
    // 按照剩余数量从低到高排序
    // 读取音像图书库中的信息
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return;
    }

    // 读取并存储音像图书信息
    struct Multimedia library[100];
    int count = 0;
    while (fscanf(file, "%s %s %f %d %d", library[count].code, library[count].name, &library[count].price, &library[count].originalQuantity, &library[count].remainingQuantity) != EOF) {
        count++;
    }
    fclose(file);

    // 检查是否有内容，并进行排序和打印
    if (count > 0) {
        // 按照剩余数量从低到高排序
        qsort(library, count, sizeof(struct Multimedia), compare);

        // 打印排序后的音像图书库信息
        printf("按照剩余数量从低到高排序的音像图书库信息：\n");
        printf("编号  名称  价格 原数量 剩余数量\n");
        for (int i = 0; i < count; i++) {
            printf("%s  %s  %.2f  %d  %d\n", library[i].code, library[i].name, library[i].price, library[i].originalQuantity, library[i].remainingQuantity);
        }
    } else {
        printf("音像图书库中没有任何内容\n");
    }
}

int main() {
    srand(time(0)); // 初始化随机数种子

    createMultimediaLibrary(); // 创建音像图书库

    int choice;
    do {
        printf("音像图书租借管理主菜单\n");
        printf("1-创建音像图书库\n");
        printf("2-租借音像图书\n");
        printf("3-归还音像图书\n");
        printf("4-购进音像图书\n");
        printf("5-报废音像图书\n");
        printf("6-查询音像图书\n");
        printf("0-退出系统\n");
        printf("请输入选项编号(0—6):");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createMultimediaLibrary();
                break;
            case 2:
                rentMultimedia();
                break;
            case 3:
                returnMultimedia();
                break;
            case 4:
                purchaseMultimedia();
                break;
            case 5:
                scrapMultimedia();
                break;
            case 6:
                searchMultimedia();
                break;
            case 0:
                printf("退出系统\n");
                break;
            default:
                printf("无效的选项\n");
        }
    } while (choice != 0);

    return 0;
}


