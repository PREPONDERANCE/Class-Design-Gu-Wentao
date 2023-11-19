#include <iostream>
#include <string.h>
#include <string>
#include <iomanip>
#include <ios>
#include <algorithm>
#include <fstream>
#define m 200
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
// 开放地址法散列表的存储表示
	Food *key;
	int length;
} HashTable;

void InitHT(HashTable &HT){
// 散列表初始化
	HT.length = 0;
	HT.key = new Food[m];
}

int Hash(char *sname){
	int sum = 0;
	for (int i = 0; i < strlen(sname); i++) sum += (i * i * int(sname[i]));
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

void HTInsert(HashTable &HT, Food* f, int &sumCmp){
// 往散列表中插入新的食材f
// 在插入的过程中统计总的比较次数sumCmp
	int index = Hash(f->sname);
	sumCmp += 1;
	
	while( strcmp(HT.key[index].sname, "") ){
		if( !strcmp(HT.key[index].sname, f->sname) ){
			copy(HT.key+index, f);
			return;
		}
		
		index += 1;
		sumCmp += 1;
		
		if( index >= m ) index = 0;
	}
	
	copy(HT.key+index, f);
}

void ReadFile(HashTable &HT, int &sumCmp, string filename){
// 读取文件，调用HTInsert函数将每条食材数据插入散列表
	string line; int count = 0;
	ifstream inputFile(filename);
	Food* f = new Food;
	
	while( getline(inputFile, line) ){
		if( line == "" ) return;
		if( line == "#" ){
			count = 0;
			HT.length += 1;
			HTInsert(HT, f, sumCmp);
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
	
	HTInsert(HT, f, sumCmp);
	HT.length += 1;
	inputFile.close();
}

void Print(HashTable HT, int pos){
// 输出食材信息
	cout << "中文名称：" << HT.key[pos].name << endl;
	cout << "英文名称：" << HT.key[pos].sname << endl;
	cout << "养生功效：" << HT.key[pos].health << endl;
	cout << "营养与功效：" << HT.key[pos].nutrition << endl;
	cout << "专家提醒：" << HT.key[pos].expert << endl;
	cout << "相关链接：" << HT.key[pos].link << endl;
	
	if( HT.key[pos].recipe_size ){
		cout << "养生保健食谱：" << endl;
		for(int j = 0; j != HT.key[pos].recipe_size; j++) cout << HT.key[pos].recipe[j] << endl;
	}
	
	if( HT.key[pos].therapy_size ){
		cout << "食疗验方：" << endl;
		for(int j = 0; j != HT.key[pos].therapy_size; j++) cout << HT.key[pos].therapy[j] << endl;
	}
}

int SearchHash(HashTable HT, char *key){
// 在散列表HT中查找食材英文名称等于key的元素
// 若找到，则返回散列表的单元标号，否则返回-1
	int index = Hash(key);
	
	while( strcmp("", HT.key[index].sname) ){
		if( !strcmp(key, HT.key[index].sname) ) return index;
		index += 1;
		if( index >= m ) index = 0;
	}
	
	return -1;
}

double GetASL(HashTable HT, int sumCmp){
// 返回基于开放地址法的散列查找的ASL
	return (double)sumCmp / HT.length;
}

//void test(HashTable& HT){
//	for(int i = 0; i != 200; i++){
//		if( strcmp("", HT.key[i].sname) ){
//			cout << "中文名称：" << HT.key[i].name << endl;
//			cout << "英文名称：" << HT.key[i].sname << endl;
//			cout << "养生功效：" << HT.key[i].health << endl;
//			cout << "营养与功效：" << HT.key[i].nutrition << endl;
//			cout << "专家提醒：" << HT.key[i].expert << endl;
//			cout << "相关链接：" <<  HT.key[i].link << endl;
//			
//			if( HT.key[i].recipe_size ){
//				cout << "养生保健食谱：" << endl;
//				for(int j = 0; j != HT.key[i].recipe_size; j++) cout << HT.key[i].recipe[j] << endl;
//			}
//			if( HT.key[i].therapy_size ){
//				cout << "食疗验方：" << endl;
//				for(int j = 0; j != HT.key[i].therapy_size; j++) cout << HT.key[i].therapy[j] << endl;
//			}
//			
//		}
//	}
//}

int main(){
	HashTable HT;
	InitHT(HT);
	string filename = "../food.txt";
	int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
	ReadFile(HT, sumCmp, filename);
	
	char sname[100]; // 输入要查找的食材英文名称
	cin.getline(sname, 100);
	int pos = SearchHash(HT, sname);
	if (pos != -1){
		Print(HT, pos);
		double ASL = GetASL(HT, sumCmp);
		cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
	}
	else{
		cout << "查找失败" << endl;
	}
	return 0;
}