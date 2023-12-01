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

struct Renter renterArray[100]; // �ṹ���������ڱ����������Ϣ
int renterCount = 0; // ��¼��ǰ���������

void createMultimediaLibrary() {
    // ʵ������ͼ���Ĵ���
    // ���浽�ļ���
    FILE *file = fopen("multimedia_library.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ�\n");
    } else {
        // ������ɶ��ʾ������ͼ�鲢���浽�ļ���
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
        printf("����ͼ��ⴴ���ɹ�\n");
    }
}

void rentMultimedia() {
    // ʵ������ͼ������
    // �޸��ļ��е�ʣ������
    // ����������Ϣ���ṹ������
    // ��ȡ����ӡ����ͼ����е���Ϣ
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    printf("��ǰ����ͼ����е���Ϣ��\n");
    printf("���  ����  �۸� ԭ���� ʣ������\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // ѡ��Ҫ��������ͼ��
    char code[10];
    printf("������Ҫ��������ͼ���ţ�");
    scanf("%s", code);

    // �ҵ�Ҫ��������ͼ�鲢�޸��ļ��е�ʣ������
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            if (item.remainingQuantity > 0) {
                item.remainingQuantity--;
                fseek(file, -((int)sizeof(struct Multimedia)), SEEK_CUR);
                fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
                printf("����ͼ�� %s ���ɹ�\n", item.name);
            } else {
                printf("����ͼ�� %s ��治�㣬�޷����\n", item.name);
            }
            break;
        }
    }
    fclose(file);

    // ����������Ϣ���ṹ������
    struct Renter renter;
    strcpy(renter.code, code);
    printf("����������������");
    scanf("%s", renter.name);
    printf("������������ڣ�");
    scanf("%s", renter.rentDate);
    renterArray[renterCount++] = renter;
}

void returnMultimedia() {
    // ʵ������ͼ��Ĺ黹
    // �޸��ļ��е�ʣ������
    // ����������ں͹黹���ڼ������
    // ɾ���������Ϣ
    // ��ȡ����ӡ����ͼ����е���Ϣ
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    printf("��ǰ����ͼ����е���Ϣ��\n");
    printf("���  ����  �۸� ԭ���� ʣ������\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // ѡ��Ҫ�黹������ͼ��
    char code[10];
    printf("������Ҫ�黹������ͼ���ţ�");
    scanf("%s", code);

    // �ҵ�Ҫ�黹������ͼ�鲢�޸��ļ��е�ʣ������
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            item.remainingQuantity++;
            fseek(file, -((int)sizeof(struct Multimedia)), SEEK_CUR);
            fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
            printf("����ͼ�� %s �黹�ɹ�\n", item.name);
            break;
        }
    }
    fclose(file);

    // ����������ں͹黹���ڼ������
    for (int i = 0; i < renterCount; i++) {
        if (strcmp(renterArray[i].code, code) == 0) {
            printf("������黹���ڣ�");
            char returnDate[20];
            scanf("%s", returnDate);
            // ������Ը���������ں͹黹���ڼ������
            // �������Ϊÿ��5Ԫ
            int rentDays = 0; // �����������
            // �������
            float rent = 5 * rentDays;
            printf("���Ϊ��%.2f Ԫ\n", rent);
            // ɾ���������Ϣ
            for (int j = i; j < renterCount - 1; j++) {
                renterArray[j] = renterArray[j + 1];
            }
            renterCount--;
            break;
        }
    }
}

