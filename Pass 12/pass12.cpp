#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <ios>
#include <algorithm>
#define MAXSIZE 10000
using namespace std;

typedef struct Food{
	char name[100];		        // 中文名称
	char sname[100];	        // 英文名称
	char health[10000];	        // 养生功效
	char nutrition[10000];      // 营养与功效
	char expert[10000];	        // 专家提醒
	char link[10000];	        // 相关链接
	string recipe[30];	        // 养生保健食谱
	int recipe_size = 0;        // 食谱数量
	string therapy[30];	        // 食疗验方
	int therapy_size = 0;       // 验方数量
} Food;

typedef struct{
	Food *elem;                 // 指向数组的指针
	int length;                 // 数组的长度
} SqList;

void InitList(SqList &L){
// 使用动态内存分配new进行初始化
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList &L){
// 释放内存
	delete[] L.elem;
	L.length = 0;
}

void ReadFile(SqList &L, string filename){
// 从文件中读取食材信息，将其按顺序存入L.elem指向的数组中
	InitList(L);
	
	string line; int count = 0;
	ifstream inputFile(filename);
	
	while( getline(inputFile, line) ){
		if( line == "" ) return;
		
		if( line == "#" ){
			count = 0;
			L.length += 1;
			continue;
		}
		
		if( line.substr(0, 12) == "中文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].name);
			count += 1;
		}else if( line.substr(0, 12) == "英文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].sname);
			count += 1;
		}else if( line.substr(0, 12) == "养生功效" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].health);
			count += 1;
		}else if( line.substr(0, 15) == "营养与功效" ){
			string::iterator head = line.begin()+18;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].nutrition);
			count += 1;
		}else if( line.substr(0, 12) == "专家提醒" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].expert);
			count += 1;
		}else if( line.substr(0, 12) == "相关链接" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, L.elem[L.length].link);
			count += 1;
		}else if( line.substr(0, 18) == "养生保健食谱" || line.substr(0, 12) == "食疗验方" ){
			count += 1;
			continue;
		}
		
		if( count == 7 ){
			auto head = line.begin();
			auto tail = line.end();
			L.elem[L.length].recipe[L.elem[L.length].recipe_size] = string(head, tail);
			L.elem[L.length].recipe_size += 1;
		}else if( count == 8 ){
			string::iterator head = line.begin();
			string::iterator tail = line.end();
			L.elem[L.length].therapy[L.elem[L.length].therapy_size] = string(head, tail);
			L.elem[L.length].therapy_size += 1;
		}
	}
	
	L.length += 1;
}

void GetNext(const char *T, int next[]){
// 计算子串T的next数组

}

bool KMP(const char *S, const char *T, int next[]){
// 利用模式串T的next数组求子串T在主串S中是否存在
// 如果查找成功则返回true，如果查找失败则返回false
	int len1 = strlen(S), len2 = strlen(T);
	int lps[len2]; for(int i = 0; i != len2; i++) lps[i] = 0;
	
	int prevLPS = 0, i = 1;
	while( i < len2 ){
		if( T[i] == T[prevLPS] ){
			lps[i] = prevLPS + 1;
			i += 1;
			prevLPS += 1;
		}else if( prevLPS == 0 ){
			lps[i] = 0;
			i += 1;
		}else prevLPS = lps[prevLPS-1];
	}
	
	i = 0; int j = 0;
	while( i < len1 ){
		if( S[i] == T[j] ){
			i += 1;
			j += 1;
		}else{
			if( j == 0 ) i += 1;
			else j = lps[j-1];
		}
		
		if( j >= len2 ) return true;
	}
	
	return false;
}

bool SearchList(SqList &L, char *keyword, int next[]){
// 遍历顺序表食材的养生功效和营养与功效信息，调用KMP算法
// 如果在食材中查找成功则返回true，如果查找失败则返回false
	bool flag = false;
	
	for(int i = 0; i != L.length; i++)
		if( KMP(L.elem[i].health, keyword, next) ||  KMP(L.elem[i].nutrition, keyword, next) ){
			cout << L.elem[i].name << endl;
			flag = true;
		}
	
	return flag;
}

int main(){
	SqList L; InitList(L);
	ReadFile(L, "../food.txt");
	
	char *keyword = new char[100];
	cin >> keyword;
	
	int next[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
		next[i] = 0;
	GetNext(keyword, next);
	if (!SearchList(L, keyword, next))
		cout << "无匹配" << endl;
	FreeList(L);
	return 0;
}