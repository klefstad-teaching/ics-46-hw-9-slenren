#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}

#include "../src/ladder.h"

void verify_word_ladder() {

    set<string> word_list;

    load_words(word_list, "/Users/coolkid/Downloads/ics46/ics-46-hw-9-slenren/src/words.txt");

    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);

    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);

    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);

    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);

    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);

    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

int main() {
    // verify_word_ladder();

    set<string> word_list;

    load_words(word_list, "/Users/coolkid/Downloads/ics46/ics-46-hw-9-slenren/src/words.txt");

    vector<string> ladder = generate_word_ladder("were", "were", word_list);
    cout << ladder.size();
    print_word_ladder(ladder);
}