void purchaseMultimedia() {
    // ʵ������ͼ��Ĺ���
    // �޸��ļ��е�ԭ����
    // ��ȡ����ӡ����ͼ����е���Ϣ
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    printf("��ǰ����ͼ����е���Ϣ��\n");
    printf("���  ����  �۸� ԭ���� ʣ������\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // �����¹���������ͼ����Ϣ
    printf("�������¹���������ͼ����Ϣ��\n");
    struct Multimedia newItem;
    printf("��ţ�");
    scanf("%s", newItem.code);
    printf("���ƣ�");
    scanf("%s", newItem.name);
    printf("�۸�");
    scanf("%f", &newItem.price);
    printf("������");
    scanf("%d", &newItem.originalQuantity);
    newItem.remainingQuantity = newItem.originalQuantity;

    // ���¹���������ͼ����Ϣд���ļ�
    file = fopen("multimedia_library.txt", "a");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    fprintf(file, "%s %s %.2f %d %d\n", newItem.code, newItem.name, newItem.price, newItem.originalQuantity, newItem.remainingQuantity);
    fclose(file);

    printf("����ͼ�� %s �ѳɹ�����\n", newItem.name);
}

void scrapMultimedia() {
    // ʵ������ͼ��ı���
    // �޸��ļ��е�ʣ������
    // ��ȡ����ӡ����ͼ����е���Ϣ
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    printf("��ǰ����ͼ����е���Ϣ��\n");
    printf("���  ����  �۸� ԭ���� ʣ������\n");
    struct Multimedia item;
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        printf("%s  %s  %.2f  %d  %d\n", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
    }
    fclose(file);

    // ����Ҫ���ϵ�����ͼ���ź�����
    char code[10];
    int quantity;
    printf("������Ҫ���ϵ�����ͼ���ţ�");
    scanf("%s", code);
    printf("������Ҫ���ϵ�����ͼ��������");
    scanf("%d", &quantity);

    // �����ļ��ж�Ӧ����ͼ���ʣ������
    file = fopen("multimedia_library.txt", "r+");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }
    while (fscanf(file, "%s %s %f %d %d", item.code, item.name, &item.price, &item.originalQuantity, &item.remainingQuantity) != EOF) {
        if (strcmp(item.code, code) == 0) {
            if (quantity <= item.remainingQuantity) {
                item.remainingQuantity -= quantity;
                fseek(file, -sizeof(item), SEEK_CUR);
                fprintf(file, "%s %s %.2f %d %d", item.code, item.name, item.price, item.originalQuantity, item.remainingQuantity);
                printf("����ͼ�� %s �ѳɹ�����\n", item.name);
            } else {
                printf("������������ʣ���������޷�����\n");
            }
            break;
        }
    }
    fclose(file);
}

// �ȽϺ�������������
int compare(const void *a, const void *b) {
    const struct Multimedia *multimediaA = (struct Multimedia *)a;
    const struct Multimedia *multimediaB = (struct Multimedia *)b;
    return multimediaA->remainingQuantity - multimediaB->remainingQuantity;
}

void searchMultimedia() {
    // ʵ������ͼ��Ĳ�ѯ
    // ����ź�ʣ��������ѯͼ���
    // ����ʣ�������ӵ͵�������
    // ��ȡ����ͼ����е���Ϣ
    FILE *file = fopen("multimedia_library.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ�\n");
        return;
    }

    // ��ȡ���洢����ͼ����Ϣ
    struct Multimedia library[100];
    int count = 0;
    while (fscanf(file, "%s %s %f %d %d", library[count].code, library[count].name, &library[count].price, &library[count].originalQuantity, &library[count].remainingQuantity) != EOF) {
        count++;
    }
    fclose(file);

    // ����Ƿ������ݣ�����������ʹ�ӡ
    if (count > 0) {
        // ����ʣ�������ӵ͵�������
        qsort(library, count, sizeof(struct Multimedia), compare);

        // ��ӡ����������ͼ�����Ϣ
        printf("����ʣ�������ӵ͵������������ͼ�����Ϣ��\n");
        printf("���  ����  �۸� ԭ���� ʣ������\n");
        for (int i = 0; i < count; i++) {
            printf("%s  %s  %.2f  %d  %d\n", library[i].code, library[i].name, library[i].price, library[i].originalQuantity, library[i].remainingQuantity);
        }
    } else {
        printf("����ͼ�����û���κ�����\n");
    }
}

int main() {
    srand(time(0)); // ��ʼ�����������

    createMultimediaLibrary(); // ��������ͼ���

    int choice;
    do {
        printf("����ͼ�����������˵�\n");
        printf("1-��������ͼ���\n");
        printf("2-�������ͼ��\n");
        printf("3-�黹����ͼ��\n");
        printf("4-��������ͼ��\n");
        printf("5-��������ͼ��\n");
        printf("6-��ѯ����ͼ��\n");
        printf("0-�˳�ϵͳ\n");
        printf("������ѡ����(0��6):");
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
                printf("�˳�ϵͳ\n");
                break;
            default:
                printf("��Ч��ѡ��\n");
        }
    } while (choice != 0);

    return 0;
}


