#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> nums;
vector<int> pos;
vector<bool> mark;
vector<int> bit;

void add(int x, int v) {
    for(int i = x+1; i < bit.size(); i += i & -i) {
        bit[i] += v;
    }
}

int query(int x) {
    int r = 0;
    for(int i = x+1; i > 0; i -= i & -i) {
        r += bit[i];
    }
    return r;
}

int main() {
    while(cin >> N, N != 0) {
        nums.resize(N);
        pos.resize(N);
        mark.assign(N, false);
        bit.assign(N+1,0);

        for(int & n : nums) {
            cin >> n;
            n--;
        }
        for(int i = 0; i < N; ++i) {
            pos[nums[i]] = i;
            add(i, 1);
        }
        add(0, -1);

        /*
        for(int & n : nums) {
            cout <<  n << ' ';
        }
        cout << '\n';
        */

        int cost = 0;
        for(int i = 0, p = 0; i < N;) {
            //printf(">>>>> i=%d\n", i);
            if(mark[i]) {
                //printf("mark\n");
                ++i;
                //add(0, -1);
                continue;
            }
            if(nums[i] == p) {
                //printf("eq\n");
                p++;
                i++;
            }
            else {
                //printf("pull\n");
                mark[pos[p]] = true;
                //printf("cost=%d pos[%d]=%d query=%d\n", cost, p, pos[p], query(pos[p]));
                cost += query(pos[p]) - p;
                //printf("cost'=%d\n", cost);
                add(i, 1);
                add(pos[p], -1);
                p++;
            } 
        }

        //cout << cost << '\n';
        cout << (cost % 2 == 0 ? "Carlos" : "Marcelo") << '\n';


    }

}
