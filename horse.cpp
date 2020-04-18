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
        int vertexInitial;
        int vertexEnd;
    public:
        Graph(int numOfVertex,int x1,int x2,int y1,int y2){
            this->numOfVertex = numOfVertex;
            this->adjMatrix = new int*[this->numOfVertex];
            this->colors = new int[numOfVertex];
            for(int i = 0; i < this->numOfVertex ; i++){
                adjMatrix[i] = new int[this->numOfVertex];
            }
            for(int i = 0; i < this->numOfVertex ; i++){
                memset(adjMatrix[i], 0 ,this->numOfVertex*sizeof(int));
            }
            vertexInitial = x1 + y1*8;
            vertexEnd = x2 + y2*8;
        }
        void insertEdge(int v1 , int v2){
            this->adjMatrix[v1][v2] = 1;
            this->adjMatrix[v2][v1] = 1;
        }
       
        int bfs(){
            int dist = 0;
            for(int i=0;i<64;i++){
                this->colors[i]=WHITE;
            }
            queue<int> Q;
            int * distances = new int[numOfVertex];
            memset(distances,0,sizeof(int)*numOfVertex);
            Q.push(vertexInitial);
            while(!Q.empty()){
                int u=Q.front();
                Q.pop();
                for(int v = 0; v< this->numOfVertex ; v++){
                    if(adjMatrix[u][v]==1 && colors[v]==WHITE){
                        distances[v] = distances[u]+1;
                        colors[v] = GRAY;
                        Q.push(v);
                    }
                }
                colors[u] = BLACK;
            }
            return distances[vertexEnd];
        }
        void buildHorseGraph(int x, int y){
            int vertexMatrix = x + (y*8);
            if(x+2<8 && y+1<8&&adjMatrix[vertexMatrix][(x+2)+((y+1)*8)]==0){
                this->insertEdge(vertexMatrix,(x+2)+((y+1)*8));
                buildHorseGraph(x+2,y+1);
            }
            if(x+2<8 && y-1>=0&&adjMatrix[vertexMatrix][(x+2)+((y-1)*8)]==0){
                this->insertEdge(vertexMatrix,(x+2)+((y-1)*8));
                buildHorseGraph(x+2,y-1);
            }
            if(x-2>=0 && y+1<8&&adjMatrix[vertexMatrix][(x-2)+((y+1)*8)]==0){
                this->insertEdge(vertexMatrix,(x-2)+((y+1)*8));
                buildHorseGraph(x-2,y+1);
            }
            if(x-2>=0 && y-1>=0&&adjMatrix[vertexMatrix][(x-2)+((y-1)*8)]==0){
                this->insertEdge(vertexMatrix,(x-2)+((y-1)*8));
                buildHorseGraph(x-2,y-1);
            }
            if(x+1<8 && y+2<8&&adjMatrix[vertexMatrix][(x+1)+((y+2)*8)]==0){
                this->insertEdge(vertexMatrix,(x+1)+((y+2)*8));
                buildHorseGraph(x+1,y+2);
            }
            if(x-1>=0 && y+2<8&&adjMatrix[vertexMatrix][(x-1)+((y+2)*8)]==0){
                this->insertEdge(vertexMatrix,(x-1)+((y+2)*8));
                buildHorseGraph(x-1,y+2);
            }
            if(x+1<8 && y-2>=0&&adjMatrix[vertexMatrix][(x+1)+((y-2)*8)]==0){
                this->insertEdge(vertexMatrix,(x+1)+((y-2)*8));
                buildHorseGraph(x+1,y-2);
            }  
            if(x-1>=0 && y-2>=0&&adjMatrix[vertexMatrix][(x-1)+((y-2)*8)]==0){
                this->insertEdge(vertexMatrix,(x-1)+((y-2)*8));
                buildHorseGraph(x-1,y-2);
            }
        }

};



int main(){
    string a,b;
    while(cin>>a>>b != NULL ){
         int x1,x2,y1,y2;
        x1 = (a.at(0)-49)%48;
        y1 =  a.at(1) - 49;
        x2 = (b.at(0)-49)%48;
        y2 =  b.at(1) - 49;
        Graph * graph = new Graph(64,x1,x2,y1,y2);
        graph->buildHorseGraph(x1,y1);
        cout<<"To get from "<<a<<" to "<<b<<" takes "<<graph->bfs()<<" knight moves."<<endl;
    }
    return 0;
}
