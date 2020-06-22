/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
      vector<std::tuple<std::string, std::string, std::string>> ret;

      /* Your code goes here! */
      ifstream filewords(word_list_fname);
      string word;
      if(filewords.is_open()==1){
    	   while(getline(filewords, word)){
        	if(word.length() == 5){
            string str1 = word.substr(0, 1);
        		string str2 = word.substr(1, word.length()-1);
        		string str3 = word.substr(2, word.length()-2);
        		str1.append(str3);
        		if(d.homophones(str2, str1)){
        			ret.push_back(make_tuple(word, str2, str1));
        		}
        	}
        }
    }
    return ret;
}
