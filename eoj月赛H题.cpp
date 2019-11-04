#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
const int N = 1005;
const int M = 19999999;
using namespace std;

int n, a[N];

struct Hash {
  int value, s, e;
  Hash *next;
};
 
Hash *hashing[M]; 

Hash *search(int n) {
    int a = (unsigned)n%M;
    Hash *p = hashing[a];
    while(p)
        if(p->value == n) return p;
        else p = p->next;
    return NULL;
}

Hash *newnode(int n, int i, int j) {
    Hash *p_node = (Hash *)malloc(sizeof(Hash));
    p_node->value = n;
    p_node->s = i;
    p_node->e = j;
    p_node->next = NULL;
    return p_node;
}

void addhash(int n, int i, int j) {
    int a = (unsigned)n%M;
    Hash *p_node = search(n);
    if(!p_node) {
        Hash *p = hashing[a];
        hashing[a] = newnode(n, i, j);
        hashing[a]->next = p;
    }
    else {
    	Hash *p = hashing[a];
    	hashing[a] = newnode(n, i, j);
    	hashing[a]->next = p;
    }
}

void clearhash() {
	for(int i = 0; i < M; ++i) {
		delete hashing[i];
		hashing[i] = NULL;
	}
}

int main() {
    while(cin >> n && n) {
        int ans = -1;
        for(int i = 0; i < n; ++i) cin >> a[i];
        sort(a, a+n);
        int cnt = 0;
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
            	addhash(a[i]+a[j], i, j);
                
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j < n; ++j) {
                if(i == j) continue;
                int temp = a[i]-a[j];
                Hash *p = search(temp);
                if(p && p->e != i && p->s != j && p->e != j && p->s != i) {
                    ans = i;
                    break;
                }
            }
            if(ans != -1) break;
        }
        if(ans != -1) cout << a[ans] << endl;
        else cout << "No Solution" << endl;
        clearhash();
    }
}

