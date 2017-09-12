#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

class PathDatabase {
    vector< set<int> > m_db;
    int m_num;
public:
    PathDatabase(int num_of_nodes)
        : m_db(num_of_nodes, set<int>())
        , m_num(num_of_nodes)
    {
    }
    
    void setConnect(int n1, int n2, bool connect = true) {
        if (n1 == n2 || n1 < 0 || n1 >= m_num || n2 < 0 || n2 >= m_num) {
            return;
        }
        m_db[n1].insert(n2);
        m_db[n2].insert(n1);
    }
    
    bool isConnected(int n1, int n2) const {
        if (n1 == n2 || n1 < 0 || n1 >= m_num || n2 < 0 || n2 >= m_num) {
            return false;
        }
        return m_db[n1].find(n2) != m_db[n1].end();
    }
};

typedef vector<vector<int>> Network;

void find_connected_cities(const Network& roads, vector<bool>& visited, int start, vector<int>& cities) {
    cout << "Start = " << start + 1 << endl;
    
    if (visited[start]) {
        return;
    } else {
        visited[start] = true;
        for (int i = 0; i < visited.size(); i++) {
            cout << (visited[i] ? "1" : "0");
        }
        cout << endl;

        cities.push_back(start);
        for (int c : roads[start]) {
            cout << c + 1 << " ";
        }
        cout << endl;

        cout << roads[1][0];
	cout << roads[8][0];
	cout << endl;

	cout << "sizeof roads[" << start << "] = " << roads[start].size() << endl;

        for (int node : roads[start]) {
            find_connected_cities(roads, visited, node, cities);
        }
        /*
        for (int i = 0; i < visited.size(); i++) {
            if (roads.isConnected(start, i)) {
                find_connected_cities(roads, visited, i, cities);
            }
        }
        */
    }
}

int find_min_cost(int cities_count, const Network& roads, int road_cost, int lib_cost) {
    if (lib_cost <= road_cost) {
        return lib_cost * cities_count;
    } else {
        vector<bool> visited(cities_count, false);
        int total_cost = 0;
        for (int i = 0; i < cities_count; i++) {
            if (!visited[i]) {
                vector<int> cities(0);
                find_connected_cities(roads, visited, i, cities);
                total_cost += (lib_cost + (cities.size() - 1) * road_cost);
            }
        }
        return total_cost;
    }
}

int main() {
    int queries;
    cin >> queries;
    for (int i = 0; i < queries; i++) {
        int cities_count, roads_count, road_cost, lib_cost;
        cin >> cities_count
            >> roads_count
            >> lib_cost
            >> road_cost;
        
        cout << "Roads count :" << roads_count << endl;
        
        Network roads(roads_count, vector<int>(0));
        int n1, n2;
        for (int j = 0; j < roads_count; j++) {
            cin >> n1 >> n2;
            roads[n1 - 1].push_back(n2 - 1);
            roads[n2 - 1].push_back(n1 - 1);
        }
        for (int c : roads[8]) {
            cout << c + 1 << " ";
        }
        cout << endl;
        
        cout << find_min_cost(cities_count, roads, road_cost, lib_cost) << endl;
    }
    return 0;
}

