#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

string word;

int value = 0;
vector<bool> marked;

int val(char c) {
    if(c=='$') return 0;
    return c - 'a' +1;
}


struct ST {
    ST(ST* parent, int begin, char c):
        parent(parent), link(nullptr),
        begin(begin),
        c(c),
        lazy(true)
    {
    }
    ST * parent, *link;
    int begin;
    char c;
    bool lazy;
    map<char, ST*> children;


    void materialize() {
        if(!lazy) return;
        lazy = false;
        if(begin+1 < word.size())
            children.emplace(word[begin], new ST(this, begin+1, word[begin]));
    }

    ST* getChild(char c) {
        materialize();
        auto p = children.find(c);
        if(p == children.end()) {
            cerr << "ERROR: getChild\n";
        }
        p->second->materialize();
        return p->second;
    }

    ST* getLink() {
        if(link != nullptr) return link;
        if(parent == nullptr) return link = this;
        if(parent->parent == nullptr) return link = parent;
        
        link = parent->getLink()->getChild(c);
        return link;
    }

    void addSuffixIt() {
        int i = 0;
        ST * x = this;
        while(i < word.size()) {
            //printf("// while: %u i=%d \n", x, i);
            x->materialize();
            char ci = word[i];
            auto p = x->children.find(ci);
            if(p != x->children.end()) {
                x = p->second;
                ++i;
            }
            else {
                x->children.emplace(ci, new ST(x, i+1, ci));
                if(x->parent == nullptr) {
                    ++i;
                }
                else {
                    x = x->getLink();
                }
            }
        }
    }

    void print(int h) {
        //printf("adding to ranks %d %u\n", h, this);
        if(lazy) {
            printf("%u [label=\"%s\"];\n", this,  word.substr(begin, word.size()).c_str());
        }
        else {
            for(auto it : children) {
                it.second->print(h+1);
                printf("%u -> %u [label=\"%c\"];\n", this, it.second, it.first);
            }
        }
        if(link != nullptr) {
            printf("%u -> %u [style=dotted];\n", link, this); //, getLink());
        }
    }

    void dfs(int h) {
        //printf("//dfs %d\n", h);

        if(lazy) {
            for(int p = begin; p < word.size(); ++p) {
                h += val(word[p]);
                if(!marked[h]) value++;
                marked[h]= true;
            }
        }
            for(auto it : children) {
                int nh = h+val(it.first);
                if(!marked[nh]) value++;
                marked[nh] = true;

                it.second->dfs(nh);
            }
    }
};


int main() {
    //ios_base::sync_with_stdio(false);
    cin >> word;
    word += '$';
    ST x(nullptr, 0, '$');
    marked.assign(word.size()*30, false);
    //x.materialize();
    x.lazy = false;
    //x.addSuffix(0);
    x.addSuffixIt();
    x.children.erase(x.children.find('$'));

    //cout << "digraph G {\n";
    //x.print(0);
    //cout << "}\n";

    x.dfs(0);
    cout << value << '\n';
}
