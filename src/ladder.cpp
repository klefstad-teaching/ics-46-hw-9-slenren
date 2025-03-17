#include "../src/ladder.h"
#include <unordered_set>

void error(string word1, string word2, string message) {
    cout << word1 << word2 << message << endl;
}

inline bool edit_distance_within(const string& word1, const string& word2, int d) {
    if (word1 == word2) return false;

    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > d) return false;

    int i = 0, j = 0, count = 0;

    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++count > d) return false;
            (len1 > len2) ? ++i : (len1 < len2) ? ++j : (++i, ++j);
        } else {
            ++i; ++j;
        }
    }

    if (i == len1 && j == len2) return true;

    return count + abs((len1 - i) - (len2 - j)) <= d;
}

inline bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {

    if (begin_word == end_word) return {};
    if (!word_list.count(end_word)) return {};
    queue<vector<string>> ladders;
    unordered_set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int size = ladders.size();
        unordered_set<string> level_visited;

        for (int i = 0; i < size; ++i) {
            vector<string> ladder = std::move(ladders.front());
            ladders.pop();
            const string& last_word = ladder.back();

            if (last_word == end_word) return ladder;

            for (const string& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladders.push(std::move(new_ladder));
                    level_visited.insert(word);
                }
            }
        }
        visited.insert(level_visited.begin(), level_visited.end());
    }
    return {};
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (file) {
        string word;
        while (file >> word) {
            word_list.insert(word);
       }
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    
    cout << "Word ladder found: ";
    for (const auto& word : ladder) {
        cout << word << " ";
    }
    cout << endl;
}

