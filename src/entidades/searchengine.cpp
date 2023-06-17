#include "../include/searchengine.hpp"
#include <string>
#include <fstream>
#include <algorithm>

using std::string;
using std::map;

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

void SearchEngine::InvertedIndex(vector<string>& files, string folderPath, set<string>& wordbook) {
    for (const auto& filename : files) {
        string filepath = folderPath + "/" + filename;
        ifstream file(filepath);
        string word;
        while (file >> word) {
            word = normalizeWord(word);
            wordbook.insert(word);
            invertedIndex[word][filename]++;
        }
    }
}


vector<string> SearchEngine::retrieveDocuments(const vector<string>& queryWords) {
    map<string, int> documentCounts;
    map<string, int> documentScores;

    for (const auto& word : queryWords) {
        if (invertedIndex.count(word) > 0) {
            const auto& documents = invertedIndex.at(word);
            for (const auto& document : documents) {
                const string& documentName = document.first;
                int score = document.second;

                documentCounts[documentName]++;
                documentScores[documentName] += score;
            }
        }
    }

    vector<pair<string, int>> sortedDocuments;
    for (const auto& document : documentCounts) {
        if (document.second == queryWords.size()) {
            sortedDocuments.push_back({document.first, documentScores[document.first]});
        }
    }

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