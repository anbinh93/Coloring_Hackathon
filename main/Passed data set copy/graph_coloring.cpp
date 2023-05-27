#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

//Định nghĩa hàm Dsatur
vector<int> dsatur(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> colors(n, 0);
    vector<int> saturation(n, 0);
    set<int> uncolored;
    for (int i = 0; i < n; i++) {
        uncolored.insert(i);
    }

    while (!uncolored.empty()) {
        int max_saturation = -1;
        int max_degree = -1;
        int selected_vertex = -1;

        for (int vertex : uncolored) {
            if (saturation[vertex] > max_saturation || (saturation[vertex] == max_saturation && graph[vertex].size() > max_degree)) {
                max_saturation = saturation[vertex];
                max_degree = graph[vertex].size();
                selected_vertex = vertex;
            }
        }

        set<int> used_colors;
        for (int neighbor : graph[selected_vertex]) {
            if (colors[neighbor] != 0) {
                used_colors.insert(colors[neighbor]);
            }
        }

        int color = 1;
        while (used_colors.find(color) != used_colors.end()) {
            color++;
        }

        colors[selected_vertex] = color;
        uncolored.erase(selected_vertex);

        for (int neighbor : graph[selected_vertex]) {
            if (colors[neighbor] == 0) {
                saturation[neighbor]++;
            }
        }
    }

    return colors;
}

int main() {
    ifstream infile("dothi.txt");
    ofstream outfile("dothitomau.txt");

    int n, m;
    infile >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        infile >> u >> v;
        graph[u - 1].push_back(v - 1);
        graph[v - 1].push_back(u - 1);
    }

    vector<int> colors = dsatur(graph);
    int max_color = *max_element(colors.begin(), colors.end());
    outfile << max_color << endl;
    for (int i = 0; i < n; i++) {
        outfile << colors[i] << endl;
    }

    infile.close();
    outfile.close();

    return 0;
}
