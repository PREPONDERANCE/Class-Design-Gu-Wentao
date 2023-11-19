#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <ios>
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

typedef struct TNode{
// 定义字典树结构体
	Food *foodPtr;		        // 食材指针
	struct TNode *child[53];    // 子结点的指针数组，由26个小写字母，26个大写字母，1个空格组成
} TNode, *TrieTree;

void InitList(SqList &L){
// 使用动态内存分配new进行初始化
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList &L){
// 释放内存
	delete [] L.elem;
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

TNode *InitTNode(){
	TNode* newNode = new TNode;
	newNode->foodPtr = nullptr;
	for(int i = 0; i != 53; i++) newNode->child[i] = nullptr;
	return newNode;
}

int ord(char c){
	if( c >= 'A' && c <= 'Z' ) return c-'A'+1;
	else if( c >= 'a' && c <= 'z' ) return c-'a'+27;
	else return 0;
}

TNode *BuildTree(SqList &L){
	TNode* root = InitTNode();
	TNode* curr = root;
	
	for(int i = 0; i != L.length; i++){
		for(int j = 0; j != strlen(L.elem[i].sname); j++){
			if( !curr->child[ord(L.elem[i].sname[j])] )
				curr->child[ord(L.elem[i].sname[j])] = InitTNode();
			curr = curr->child[ord(L.elem[i].sname[j])];
		}
		curr->foodPtr = L.elem + i;
		curr = root;
	}
	
	return root;
}

Food *TrieSearch(TNode *root, char *sname){
// 基于字典树的查找
// 如果查找成功则返回指向该食材的指针，如果查找失败则返回NULL
	for(int i = 0; i != strlen(sname); i++){
		if( !root->child[ord(sname[i])] ) return nullptr;
		root = root->child[ord(sname[i])];
	}
		
	return root->foodPtr;
}

void Print(Food *food){
// 输出Trie树中指针food指向的结点
	cout << "中文名称：" << food->name << endl;
	cout << "英文名称：" << food->sname << endl;
	cout << "养生功效：" << food->health << endl;
	cout << "营养与功效：" << food->nutrition << endl;
	cout << "专家提醒：" << food->expert << endl;
	cout << "相关链接：" <<  food->link << endl;
	
	if( food->recipe_size ){
		cout << "养生保健食谱：" << endl;
		for(int i = 0; i != food->recipe_size; i++) cout << food->recipe[i] << endl;
	}
	if( food->therapy_size ){
		cout << "食疗验方：" << endl;
		for(int i = 0; i != food->therapy_size; i++) cout << food->therapy[i] << endl;
	}
}

int totalSearch(TNode* root, int curr_depth, int total_len){
	if( root->foodPtr ) total_len += curr_depth;
	
	for(int i = 0; i != 53; i++)
		if( root->child[i] )
			total_len = totalSearch(root->child[i], curr_depth+1, total_len);
	
	
	return total_len;
}

double GetASL(SqList &L){
// 计算查找成功时的平均查找长度ASL
//	TNode* root = BuildTree(L);
//	return (double)totalSearch(root, 0, 0) / L.length;
	
	double total = 0;
	for(int i = 0; i != L.length; i++) total += strlen(L.elem[i].sname);
	return total / L.length;
}

void test(SqList &L){
	// 输出食材信息
	for(int i = 0; i != L.length; i++){
		cout << "中文名称：" << L.elem[i].name << endl;
		cout << "英文名称：" << L.elem[i].sname << endl;
		cout << "养生功效：" << L.elem[i].health << endl;
		cout << "营养与功效：" << L.elem[i].nutrition << endl;
		cout << "专家提醒：" << L.elem[i].expert << endl;
		cout << "相关链接：" << L.elem[i].link << endl;
		
		cout << "养生保健食谱：" << endl;
		for(int j = 0; j != L.elem[i].recipe_size; j++) cout << L.elem[i].recipe[j] << endl;
		
		cout << "食疗验方：" << endl;
		for(int j = 0; j != L.elem[i].therapy_size; j++) cout << L.elem[i].therapy[j] << endl;
	}
}

int main(){
	SqList L;
	InitList(L);
	ReadFile(L, "../food.txt");
	TNode *root = BuildTree(L);
	
	char *sname = new char[100];
	cin.getline(sname, 100);
	Food *food = TrieSearch(root, sname);
	if (food != NULL){
		Print(food);
		double ASL = GetASL(L);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else
		puts("查找失败");
	FreeList(L);
	return 0;
}