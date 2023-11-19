#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>
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
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList &L){
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void ReadFile(SqList &L, string filename){
	// 从文件中读取食材信息，将其按顺序存入L.elem指向的数组中，L.elem[0]用做哨兵单元不存数据
	InitList(L); L.length += 1;
	
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

void BubbleSort(SqList &L, int &kcn, int &rmn){
// 对顺序表L做冒泡排序
// 注：elem[0]闲置
// 输出排序后的食材英文名称、KCN和RMN
	int flag = 1;
	
	for(int i = L.length-2; i > 0 && flag; i--){
		flag = 0;
		for(int j = 1; j <= i; j++){
			kcn += 1;
			if( strcmp(L.elem[j].sname, L.elem[j+1].sname) > 0 ){
				flag = 1;
				char temp[100];
				strcpy(temp, L.elem[j+1].sname);
				strcpy(L.elem[j+1].sname, L.elem[j].sname);
				strcpy(L.elem[j].sname, temp);
				
				rmn += 3;
			}
		}
	}
	
	for(int i = 1; i != L.length; i++) cout << L.elem[i].sname << endl;
	cout << "总的关键字比较次数KCN为：" << kcn << endl;
	cout << "总的记录移动次数RMN为：" << rmn << endl;
}

int main(){
	SqList L;
	InitList(L);
	int kcn = 0;
	int rmn = 0;
	ReadFile(L, "../food.txt");
	
	BubbleSort(L, kcn, rmn);
	FreeList(L);
	return 0;
}