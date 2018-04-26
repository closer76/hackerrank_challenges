#include <iostream>
#include <vector>
#include <bitset>

#include "mylib.h"

using namespace std;
using namespace KennethLo;

int HammingWeight(uint64_t num) {
    constexpr uint64_t m1 = 0x5555555555555555; // 0b01010101010101010101.....
    constexpr uint64_t m2 = 0x3333333333333333; // 0b00110011001100110011.....
    constexpr uint64_t m4 = 0x0F0F0F0F0F0F0F0F; // 0b00001111000011110000.....
    constexpr uint64_t m8 = 0x00FF00FF00FF00FF;
    constexpr uint64_t m16 = 0x0000FFFF0000FFFF;
    constexpr uint64_t m32 = 0x00000000FFFFFFFF;
    constexpr uint64_t h01 = 0x0101010101010101;

    num -= (num >> 1) & m1;
    num = (num & m2) + ((num >> 2) & m2);
    num = (num + (num >> 4)) & m4;
    return static_cast<int>((num * h01) >> 56);
}

int main() {
    ios::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<uint64_t> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        d[i] = (bitset<64>(d[i]).count() > 1) ? d[i] : 0;
    }

    vector<vector<uint64_t>> graph;
    graph.push_back(vector<uint64_t>(1, 0));
    for (int i = 0; i < d.size(); ++i) {
        int count = graph.size();
        for (int j = 0; j < count; j++) {
            vector<uint64_t> node(graph[j]);
            uint64_t accu = d[i];
            int comp_count = node.size();
            for (int k = comp_count - 1; k >= 0; --k) {
                if (node[k] == 0 || (accu & node[k]) != 0) {
                    accu |= node[k];
                    node.erase(node.begin() + k);
                }
            }
            node.push_back(accu);
            graph.push_back(node);
        }
    }

    int ans = 0;
    for (auto& v : graph) {
        if (v[0] == 0) {
            ans += 64;
        } else {
            uint64_t accu = 0;
            for (auto x : v) {
                accu |= x;
            }
            ans += (64 - bitset<64>(accu).count()) + v.size();
        }
    }

    cout << ans << endl;

    return 0;
}