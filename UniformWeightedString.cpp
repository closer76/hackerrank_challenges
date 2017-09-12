#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool hasUniformString(int weight, const vector<int>& freq) {
    //int rx = sqrt(weight);
    for (int i = 1; i <= 26 && weight >= i; i++) {
        if (weight % i == 0) {
            int j = weight / i;
            if (freq[i - 1] >= j) {
                return true;
            }
        }
    }
    
    return false;
}

int main(){
    string s;
    cin >> s;

    vector<int> freq(26, 0);
    char last_ch = 0;
    int seq = 0;
    for (char ch : s) {
        if (last_ch != ch) {
            last_ch = ch;
            seq = 1;
        } else {
            seq++;
        }
        freq[ch - 'a'] = max(freq[ch - 'a'], seq);
    }

    for (int i = 0; i < 26; i++) {
	cerr << 1 + i << ":" << freq[i] << endl;
    }
    
    int n;
    cin >> n;
    for(int a0 = 0; a0 < n; a0++){
        int x;
        cin >> x;
        
        cout << (hasUniformString(x, freq) ? "Yes" : "No") << endl;
    }
    return 0;
}


