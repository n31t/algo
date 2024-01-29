#include <iostream>
#include <climits>
using namespace std;

string karp(const string& t, const string& s) {
    string outp;
    int pos_cnt = 0;
    const long long q = INT_MAX;
    long long po[t.size()];
    long long p[t.size()];
    long long h[t.size()];
    po[0] = -1;
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
            if (t.substr(i, s.size()) == s) {
                po[pos_cnt] = i;
                pos_cnt++;
            }
        }
    }

    for(int k = 0 ; k < pos_cnt; k++){
        outp = po[k];
    }
    // cout << endl;
    return outp;
}

int main() {
    string t1, t2, s;
    cin >> t1 >> t2 >> s;
    int a1,a2;
    t1 = karp(t1, s);
    t2 = karp(t2, s);
    cout << t1 << t2;
    return 0;
}
// kbtuutbkkbtu
// utbkkbtukbtu
// kbtu