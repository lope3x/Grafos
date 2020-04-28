#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>


using namespace std;

typedef struct {
    int x;
    int y;
} Coordinate;

class Graph{
    private:
    
        int numOfVertex;
        double ** adjMatrix;
        Coordinate * coordinates;
    public:
        Graph(int numOfVertex, Coordinate * coordinates){
            this->numOfVertex = numOfVertex;
            this->adjMatrix = new double*[this->numOfVertex];
            this->coordinates = coordinates;
            for(int i = 0 ; i < this->numOfVertex ; i++){
                this->adjMatrix[i] = new double[this->numOfVertex];
                memset(adjMatrix[i],0,sizeof(double)*this->numOfVertex);
            }
        }
        void insertEdge(int v1 , int v2,double distance){
            this->adjMatrix[v1][v2] = distance;
            this->adjMatrix[v2][v1] = distance;
        }
        void insertVertex(int indexVertex){
            Coordinate coordinate = this->coordinates[indexVertex];
            for(int i = 0; i<this->numOfVertex ; i++){
                if(i!=indexVertex && this->adjMatrix[indexVertex][i] == 0.0 ){
                    double distance = distanceTwoPoints(coordinate,this->coordinates[i]);
                    insertEdge(indexVertex,i,distance);
                }
            }
        }
        double distanceTwoPoints(Coordinate c1 , Coordinate c2){
            return sqrt(pow(c1.x-c2.x,2.0)+pow(c1.y-c2.y,2.0));
        }
        void printAdjMatrix(){
            for(int i = 0; i < this->numOfVertex ; i++){
                for(int j = 0; j < this->numOfVertex ; j++){
                    cout<<this->adjMatrix[i][j]<<"      ";
                }
                cout<<endl;
            }
        }
     
};

int main(){
    int n,x,y;
    cin>>n;
    Coordinate * coordinates = new Coordinate [n];
    for(int i = 0; i<n ; i++){
        cin>>x>>y;
        coordinates[i].x = x;
        coordinates[i].y = y;
    }
    Graph * graph = new Graph(n,coordinates);
    for(int i = 0; i<n ; i++){
        graph->insertVertex(i);
    }
    graph->printAdjMatrix();
    // cs[0].x = 10;
    // cs[0].y = 15;
    // cout<<cs[0].x<<cs[0].y;


}