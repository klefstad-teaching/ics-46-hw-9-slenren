#include "../src/ladder.h"

void error(string word1, string word2, string message) {
    cout << word1 << word2 << message << endl;
}

bool edit_distance_within(const string& word1, const string& word2, int d) {
    if (word1 == word2) return true;
    int len1 = word1.length(), len2 = word2.length();
    if (abs(len1 - len2) > d) return false;

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

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) return {};
    queue<vector<string>> ladders;
    set<string> visited;
    ladders.push({begin_word});
    visited.insert(begin_word);

    while (!ladders.empty()) {
        int size = ladders.size();
        set<string> level_visited;

        for (int i = 0; i < size; ++i) {
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();

            if (last_word == end_word) return ladder;

            for (const string& word : word_list) {
                // cout << word;
                if (!visited.count(word) && is_adjacent(last_word, word)) {
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    level_visited.insert(word);
                    // cout << "CHOSEN!!!" << word << endl;;
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
    }
    
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i) {
        cout << ladder[i] << " ";
    }
    cout << endl;
}

