#include "stone_internal_header.h"

int dfs_check_bipartite(int x,int p,vector<int>* arr,int* vit){
    vit[x]=vit[x]==NOTHING?1:3-vit[p];
    int res=NOTHING;
    for(int y:arr[x]){
        if(vit[y]){
            if(vit[x]==vit[y]) return IMPOSSIBLE;
            continue;
        }
        dfs_check_bipartite(y,x,arr,vit);
    }
    return res;
}

bool is_bipartite(int n,vector<int>* arr){ 
    int*vit=new int[n]; memset(vit,0,n*sizeof(int));
    int res=dfs_check_bipartite(0,-1,arr,vit);
    delete[] vit;
    return res!=IMPOSSIBLE;
}

bool dfs_check_tree(int x,int p,vector<int>* arr,int* vit){
	vit[x]=1;
	for(int y:arr[x])if(y!=p){
		if(vit[y])return false;
		if(!dfs_check_tree(y,x,arr,vit))return false;
	}
	return true;
}

bool is_tree(int n,vector<int>* arr){
	int*vit=new int[n]; memset(vit,0,n*sizeof(int));
	bool res=dfs_check_tree(0,-1,arr,vit);
	delete[] vit;
	return res;
}

//return : backedge to..
int dfs_check_cactus(int x,int p,vector<int>* arr,int* vit){
	vit[x]=p==NOTHING?1:vit[p]+1;
	int res=NOTHING;
	for(int y:arr[x])if(y!=p&&vit[y]<vit[x]){
		int yret=vit[y] ? y : dfs_check_cactus(y,x,arr,vit);
		if(yret==IMPOSSIBLE)
			return IMPOSSIBLE;
		if(yret!=NOTHING && yret!=x){
			if(res!=NOTHING)
				return IMPOSSIBLE;
			res=yret;
		}
	}
	return res;
}

bool is_cactus(int n,vector<int>* arr){ // cactus := edge cactus
	int*vit=new int[n]; memset(vit,0,n*sizeof(int));
	int res=dfs_check_cactus(0,-1,arr,vit);
	delete[] vit;
	return res!=IMPOSSIBLE;
}

bool is_planar(int n,vector<int>* arr){
	boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,int> g(n);
	for(int i=0;i<n;i++)
		for(int j:arr[i])if(i<j)
			add_edge(i,j,g);
	return boost::boyer_myrvold_planarity_test(g);
}
