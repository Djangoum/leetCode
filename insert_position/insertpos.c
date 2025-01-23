#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMS_SIZE 4

int searchInsert(int* nums, int numsSize, int target) {
    int start = 0;
    int end = numsSize;

    while(true)
    {
        int index = (end + start) / 2;

        if (nums[index] == target) 
        {
            return index;
        }
        else if (target > nums[index])
        {
            if (index + 1 == numsSize || target < nums[index + 1]) return index + 1;

            start = index;
        }
        else if (target < nums[index])
        {
            if (index - 1 == -1 || target > nums[index - 1]) return index;

            end = index;
        }
    }
}

int main ()
{
    int nums[NUMS_SIZE] = { 1,3,5,6 };

    int result = searchInsert(nums, NUMS_SIZE, 2);

    printf("%d", result);
}