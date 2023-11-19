#include <iostream>
#include <string>
#include <string.h>
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
typedef struct LNode{
	Food data;			        // 食材信息
	struct LNode *next;         // 指向下一级结点
} LNode, *LinkList;

void InitList(LinkList &L){
	L = new LNode;
	L->next = nullptr;
}

void FreeList(LinkList &L){
	LNode *head = L->next, *temp;
	while( head ){
		temp = head->next;
		delete head;
		head = temp;
	}
	
	delete L;
}

void ReadFile(LinkList &L, string filename){
	LNode* head_Node = L;
	
	fstream inputFile(filename);
	string line; int count = 0;
	LNode* newNode = new LNode;
	
	while( getline(inputFile, line) ){
		if( line == "" ) return;
		if( line == "#" ){
			count = 0;
			head_Node->next = newNode;
			head_Node = head_Node->next;
			newNode = new LNode;
			continue;
		}
		
		if( line.substr(0, 12) == "中文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.name);
			count += 1;
		}else if( line.substr(0, 12) == "英文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.sname);
			count += 1;
		}else if( line.substr(0, 12) == "养生功效" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.health);
			count += 1;
		}else if( line.substr(0, 15) == "营养与功效" ){
			string::iterator head = line.begin()+18;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.nutrition);
			count += 1;
		}else if( line.substr(0, 12) == "专家提醒" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.expert);
			count += 1;
		}else if( line.substr(0, 12) == "相关链接" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, newNode->data.link);
			count += 1;
		}else if( line.substr(0, 18) == "养生保健食谱" || line.substr(0, 12) == "食疗验方" ){
			count += 1;
			continue;
		}
		
		if( count == 7 ){
			auto head = line.begin();
			auto tail = line.end();
			newNode->data.recipe[newNode->data.recipe_size] = string(head, tail);
			newNode->data.recipe_size += 1;
		}else if( count == 8 ){
			string::iterator head = line.begin();
			string::iterator tail = line.end();
			newNode->data.therapy[newNode->data.therapy_size] = string(head, tail);
			newNode->data.therapy_size += 1;
		}

	}
	
	head_Node->next = newNode;
	newNode->next = nullptr;
	inputFile.close();
}

void Print(LNode *p){
// 输出食材信息
	cout << "中文名称：" << p->data.name << endl;
	cout << "英文名称：" << p->data.sname << endl;
	cout << "养生功效：" << p->data.health << endl;
	cout << "营养与功效：" << p->data.nutrition << endl;
	cout << "专家提醒：" << p->data.expert << endl;
	cout << "相关链接：" <<  p->data.link << endl;
	
	if( p->data.recipe_size ){
		cout << "养生保健食谱：" << endl;
		for(int i = 0; i != p->data.recipe_size; i++) cout << p->data.recipe[i] << endl;
	}
	if( p->data.therapy_size ){
		cout << "食疗验方：" << endl;
		for(int i = 0; i != p->data.therapy_size; i++) cout << p->data.therapy[i] << endl;
	}
	
}

void test(LNode* head){
	LNode* p = head->next;
	
	while( p ){
		cout << "中文名称：" << p->data.name << endl;
		cout << "英文名称：" << p->data.sname << endl;
		cout << "养生功效：" << p->data.health << endl;
		cout << "营养与功效：" << p->data.nutrition << endl;
		cout << "专家提醒：" << p->data.expert << endl;
		cout << "相关链接：" <<  p->data.link << endl;
		
		if( p->data.recipe_size ){
			cout << "养生保健食谱：" << endl;
			for(int i = 0; i != p->data.recipe_size; i++) cout << p->data.recipe[i] << endl;
		}
		if( p->data.therapy_size ){
			cout << "食疗验方：" << endl;
			for(int i = 0; i != p->data.therapy_size; i++) cout << p->data.therapy[i] << endl;
		}
		
		p = p->next;
	}
}

LNode *SearchList(LinkList &L, char *sname){
// 在带头结点的单链表L中查找食材英文名称为sname的元素
	LNode* head = L->next;
	while( head ){
		if( !strcmp(sname, head->data.sname) ) return head;
		head = head->next;
	}
	return NULL;
}

int len(LNode* L){
	LNode* head = L->next;
	int size = 0;
	
	while( head ) {size += 1; head = head->next;}
	return size;
}

double GetASL(LinkList &L){
// 返回基于链表的顺序查找的ASL
	return (len(L)+1) / 2;
}

int main(){
	LinkList L; InitList(L);
	string originFilename = "../food.txt";
	ReadFile(L, originFilename);
	
	test(L);
	
	char sname[100];
	cin.getline(sname, 100);
	LNode *node = SearchList(L, sname);
	if (node){
		Print(node);
		double ASL = GetASL(L);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	FreeList(L);
	return 0;
}