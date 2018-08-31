#include <iostream>
#include <vector>
using namespace std;


const int INF = 1e8;

struct Ride {
    int points;
    int cost;
};

int N;
vector<Ride> rides;

vector<vector<int>> cache;
int pd(int i, int w) {

    if(w < 0) return -INF;
    if(i >= N) return 0;

    int & result = cache[i][w];
    if(result != -1) return result;

    int a = rides[i].points + pd(i, w - rides[i].cost);
    int b = pd(i+1, w);
    return result = max(a, b);
}

int main() {
    int W;
    int inst = 1;
    while(cin >> N >> W, N > 0) {
        rides.resize(N);
        for(auto & r :rides) { cin >> r.cost >> r.points; }
        cache.assign(N, vector<int>(W+1, -1));

        cout << "Instancia " << inst << '\n';
        cout << pd(0, W) << "\n\n";
        ++inst;
    }
    return 0;
}

