#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
struct Node {
    int data;
    struct Node* next;
};

// 새 노드를 생성하는 함수
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 리스트 출력 함수
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 메인 함수
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int input;

    printf("숫자를 입력하세요 (0: 종료): ");

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

    printf("입력된 숫자들: \n");
    printList(head);

    // 메모리 해제
    struct Node* current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
