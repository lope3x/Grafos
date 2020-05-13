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

/*
    Classe que define a fila de prioriade utilizada, no caso foi implementado um array com as funções necessárias para a fila
*/
class PriorityQueue{
    private:
        vector<double> priorityQueue;
    public:
        /*Retornar a menor chave da fila*/
        double getMinKey(){
            double min  = DBL_MAX;
            for(int i = 0;i< priorityQueue.size(); i++){
                if(priorityQueue[i]<min&&priorityQueue[i]!=-1){
                    min = priorityQueue[i];
                }
            }
            return min;
        }
        /*Extrai a menor chave a fila e atualiza a fila*/
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
        /*Altera o valor da chave passada para o valor passado por parametro*/
        void decreaseKey(int vertex, double value){
            priorityQueue[vertex] = value;
        }
        /*Verifica se a chave passada ainda está na fila*/
        bool keyIsOnQueue(int vertex){
            return priorityQueue[vertex]!=-1;
        }
        /*Insere o valor passado na fila*/
        void insertKey(double value){
            priorityQueue.push_back(value);
        }
        /*Retorna o valor da chave passada por parametro*/
        double getKeyValue(int vertex){
            return priorityQueue[vertex];
        }
        /*Verifica se a fila esta vazia*/
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
        /*
            Cria um grafo completo com o numero de vértices recebidos por parametro e com as coordenadas recebidas
        */
        Graph(int numOfVertex, Coordinate * coordinates){
            this->numOfVertex = numOfVertex;
            this->adjMatrix = new double*[this->numOfVertex];
            this->coordinates = coordinates;
            for(int i = 0 ; i < this->numOfVertex ; i++){
                this->adjMatrix[i] = new double[this->numOfVertex];
                memset(adjMatrix[i],0,sizeof(double)*this->numOfVertex);
            }
        }
        /*
            Insere uma aresta ponderada no grafo entre os vertices passados e com o peso passado
        */
        void insertEdge(int v1 , int v2,double distance){
            this->adjMatrix[v1][v2] = distance;
            this->adjMatrix[v2][v1] = distance;
        }
        /*
            Insere um vértice no grafo, cada vértice inserido deve ser adjacente a todos os outros vértices do grafo
            Parametro: indexVertex recebe o index no array de coordenadas do vértice correspondente
        */
        void insertVertex(int indexVertex){
            //Coordenada da pessoa correspondente ao index do vertex passado por parametro
            Coordinate coordinate = this->coordinates[indexVertex];
            //Insere aresta entre o vértice atual e todos os outros vértices do grafo
            for(int i = 0; i<this->numOfVertex ; i++){
                if(i!=indexVertex && this->adjMatrix[indexVertex][i] == 0.0 ){
                    //calcula a distância entre a pessoa atual(indexVertex) e a pessoa(i)
                    double distance = distanceTwoPoints(coordinate,this->coordinates[i]);
                    insertEdge(indexVertex,i,distance);
                }
            }
        }
        /*
            Calcula a distância euclidiana entre dois pontos na malha 2D
        */
        double distanceTwoPoints(Coordinate c1 , Coordinate c2){
            return sqrt(pow(c1.x-c2.x,2.0)+pow(c1.y-c2.y,2.0));
        }
        /*
            Executa o algoritmo de Prim e retorna o tomanho da AGM gerada.
        */
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
        //Cria um array de coordenadas para salvar as coordenadas das pessoas na malha 2d
        Coordinate * coordinates = new Coordinate [n];
        for(int i = 0; i<n ; i++){
            cin>>x>>y;
            coordinates[i].x = x;
            coordinates[i].y = y;
        }
        Graph * graph = new Graph(n,coordinates);
        //Atribui a cada pessoa na malha um numero arbitrário que será o numero de seu vértice no grafo 
        for(int i = 0; i<n ; i++){
            graph->insertVertex(i);
        }
        cout << fixed << setprecision(2);
        cout<<graph->prim(0)/100<<endl<<endl;
    }

}