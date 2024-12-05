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

// ���밪�� ���� ��带 �����ϴ� �Լ�
struct Node* deleteNode(struct Node* head, int data, struct Node** deletedHead) {
    struct Node* current = head;
    struct Node* previous = NULL;

    while (current != NULL) {
        if (abs(current->data) == abs(data)) {
            struct Node* temp = current;
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }

            // ������ ��带 ������ ����Ʈ�� �߰�
            temp->next = *deletedHead;
            *deletedHead = temp;

            current = previous ? previous->next : head;
        } else {
            previous = current;
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
        //������ ��� ����
        else if (input < 0) {
            head = deleteNode(head, input, &deletedHead);
        } else {
            struct Node* newNode = createNode(input);
            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    //���� ����Ʈ ���
    printf("���� ����Ʈ: \n");
    printList(head);

    //������ ��� ���
    printf("������ ���ڵ�: \n");
    printList(deletedHead);

    return 0;
}
