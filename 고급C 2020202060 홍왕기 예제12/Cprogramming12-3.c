#include <stdio.h>
#include <stdlib.h>

// ��� ����ü ����
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// �� ��带 �����ϴ� �Լ�
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
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

// ���밪�� ���� ��带 �����ϴ� �Լ�
struct Node* deleteNode(struct Node* head, int data, struct Node** deletedHead) {
    struct Node* current = head;

    while (current != NULL) {
        if (abs(current->data) == abs(data)) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            // ������ ��带 ������ ����Ʈ�� �߰�
            current->next = *deletedHead;
            if (*deletedHead != NULL) {
                (*deletedHead)->prev = current;
            }
            current->prev = NULL;
            *deletedHead = current;

            current = head;
        } else {
            current = current->next;
        }
    }

    return head;
}

// ���� �Լ�
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* deletedHead = NULL;
    int input;

    printf("���ڸ� �Է��ϼ��� (0: ����): ");

    while (1) {
        scanf("%d", &input);

        if (input == 0) {
            break;
        }
        // ������ ��� ����
        else if (input < 0) {
            head = deleteNode(head, input, &deletedHead);
        } else {
            struct Node* newNode = createNode(input);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                newNode->prev = tail;
                tail = newNode;
            }
        }
    }

    // ���� ����Ʈ ���
    printf("���� ����Ʈ: \n");
    printList(head);

    // ������ ��� ���
    printf("������ ���ڵ�: \n");
    printList(deletedHead);

    return 0;
}
