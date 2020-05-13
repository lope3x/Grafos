#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define WHITE 0
#define GRAY 1
#define BLACK 2

using namespace std;

class Graph{
    private:
        int ** adjMatrix;
        int numOfVertex;
        int * colors;
        bool connectivity;
    public:
        /*
            Construtor da classe, recebe o numero de vértices como parametro
        */
        Graph(int numOfVertex){
            this-> numOfVertex = numOfVertex+1;
            adjMatrix = new int*[this->numOfVertex];
            for(int i=0 ; i<this->numOfVertex ;i++){
                adjMatrix[i] = new int[this->numOfVertex];
            }
            for(int i=0 ; i<this->numOfVertex ;i++){
                memset(adjMatrix[i],0,sizeof(int)*this->numOfVertex);
            }
            colors = new int[this->numOfVertex];
            memset(colors,WHITE,sizeof(int)*this->numOfVertex);
            this->connectivity = true;
        }
        /*
            Recebe dois vértices como parametro e insere uma aresta que vai de v1 para v2
        */
        void insertEdge(int v1,int v2){
            adjMatrix[v1][v2] = 1;
        }
        /*
            Recebe dois vértices como parametro e insere uma aresta que vai de v1 para v2 e de v2 para v1
        */
        void insertDoubleEdge(int v1,int v2){
            adjMatrix[v1][v2] = 1;
            adjMatrix[v2][v1] = 1;
        }
        /*
            Metodo que verifica se o grafo é conexo
        */
        void visitaGeral(){
            for(int i=1 ; this->connectivity && i<this->numOfVertex; i++){
                memset(colors,WHITE,sizeof(int)*this->numOfVertex);
                this->bfs(i);
                this->verifyConectivity();
            }
            cout<<connectivity<<endl;;
        }
        /*
            Metodo que executa o algoritmo busca em largura
        */
        void bfs(int s){
            queue<int> Q;
            int * distances = new int[this->numOfVertex];
            memset(distances,0,sizeof(int)*this->numOfVertex);
            Q.push(s);
            while(!Q.empty()){
                int u=Q.front();
                Q.pop();
                for(int v = 1; v< this->numOfVertex ; v++){
                    if(adjMatrix[u][v]==1 && colors[v]==WHITE){
                        distances[v] = distances[u]+1;
                        colors[v] = GRAY;
                        Q.push(v);
                    }
                }
                colors[u] = BLACK;
            }
        }
        /*
            Metodo que verifica se a partir de um vertice é possivel chegar em todos os outros
        */
        void verifyConectivity(){
            for(int i = 1;i< this->numOfVertex ; i++){
                if(colors[i]==WHITE){
                    this->connectivity = false;
                    return;
                }
            }
            this->connectivity = true;
        }

};

int main(){
    int N,M,V,W,P;

    cin>>N>>M;
    while(N!=0&&M!=0){
        //Constroi um grafo baseado nas informações da entrada padrão
        Graph * graph = new Graph(N);
        for(int i=0;i<M;i++){
            cin>>V>>W>>P;
            if(P==1){
                graph->insertEdge(V,W);
            }
            else{
                graph->insertDoubleEdge(V,W);
            }
        }
        graph->visitaGeral();
        cin>>N>>M;
    }
    return 0;
}