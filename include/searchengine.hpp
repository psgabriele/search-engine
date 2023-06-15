#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;
using std::string;
using std::vector;
using std::set;
using std::map;

class SearchEngine {
public:
    void InvertedIndex(vector<string>& words, string filename, set<string>& wordbook);
    vector<string> retrieveDocuments(const vector<string>& queryWords);
    string normalizeWord(string word);

private:
    map<string, map<string, int>> invertedIndex;
};

#endif
