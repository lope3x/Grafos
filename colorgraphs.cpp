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
        void setColor(int vertex,int color){
            this->colors[vertex] = color;
        }
        void insertEdge(int v1 , int v2){
            this->adjMatrix[v1][v2] = 1;
            this->adjMatrix[v2][v1] = 1;
        }
        bool verifyPossibleInsertEdge(int P){
            for(int i=1; i < this->numOfVertex ; i++){
                for(int j=1 ; j < this->numOfVertex ; j++){
                    if(this->adjMatrix[i][j]==0&&this->colors[i] != this->colors[j] && P>0 && i!=j){
                        this->adjMatrix[i][j] = 1;
                        P--;
                    }
                }
            }
            return (P==0) ? true : false;
        }
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