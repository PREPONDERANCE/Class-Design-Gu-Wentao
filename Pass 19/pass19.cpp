#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <ios>
#include <algorithm>
#define MAXSIZE 10000
using namespace std;

bool isAsterisk(char c){
    return c == '*';
}

bool notAsterisk(char c){
    return c != '*';
}

//bool EntityRecognition(const char *S, const char *T){
//  string pattern = string(T, T+strlen(T)), match = string(S, S+strlen(S));
//  int i = 0, j = 0, char_ch = 0, char_eng = 0;
//  bool flag = false;
//  
//  while( i < match.length() ){
//      if( isalnum(match[i]) || match[i] == '%' ) i += 1;
//      if( pattern[j] != '*' && match.substr(i,3) == pattern.substr(j,3) ){
//          i += 3;
//          j += 3;
//          char_ch += 1;
//      }else if( pattern[j] == '*' ){
//          i += 3;
//          j += 1;
//          char_eng += 1;
//      }else{
//          i = i-(char_ch + char_eng)*3+3;
//          char_eng = 0, char_ch = 0;
//          j = 0;
//      }
//
//      if( j >= pattern.length() ){
//          flag = true;
//          auto head = find_if(pattern.begin(), pattern.end(), isAsterisk);
//          auto tail = find_if(head, pattern.end(), notAsterisk);
//          int asterisk_placeholder = pattern.end()-tail + (tail-head) * 3;
//          cout << match.substr(i-asterisk_placeholder, (tail-head)*3) << endl;
//          i += 3;
//      }
//  }
//  
//  return flag;
//}


bool EntityRecognition(const char* S, const char* T) {
    int lenS = strlen(S);
    int lenT = strlen(T);
    bool found = false;
    
    for (int i = 0; i <= lenS - lenT; i++) {
        int j;
        for (j = 0; j < lenT; j++) {
            if (T[j] != '*' && T[j] != S[i + j]) {
                break;
            }
        }
        
        if (j ==lenT)
            {
                int k = 0;
                for (k = 0; k < lenT; k++) {
                    if (T[k] == '*') {
                        break;
                    }
                }
                
                int start = i+k;
                int m = k;
                for(; m < lenT; m++){
                    if( T[m] != '*' )
                        break;
                }
                int end = start+(m-k)*3;
                
                for(int s = start; s != end; s++)
                    cout << S[s];
                
                cout << endl;
                found = true;
                // 如果找到一个匹配，跳过这个匹配的长度，继续搜索
                i += lenT - 1;
            }
    }
    
    return found;
}

int main(){
    char *keyword = new char[100];
    char text[1000000];
    cin >> keyword >> text;
    if(!EntityRecognition(text, keyword))
        cout<<"无匹配"<<endl;
    return 0;
}