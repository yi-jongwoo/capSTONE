#include "stone_internal_header.h"

bool dfs_check_tree(int x,int p,vector<int>* arr,int* vit){
	vit[x]=1;
	for(int y:arr[x])if(y!=p){
		if(vit[y])return false;
		if(!bfs_check_tree(y,x,arr,vit))return false;
	}
	return true;
}

bool is_tree(int n,vector<int>* arr){
	int*vit=new int[n];
	bool res=dfs_check_tree(0,-1,arr,vit);
	delete[] vit;
	return res;
}
