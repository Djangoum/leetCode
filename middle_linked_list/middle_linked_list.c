#include <stdlib.h>
#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* middleNode(struct ListNode* head) {
    int index = 0;

    for(;;)
    {
        struct ListNode node = head[index];
        struct ListNode double_node = head[index * 2];

        if (double_node.next == NULL)
        {
            return &node;
        }

        index ++;
    }
}

int main () 
{
    int max_nodes = 5;
    struct ListNode *list = (struct ListNode *)malloc(sizeof(struct ListNode) * max_nodes);

    struct ListNode *previous = NULL;
    for(int i = 0; i < max_nodes; i ++)
    {
        list[i].val = i;
        if (previous != NULL)
        {
            list[i].next = previous;
        }
        
        previous = &list[i];
    }

    struct ListNode *middle = middleNode(&list[max_nodes]);

    return EXIT_SUCCESS;
}