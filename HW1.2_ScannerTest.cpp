#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

struct Token{
    string type;
    string text;
};

vector<Token> tokens;

int main(){
    string input;
    string line;
    while(getline(cin, line)){
        input+= line;
        input+= '\n';
    }
    for(int i=0; i<input.size(); ++i){
        char ch=input[i];
        if(isspace(static_cast<unsigned char>(ch))){
            continue;
        }
        else{
            if(ch>='0' && ch<='9'){
                int start=i;
                while(i<input.size() && input[i]>='0' && input[i]<='9'){
                    ++i;

                }
                tokens.push_back({"NUM", input.substr(start, i-start)});
                --i;
            }
            else if(ch=='+'){
                tokens.push_back({"PLUS", "+"});
            }
            else if(ch=='-'){
                tokens.push_back({"MINUS", "-"});
            }
            else if(ch=='*'){
                tokens.push_back({"MUL", "*"});
            }
            else if(ch=='/'){
                tokens.push_back({"DIV", "/"});
            }
            else if(ch=='('){
                tokens.push_back({"LPR", "("});
            }
            else if(ch==')'){
                tokens.push_back({"RPR", ")"});
            }
        }
    }

    for(const Token &token : tokens){
        if(token.type=="NUM"){
            cout << token.type << ' ' << token.text << '\n';
        }
        else{
            cout << token.type << '\n';
        }
    }

    return 0;
}