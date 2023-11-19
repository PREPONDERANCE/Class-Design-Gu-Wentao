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
	string relation;    //关系名称
	string rule[10];    //规则数组
} Relation;

int BF(char* s, char* t){
	int i = 0, j = 0;
	string haystack = string(s, s+strlen(s));
	string needle = string(t, t+strlen(t));
	
	while( i < haystack.length() ){
		if( isalnum(haystack[i]) || haystack[i] == '%' ) i += 1;
		if( haystack.substr(i,3) == needle.substr(j,3) ){
			i += 3;
			j += 3;
		}else{
			i = i-j+3;
			j = 0;
		}
		
		if( j >= needle.length() ) return i-needle.length();
	}
	
	return haystack.length();
}

bool RelationExtraction(char *text, char *entity1, char *entity2, Relation *r){
// 如果实体之间存在关系返回true，否则返回false
// 输出所有存在的三元组
	string target_text = string(text, text + strlen(text));
	string entity_one = string(entity1, entity1 + strlen(entity1));
	string entity_two = string(entity2, entity2 + strlen(entity2));
//	
//	int entity1_pos = BF(target_text, entity_one);
//	int entity2_pos = BF(target_text, entity_two);
//	if( entity1_pos >= target_text.length() || entity2_pos >= target_text.length() ) return false;
//	
//	string relation = target_text.substr(entity1_pos, entity2_pos - entity1_pos);
//	
//	for(int i = 0; i != 4; i++)
//		for(int j = 0; r[i].relation != ""; j++){
//			auto end = std::find(r[i].rule[j].begin(), r[i].rule[j].end(), 'B');
//			auto beg = r[i].rule[j].begin()+1;
//			string cmp = string(beg, end);
//			
//			if( cmp == relation ){
//				cout << entity1 << "——" << relation << "——" << entity2 << endl;
//				return true;
//			}
//		}
	
	int k = 0;
	while( k < target_text.length() ){
		if( isalnum(target_text[k]) || target_text[k] == '%' ) k += 1;
		int entity1_pos = BF(text+k, entity1)+k;
		int entity2_pos = BF(text+k, entity2)+k;
		if( entity1_pos >= target_text.length() || entity2_pos >= target_text.length() ) return false;
		
		string relation = target_text.substr(entity1_pos+entity_one.length(), entity2_pos-entity1_pos-entity_one.length());
		
		for(int i = 0; i != 4; i++)
			for(int j = 0; j != 10; j++){
				if( r[i].rule[j] == "" ) break;
				
				auto end = std::find(r[i].rule[j].begin(), r[i].rule[j].end(), 'B');
				auto beg = r[i].rule[j].begin()+1;
				string cmp = string(beg, end);
				
				if( cmp == relation ){
					cout << entity1 << "-" << r[i].relation << "-" << entity2 << endl;
					return true;
				}
			}
		
		k += entity1_pos+entity_one.length();
	}
	
	return false;
}

void InitRelation(Relation *r){
	r[0].relation = "功效";
	r[0].rule[0] = "A具有B";
	r[0].rule[1] = "A功效为B";
	r[0].rule[2] = "A有利于B";
	r[0].rule[3] = "A有益于B";
	r[0].rule[4] = "A可以B";
	
	r[1].relation = "防治";
	r[1].rule[0] = "A可防治B";
	r[1].rule[1] = "A具备了防治B";
	r[1].rule[2] = "A可以治疗B";
	r[1].rule[3] = "A有利于预防B";
	
	r[2].relation = "性味";
	r[2].rule[0] = "A的性味是B";
	r[2].rule[1] = "A的性味为B";
	
	r[3].relation = "防治";
	r[3].rule[0] = "A包括B";
	r[3].rule[1] = "A主要有B";
	r[3].rule[2] = "A分解成B";
}

int main(){
	char *entity1 = new char[100];
	char *entity2 = new char[100];
	char text[10000];
	Relation *r	= new Relation[10];;
	InitRelation(r);
	
	cin >> entity1; getchar();
	cin >> entity2; getchar();
	cin >> text;
	
	if (!RelationExtraction(text, entity1, entity2, r))
		cout << "实体之间不存在关系" << endl;
	return 0;
}