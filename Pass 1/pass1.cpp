#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 以下定义的函数可供其他函数调用，以实现本题功能
// 本题的输入需自己设置，可以使用switch case实现调用对应的函数
void InsertFood() {
    cout << "食材信息增加" << endl;
}

void DeleteFood() {
    cout << "食材信息删除" << endl;
}

void ModifyFood() {
    cout << "食材信息修改" << endl;
}

void SeqSearch() {
    cout << "基于顺序表的顺序查找" << endl;
}

void BinarySearch() {
    cout << "基于顺序表的折半查找" << endl;
}

void SearchList() {
    cout << "基于链表的顺序查找" << endl;
}

void SearchBST() {
    cout << "基于二叉排序树的查找" << endl;
}

void TrieSearch() {
    cout << "基于字典树的查找" << endl;
}

void SearchHash() {
    cout << "基于开放地址法的散列查找" << endl;
}

void SearchHL() {
    cout << "基于链地址法的散列查找" << endl;
}

void KMP() {
    cout << "基于KMP算法的食材关键信息查询" << endl;
}

void InsertSort() {
    cout << "直接插入排序" << endl;
}

void BInsertSort() {
    cout << "折半插入排序" << endl;
}

void SelectSort() {
    cout << "简单选择排序" << endl;
}

void BubbleSort() {
    cout << "冒泡排序" << endl;
}

void QuickSort() {
    cout << "快速排序" << endl;
}

void MSDSort() {
    cout << "高位优先字符串排序" << endl;
}

void EntityRecognition() {
    cout << "基于规则的实体识别" << endl;
}

void RelationExtraction() {
    cout << "基于规则的关系抽取" << endl;
}

void CreateUDG() {
    cout << "基于邻接表的知识图谱构建" << endl;
}

void QuestionAnswering() {
    cout << "基于路径推理的知识图谱多跳问答" << endl;
}

void CreateAMG() {
    cout << "基于编辑距离的食材功效矩阵构建" << endl;
}

void ShortestPathDIJ() {
    cout << "基于Dijkstra算法的食材推荐" << endl;
}

void ShortestPathFloyd() {
    cout << "基于Floyd算法的食材推荐" << endl;
}

void FoodADM() {
// 食材基本信息的增加、删除与修改模块，调用对应的功能函数实现
    cout << "食材基本信息的增加、删除与修改" << endl;

}

void FoodSearch() {
// 基于多种查找策略的食材信息查找模块，调用对应的功能函数实现
    cout << "基于多种查找策略的食材信息查找" << endl;

}

void FoodSort() {
// 基于多种排序策略的食材信息排序模块，调用对应的功能函数实现
    cout << "基于多种排序策略的食材信息排序" << endl;

}

void FoodManagement() {
// 食材基本信息管理模块
// 调用FoodADM()、FoodSearch()、KMP()、FoodSort()函数实现
    cout << "食材基本信息管理" << endl;
 
}

void CreateKG() {
// 中医食疗知识图谱构建模块，调用对应的功能函数实现
    cout << "中医食疗知识图谱构建" << endl;

}

void QAAndRecommendation() {
// 中医食疗问答与推荐模块，调用对应的功能函数实现
    cout << "中医食疗问答与推荐" << endl;
}

void SystemCall(){
// 基于知识图谱的中医食疗数据管理与应用系统功能调用
// 调用FoodManagement()、CreateKG()、QAAndRecommendation()函数实现
    string choice; cin >> choice;
    vector<int> selections;
    int level = 0;
    
    for(int i = 0; i != choice.length(); i++){
        if( choice[i] != '0' ){
            level += 1;
            
            if( level == 1 ){
                switch (choice[i] - '0') {
                    case 1 : FoodManagement(); break;
                    case 2 : CreateKG(); break;
                    case 3 : QAAndRecommendation(); break;
                }
            }else if( level == 2 ){
                if( selections[0] == 1 ){
                    switch (choice[i] - '0') {
                        case 1: FoodADM(); break;
                        case 2: FoodSearch(); break;
                        case 3: KMP(); break;
                        case 4: FoodSort(); break;
                    }
                }else if( selections[0] == 2 ){
                    switch (choice[i] - '0') {
                        case 1: EntityRecognition(); break;
                        case 2: RelationExtraction(); break;
                        case 3: CreateUDG(); break;
                    }
                }else{
                    switch (choice[i] - '0') {
                        case 1: QuestionAnswering(); break;
                        case 2: CreateAMG(); break;
                        case 3: ShortestPathDIJ(); break;
                        case 4: ShortestPathFloyd(); break;
                    }
                }
            }else{
                int parent = selections[selections.size()-1];
                if( parent == 1 ){
                    switch (choice[i] - '0') {
                        case 1: InsertFood(); break;
                        case 2: DeleteFood(); break;
                        case 3: ModifyFood(); break;
                    }
                }else if( parent == 2 ){
                    switch (choice[i] - '0') {
                        case 1: SeqSearch(); break;
                        case 2: BinarySearch(); break;
                        case 3: SearchList(); break;
                        case 4: SearchBST(); break;
                        case 5: TrieSearch(); break;
                        case 6: SearchHash(); break;
                        case 7: SearchHL(); break;
                    }
                }else{
                    switch (choice[i] - '0') {
                        case 1: InsertSort(); break;
                        case 2: BInsertSort(); break;
                        case 3: SelectSort(); break;
                        case 4: BubbleSort(); break;
                        case 5: QuickSort(); break;
                        case 6: MSDSort(); break;
                    }
                }
            }
                
            selections.push_back(choice[i]-'0');
        }else{
//          if( !selections.empty() ){
//              level -= 1;
//              selections.pop_back();
//          }
//          if( !selections.empty() ){
//              level -= 1;
//              selections.pop_back();
//          }
            
            level -= 1;
            selections.pop_back();
        }
    }
    
    cout << "退出系统" << endl;
}

int main(){
    SystemCall();
    return 0;
}