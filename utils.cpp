#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll INF = 1e9; 

// Split de un string
// params: string s, vector<string> a, char x
// identifica los substrings entre el caracter x (o el final) y los guarda en a
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos + 1 ) );

    return strs.size();
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    string s; 
    getline (cin, s);
    vector<string> a;
    split(s, a, ' ');

    return 0;
}