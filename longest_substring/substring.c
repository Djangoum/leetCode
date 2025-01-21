#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int table_size = 50;

typedef struct hashmap_entry HashmapEntry;

struct hashmap_entry {
    char key;
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
        hash_map[i].key = -1;
        hash_map[i].value = 0;
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

void free_hashmap(HashmapEntry *hash_map) {
    for (int i = 0; i < table_size; i++) {
        HashmapEntry *entry = hash_map[i].next;
        while (entry != NULL) {
            HashmapEntry *temp = entry;
            entry = entry->next;
            free(temp);
        }
    }
    free(hash_map);
}

int search_closest(HashmapEntry *hash_map, char key, int target) {
    int hashed_key = hash(key);
    HashmapEntry *entry = &hash_map[hashed_key];
    int closest_value = INT32_MAX;
    int min_diff = INT32_MAX;

    while (entry != NULL) {
        if (entry->key == key) {
            int diff = abs(entry->value - target);
            if (diff < min_diff) {
                min_diff = diff;
                closest_value = entry->value;
            }
        }
        entry = entry->next;
    }

    return (closest_value == INT32_MAX) ? -1 : closest_value;
}

int lengthOfLongestSubstring(char* s) {
    int s_length = strlen(s);
    int window_start = 0;
    int longest_substring_length = 1;

    if (s_length == 0) return 0;

    HashmapEntry *hashmap = create_hashmap(256);

    for (int window_end = 0; window_end < s_length; window_end++) {
        char current_char = s[window_end];
        int closest_index = search_closest(hashmap, current_char, window_end);

        if (closest_index != -1 && closest_index >= window_start) {
            window_start = closest_index + 1;
        }

        insert(hashmap, current_char, window_end);

        int current_window_length = window_end - window_start + 1;
        if (current_window_length > longest_substring_length) {
            longest_substring_length = current_window_length;
        }
    }

    free_hashmap(hashmap);

    return longest_substring_length;
}

int main ()
{
    char *s = "abcabcbb";

    int longest_substring = lengthOfLongestSubstring(s);

    printf("%d", longest_substring);
}

/* 

for(int j = i + window_size - 1; j >= i; j --)
            {
                char evaluating_char = s[j];
                for(int h = 1; h < window_size; h ++) 
                {

                    if (evaluating_char == s[j - h])
                    {
                        goto next;
                    }
                }

                longest_substring_lenght ++;
                goto next_window_size;
            }
*/