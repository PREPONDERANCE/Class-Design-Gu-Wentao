#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
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
    L.elem = new Food[MAXSIZE];
    L.length = 0;
}

void FreeList(SqList &L){
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

bool InsertFood(SqList &L){
    // 插入食材信息，输入食材中文名称、英文名称、养生功效、营养与功效、养生保健食谱和食疗验方信息
    // 如果插入成功，返回true，否则，返回false
    string madarin_name, english_name, health_efficacy, nutrition_efficacy, expert_notification, related_links;
    int recipe_size, therapy_size;
    string recipe_collection[30], therapy_collection[30];
    
    getline(cin, madarin_name);
    getline(cin, english_name);
    getline(cin, health_efficacy);
    getline(cin, nutrition_efficacy);
    getline(cin, expert_notification);
    getline(cin, related_links);
    
    cin >> recipe_size;
    for(int i = 0; i != recipe_size; i++){
        string recipy; cin >> recipy;
        recipe_collection[i] = recipy;
    }
    
    cin >> therapy_size;
    for(int i = 0; i != therapy_size; i++){
        string therapy; cin >> therapy;
        therapy_collection[i] = therapy;
    }
    
    for(int i = 0; i != L.length; i++)
        if( std::equal(L.elem[i].name, L.elem[i].name + strlen(L.elem[i].name), madarin_name.begin()) )
        return false;
    
    std::copy(madarin_name.begin(), madarin_name.end(), L.elem[L.length].name);
    std::copy(english_name.begin(), english_name.end(), L.elem[L.length].sname);
    std::copy(health_efficacy.begin(), health_efficacy.end(), L.elem[L.length].health);
    std::copy(nutrition_efficacy.begin(), nutrition_efficacy.end(), L.elem[L.length].nutrition);
    std::copy(expert_notification.begin(), expert_notification.end(), L.elem[L.length].expert);
    std::copy(related_links.begin(), related_links.end(), L.elem[L.length].link);
    
    for(int i = 0; i != recipe_size; i++)
        L.elem[L.length].recipe[i] = string(recipe_collection[i].begin(), recipe_collection[i].end());
    L.elem[L.length].recipe_size = recipe_size;
    for(int i = 0; i != therapy_size; i++)
        L.elem[L.length].therapy[i] = string(therapy_collection[i].begin(), therapy_collection[i].end());
    L.elem[L.length].therapy_size = therapy_size;
    
    L.length += 1;
    return true;
}

void Print(SqList &L){
    // 输出食材信息
    cout << "中文名称：" << L.elem[L.length-1].name << endl;
    cout << "英文名称：" << L.elem[L.length-1].sname << endl;
    cout << "养生功效：" << L.elem[L.length-1].health << endl;
    cout << "营养与功效：" << L.elem[L.length-1].nutrition << endl;
    cout << "专家提醒：" << L.elem[L.length-1].expert << endl;
    cout << "相关链接：" << L.elem[L.length-1].link << endl;
    
    cout << "养生保健食谱：" << endl;
    for(int j = 0; j != L.elem[L.length-1].recipe_size; j++) cout << L.elem[L.length-1].recipe[j] << endl;
    
    cout << "食疗验方：" << endl;
    for(int j = 0; j != L.elem[L.length-1].therapy_size; j++) cout << L.elem[L.length-1].therapy[j] << endl;
}

int main(){
    SqList L;
    InitList(L);
    string originFilename = "../food.txt";
    string newFilename = "new_food.txt";
    
    ReadFile(L, originFilename);
    Print(L);
    
    if (InsertFood(L)){
        SaveFile(L, newFilename);
        ReadFile(L, newFilename);
        Print(L);
    }
    else{
        cout << "增加失败" << endl;
    }
    FreeList(L);
    return 0;
}