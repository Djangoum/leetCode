#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverse_list(struct ListNode *head)
{
    struct ListNode *prev = NULL;
    struct ListNode *current = head;
    struct ListNode *next;

    while(current)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

struct ListNode* createNode(int val) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

struct ListNode* createLinkedList(int* nums, int size) {
    if (size == 0) return NULL;

    struct ListNode* head = createNode(nums[0]);
    struct ListNode* current = head;

    for (int i = 1; i < size; i++) {
        current->next = createNode(nums[i]);
        current = current->next;
    }

    return head;
}

void printLinkedList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d", current->val);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* current = &dummy;
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry != 0) {
        int sum = carry;
        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }

        carry = sum / 10;
        current->next = createNode(sum % 10);
        current = current->next;
    }

    return dummy.next;
}

int main ()
{
    int nums1[] = {1,8}; // Represents the number 342
    int nums2[] = {0}; // Represents the number 465

    struct ListNode* l1 = createLinkedList(nums1, 2);
    struct ListNode* l2 = createLinkedList(nums2, 1);

    struct ListNode* result = addTwoNumbers(l1, l2);

    printf("Result: ");
    printLinkedList(result);

    // Free the allocated memory (not shown here for brevity)

    return 0;
}