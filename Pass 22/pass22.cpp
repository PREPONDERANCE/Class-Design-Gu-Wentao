#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <ios>
#include <map>
#include <algorithm>
#define MVNum 10000
using namespace std;

string Relationship[] = {"有功效","有食谱","有推荐食材","有证机概要"};
typedef struct ArcNode {
	int adjvex;                     // 该边所指向顶点的位置
	int relationship;               // 表示边的类型，即关系的类型，对应为数组下标 
	struct ArcNode* nextarc;        // 下一条边
} ArcNode;                          // 边结点

string Entity[]= {"食材","疾病","功效","食谱","证机概要"};
typedef struct VNode {
	int entity;                     // 表示顶点的类型，即实体的类型，对应为数组下标
	string info;                    // 表示顶点的内容，即实体的内容
	ArcNode* firstarc;              // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum];

typedef struct{
	AdjList vertices;               // 邻接表
	int vexnum, arcnum;             // 图的当前顶点数和边数
} ALGraph;

int LocateVex(ALGraph& G, string str) {
	// 返回str在AdjList中的位置
	for(int i = 0; i != G.vexnum; i++) if( G.vertices[i].info == str ) return i;
	return -1;
}

int LocateEntity(string str) {
	return std::distance(std::begin(Entity), std::find(std::begin(Entity), std::end(Entity), str));
}

int LocateRelationship(string str) {
	return std::distance(std::begin(Relationship), std::find(std::begin(Relationship), std::end(Relationship), str));
}

void InitALGraph(ALGraph& G) {
	G.vexnum = 0, G.arcnum = 0;
}

void CreateAdjList(ALGraph& G, string filename) {
	fstream inputFile(filename);
	
	while( !inputFile.eof() ){
		string vertex_type;
		inputFile >> G.vertices[G.vexnum].info >> vertex_type;
		G.vertices[G.vexnum].entity = LocateEntity(vertex_type);
		G.vertices[G.vexnum].firstarc = nullptr;
		G.vexnum += 1;
	}
	
	inputFile.close();
}

ArcNode* createArcNode(int adjVectex, int relationship){
	ArcNode* node = new ArcNode;
	node->adjvex = adjVectex;
	node->relationship = relationship;
	node->nextarc = nullptr;
	return node;
}

void CreateUDG(ALGraph& G, string filename) {
	fstream inputFile(filename);
	
	while( !inputFile.eof() ){
		string entity1, relationship, entity2;
		inputFile >> entity1 >> relationship >> entity2;
		
		int index1 = LocateVex(G, entity1), index2 = LocateVex(G, entity2);
		int connection = LocateRelationship(relationship);
		
		ArcNode* newNode1 = createArcNode(index2, connection);
		if( G.vertices[index1].firstarc ){
			newNode1->nextarc = G.vertices[index1].firstarc;
			G.vertices[index1].firstarc = newNode1;
		}else G.vertices[index1].firstarc = newNode1;
		
		ArcNode* newNode2 = createArcNode(index1, connection);
		if( G.vertices[index2].firstarc ){
			newNode2->nextarc = G.vertices[index2].firstarc;
			G.vertices[index2].firstarc = newNode2;
		}else G.vertices[index2].firstarc = newNode2;
	}
	
	inputFile.close();
}

bool recipeExist(ALGraph& G, int v){
	ArcNode* head = G.vertices[v].firstarc;
	while( head ){
		if( head->relationship == 1 ) return true;
		head = head->nextarc;
	}
	return false;
}

void DFS(ALGraph& G, int i, bool visited[], string path, int level) {
// 深度优先搜索多跳问答路径，i为输入的证机概要在AdjList中的下标，path为问答路径
// 函数可增加额外的参数
	if( G.vertices[i].entity == 3 ){
		cout << path << endl;
		return;
	}
	
	ArcNode* head = G.vertices[i].firstarc;
	bool flag = false;
	
	while( head ){
		if( level == 1 ){
			if( head->relationship == 3 ){
				DFS(G, LocateVex(G, G.vertices[head->adjvex].info), visited, path + "->" + G.vertices[head->adjvex].info, level+1);
				flag = true;
			}
		}else if( level == 2 ){
			if( head->relationship == 2 ){
				DFS(G, LocateVex(G, G.vertices[head->adjvex].info), visited, path + "->" 
					+ G.vertices[head->adjvex].info, level+1);
				flag = true;
			}
		}else{
			if( head->relationship == 1 ){
				DFS(G, LocateVex(G, G.vertices[head->adjvex].info), visited, path + "->" + G.vertices[head->adjvex].info, level+1);
				flag = true;
			}
		}
		head = head->nextarc;
	}
	
	if( !flag ) cout << path << endl;
}

void QuestionAnswering(ALGraph& G, string symptom) {
// 调用DFS函数，遍历图G，输出问答序列，symptom为证机概要
	bool visited[MVNum]; memset(visited, false, MVNum);
	string path = symptom;
	
	DFS(G, LocateVex(G, symptom), visited, path, 1);
}

int main() {
	ALGraph G; InitALGraph(G);
	
	CreateAdjList(G, "../entity.txt");
	CreateUDG(G, "../relationship.txt");
	
//	string symptom; cin >> symptom;
	string symptom = "脾胃失和";
	QuestionAnswering(G, symptom);
	
	return 0;
}