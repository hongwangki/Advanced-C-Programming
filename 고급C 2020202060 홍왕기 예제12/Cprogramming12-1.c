#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
struct Node {
    int data;
    struct Node* next;
};

// �� ��带 �����ϴ� �Լ�
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// ����Ʈ ��� �Լ�
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ���� �Լ�
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int input;

    printf("���ڸ� �Է��ϼ��� (0: ����): ");

    while (1) {
        scanf("%d", &input);

        if (input == 0) {
            break;
        }

        struct Node* newNode = createNode(input);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("�Էµ� ���ڵ�: \n");
    printList(head);

    // �޸� ����
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
