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

// 절대값이 같은 노드를 삭제하는 함수
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

            // 삭제된 노드를 삭제된 리스트에 추가
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

// 메인 함수
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* deletedHead = NULL;
    int input;

    printf("숫자를 입력하세요 (0: 종료): ");

    while (1) {
        scanf("%d", &input);

        if (input == 0) {
            break;
        }
        //음수면 노드 삭제
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

    //최종 리스트 출력
    printf("최종 리스트: \n");
    printList(head);

    //삭제한 노드 출력
    printf("삭제된 숫자들: \n");
    printList(deletedHead);

    return 0;
}
