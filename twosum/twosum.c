#include <stdlib.h>
#include <stdio.h>

int table_size = 50;

typedef struct hashmap_entry HashmapEntry;

struct hashmap_entry {
    int key;
    int value;
    HashmapEntry *next;
};

int hash(int value)
{
    return abs(value) % table_size;
}

HashmapEntry *create_hashmap(int max_nums)
{
    table_size = max_nums;
    HashmapEntry *hash_map = (HashmapEntry *)malloc(sizeof(HashmapEntry) * table_size);

    for (int i = 0; i < table_size; i++) {
        hash_map[i].key = INT32_MAX;
        hash_map[i].value = INT32_MAX;
        hash_map[i].next = NULL;
    }

    return hash_map;
}

void insert(HashmapEntry *hash_map, int key, int value)
{
    int hashed_key = hash(key);
    HashmapEntry *bucket = &hash_map[hashed_key];

    if (bucket->key == INT32_MAX && bucket->next == NULL) 
    {
        bucket->key = key;
        bucket->value = value;
    }
    else
    {
        HashmapEntry *new_entry = (HashmapEntry *)malloc(sizeof(HashmapEntry));
        new_entry->key = key;
        new_entry->value = value;
        new_entry->next = bucket->next;
        bucket->next = new_entry;
    }
}

int search(HashmapEntry *hash_map, int key)
{
    int hashed_key = hash(key);

    HashmapEntry *entry = &hash_map[hashed_key];
    while(entry->next != NULL)
    {
        if (entry->key == key)
            return entry->value;

        entry = entry->next;
    }

    if (entry->key == key)
        return entry->value;

    return INT32_MIN;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    HashmapEntry *hashmap = create_hashmap(numsSize);
    *returnSize = 2;

    for(int j = 0; j < numsSize; j ++) 
    {
        int substraction = target - nums[j];

        int resultIndex = search(hashmap, substraction);

        if (resultIndex != INT32_MIN && j != resultIndex)
        {
            int *results = (int *)malloc(sizeof(int) * 2);
            results[0] = j;
            results[1] = resultIndex;

            return results;
        }
  
        insert(hashmap, nums[j], j);
    }

    return (int *)malloc(sizeof(int) * 2);
}

int main()
{
    int nums[10] = {-11,7,3,2,1,7,-10,11,21,3};

    int returnSize;

    int *results = twoSum(nums, 10, 11, &returnSize);

    printf("[%d,%d]", results[0], results[1]);

    return EXIT_SUCCESS;
}