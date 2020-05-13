#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

#define WHITE 0
#define GRAY 1
#define BLACK 2

class Graph{
    private:
        int ** adjMatrix;
        int * colors;
        int numOfVertex;
        int numOfColors;
        int * colorsVisit;
    public:
        /*
            Cria um grafo com o numero de vértices passados
            
        */
        Graph(int numOfVertex,int numOfColors){
            this->numOfVertex = numOfVertex+1;
            this->numOfColors = numOfColors+1;
            adjMatrix = new int * [this->numOfVertex];
            colors = new int[this->numOfVertex];
            colorsVisit = new int[this->numOfVertex];
            for(int i = 1 ; i <= this->numOfVertex ; i++){
                adjMatrix[i] = new int[this->numOfVertex];
                memset(adjMatrix[i],0,sizeof(int)*this->numOfVertex);
            }
            memset(colorsVisit,WHITE,sizeof(int)*this->numOfVertex);
        }
        /*
            Seta a cor de um vértice do grafo
        */
        void setColor(int vertex,int color){
            this->colors[vertex] = color;
        }
        /*
            Insere uma aresta no grafo
        */
        void insertEdge(int v1 , int v2){
            this->adjMatrix[v1][v2] = 1;
            this->adjMatrix[v2][v1] = 1;
        }
        /*
            Verifica se é possível inserir a quantidade de arestas passadas como parametros no grafo.
        */
        bool verifyPossibleInsertEdge(int P){
            for(int i=1; i < this->numOfVertex ; i++){
                for(int j=1 ; j < this->numOfVertex ; j++){
                    if(this->adjMatrix[i][j]==0&&this->colors[i] != this->colors[j] && P>0 && i!=j){
                        this->insertEdge(i,j);
                        P--;
                    }
                }
            }
            return (P==0) ? true : false;
        }
        /*
            Executa o algoritmo busca em profundidade
        */
        void bfs(int s){
            queue<int> Q;
            Q.push(s);
            while(!Q.empty()){
                int u=Q.front();
                Q.pop();
                for(int v = 1; v< this->numOfVertex ; v++){
                    if(adjMatrix[u][v]==1 && colorsVisit[v]==WHITE){
                        colorsVisit[v] = GRAY;
                        Q.push(v);
                    }
                }
                colorsVisit[u] = BLACK;
            }
        }
        /*
            Verifica que o grafo é conexo
        */
        bool verifyConectivity(){
            for(int i = 1;i< this->numOfVertex ; i++){
                if(colorsVisit[i]==WHITE){
                    return false;
                }
            }
            return true;
        }
};

int main(){
    int T,N,M,P,K,color,v1,v2;
    cin>>T;
    for(int t = 0; t<T;t++){
        cin>>N>>M>>P>>K;
        Graph * graph = new Graph(N,K);
        for(int i = 1; i <=N ;i++){
            cin>>color;
            graph->setColor(i,color);
        }
        for(int i=0; i < M ;i++){
            cin>>v1>>v2;
            graph->insertEdge(v1,v2);
        }
        if(graph->verifyPossibleInsertEdge(P)){
            graph->bfs(1);
            if(graph->verifyConectivity()){
                cout<<"Y"<<endl<<endl;
            }
            else{
                cout<<"N"<<endl<<endl;
            }
        }
        else{
            cout<<"N"<<endl<<endl;
        }
    }

    return 0;
}