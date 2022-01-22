#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct start{
    T data;
    list<int> lst;
};

template <typename T>
class Graph{
private:
    vector<start<T>> adjlst;
    void fillvector(int g, vector<int> k){
        for(int i=0;i<k.size();i++){
            k[i]=g;
        }
        return;
    }
    void swap(int pos1, int pos2){
        start<T> x;
        Equal(x,adjlst[pos1]);
        Equal(adjlst[pos1],adjlst[pos2]);
        Equal(adjlst[pos2],x);
    }
    void Equal(start<T>& x, start<T> y){
        x.lst.clear();
        x.data=y.data;
        for(list<int>::iterator cnt=y.lst.begin();cnt!=y.lst.end();cnt++){
            x.lst.push_back(*cnt);
        }
        return;
    }
    void sizeup(){
        adjlst.resize(adjlst.size()+1);
    }
    void sizedown(){
        adjlst.resize(adjlst.size()-1);
    }
    int Find(T data){
        for(int i=0; i<adjlst.size();i++){
            if(adjlst[i].data==data)
                return i;
        }
        return -1;
    }
    bool alltrue(vector<int> k){
        for(int i=0;i<k.size();i++){
            if(!(k[i]==2))
                return false;
        }
        return true;
    }
    void ChangeReference(int to,int from){
        for(int i=0;i<adjlst.size();i++){
            for(list<int>::iterator cnt=adjlst[i].lst.begin();cnt!=adjlst[i].lst.end();cnt++){
                if(*cnt==from)
                    *cnt=to;
            }
        }
    }
    void RemoveNonexistentReferences(int g){
        for(int i=0;i<adjlst.size();i++){
            adjlst[i].lst.remove(g);
        }
    }
    void addconnection(int x, int y){
        adjlst[x].lst.push_back(y);
    }
    bool exist(int x, int y){
        for(list<int>::iterator cnt=adjlst[x].lst.begin();cnt!=adjlst[x].lst.end();cnt++){
                if(*cnt==y)
                    return true;
        }
        return false;
    }
public:
    Graph(){
        adjlst.resize(0);
    }
    Graph(Graph<T>& x){
	adjlst.resize(x.adjlst.size());
    for(int i=0;i<adjlst.size();i++){
        Equal(adjlst[i], x.adjlst[i]);
    }
    }
    void DeleteEdge(T data1, T data2){
        int x,y;
        x=Find(data1);
        y=Find(data2);
        if(x<0 || y<0 || !exist(x,y))
            return;
        adjlst[x].lst.remove(y);
    }
    void AddEdge(T data1, T data2){
        int x,y;
        x=Find(data1);
        y=Find(data2);
        if(x<0 || y<0 || exist(x,y))
            return;
        addconnection(x,y);
    }
    void addNode(T data){
        if(Find(data)!=-1)
            return;
        sizeup();
        adjlst[adjlst.size()-1].data=data;
        adjlst[adjlst.size()-1].lst.clear();
        return;
    }
    void DeleteNode(T data){
        int g=Find(data);
        if(g<0)
            return;
        swap(g,adjlst.size()-1);
        RemoveNonexistentReferences(g);
        ChangeReference(g,adjlst.size()-1);
        sizedown();
    }
    void dfs(T r, void visit(T data)){
        int g=Find(r);
        if(g<0)
            return;
        stack<int> x;
        vector<int> passed;
        passed.resize(adjlst.size());
        fillvector(0,passed);
        passed[g]=1;
        x.push(g);
        cout << "Depth First Traversal: ";
        while(!alltrue(passed) && !x.empty()){
            g=x.top();
            x.pop();
            visit(adjlst[g].data);
            passed[g]=2;
            for(list<int>::iterator i=adjlst[g].lst.begin();i!=adjlst[g].lst.end();i++){
                if(!passed[*i]){
                    x.push(*i);
                    passed[*i]=1;
                }
            }
        }
        cout << endl;
        return;
    }
    void bfs(T r, void visit(T data)){
        int g=Find(r);
        if(g<0)
            return;
        queue<int> x;
        vector<int> passed;
        passed.resize(adjlst.size());
        fillvector(0,passed);
        passed[g]=1;
        x.push(g);
        cout << "Breadth First Traversal: ";
        while(!alltrue(passed) && !x.empty()){
            g=x.front();
            x.pop();
            visit(adjlst[g].data);
            passed[g]=2;
            for(list<int>::iterator i=adjlst[g].lst.begin();i!=adjlst[g].lst.end();i++){
                if(!passed[*i]){
                    x.push(*i);
                    passed[*i]=1;
                }
            }
        }
        cout << endl;
        return;
    }
};

void print(int data){
    cout << data << " ";
}

int main()
{
    Graph<int> r;
    r.addNode(5);
    r.addNode(6);
    r.addNode(9);
    r.addNode(3);
    r.AddEdge(5,9);
    r.AddEdge(6,5);
    r.AddEdge(6,3);
    r.addNode(4);
    r.addNode(0);
    r.AddEdge(3,4);
    r.AddEdge(4,0);
    r.dfs(6,print);
    Graph<int> y(r);
    y.bfs(6,print);
    y.removeNode(0);
    y.dfs(6,print);
    y.addNode(8);
    y.dfs(3,print);
    y.DeleteConnection(3,4);
    y.dfs(3,print);
    return 0;
}
