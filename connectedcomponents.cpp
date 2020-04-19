#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

enum Color{
    WHITE,
    GRAY,
    BLACK
};

class Graph{
    private:
        int ** adjMatrix;
        int numOfVertex;
        vector<Color> colors;
        int numOfComponents;
    public:
        Graph(int numOfVertex){
            this->numOfVertex = numOfVertex;
            adjMatrix = new int*[this->numOfVertex];
            for(int i = 0 ; i < this->numOfVertex ; i++){
                adjMatrix[i] = new int[this->numOfVertex];
                memset(adjMatrix[i],0,sizeof(int)*this->numOfVertex);
                colors.push_back(WHITE);
            }
            numOfComponents = 0;
        }
    void dfs();
    vector<int> dfs_visit(int vertex,vector<int> elements);
    void insertEdge(int v1,int v2);
    char numToChar(int n);
    int getNumOfComponents(){
        return this->numOfComponents;
    }
        
};
void Graph::insertEdge(int v1,int v2){
    this->adjMatrix[v1][v2] = 1;
    this->adjMatrix[v2][v1] = 1;
}
void Graph::dfs(){
    for(int vertex = 0;vertex< this->numOfVertex ; vertex++){
        if(colors[vertex]==WHITE){
            vector<int> elements;
            elements=dfs_visit(vertex,elements);
            sort(elements.begin(),elements.end());
            for(int i = 0; i<elements.size();i++){
                cout<<numToChar(elements.at(i))<<",";
            }
            cout<<endl;
            this->numOfComponents++;
        }
    }
}
vector<int> Graph::dfs_visit(int vertex,vector<int> elements){
    if(colors[vertex]== WHITE){
        elements.push_back(vertex);
    }
    colors[vertex] = GRAY;
    
    for(int i=0; i < this->numOfVertex ; i++){
        if(adjMatrix[vertex][i] == 1 && colors[i]== WHITE){
            elements=dfs_visit(i,elements);                
        
        }
    }
    colors[vertex] = BLACK;
    return elements;
}

int charToNum(char c){
    return c-97;
}

char Graph::numToChar(int n){
    return n+97;
}


int main(){
    int N,V,E;
    char v1,v2;
    cin>>N;
    for(int cases = 1;cases<=N;cases++){
        cin>>V>>E;
        Graph * graph = new Graph(V);
        for(int i = 0 ; i < E; i++){
            cin>>v1>>v2;
            graph->insertEdge(charToNum(v1),charToNum(v2));
        }
        cout<<"Case #"<<cases<<":"<<endl;
        graph->dfs();
        cout<<graph->getNumOfComponents()<<" connected components"<<endl<<endl;
    }
}