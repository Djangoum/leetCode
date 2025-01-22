#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int lengthOfLongestSubstring(char* s) {
    int window_start = 0;
    int longest_substring_length = 0;
    int map[256];

    memset(map, -1, sizeof(map));

    for (int window_end = 0; window_end < INT32_MAX; window_end++) {
        if (s[window_end] == '\0') break;

        char current_char = s[window_end];
        int closest_index = map[s[window_end]];

        if (closest_index != -1 && closest_index >= window_start) {
            window_start = closest_index + 1;
        }

        map[s[window_end]] = window_end;

        int current_window_length = window_end - window_start + 1;
        if (current_window_length > longest_substring_length) {
            longest_substring_length = current_window_length;
        }
    }

    return longest_substring_length;
}

int main ()
{
    char *s = "au";

    int longest_substring = lengthOfLongestSubstring(s);

    printf("%d", longest_substring);
}
