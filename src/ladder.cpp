#include "../src/ladder.h"

void error(string word1, string word2, string message) {
    cout << word1 << word2 << message << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > 1) return false;

    int i = 0, j = 0, count = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++count > 1) {
                return false;
            }
            if (len1 > len2) {
                i++;
            } else if (len1 < len2) {
                j++;
            } else {
                i++;
                j++;
            }
        } else {
            i++;
            j++;
        }
    }
    return true;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladders;
    set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);
}