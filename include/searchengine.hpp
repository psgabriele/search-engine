#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <vector>
#include <set>

using namespace std;
using std::string;

class SearchEngine {
public:
    void InvertedIndex(vector<string>& words, string filename, set<string>& wordbook);

private:
    string normalizeWord(string word);
};

#endif
