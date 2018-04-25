#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <chrono>
#include <algorithm>
#include <queue>

#include "mylib.h"

using namespace std;
using namespace std::chrono;
using namespace KennethLo;

vector<string> split_string(string);

/**
 * @brief Dijkstra with priority_queue
 * 
 * This one is modified from the reference answer of Hackerrank's
 * editorial.
 * 
 * @param n Number of vertices.
 * @param edges The vector of edges.
 * @param s Starting vertex.
 */
vector<int>dijkstra_method4(int n, const vector<vector<int>>& edges, int s) {
    // organize graph
    vector<map<int, int>> graph(n + 1);
    for (const auto& edge : edges) {
        if (graph[edge[0]].find(edge[1]) == graph[edge[0]].end() ||
            graph[edge[0]][edge[1]] > edge[2])
        {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
    }

    vector<int> dist(n + 1, -1);
    vector<int> visited(n + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    dist[s] = 0;
    q.push({0, s});

    int curr_vertex = s;
    while(!q.empty()) {
        int v = q.top().second;
        int d = q.top().first;
        q.pop();

        // Filter out dupicated nodes.
        if (visited[v])
            continue;
        visited[v] = 1;
        dist[v] = d;

        for (const auto& edge : graph[v]) {
            if (dist[edge.first] == -1 ||
                dist[edge.first] > dist[v] + edge.second)
            {
                // No need to "update" existing node in queue; just add new.
                // 1. The smallest node will be popped first since queue is
                //    always sorted.
                // 2. Duplicated nodes will be dropped directly.
                dist[edge.first] = dist[v] + edge.second;
                q.push({dist[edge.first], edge.first});
            }
        }
    }

    dist.erase(dist.begin() + s);
    dist.erase(dist.begin());

    return dist;
}

/**
 * @brief Dijkstra with heap
 * 
 * This is my final submission.
 * 
 * @param n Number of vertices.
 * @param edges The vector of edges.
 * @param s Starting vertex.
 */
vector<int>dijkstra_method3(int n, const vector<vector<int>>& edges, int s) {
    // organize graph
    vector<map<int, int>> graph(n + 1);
    for (const auto& edge : edges) {
        if (graph[edge[0]].find(edge[1]) == graph[edge[0]].end() ||
            graph[edge[0]][edge[1]] > edge[2])
        {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
    }

    vector<int> dist(n + 1);
    vector<int> heap;

    for (int i = 0; i < dist.size(); i++) {
        dist[i] = -1;
    }
    dist[s] = 0;

    auto compare = [&](int a, int b) { return dist[a] > dist[b]; };
    int curr_vertex = s;
    heap.push_back(s);
    while (heap.size() > 0) {
        // Find the vertex with minimum value
        pop_heap(heap.begin(), heap.end(), compare);
        //cout << heap << endl;
        //cout << "dist[" << heap.back() << "] = " << dist[heap.back()] << endl;
        curr_vertex = heap.back();
        heap.pop_back();

        // Update candidates
        for (const auto& pair : graph[curr_vertex]) {
            if (dist[pair.first] == -1) { // not decided yet
                dist[pair.first] = dist[curr_vertex] + pair.second;
                heap.push_back(pair.first);
                push_heap(heap.begin(), heap.end(), compare);
            } else {
                if (dist[pair.first] > dist[curr_vertex] + pair.second) {
                    dist[pair.first] = dist[curr_vertex] + pair.second;
                    make_heap(heap.begin(), heap.end(), compare);
                }
            }
        }
    }

    dist.erase(dist.begin() + s);
    dist.erase(dist.begin());

    return dist;
}

vector<int>dijkstra_method2(int n, const vector<vector<int>>& edges, int s) {
    // organize graph
    vector<map<int, int>> graph(n + 1);
    for (const auto& edge : edges) {
        if (graph[edge[0]].find(edge[1]) == graph[edge[0]].end() ||
            graph[edge[0]][edge[1]] > edge[2])
        {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
    }

    map<int, int> mapCand;
    map<int, int> mapDone;
    map<int, int> mapOrphan;

    mapDone[s] = 0;
    for (int i = 1; i <= n; i++) {
        if (i != s) {
            mapOrphan[i] = -1;
        }
    }
    int curr_vertex = s;
    for (;;) {
        // Update candidates
        for (const auto& pair : graph[curr_vertex]) {
            if (mapDone.find(pair.first) == mapDone.end()) { // not decided yet
                if (mapOrphan.find(pair.first) != mapOrphan.end()) {
                    mapOrphan.erase(pair.first);
                    mapCand[pair.first] = mapDone[curr_vertex] + pair.second;
                } else if (mapCand[pair.first] > mapDone[curr_vertex] + pair.second) {
                    mapCand[pair.first] = mapDone[curr_vertex] + pair.second;
                }
            }
        }

        // Find the vertex with minimum value
        int min_value = numeric_limits<int>::max();
        map<int, int>::iterator min_vertex = mapCand.end();
        for (auto itor = mapCand.begin(); itor != mapCand.end(); ++itor) {
            if (min_value > itor->second) {
                min_value = itor->second;
                min_vertex = itor;
            }
        }
        if (min_vertex != mapCand.end())
        {
            mapDone[min_vertex->first] = min_vertex->second;
            curr_vertex = min_vertex->first;
            mapCand.erase(min_vertex);
        }

        if (mapCand.size() == 0 && mapOrphan.size() == 0) {
            break;
        }
    }

    vector<int> result(n + 1, -1);
    for (const auto& item : mapDone) {
        result[item.first] = item.second;
    }
    result.erase(result.begin() + s);
    result.erase(result.begin());
    return result;
}

vector<int>dijkstra_method(int n, const vector<vector<int>>& edges, int s) {
    vector<int> result(n + 1, -1);

    // organize graph
    vector<map<int, int>> graph(n + 1);
    for (const auto& edge : edges) {
        if (graph[edge[0]].find(edge[1]) == graph[edge[0]].end() ||
            graph[edge[0]][edge[1]] > edge[2])
        {
            graph[edge[0]][edge[1]] = edge[2];
            graph[edge[1]][edge[0]] = edge[2];
        }
    }
    
    vector<int> candidates(n + 1, -1);
    candidates[s] = result[s] = 0;
    int curr_vertex = s;
    for (;;) {
        for (const auto& pair : graph[curr_vertex]) {
            if (result[pair.first] == -1) { // not decided yet
                if (candidates[pair.first] == -1 ||
                    candidates[pair.first] > result[curr_vertex] + pair.second)
                {
                    candidates[pair.first] = result[curr_vertex] + pair.second;
                }
            }
        }

        int min_value = numeric_limits<int>::max();
        int min_vertex = 0;
        for (int i = 1; i <= n; i++) {
            if (result[i] == -1 && candidates[i] != -1 &&
                min_value > candidates[i])
            {
                min_value = candidates[i];
                min_vertex = i;
            }
        }
        if (min_vertex != 0)
        {
            result[min_vertex] = min_value;
            curr_vertex = min_vertex;
        }
        else
        {
            break;
        }
    }

    result.erase(result.begin() + s);
    result.erase(result.begin());
    return result;
}

/*
 * Complete the shortestReach function below.
 */
vector<int> shortestReach(int n, const vector<vector<int>>& edges, int s) {
    return dijkstra_method4(n, edges, s);
}

#define USE_SCANF

int main()
{
#ifndef USE_SCANF
    ios::sync_with_stdio(false);
    cin.tie(0);
#endif
    ofstream fout(getenv("OUTPUT_PATH"));

    high_resolution_clock::time_point t1 = high_resolution_clock::now();

    int t;
#ifdef USE_SCANF
    scanf("%d", &t);
#else
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

    for (int t_itr = 0; t_itr < t; t_itr++) {
#ifdef USE_SCANF
        int n, m;
        scanf("%d %d", &n, &m);
#else
       string nm_temp;
       getline(cin, nm_temp);

       vector<string> nm = split_string(nm_temp);

       int n = stoi(nm[0]);

       int m = stoi(nm[1]);
#endif

        vector<vector<int>> edges(m);
        for (int edges_row_itr = 0; edges_row_itr < m; edges_row_itr++) {
            edges[edges_row_itr].resize(3);
#ifdef USE_SCANF
            scanf("%d %d %d", &edges[edges_row_itr][0], &edges[edges_row_itr][1], &edges[edges_row_itr][2]);
#else
            for (int edges_column_itr = 0; edges_column_itr < 3; edges_column_itr++) {
               cin >> edges[edges_row_itr][edges_column_itr];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif
        }

        int s;
#ifdef USE_SCANF
        scanf("%d", &s);
#else
        cin >> s;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
#endif

        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(t2 - t1).count();
        cout << duration << "ms\n";
        vector<int> result = shortestReach(n, edges, s);

        for (int result_itr = 0; result_itr < result.size(); result_itr++) {
            fout << result[result_itr];

            if (result_itr != result.size() - 1) {
                fout << " ";
            }
        }

        fout << "\n";
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(t2 - t1).count();
    cout << duration << "ms\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
