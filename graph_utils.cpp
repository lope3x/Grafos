void dfs(){
            for(int i=0;i<64;i++){
                this->colors[i]=WHITE;
            }
            dfs_visit(vertexInitial,0);
        }
        int dfs_visit(int vertex,int dist){
            colors[vertex] = GRAY;
            if(vertex  == vertexEnd&&dist < this->dist){
                this->dist = dist;
            }
            for(int i=0; i < this->numOfVertex ; i++){
                if(adjMatrix[vertex][i] == 1 && colors[i]==WHITE || colors[i]==GRAY){
                    dfs_visit(i,dist+1);                }
            }
            colors[vertex] = BLACK;
            return 0;
        }
        void printAdjMatrix(){
            for(int i = 0; i < this->numOfVertex ; i++){
                for(int j = 0; j < this->numOfVertex ; j++){
                    cout<<this->adjMatrix[i][j];
                }
                cout<<endl;
            }
        }
        void removeEdge(int v1, int v2){
            this->adjMatrix[v1][v2] = 0;
            this->adjMatrix[v2][v1] = 0;
        }