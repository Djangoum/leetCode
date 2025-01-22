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

void insert(HashmapEntry *hash_map, char key, int value) {
    int hashed_key = hash(key);
    HashmapEntry *bucket = &hash_map[hashed_key];

    while (bucket != NULL) {
        if (bucket->key == key) {
            bucket->value = value;
            return;
        }
        bucket = bucket->next;
    }

    HashmapEntry *new_entry = (HashmapEntry *)malloc(sizeof(HashmapEntry));
    new_entry->key = key;
    new_entry->value = value;
    new_entry->next = hash_map[hashed_key].next;
    hash_map[hashed_key].next = new_entry;
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

int lengthOfLongestSubstring(char* s) {
    int s_length = strlen(s);
    int window_start = 0;
    int longest_substring_length = 1;

    if (s_length == 0) return 0;

    HashmapEntry *hashmap = create_hashmap(256);

    for (int window_end = 0; window_end < s_length; window_end++) {
        char current_char = s[window_end];
        int closest_index = search(hashmap, current_char);

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
