#include <iostream>
#include <string>
#include <fstream>
#define MAXSIZE 10000
using namespace std;

typedef struct Food{
	char name[100];		        // 中文名称
	char sname[100];	            // 英文名称
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

void copy(Food* dst, Food* src){
	strcpy(dst->name, src->name);
	strcpy(dst->sname, src->sname);
	strcpy(dst->health, src->health);
	strcpy(dst->nutrition, src->nutrition);
	strcpy(dst->expert, src->expert);
	strcpy(dst->link, src->link);
	
	dst->recipe_size = src->recipe_size;
	dst->therapy_size = src->therapy_size;
	
	for(int i = 0; i != src->recipe_size; i++)
		dst->recipe[i] = string(src->recipe[i].begin(), src->recipe[i].end());
	for(int i = 0; i != src->therapy_size; i++)
		dst->therapy[i] = string(src->therapy[i].begin(), src->therapy[i].end());
}

Food *DeleteFood(SqList &L, char *name){
	Food* target = new Food;
	int pos = 0;
	
	for(int i = 0; i != L.length; i++)
		if( !strcmp(L.elem[i].name, name) ){
			pos = i;
			break;
		}else pos += 1;
	
	if( pos == L.length ) return NULL;
	
	copy(target, L.elem+pos);
	for(int i = pos+1; i != L.length; i++) copy(L.elem+i-1, L.elem+i);
	
	L.length -= 1;
	return target;
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

bool check(SqList &L, char *name){
	for (int i = 0; i < L.length; i++){
		if (strcmp(name, L.elem[i].name) == 0){
			return false;
		}
	}
	return true;
}

int main(){
	SqList L;
	InitList(L);
	
	string originFilename = "../food.txt";
	string newFilename = "new_food.txt";
	char name[100];
	
	cin >> name;
	ReadFile(L, originFilename);
	Food *food = DeleteFood(L, name);
	if (food){
		SaveFile(L, newFilename);
		ReadFile(L, newFilename);
		if (check(L, name))
			Print(food);
		else
			cout << "删除失败" << endl;
	}
	else{
		cout << "删除失败" << endl;
	}
	FreeList(L);
	return 0;
}