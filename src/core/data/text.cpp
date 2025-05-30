#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "core/data/text.h"
#include "core/data/reading.h"


using std::vector;
using std::string;
using std::unordered_map;
using vec_of_vec_str_map = vector<unordered_map<string, vector<string>>>;


string lower_str(string str) {
  string lowered {""};
  for (char c: str) {
    lowered += tolower(c);
  }
  return lowered;
}

string remove_punctuation(string& word) {
  string cleaned_word {word};
  cleaned_word.erase(cleaned_word.begin(),
      std::find_if(cleaned_word.begin(), 
        cleaned_word.end(), 
        [](unsigned char ch){
        return std::isalnum(ch);
        })
  );
  cleaned_word.erase(
      std::find_if(cleaned_word.rbegin(),
        cleaned_word.rend(),
        [](unsigned char ch){
        return std::isalnum(ch);
        }).base(),
      cleaned_word.end()
      );
  return lower_str(cleaned_word);
}

string cleanWord(const string& word) {
    string cleanedWord;

    // Iterate over each character in the word
    for (char ch : word) {
        // Keep only alphabetic characters
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            // Convert to lowercase and add to the result
            cleanedWord += std::tolower(static_cast<unsigned char>(ch));
        }
    }
    return cleanedWord;
}

vector<string> tokenizer(const string& s) {
     vector<string> words;
     std::stringstream ss(s);
     string word;
            
     while (ss >> word) {
        // Clean the word: remove punctuation, remove numbers, and convert to lowercase
        word = cleanWord(word);

        // Add the word to the list if it's not empty       
        if (!word.empty()) {
            words.push_back(word);
                }
            }
     return words;
}
vector<vector<string>> tokenize_dataset(const vector<vector<string>> data){
  vector<vector<string>> result;
  for (const auto& row : data) {
    vector<string> row_words;
    for (const auto& col : row) {
      auto col_words = tokenizer(col);
      row_words.insert(row_words.end(), col_words.begin(), col_words.end());
    }
    result.push_back(row_words);
  }
  return result;
}
