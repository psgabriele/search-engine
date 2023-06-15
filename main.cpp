#include "./include/searchengine.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    SearchEngine searchEngine;
    string folderPath = "./documents";

    vector<string> files;
    set<string> wordbook;
    searchEngine.InvertedIndex(files, folderPath, wordbook);

    string query;
    cout << "Digite sua consulta: ";
    getline(cin, query);

    vector<string> queryWords;
    string word;
    istringstream iss(query);
    while (iss >> word) {
        queryWords.push_back(searchEngine.normalizeWord(word));
    }

    vector<string> relevantDocuments = searchEngine.retrieveDocuments(queryWords);

    cout << "Documentos relevantes:" << endl;
    for (const auto& doc : relevantDocuments) {
        cout << doc << endl;
    }

    return 0;
}