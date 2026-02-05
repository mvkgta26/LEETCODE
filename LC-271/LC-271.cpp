#include <string>
#include <vector>
#include <iostream>


using namespace std;


string encode(vector<string>& strs) 
{
	string encoded_output = "";
	
	
	for (int i=0; i < strs.size(); i++)
	{
		string word = strs[i];
		int word_len = word.size();
		string word_len_str = to_string(word_len);
		
		word_len_str = word_len_str + "#" ;		// Ex: 5#, 22#, 199#
		
		// Append : Current word and the padded word length to the encoded_output
		// Makes "5#ABCDE"
		encoded_output = encoded_output + word_len_str + word;
	}
	
	return encoded_output;
}

vector<string> decode(string s) 
{
	vector<string> output;
	
	string word_len_str = "";
	string word = "";
	
	for ( int i=0; i < s.size(); i++ )
	{
		if (s[i] == '#')
		{
			int word_len = stoi(word_len_str);
			string word = "";
			
			// Iterate the current word in the string
			i++;
			for( int j=0 ; j < word_len; j++ ) 
			{
				word = word + s[i];
				i++;
			}
			i--;  // outer for will do i++; don't skip first digit of next token

			output.push_back(word);
			word_len_str = ""; 	// Reset the word length string
			continue;  // skip the append below. otherwise it will append the last character of the previous word.
		}

		word_len_str = word_len_str + s[i];
	}
	
	return output;
}




int main()
{
	vector<string> strs = {"Hello", "World"};
	
	string encoded = encode(strs);
	cout << "Encoded: " << encoded << endl;
	
	vector<string> decoded = decode(encoded);
	cout << "Decoded: [";
	for (int i = 0; i < decoded.size(); i++)
	{
		cout << "\"" << decoded[i] << "\"";
		if (i < decoded.size() - 1) cout << ", ";
	}
	cout << "]" << endl;
	
	return 0;
}