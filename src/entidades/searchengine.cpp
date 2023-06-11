#include "../include/searchengine.hpp"
#include <string>

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