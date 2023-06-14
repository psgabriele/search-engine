#include "../include/searchengine.hpp"
#include <string>
#include <fstream>

using std::string;

using namespace std;

string SearchEngine::normalizeWord(string word) {
    string normalizedWord;
    for (char character : word) {
        if (isalpha(character)) {
            normalizedWord += tolower(character);
        }
    }
    return normalizedWord;
}

void SearchEngine::InvertedIndex(vector<string>& words, string filename, set<string>& wordbook) {
    fstream file;
    filename = "../documents/" + filename;
    file.open(filename.c_str(), fstream::in | fstream::out);
    string word;
    if(file.is_open()) {
        while(file >> word) {
            word = normalizeWord(word);
            words.push_back(word);
            wordbook.insert(word);
        }
        file.close();
    }
}