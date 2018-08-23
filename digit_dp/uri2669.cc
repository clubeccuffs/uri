#include <iostream>
#include <vector>
using namespace std;


int ctoi(const char c) {
    return c - '0';
}

const int64_t INF = 1e18;

string S;
vector<char> R;
int N;

void ps(int x) { for (int i =0; i < x; ++i) cout << "  "; }

vector<vector<int>> cache;
bool pd(int i, int rem) {
    int &r = cache[i][rem];
    if(r != -1) return r;

    // ps(i); printf("pd(%d, %d)\n", i, rem);
    if(i == S.size()) {
        // ps(i); printf("rem? %d\n", rem);
        return rem == 0;
    }

    if(S[i] != '?') {
        int d = ctoi(S[i]);
        R[i] = S[i];
        return r = pd(i+1, (rem * 10 + d) % N);
    }

    for(char c = '0'; c <= '9'; ++c) {
        if(i==0 && c == '0') continue;
        int d = ctoi(c);
        // ps(i); printf("trying %c for %d = %d\n", c, i, (rem * 10 + d) % N);
        if (pd(i+1, (rem * 10 + d) % N)) {
            R[i] = c;
            //S[i] = c;
            return r = true;
        }
    }
    return r = false;
}


int main() {
    cin >> S >> N;
    cache.assign(S.size()+1, vector<int>(N, -1));
    R.resize(S.size());
    if(pd(0, 0)) {
        for(char c : R) cout << c;
        cout << '\n';
        //cout << R << '\n';
    }
    else {
        cout << "*\n";
    }
}
