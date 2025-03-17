#include "../src/ladder.h"

void error(string word1, string word2, string message) {
    cout << word1 << word2 << message << endl;
}

inline bool edit_distance_within(const string& word1, const string& word2, int d) {
    int len1 = word1.size(), len2 = word2.size();
    if (abs(len1 - len2) > 1) return false;
    
    int i = 0, j = 0, count = 0;
    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++count > 1) return false;
            if (len1 > len2) ++i;
            else if (len1 < len2) ++j;
            else { ++i; ++j; }
        } else {
            ++i; ++j;
        }
    }
    return true;
}

inline bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word || !word_list.count(end_word)) return {};
    
    queue<vector<string>> ladders;
    unordered_set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);
    
    while (!ladders.empty()) {
        int size = ladders.size();
        unordered_set<string> level_visited;
        
        while (size--) {
            vector<string> ladder = std::move(ladders.front());
            ladders.pop();
            const string& last_word = ladder.back();
            
            for (const auto& word : word_list) {
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) return new_ladder;
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
