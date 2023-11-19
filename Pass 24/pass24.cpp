#include <iostream>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>
#include <ios>
#include <map>
#include <limits.h>
#include <vector>
#include <algorithm>
#define MVNum 10000
#define INF INT_MAX
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

typedef struct {
    AdjList vertices;               // 邻接表
    int vexnum, arcnum;             // 图的当前顶点数和边数
} ALGraph;

typedef struct {
    int vexs[100];                  // 顶点表
    double arcs[100][100];          // 邻接矩阵
    int vexnum, arcnum;             // 图的当前顶点数和边数
} AMGraph;

int LocateVex(ALGraph& G, string str) {
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

void InitAMGraph(AMGraph& G) {
    G.vexnum = 0, G.arcnum = 0;
    for(int i = 0; i != 100; i++) G.arcs[i][i] = 0;
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
        
        G.arcnum += 2;
    }
    
    inputFile.close();
}

int LevenshteinDistance(string s1, string s2) {
    // 定义一个函数，计算两个字符串的莱文斯坦距离
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
    }
    return dp[m][n];
}

double TextSimilarity(string s1, string s2) {
    // 定义一个函数，计算两个字符串的文本相似度，文本相似度 = 1 - 莱文斯坦距离 / 最大字符串长度
    int dist = LevenshteinDistance(s1, s2);
    int max_len = max(s1.length(), s2.length());
    double s = 1.0 - (double)dist / max_len;
    return s;
}

void CreateAMG(AMGraph& GM, ALGraph& G) {
    // 调用编辑距离算法计算相似度，构建食材之间的邻接矩阵
    for(int i = 0; i != 100; i++){
        string efficacy1 ;
        ArcNode* head1 = G.vertices[i].firstarc;
        while( head1 ){
            if( !head1->relationship ) efficacy1 += G.vertices[head1->adjvex].info;
            if( !head1->relationship && head1->nextarc ) efficacy1 += "#";
            head1 = head1->nextarc;
        }
        for(int j = i+1; j != 100; j++){
            string efficacy2;
            ArcNode* head2 = G.vertices[j].firstarc;
            while( head2 ){
                if( !head2->relationship ) efficacy2 += G.vertices[head2->adjvex].info;
                if( !head2->relationship && head2->nextarc ) efficacy2 += "#";
                head2 = head2->nextarc;
            }
            GM.arcs[i][j] = GM.arcs[j][i] = 1-TextSimilarity(efficacy1, efficacy2);
            GM.arcnum += 1;
        }
        GM.vexs[i] += 1;
        GM.vexnum += 1;
    }
}

void findMin(AMGraph& G, bool* visited, double* dist, int& node, double& weight){
    double min = INT_MAX; int idx = 0;
    
    for(int i = 0; i != G.vexnum; i++){
        if( !visited[i] )
            if( dist[i] < min ){
                min = dist[i];
                idx = i;
            }
    }
    
    node = idx;
    weight = min;
}

void ShortestPathDIJ(AMGraph& G, bool S[], double D[], int v0) {
// 使用迪杰斯特拉算法求最短路径，S表示是否已被确定最短路径长度，D表示最短路径长度，v0表示顶点下标
    for(int i = 0; i != 100; i++) D[i] = INT_MAX; D[v0] = 0;
    for(int i = 0; i != 100; i++) S[i] = false;
    
    for(int i = 0; i != 100; i++){
        int node; double weight;
        findMin(G, S, D, node, weight);
        S[node] = true;
        
        for(int j = 0; j != 100; j++){
            if( weight + G.arcs[node][j] < D[j] )
                D[j] = weight + G.arcs[node][j];
        }
    }
}

int main() {
    ALGraph G; InitALGraph(G);
    
    CreateAdjList(G, "../entity.txt");
    CreateUDG(G, "../relationship.txt");
    
    AMGraph GM; InitAMGraph(GM);
    CreateAMG(GM, G);
    
    double T; string food;
    cin >> food >> T;
    
    int v0 = LocateVex(G, food);
    bool S[100]; double D[100];
    ShortestPathDIJ(GM, S, D, v0);
    
    for (int i = 0; i < GM.vexnum; i++)
        if (S[i] && D[i] < T) cout << G.vertices[i].info << " ";
    
    return 0;
}