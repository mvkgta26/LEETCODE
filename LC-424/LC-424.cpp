#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int characterReplacement(string s, int k) 
{
    int n = s.length();

    // Start initially with window-size = k+1
    int left = 0;   // left = 0 , left window edge
    int right = k;  // right = k,
    int max_substring_length = k+1;     // Initialise the max values based on the first window

    vector<int> hash(26,0);     // Constant size array to store the frequency of any upper-case character
    int max_char_freq = 0;    // Frequency of the character with the maximum frequency in the window
    int min_char_to_replace = 0;    // Minimum number of characters to replace to make the window all the same letters

    //First window operations
    //Hash the distinct characters and calc the count of all the distinct characters in the initial window 
    for (int i=left; i <= right; i++)
    {
        // New distinct character discovered in the window, hash it and count it
        hash[s[i]-'A']++;

        // Update the max_char_freq
        max_char_freq = *max_element(hash.begin(), hash.end());
        min_char_to_replace = (right - left + 1) - max_char_freq;    // Window-size - max_char_freq will be least the number of characters to replace to make the window/substring all the same characters
    }

    // Min subtring/window size is k+1. 
    // Hence, the smallest possible substring will result when left = n-(k+1) and right = n-1. 
    // For obvious reasons, no need to iterate for left beyond this point
    while (left <= n-(k+1))
    {
        right = right+1;  // Expand the window to the right
        
        // Corner Case: Expanded till the right end with the current left
        // This means [left:right=n-1] is the longest possible substring for current value of left or any larger value of left
        // Return the maximum substring length, no need to iterate further
        if (right >= n)
        {
            return max_substring_length;
        }

        // Update the hash and max_char_freq for the new right element
        hash[s[right]-'A']++;

        // Update the max_char_freq
        max_char_freq = *max_element(hash.begin(), hash.end());
        min_char_to_replace = (right - left + 1) - max_char_freq;    // Window-size - max_char_freq will be least the number of characters to replace to make the window/substring all the same characters


        
        // New distinct character discovered in the window
        if (hash[s[right]-'A'] == 0)
        {
            // min_char_to_replace, i.e, the number of distinct characters in a substring/window cannot exceed k
            // If after expanding the new right element in the window, max_char_freq will still be proper, then include the new element to the window
            if ( (min_char_to_replace) <= k )
            {
            }

            // If you cannot expand any more on the right with the current left edge, move the left edge to the right
            else
            {   
                // Keep moving the left edge to the right until the window [left:right] has at most k+1 distinct characters
                // Ensure that left does not exceed 
                while ( (min_char_to_replace > k) && (left <= n-(k+1)) )   
                {
                    // Remove the previous left element from the window
                    hash[s[left]-'A']--;
                    left++;

                    // Update the max_char_freq
                    max_char_freq = *max_element(hash.begin(), hash.end());
                    min_char_to_replace = (right - left + 1) - max_char_freq;    // Window-size - max_char_freq will be least the number of characters to replace to make the window/substring all the same characters

                }
            }
        }

        // s[right] element already exists in the window
        else
        {
            // Do nothing, It will not cause any issues with the new window satisfying criteria
        }

        // Update the max_substring_length based on the new window size
        if ( (right-left+1) > max_substring_length )
        {
            max_substring_length = right - left + 1;
        }
    }   

    return max_substring_length;
}

int main()
{   
    // string str = "ABAB";
    // int k = 2;

    string str = "AABABBA";
    int k = 1;

    int out = characterReplacement(str, k);
    cout << out << endl;

    return 0;
}