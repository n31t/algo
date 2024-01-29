#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

vector<int> karp(const string& t, const string& s) {
    vector<int> positions;
    const long long q = INT_MAX;
    long long p[t.size()];
    long long h[t.size()];
    p[0] = 1;

    for (int i = 1; i < t.size(); ++i) {
        p[i] = (p[i - 1] * 31) % q;
    }

    for (int i = 0; i < t.size(); ++i) {
        if (i == 0) h[i] = t[i] - 'a' + 1;
        else h[i] = (h[i - 1] + (((t[i] - 'a' + 1) * p[i]) % q + q) % q) % q;
    }

    long long h_s = 0;
    for (int i = 0; i < s.size(); ++i) {
        h_s = (h_s + (((s[i] - 'a' + 1) * p[i]) % q + q) % q) % q;
    }

    for (int i = 0; i < t.size() - s.size() + 1; ++i) {
        long long temp = h[i + s.size() - 1];
        if (i > 0) {
            temp -= h[i - 1];
            if (temp < 0) {
                temp += q;
            }
        }
        if (temp == (h_s * p[i]) % q) {
            bool match = true;
            for (int j = 0; j < s.size(); ++j) {
                if (t[i + j] != s[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                positions.push_back(i);
            }
        }
    }

    return positions;
}

int main() {
    string t1, t2, s;
    cin >> t1 >> t2 >> s;
    vector<int> positions1 = karp(t1, s);
    vector<int> positions2 = karp(t2, s);
    int cnt = 0;
    for (int i = 0; i < positions1.size(); i++) {
        if (binarySearch(positions2, positions1[i]) != -1) {
            cnt++;
        }
    }

    cout << cnt;
    return 0;
}
