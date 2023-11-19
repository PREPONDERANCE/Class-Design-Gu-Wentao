#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ���¶���ĺ����ɹ������������ã���ʵ�ֱ��⹦��
// ������������Լ����ã�����ʹ��switch caseʵ�ֵ��ö�Ӧ�ĺ���
void InsertFood() {
    cout << "ʳ����Ϣ����" << endl;
}

void DeleteFood() {
    cout << "ʳ����Ϣɾ��" << endl;
}

void ModifyFood() {
    cout << "ʳ����Ϣ�޸�" << endl;
}

void SeqSearch() {
    cout << "����˳����˳�����" << endl;
}

void BinarySearch() {
    cout << "����˳�����۰����" << endl;
}

void SearchList() {
    cout << "���������˳�����" << endl;
}

void SearchBST() {
    cout << "���ڶ����������Ĳ���" << endl;
}

void TrieSearch() {
    cout << "�����ֵ����Ĳ���" << endl;
}

void SearchHash() {
    cout << "���ڿ��ŵ�ַ����ɢ�в���" << endl;
}

void SearchHL() {
    cout << "��������ַ����ɢ�в���" << endl;
}

void KMP() {
    cout << "����KMP�㷨��ʳ�Ĺؼ���Ϣ��ѯ" << endl;
}

void InsertSort() {
    cout << "ֱ�Ӳ�������" << endl;
}

void BInsertSort() {
    cout << "�۰��������" << endl;
}

void SelectSort() {
    cout << "��ѡ������" << endl;
}

void BubbleSort() {
    cout << "ð������" << endl;
}

void QuickSort() {
    cout << "��������" << endl;
}

void MSDSort() {
    cout << "��λ�����ַ�������" << endl;
}

void EntityRecognition() {
    cout << "���ڹ����ʵ��ʶ��" << endl;
}

void RelationExtraction() {
    cout << "���ڹ���Ĺ�ϵ��ȡ" << endl;
}

void CreateUDG() {
    cout << "�����ڽӱ��֪ʶͼ�׹���" << endl;
}

void QuestionAnswering() {
    cout << "����·�������֪ʶͼ�׶����ʴ�" << endl;
}

void CreateAMG() {
    cout << "���ڱ༭�����ʳ�Ĺ�Ч���󹹽�" << endl;
}

void ShortestPathDIJ() {
    cout << "����Dijkstra�㷨��ʳ���Ƽ�" << endl;
}

void ShortestPathFloyd() {
    cout << "����Floyd�㷨��ʳ���Ƽ�" << endl;
}

void FoodADM() {
// ʳ�Ļ�����Ϣ�����ӡ�ɾ�����޸�ģ�飬���ö�Ӧ�Ĺ��ܺ���ʵ��
    cout << "ʳ�Ļ�����Ϣ�����ӡ�ɾ�����޸�" << endl;

}

void FoodSearch() {
// ���ڶ��ֲ��Ҳ��Ե�ʳ����Ϣ����ģ�飬���ö�Ӧ�Ĺ��ܺ���ʵ��
    cout << "���ڶ��ֲ��Ҳ��Ե�ʳ����Ϣ����" << endl;

}

void FoodSort() {
// ���ڶ���������Ե�ʳ����Ϣ����ģ�飬���ö�Ӧ�Ĺ��ܺ���ʵ��
    cout << "���ڶ���������Ե�ʳ����Ϣ����" << endl;

}

void FoodManagement() {
// ʳ�Ļ�����Ϣ����ģ��
// ����FoodADM()��FoodSearch()��KMP()��FoodSort()����ʵ��
    cout << "ʳ�Ļ�����Ϣ����" << endl;
 
}

void CreateKG() {
// ��ҽʳ��֪ʶͼ�׹���ģ�飬���ö�Ӧ�Ĺ��ܺ���ʵ��
    cout << "��ҽʳ��֪ʶͼ�׹���" << endl;

}

void QAAndRecommendation() {
// ��ҽʳ���ʴ����Ƽ�ģ�飬���ö�Ӧ�Ĺ��ܺ���ʵ��
    cout << "��ҽʳ���ʴ����Ƽ�" << endl;
}

void SystemCall(){
// ����֪ʶͼ�׵���ҽʳ�����ݹ�����Ӧ��ϵͳ���ܵ���
// ����FoodManagement()��CreateKG()��QAAndRecommendation()����ʵ��
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
    
    cout << "�˳�ϵͳ" << endl;
}

int main(){
    SystemCall();
    return 0;
}