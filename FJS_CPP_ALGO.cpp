
#include<bits/stdc++.h>
using namespace std;

int betap[101];
int Delta[256];

void output(int pos) {
    static int matches = 0;
    cout<<"Match "<<++matches<<" Found at Position "<<pos<<endl;
}

void makebetap(string& p, int m) {
    int i = 0, j = betap[0] = -1;

    while(i < m) {
        while((j > -1) && (p[i] != p[j])) {
            j = betap[j];
        }
        if(p[++i] == p[++j]) {
            betap[i] = betap[j];
        } else {
            betap[i] = j;
        }
    }
}

void makeDelta(string& p, int m) {
    int i;

    for(i = 0; i < 256; ++i) {
        Delta[i] = m + 1;
    }
    for(i = 0; i < m; ++i) {
        Delta[p[i]] = m - i;
    }
}

void FJS(string& p, int m, string& x, int n) {
    if(m < 1) return ;
    makebetap(p, m);
    makeDelta(p, m);

    int i = 0, j = 0, mp = m-1, ip = mp;
    while(ip < n) {
        if(j <= 0) {
            while(p[mp] != x[ip]) {
                ip += Delta[x[ip + 1]];
                if(ip >= n) return;
            }
            j = 0;
            i = ip - mp;
            while((j < mp) && (x[i] == p[j])) {
                ++i; ++j;
            }
            if(j == mp) {
                output(i - mp);
                ++i; ++j;
            }
            if(j <= 0) {
                ++i;
            } else {
                j = betap[j];
            }
        } else {
            while((j < m) && (x[i] == p[j])) {
                ++i; ++j;
            }
            if(j == m) {
                output(i - m);
            }
            j = betap[j];
        }
        ip = i + mp - j;
    }
}

int main() {
    string p, s;
    cout<<"Enter the Pattern Text : ";
    cin>>p;
    cout<<"Enter the Search Text : ";
    cin>>s;
    if(p.size() <= 100){
        FJS(p, p.size(), s, s.size());
    }
    else{
        cout<<"Re-run Program with Pattern Length less than 100";
    }
    return 0;
}