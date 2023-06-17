#include "./include/searchengine.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
    SearchEngine searchEngine;
    string folderPath = "documents";

    vector<string> files;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename());
        }
    }

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

    if (relevantDocuments.empty()) {
        cout << "Nenhum documento encontrado." << endl;
    } else {
        cout << "Documentos relevantes:" << endl;
        for (const auto& doc : relevantDocuments) {
            cout << doc << endl;
        }
    }

    return 0;
}