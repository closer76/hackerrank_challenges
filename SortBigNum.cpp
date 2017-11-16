#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> arr(n);
    vector<int> index(n);
    vector<int> length(n);
    for (int i = 0; i < n; i++) {
        cin >> (arr)[i];
	index[i] = i;
	length[i] = arr[i].length();
	//cout << length[i] << endl;
    }

    cout << "Read ok" << endl;
    
    auto compStr = [](string& a, string& b) -> bool {
        if (a.length() != b.length()) {
            return a.length() < b.length();
        } else {
            auto itor_a = a.begin();
            auto itor_b = b.begin();
            for (; itor_a != a.end(); ++itor_a, ++itor_b) {
                if (*itor_a != *itor_b) {
                    return *itor_a < *itor_b;
                }
            }
            //    if (a[i] != b[i]) {
            //        return a[i] < b[i];
            //    }
            //}

	        //return a < b;
        }
        
        // Two strings are equal, so return whether true or false is ok.
        return true;
    };

    auto compIndex = [&arr,&length](int a, int b) -> bool {
	//cout << "[" << a << "," << b << "]=>(" << length[a] << "," << length[b] << ")" << endl;
        if (length[a] != length[b]) {
            return length[a] < length[b];
        } else {
            for (int i = 0; i < length[a]; i++) {
                if (arr[a][i] != arr[b][i]) {
                    return arr[a][i] < arr[b][i];
                }
            }
        }
        
        // Two strings are equal, so return whether true or false is ok.
        return true;
    };
    
    sort((arr).begin(), (arr).end(), compStr);
    //sort(index.begin(), index.end(), compIndex);
    //stable_sort(index.begin(), index.end(), compIndex);


    
    cout << "Sort ok" << endl;

    for (int i : index) {
        cout << arr[i] << endl;
    }

    //delete arr;
    
    return 0;
}

