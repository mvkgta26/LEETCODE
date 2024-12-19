#include <iostream>
#include <unordered_map>
#include <queue>

using namespace std;

int characterReplacement(string s, int k) 
{
    int n = s.length();

    // Start initially with window-size = k+1
    // left = 0 , left window edge
    // right = k

    int left = 0;
    int right = k;
    unordered_map<char, int> hash;
    int min_char_freq = 0;    // Frequency of the character with the minimum frequency in the window

    //First window operations
    //Hash the distinct characters and calc the count of all the distinct characters in the initial window 
    for (int i=left; i <= right; i++)
    {
        // New distinct character discovered in the window, hash it and count it
        if (hash[s[i]] == 0)
        {   
            hash[s[i]]++;
            // min_char_freq++;


            // Update the min_char_freq
            if ( (hash[s[i]] < min_char_freq) )   //(hash[s[i]] != 0) && 
            {
                min_char_freq = hash[s[i]];
            }

        }

        // Previously discovered character
        else
        {
            //do nothing
        }
    }

    // Initialise the max values based on the first window
    // string max_substring = s.substr(0, k+1);
    int max_substring_length = k+1;

    // Min subtring/window size is k+1. 
    // Hence, when left = n-(k+1) and right = n-1, the smallest possible substring will result.
    // For obvious reasons, no need to iterate for left beyond this point
    while (left <= n-(k+1))
    {
        right = right+1;  // Expand the window to the right
        
        // Corner Case: Expanded as much as possible to right with the current left
        // This means [left:right=n-1] is the longest possible substring
        // Return the maximum substring length
        if (right >= n)
        {
            return max_substring_length;
        }

        // Update the hash and min_char_freq for the new right element
        hash[s[right]]++;
        // min_char_freq++;
        
        // New distinct character discovered in the window
        if (hash[s[right]] == 0)
        {
            // min_char_freq, i.e, the number of distinct characters in a substring/window cannot exceed k+1
            // If after expanding the new right element in the window, min_char_freq will still be proper, then include the new element to the window
            if ( (min_char_freq) <= k+1 )
            {
                // hash[s[right]]++;
                min_char_freq++;
            }

            // If you cannot expand any more on the right with the current left edge, move the left edge to the right
            else
            {   
                // Keep moving the left edge to the right until the window [left:right] has at most k+1 distinct characters
                // Ensure that left does not exceed 
                while ( (min_char_freq <= k+1) && (left <= n-(k+1)) )   
                {
                    // Remove the previous left element from the window
                    hash[left]--;

                    // If after removing the previous left edge element, there are no more of the s[left] elements in the new window, reduce the distinct character count
                    if (hash[left] == 0)
                    {
                        min_char_freq--;
                    }

                    left++;
                }
            }
        }

        // s[right] element already exists in the window
        else
        {
            // Do nothing
            // It will not cause any issues with the new window satisfying criteria
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