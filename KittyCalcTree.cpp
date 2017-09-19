#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

//#define DBG

class Query {
    vector<int> m_rtree;
public:
    Query(size_t size)
        : m_rtree(size,0)
    {}

    void setRTree(int index, int parent) { m_rtree[index] = parent; }
    #ifdef DBG
    void printRTree() {
        for (auto i : m_rtree) {
            cout << i << " ";
        }
        cout << endl;
    }
    #endif
    
    int getDistance(int a, int b) {
        stack<int> sa, sb;
        #ifdef DBG
        cout << a << " ";
        #endif
        sa.push(a);
        while(a) {
            a = m_rtree[a];
            #ifdef DBG
            cout << a << " ";
            #endif
            sa.push(a);
        }
        #ifdef DBG
        cout << endl;
        cout << b << " ";
        #endif
        sb.push(b);
        while(b) {
            b = m_rtree[b];
            #ifdef DBG
            cout << b << " ";
            #endif
            sb.push(b);
        }
        #ifdef DBG
        cout << endl;
        #endif
        
        while(!sa.empty() && !sb.empty() && sa.top() == sb.top()) {
            #ifdef DBG
            cout << sa.top() << " ";
            #endif
            sa.pop();
            sb.pop();
        }
        
        return sa.size() + sb.size();
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    
    Query query(n);
    int tmp1, tmp2;
    for (int i = 0; i < n - 1; i ++) {
        cin >> tmp1 >> tmp2;
        query.setRTree(max(tmp1, tmp2) - 1, min(tmp1, tmp2) - 1);
    }
    
    #ifdef DBG
    //query.printRTree();
    #endif
    for (int i = 0; i < q; i++) {
        int count;
        cin >> count;
        vector<int> arr(count);
        for (int j = 0; j < count; j++) {
            cin >> arr[j];
        }
        
        int result = 0;
        for (int x = 0; x < arr.size() - 1; x++) {
            for (int y = x + 1; y < arr.size(); y++) {
                result += arr[x] * arr[y] * query.getDistance(arr[x] - 1, arr[y] - 1);
                if (result >= 1000000007) {
                    result -= 1000000007;
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}
