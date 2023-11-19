#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
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

void SaveFile(SqList &L, string filename){
// 保存食材信息到文件
	ofstream fp(filename);
	
	for(int i = 0; i != L.length; i++){
		fp << "中文名称：" << L.elem[i].name << endl;
		fp << "英文名称：" << L.elem[i].sname << endl;
		fp << "养生功效：" << L.elem[i].health << endl;
		fp << "营养与功效：" << L.elem[i].nutrition << endl;
		fp << "专家提醒：" << L.elem[i].expert << endl;
		fp << "相关链接：" << L.elem[i].link << endl;
		
		if( L.elem[i].recipe_size ){
			fp << "养生保健食谱：" << endl;
			for(int j = 0; j != L.elem[i].recipe_size; j++)
				fp << L.elem[i].recipe[j] << endl;
		}
		if( L.elem[i].therapy_size ){
			fp << "食疗验方：" << endl;
			for(int j = 0; j != L.elem[i].therapy_size; j++)
				fp << L.elem[i].therapy[j] << endl;
		}
		
		if( i != L.length-1 ) fp << "#" << endl;
	}
	
	fp.close();
}

bool ModifyFood(SqList &L, int type, char *name, string lines[], int n){
// 食材信息修改，如果type是0，则修改养生保健食谱，否则修改食疗验方信息
// 如果修改成功，返回true，否则，返回false
	for(int i = 0; i != L.length; i++){
		if( !strcmp(name, L.elem[i].name) ){
			if( !type ){
				for(int j = 0; j != n; j++) L.elem[i].recipe[j] = lines[j];
				L.elem[i].recipe_size = n;
			}
			else{
				for(int j = 0; j != n; j++) L.elem[i].therapy[j] = lines[j];
				L.elem[i].therapy_size = n;
			}
			
			return true;
		}
	}
	
	return false;
}

Food *getFood(SqList &L, char *name){
// 获取修改后的食材信息
	for(int i = 0; i != L.length; i++) if( !strcmp(name, L.elem[i].name) ) return L.elem+i;
	return NULL;
}

void Print(Food *food){
	cout << "中文名称：" << food->name << endl;
	cout << "英文名称：" << food->sname << endl;
	cout << "养生功效：" << food->health << endl;
	cout << "营养与功效：" << food->nutrition << endl;
	cout << "专家提醒：" << food->expert << endl;
	cout << "相关链接：" << food->link << endl;
	
	cout << "养生保健食谱：" << endl;
	for(int i = 0; i != food->recipe_size; i++) cout << food->recipe[i] << endl;
	cout << "食疗验方：" << endl;
	for(int i = 0; i != food->therapy_size; i++) cout << food->therapy[i] << endl;
}

int main(){
	SqList L; InitList(L);
	string originFilename = "../food.txt";
	string newFilename = "new_food.txt";
	
	int type; cin >> type;
	char name[100]; cin >> name;
	int n; string lines[30]; cin >> n;
	for (int i = 0; i < n; i++) cin >> lines[i];
	
	ReadFile(L, originFilename);
	if (ModifyFood(L, type, name, lines, n)){
		SaveFile(L, newFilename);
		ReadFile(L, newFilename);
		Food *food = getFood(L, name);
		if (food) Print(food);
		else cout << "修改失败" << endl;
	}
	else cout << "修改失败" << endl;
	
	FreeList(L);
	return 0;
}