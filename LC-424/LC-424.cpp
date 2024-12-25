/*
    To find: The largest repeating-substring(substring with all same characters) in s, that can be obtained by replacing at most k elements in s.
    Main Claim: 
        To find the least number of characters to replace to make a substring of all the same characters,
        We need to find the character with the maximum frequency in the substring (max_char_freq), 
        and then subtract this frequency from the 'number of characters in the substring/window' to get the minimum number of characters to replace to make the substing/window all the same characters (min_char_to_replace).
        (Why?? You can show with proof by contradiction)
    
    Logic:
        Iterate the left over the string, find the biggest possible right for every left.
        Track the maximum size of a window over all the left values.

    Algorithm:
        1. Use left and right pointer to indicate left and right edge of the window at any time.
        2. Start with a substring/window of size=1: Start with left = 0 and right = 0.
        4. Expand the window to the right, one by one element. Keep track of maximum size of valid window during all the iterations.
        5. If the window has min_char_to_replace > k, that means it is not a valid window. (You can only replace a maximum of k characters)
            Shrink the window from the left, until the window becomes valid.
        6. With the new valid 'left', once again expand the window to the right, till you reach the longest possible valid window. Keep track of maximum size of valid window over all the iterations.
        7. Repeat steps 5-6, until exit conditions are met. (left > n-(k+1) or right >= n)
        
    In the end, you will have longest repeating substring length.

    Calculating the min_char_to_replace:
        min_char_to_replace = (right - left + 1) - max_char_freq ; where, right - left + 1 = window-size
        Use a 26 element vector to hash the frequency of characters in the sliding window.
        In any iteration/window, to find the character that occurs most frequently do max_char_freq = max(hash).
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int characterReplacement(string s, int k) 
{
    int n = s.length();

    // Start initially with a window-size of 1, with 1 element at the left of s[]
    int left = 0;   // left = 0 , left window edge
    int right = 0;  // Right window edge: Starts at -1 because there is right++ in the beginning of the while loop
    int max_substring_length = 0;     // The maximum length substring with repeating characters

    if (k==n || k==n-1) return n;    //Corner-Case: If k==n or k==n-1

    vector<int> hash(26,0);     // Constant size array to store the frequency of any upper-case character
    int max_char_freq = 0;    // Frequency of the character with the maximum frequency in the window
    int min_char_to_replace = 0;    // Minimum number of characters to replace to make the window all the same letters = Window-size - character with maximum frequency

    /*
    Exit-Case-1: left > n-(k+1) :
        Min subtring/window size is k+1 (Obvious reasons, make k characters same as the k+1 character). 
        Hence, the smallest possible longest_repeating_substring will result when left = n-(k+1) and right = n-1. 
        For obvious reasons, no need to iterate for left beyond this point, all these substrings will surely be smaller
    Exit-Case-2: right < n :
        Means window expanded to the right-most-end with the current left.
        This means [left:right=n-1] is the longest possible substring for current value of left or also any other larger value of left.
        Return the maximum substring length based on all the 'left' we have iterated so far, no need to iterate further, because all the further 'left' values will surely have smaller substring length.
    */
    while (left <= n-(k+1) && right < n)
    {
        // Update the hash and max_char_freq based on the expanded new right element
        hash[s[right]-'A']++;
        max_char_freq = *max_element(hash.begin(), hash.end());
        min_char_to_replace = (right - left + 1) - max_char_freq;    // Window-size - max_char_freq will be least the number of characters to replace to make the window/substring all the same characters

        /* 
        If min_char_to_replace exceeds limit k: shrink window from left till it is satisfied
        Keep moving the left edge to the right until the window [left:right] has at most 'k characters to replace to make it repeating'
        Also, Check that left does not exceed right
        */
        while ( (min_char_to_replace > k) && (left <= n-(k+1)) )   
        {
            //Shrink from left: Remove the previous left element from the window
            hash[s[left]-'A']--;
            left++;

            // Update the max_char_freq and min_char_to_replace based on this new window
            max_char_freq = *max_element(hash.begin(), hash.end());
            min_char_to_replace = (right - left + 1) - max_char_freq;    // Window-size - max_char_freq will be least the number of characters to replace to make the window/substring all the same characters
        }

        // Update the max_substring_length based on the current valid window. Note that at this line, the line will always be valid.
        if ( (right-left+1) > max_substring_length )
        {
            max_substring_length = right - left + 1;
        }

        right = right+1;  // Expand the window to the right 
    }   
    
    return max_substring_length;
}


int main()
{   
    string str = "ABAB";
    int k = 2;

    // string str = "AABABBA";
    // int k = 1;

    int out = characterReplacement(str, k);
    cout << out << endl;

    return 0;
}