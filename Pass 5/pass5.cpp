#include <iostream>
#include <ios>
#include <iomanip>
#include <string.h>
#include <string>
#include <fstream>
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
	inputFile.close();
}

int SeqSearch(SqList &L, char *sname){
	for(int i = 0; i != L.length; i++) if( !strcmp(sname, L.elem[i].sname)) return i;
	return -1;
}

double GetASL(SqList &L){
// 返回基于顺序表的顺序查找的ASL
	return (L.length+1) / 2;
}

void Print(SqList &L, int pos){
// 输出食材信息
	cout << "中文名称：" << L.elem[pos].name << endl;
	cout << "英文名称：" << L.elem[pos].sname << endl;
	cout << "养生功效：" << L.elem[pos].health << endl;
	cout << "营养与功效：" << L.elem[pos].nutrition << endl;
	cout << "专家提醒：" << L.elem[pos].expert << endl;
	cout << "相关链接：" << L.elem[pos].link << endl;
	
	if( L.elem[pos].recipe_size ){
		cout << "养生保健食谱：" << endl;
		for(int i = 0; i != L.elem[pos].recipe_size; i++) cout << L.elem[pos].recipe[i] << endl;
	}
	
	if( L.elem[pos].therapy_size ){
		cout << "食疗验方：" << endl;
		for(int i = 0; i != L.elem[pos].therapy_size; i++) cout << L.elem[pos].therapy[i] << endl;
	}
}

int main(){
	SqList L; InitList(L);
	string originFilename = "../food.txt";
	
	ReadFile(L, originFilename);
	char sname[100];
	cin.getline(sname, 100);
	
	int pos = SeqSearch(L, sname);
	if (pos != -1){
		Print(L, pos);
		double ASL = GetASL(L);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	FreeList(L);
	return 0;
}