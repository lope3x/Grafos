#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <climits> 
#include <float.h>
#include <iomanip>


using namespace std;

typedef struct {
    int x;
    int y;
} Coordinate;

class PriorityQueue{
    private:
        vector<double> priorityQueue;
    public:
        double getMinKey(){
            double min  = DBL_MAX;
            for(int i = 0;i< priorityQueue.size(); i++){
                if(priorityQueue[i]<min&&priorityQueue[i]!=-1){
                    min = priorityQueue[i];
                }
            }
            return min;
        }
        int extractMinKey(){
            int min  = 0;
            for(int i = 1;i< priorityQueue.size(); i++){
                if(priorityQueue[min]==-1){
                    min = i;
                }
                else if(priorityQueue[i]<priorityQueue[min]&&priorityQueue[i]!=-1){
                    min = i;
                }
            }
            priorityQueue[min] = -1;
            return min;
        }
        void decreaseKey(int vertex, double value){
            priorityQueue[vertex] = value;
        }
        bool keyIsOnQueue(int vertex){
            return priorityQueue[vertex]!=-1;
        }
        void insertKey(double value){
            priorityQueue.push_back(value);
        }
        double getKeyValue(int vertex){
            return priorityQueue[vertex];
        }
        bool isEmpty(){
            for(int i=0;i<priorityQueue.size() ; i++){
                if(priorityQueue[i]!=-1){
                    return false;
                }
            }
            return true;
        }
};
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
        
        float prim(int root){ 
            PriorityQueue priorityQueue;    
            for(int i = 0; i< numOfVertex ; i++){
                priorityQueue.insertKey(DBL_MAX);
            }
            priorityQueue.decreaseKey(root,0);
            double sizeAgm = 0;
            while(!priorityQueue.isEmpty()){
                sizeAgm+=priorityQueue.getMinKey();
                int u = priorityQueue.extractMinKey();
                for(int i=0 ; i< this->numOfVertex ; i++){
                    if(i!=u&&priorityQueue.keyIsOnQueue(i)&&adjMatrix[u][i]<priorityQueue.getKeyValue(i)){
                        priorityQueue.decreaseKey(i,adjMatrix[u][i]);
                    }
                }
            }
            return sizeAgm;
        }
     
};

int main(){
    int c,n,x,y;
    cin>>c;
    for(int t = 0 ;t<c;t++){
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
        cout << fixed << setprecision(2);
        cout<<graph->prim(0)/100<<endl<<endl;
    }

}