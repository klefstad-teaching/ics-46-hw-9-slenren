#include "../src/dijkstras.h"

int main() {
    Graph test; 
    vector<int> prev;
    file_to_graph("/Users/coolkid/Downloads/ics46/ics-46-hw-9-slenren/src/small.txt", test);
    vector<int> dist = dijkstra_shortest_path(test, 0, prev);
    vector<int> path = extract_shortest_path(dist, prev, 2);
    int total;
    print_path(path, total);
}