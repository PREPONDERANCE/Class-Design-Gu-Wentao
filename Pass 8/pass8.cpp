#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <ios>
#include <iomanip>
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
typedef struct BSTNode{
	Food data;				    // 食材信息
	struct BSTNode *lchild;     // 左孩子指针
	struct BSTNode *rchild;     // 右孩子指针
} BSTNode, *BSTree;

void InitBSTree(BSTree &T){
	// 二叉排序树初始化
	T = nullptr;
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

BSTNode* createNode(Food* food){
	BSTNode* newNode = new BSTNode;
	copy(&newNode->data, food);
	return newNode;
}

void InsertBST(BSTree &T, Food e){ 
	if( !T ){
		T = createNode(&e);
		return;
	}
	if( strcmp(e.sname, T->data.sname) < 0 ) InsertBST(T->lchild, e);
	else if( strcmp(e.sname, T->data.sname) > 0 ) InsertBST(T->rchild, e);
}

int ReadFile(BSTree &T, string filename){
	// 读取文件，调用InsertBST函数将每个食材数据插入二叉排序树
	// 返回食材的总数
	int total = 0;
	fstream inputFile(filename);
	
	string line; int count = 0;
	BSTNode* newNode = new BSTNode;
	while( getline(inputFile, line) ){
		if( line == "" ) return total;
		if( line == "#" ){
			count = 0;
			InsertBST(T, newNode->data);
			newNode = new BSTNode;
			total += 1;
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
	
	InsertBST(T, newNode->data);
	total += 1;
	inputFile.close();
	
	return total;
}

void Print(BSTNode *p){
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

BSTNode *SearchBST(BSTree &T, char *sname){
	// 查找对应食材
	if( !T ) return nullptr;
	if( strcmp(sname, T->data.sname) == 0 ) return T;
	else if( strcmp(sname, T->data.sname) < 0 ) return SearchBST(T->lchild, sname);
	return SearchBST(T->rchild, sname);
}

int size(BSTree T){
	if( !T ) return 0;
	return size(T->lchild) + size(T->rchild) + 1;
}

int GetSumCmp(BSTree T, int sumCmp){
	// 统计查找成功时的总比较次数
//	int l = 0, r = 0, level = 1;
//	BSTNode* queue[size(T)];
//	queue[r] = T;
//	
//	while( r >= l ){
//		int currWidth = r-l+1;
//		sumCmp += level * currWidth;
//		
//		int temp = r;
//		for(int i = l; i <= temp; i++){
//			BSTNode* node = queue[l++];
//			if( node->lchild ) queue[++r] = node->lchild;
//			if( node->rchild ) queue[++r] = node->rchild;
//		}
//		
//		level += 1;
//	}
	
	int l = 0, r = 0, level = 1;
	BSTNode* queue[MAXSIZE];
	queue[r] = T;
	
	while( r >= l ){
		int currWidth = r-l+1;
		sumCmp += level * currWidth;
		
		int temp = r;
		for(int i = l; i != temp; i++){
			BSTNode* node = queue[l++];
			if( node->lchild ) queue[++r] = node->lchild;
			if( node->rchild ) queue[++r] = node->rchild;
		}
		
		level += 1;
	}
	
	return sumCmp;
}

double GetASL(BSTree &T, int count){
	// 返回基于二叉排序树查找的ASL
	double sum = GetSumCmp(T, 0);
	return sum / count;
}

int main(){
	BSTree T = NULL;
	InitBSTree(T);
	int count = 0;
	string originFilename = "../food.txt";
	count = ReadFile(T, originFilename);
	
	char sname[100];
	cin.getline(sname, 100);
	BSTNode *t = SearchBST(T, sname);
	if (t != NULL){
		Print(t);
		double ASL = GetASL(T, count);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else
		cout << "查找失败" << endl;
	return 0;
}
