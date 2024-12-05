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

// ¦��, Ȧ�� ����Ʈ�� ������ �Լ�
void splitList(struct Node* head, struct Node** oddHead, struct Node** evenHead) {
    struct Node* current = head;

    while (current != NULL) {
        struct Node* next = current->next;  // ���� ��� ����
        current->next = current->prev = NULL;  // ���� ��� �и�

        if (current->data % 2 == 0) {
            // ¦�� ����Ʈ�� �߰�
            current->next = *evenHead;
            if (*evenHead != NULL) {
                (*evenHead)->prev = current;
            }
            *evenHead = current;
        } else {
            // Ȧ�� ����Ʈ�� �߰�
            current->next = *oddHead;
            if (*oddHead != NULL) {
                (*oddHead)->prev = current;
            }
            *oddHead = current;
        }

        current = next;  // ���� ���� �̵�
    }
}

// Ȧ�� ����Ʈ�� ¦�� ����Ʈ�� ��ġ�� �Լ�
struct Node* mergeLists(struct Node* oddHead, struct Node* evenHead) {
    if (oddHead == NULL) return evenHead;
    if (evenHead == NULL) return oddHead;

    struct Node* oddTail = oddHead;
    while (oddTail->next != NULL) {
        oddTail = oddTail->next;
    }
    oddTail->next = evenHead;
    evenHead->prev = oddTail;

    return oddHead;
}

// ����Ʈ�� �����ϴ� �Լ� (���� ���� ���)
struct Node* sortList(struct Node* head) {
    if (head == NULL || head->next == NULL) return head;

    struct Node* current;
    struct Node* lastSorted = NULL;
    int swapped;

    do {
        swapped = 0;
        current = head;

        while (current->next != lastSorted) {
            if (current->data > current->next->data) {
                // ��� �� ��ȯ
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;

                swapped = 1;
            }
            current = current->next;
        }
        lastSorted = current;
    } while (swapped);

    return head;
}

// ���� �Լ�
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* deletedHead = NULL;
    struct Node* oddHead = NULL;
    struct Node* evenHead = NULL;
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

    // ¦��, Ȧ�� ����Ʈ�� �и�
    splitList(head, &oddHead, &evenHead);

    // Ȧ�� -> ¦�� ������ ����
    struct Node* mergedList = mergeLists(oddHead, evenHead);

    // ���� �� ����Ʈ ���
    printf("���� �� ����Ʈ: \n");
    printList(mergedList);

    // ����Ʈ ����
    mergedList = sortList(mergedList);

    // ���� �� ����Ʈ ���
    printf("���� �� ����Ʈ: \n");
    printList(mergedList);

    // ������ ��� ���
    printf("������ ���ڵ�: \n");
    printList(deletedHead);

    return 0;
}
