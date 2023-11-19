#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <ios>
#include <iomanip>
#define m 200
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
typedef struct LNode{
	Food data;			        // 食材信息
	struct LNode *next;         // 指向下一级结点
} LNode, *LinkList;

void InitList(LinkList *H){
// 链表初始化
	for(int i = 0; i != m; i++) H[i] = new LNode;
}

int Hash(char *sname){
// 实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与199取余
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++) sum += ((i) * (i) * int(sname[i]));
	return sum % 199;
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

LNode* createNode(Food* food){
	LNode* newNode = new LNode;
	copy(&newNode->data, food);
	newNode->next = nullptr;
	return newNode;
}

void ListInsert(LinkList *H, Food f, int &sumCmp){
// 往散列表中插入新的食材f
// 在插入的过程中统计总的比较次数sumCmp
	int index = Hash(f.sname);
	LNode *head = H[index], *newNode = createNode(&f);
	sumCmp += 1;
	
	while( head->next ){
		head = head->next;
		sumCmp += 1;
	}
	head->next = newNode;
}

int ReadFile(LinkList *H, int &sumCmp, string filename){
// 读取文件，调用ListInsert函数将每条食材数据插入散列表
// 返回食材数据的总数
	string line; int count = 0, total = 0;
	ifstream inputFile(filename);
	Food* f = new Food;
	
	while( getline(inputFile, line) ){
		if( line == "" ) return total;
		
		if( line == "#" ){
			count = 0;
			ListInsert(H, *f, sumCmp);
			total += 1;
			f = new Food;
			continue;
		}
		
		if( line.substr(0, 12) == "中文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, f->name);
			count += 1;
		}else if( line.substr(0, 12) == "英文名称" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, f->sname);
			count += 1;
		}else if( line.substr(0, 12) == "养生功效" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, f->health);
			count += 1;
		}else if( line.substr(0, 15) == "营养与功效" ){
			string::iterator head = line.begin()+18;
			string::iterator tail = line.end();
			std::copy(head, tail, f->nutrition);
			count += 1;
		}else if( line.substr(0, 12) == "专家提醒" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, f->expert);
			count += 1;
		}else if( line.substr(0, 12) == "相关链接" ){
			string::iterator head = line.begin()+15;
			string::iterator tail = line.end();
			std::copy(head, tail, f->link);
			count += 1;
		}else if( line.substr(0, 18) == "养生保健食谱" || line.substr(0, 12) == "食疗验方" ){
			count += 1;
			continue;
		}
		
		if( count == 7 ){
			auto head = line.begin();
			auto tail = line.end();
			f->recipe[f->recipe_size] = string(head, tail);
			f->recipe_size += 1;
		}else if( count == 8 ){
			string::iterator head = line.begin();
			string::iterator tail = line.end();
			f->therapy[f->therapy_size] = string(head, tail);
			f->therapy_size += 1;
		}
	}
	
	total += 1;
	ListInsert(H, *f, sumCmp);
	inputFile.close();
	
	return total;
}

int SearchHL(LinkList *H, char *key){
// 在散列表HT中查找食材英文名称等于key的元素
// 若找到，则返回散列表的单元标号，否则返回-1
	int index = Hash(key);
	LNode* head = H[index];
	
	while( head ){
		if( !strcmp(key, head->data.sname) ) return index;
		head = head->next;
	}
	
	return -1;
}

double GetASL(int sumCmp, int count){
// 返回基于链地址法的散列查找的ASL
	return (double)sumCmp / count;
}

void Print(LNode *p, char *sname){
// 输出食材信息
	while( p ) if( !strcmp(sname, p->data.sname) ) break;
	
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

int main(){
	LinkList H[m];
	InitList(H);
	string filename = "../food.txt";
	int count = 0;	// 记录食材数据的总数
	int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
	count = ReadFile(H, sumCmp, filename);
	char sname[100]; // 输入要查找的食材英文名称
	cin.getline(sname, 100);
	int pos = SearchHL(H, sname);
	if (pos != -1){
		LinkList p = H[pos]->next; // 查找成功，将p指向单链表头结点
		Print(p, sname);
		double ASL = GetASL(sumCmp, count);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	return 0;
}