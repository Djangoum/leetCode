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
    struct ListNode *l1_r = l1;
    struct ListNode *l2_r = l2;

    struct ListNode *head = NULL;
    struct ListNode *end = NULL;

    int trailing = 0;

    while(l1_r != NULL || l2_r != NULL || trailing != 0)
    {
        int val1 = (l1_r != NULL) ? l1_r->val : 0;
        int val2 = (l2_r != NULL) ? l2_r->val : 0;

        int sum = val1 + val2 + trailing;

        if (sum >= 10)
        {
            trailing = sum / 10;
            sum = sum % 10;
        }
        else
        {
            trailing = 0;
        }

        if (head == NULL)
        {
            head = createNode(sum);
            end = head;
        }
        else
        {
            struct ListNode *new_node = createNode(sum);
            end->next = new_node;
            end = new_node;
        }

        if (l1_r != NULL) l1_r = l1_r->next;
        if (l2_r != NULL) l2_r = l2_r->next;
    }

    return head;
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