#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

enum TokenType{
    ID, 
    STRLIT,
    LBR,
    RBR,
    DOT,
    END
};

struct Token{
    TokenType type;
    string text;
};

vector<Token> tokens;
int pos=0;

bool scanner(const string& input);

TokenType peek();
bool match(TokenType expected);

bool program();
bool stmts();
bool stmt();
bool primary();
bool primary_tail();

string tokenName(TokenType type);
int main(){
    string input;
    string line;

    while(getline(cin, line)){
        input+= line;
        input+= '\n';
    }
    /*if(!scanner(input)){
        cout << "invalid input\n";
        return 0;
    }
    for(const Token& token : tokens){
        if(token.type==END){
            break;
        }
        cout << token.type << ' ' << token.text << '\n';
    }*/
    if(!scanner(input) || !program()){
        cout << "invalid input\n";
        return 0;
    }
    for(const Token&token : tokens){
        if(token.type==END){
            break;
        }
        cout << tokenName(token.type) << ' ' << token.text << '\n';
    }
    return 0;
}

bool IsIdStart(char ch){
    return (ch>='A' && ch<='Z') || (ch>='a' && ch<='z') || (ch=='_');
}

bool IsIdEnd(char ch){
    return IsIdStart(ch) || (ch>='0' && ch<='9');
}
bool scanner(const string& input){
    int i=0;
    while(i< input.size()){
        char ch=input[i];
        if(isspace(static_cast<unsigned char>(ch))){
            ++i;
            continue;
        }

        if(IsIdStart(ch)){
            int start=i;
            ++i;
            while(i<input.size() && IsIdEnd(input[i])){
                ++i;
            }
            tokens.push_back({ID, input.substr(start, i-start)});
            continue;
        }

        if(ch=='"'){
            int start=i;
            ++i;
            while(i<input.size() && input[i]!='"'){
                ++i;
            }
            if(i==input.size()){
                return false;
            }

            ++i;

            tokens.push_back({STRLIT, input.substr(start, i-start)});
            continue;
        }

        if(ch=='('){
            tokens.push_back({LBR, "("});
        }
        else if(ch==')'){
            tokens.push_back({RBR, ")"});
        }
        else if(ch=='.'){
            tokens.push_back({DOT, "."});
        }
        else{
            return false;
        }
        ++i;
    }

    tokens.push_back({END, ""});
    return true;
}

TokenType peek(){
    return tokens[pos].type;
}

bool match(TokenType expected){
    if(peek()!= expected){
        return false;
    }
    ++pos;
    return true;
}

bool program(){
    if (!stmts()){
        return false;
    }
    return peek()==END;
}

bool stmts(){
    if(peek()==ID || peek()==STRLIT){
        if(!stmt()){
            return false;
        }

        return stmts();
    }
    return true;
}

bool stmt(){
    if(peek()==ID){
        return primary();
    }

    if(peek()==STRLIT){
        return match(STRLIT);
    }
    return true;
}

bool primary(){
    if(!match(ID)){
        return false;
    }

    return primary_tail();
}

bool primary_tail(){
    if(peek()==DOT){
        match(DOT);

        if(!match(ID)){
            return false;
        }

        return primary_tail();

    }

    if(peek()==LBR){
        match(LBR);
        if(!stmt()){
            return false;
        }

        if(!match(RBR)){
            return false;
        }

        return primary_tail();
    }

    return true;
}

string tokenName(TokenType type){
    switch(type){
        case ID:    return "ID";
        case STRLIT:    return "STRLIT";
        case LBR:   return "LBR";
        case RBR:   return "RBR";
        case DOT:   return "DOT";
        default:    return "";
    }
}