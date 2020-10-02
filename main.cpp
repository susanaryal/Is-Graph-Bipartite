class Solution
{
public:
    void addEdgeOG(vector<int> OGGraph[], int u, int v)
    //Makes edges for the original graph.
    {
        OGGraph[u].push_back(v);
    }
    
    void addEdgeDUP(vector<int> DUPGraph[], int u, int v, int num)
    //Makes edges for the double/duplicate graph
    {
        DUPGraph[u].push_back(num + v);
        DUPGraph[num + v].push_back(u);
    }
    
    int numConnectedComponents(vector<int> graph[], int size)
    //Returns the number of connected components in a graph.
    {
        int numComponents = 0;
        bool visited[size];
        
        for(int i=0; i<size; i++)
        {
            visited[i] = false;
            //Initializing the visited array to false.
        }
        
        for(int i=0; i<size; i++)
        {
            if(!visited[i])
            {
                DFS(graph, size, i, visited);
                //Call the DFS function if the node is not visited.
                numComponents++;
            }
        }
        return numComponents;
    }
    
    void DFS(vector<int> mygraph[], int size, int v, bool visited[])
    //The recursive DFS(Depth First Search) for a graph to cover all connected nodes.
    {
        visited[v] = true;
        vector<int>::iterator i;
        for(i=mygraph[v].begin(); i!=mygraph[v].end(); i++)
        {
            if (!visited[*i])
            {
                DFS(mygraph, size, *i, visited);
            }
        }
    }
    
    bool isBipartite(vector<vector<int>>& graph)
    //Checks if the provided graph is bipartite or not.
    {
        int OGSize = graph.size();
        int DUPSize = 2 * OGSize;
        //Size of the new duplicate graph is doubled.
        
        vector<int> OGGraph[OGSize];
        vector<int> DUPGraph[DUPSize];
        //Making both the graphs in same form i.e., vector of arrays.
        
        for(int i=0; i<graph.size(); i++)
        {
            for(int j=0; j<graph[i].size(); j++)
            {
                addEdgeOG(OGGraph, i, graph[i][j]);
                //Making the original graph edges in OGGraph.
                addEdgeDUP(DUPGraph, i, graph[i][j], (int)graph.size());
                //Making the duplicate/double graph edges in DUPGraph.
            }
        }
        
        int OGConnectedNum = numConnectedComponents(OGGraph, OGSize);
        int DUPConnectedNum = numConnectedComponents(DUPGraph, DUPSize);
        //Finding the number of connected components in both graphs.
        
        return DUPConnectedNum == 2 * OGConnectedNum;
        //If the number of connected components in duplicated graph is double then the graph is bipartite.
    }
};
