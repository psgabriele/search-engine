#include "../include/searchengine.hpp"
#include <string>
#include <fstream>
#include <algorithm>

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

vector<string> SearchEngine::retrieveDocuments(const vector<string>& queryWords) {
    map<string, int> documentScores;

    for (const auto& word : queryWords) {
        if (invertedIndex.count(word) > 0) {
            const auto& documents = invertedIndex.at(word);
            for (const auto& document : documents) {
                const string& documentName = document.first;
                int score = document.second;

                documentScores[documentName] += score;
            }
        }
    }

    vector<pair<string, int>> sortedDocuments(documentScores.begin(), documentScores.end());
    sort(sortedDocuments.begin(), sortedDocuments.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    vector<string> relevantDocuments;
    for (const auto& document : sortedDocuments) {
        relevantDocuments.push_back(document.first);
    }

    return relevantDocuments;
}