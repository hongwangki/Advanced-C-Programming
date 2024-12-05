#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 정의
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// 새 노드를 생성하는 함수
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
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

            // 삭제된 노드를 삭제된 리스트에 추가
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

// 짝수, 홀수 리스트로 나누는 함수
void splitList(struct Node* head, struct Node** oddHead, struct Node** evenHead) {
    struct Node* current = head;

    while (current != NULL) {
        struct Node* next = current->next;  // 다음 노드 저장
        current->next = current->prev = NULL;  // 현재 노드 분리

        if (current->data % 2 == 0) {
            // 짝수 리스트에 추가
            current->next = *evenHead;
            if (*evenHead != NULL) {
                (*evenHead)->prev = current;
            }
            *evenHead = current;
        } else {
            // 홀수 리스트에 추가
            current->next = *oddHead;
            if (*oddHead != NULL) {
                (*oddHead)->prev = current;
            }
            *oddHead = current;
        }

        current = next;  // 다음 노드로 이동
    }
}

// 홀수 리스트와 짝수 리스트를 합치는 함수
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

// 리스트를 정렬하는 함수 (버블 정렬 사용)
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
                // 노드 값 교환
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

// 메인 함수
int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* deletedHead = NULL;
    struct Node* oddHead = NULL;
    struct Node* evenHead = NULL;
    int input;

    printf("숫자를 입력하세요 (0: 종료): ");

    while (1) {
        scanf("%d", &input);

        if (input == 0) {
            break;
        }
        // 음수면 노드 삭제
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

    // 짝수, 홀수 리스트로 분리
    splitList(head, &oddHead, &evenHead);

    // 홀수 -> 짝수 순서로 병합
    struct Node* mergedList = mergeLists(oddHead, evenHead);

    // 정렬 전 리스트 출력
    printf("정렬 전 리스트: \n");
    printList(mergedList);

    // 리스트 정렬
    mergedList = sortList(mergedList);

    // 정렬 후 리스트 출력
    printf("정렬 후 리스트: \n");
    printList(mergedList);

    // 삭제한 노드 출력
    printf("삭제된 숫자들: \n");
    printList(deletedHead);

    return 0;
}
