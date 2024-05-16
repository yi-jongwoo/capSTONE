#include "stone_internal_header.h"

bool dfs_check_tree(int x,int p,vector<int>* arr,int* vit){
	vit[x]=1;
	for(int y:arr[x])if(y!=p){
		if(vit[y])return false;
		if(!dfs_check_tree(y,x,arr,vit))return false;
	}
	return true;
}

bool is_tree(int n,vector<int>* arr){
	int*vit=new int[n];
	bool res=dfs_check_tree(0,-1,arr,vit);
	delete[] vit;
	return res;
}

//return : backedge to..
int dfs_check_cactus(int x,int p,vector<int>* arr,int* vit){
	vit[x]=1;
	int res=NOTHING;
	for(int y:arr[x])if(y!=p){
		int yret=vit[y] ? y : dfs_check_cactus(y,x,arr,vit);
		if(yret==IMPOSSIBLE)
			return IMPOSSIBLE;
		if(yret!=NOTHING){
			if(res!=NOTHING)
				return IMPOSSIBLE;
			res=yret;
		}
	}
	return res;
}

bool is_cactus(int n,vector<int>* arr){ // cactus := edge cactus
	int*vit=new int[n];
	bool res=dfs_check_tree(0,-1,arr,vit);
	delete[] vit;
	return res;
}



bool is_planar(int n,vector<int>* arr){
	
}
