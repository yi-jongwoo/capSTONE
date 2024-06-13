#include "stone_internal_header.h"
#include "graph_visualization.h"

vector<int>* weighted_undirectionalize(int n,vector<pair<int,int>>* arr){
	vector<int>* grr=new vector<int>[n];
	vector<pair<int,int>> edges;
	for(int i=0;i<n;i++)
		for(auto [w,j]:arr[i])
			if(i<j)
				edges.emplace_back(i,j);
			else if(i>j)
				edges.emplace_back(j,i);
	sort(edges.begin(),edges.end());
	edges.resize(unique(edges.begin(),edges.end())-edges.begin());
	for(auto[x,y]:edges){
		grr[x].push_back(y);
		grr[y].push_back(x);
	}
	return grr; // use delete[] grr later
}

bool weighted_is_undirected(int n,vector<pair<int,int>>* arr){
	set<pair<int,int>> S;
	for(int i=0;i<n;i++)
		for(auto [w,j]:arr[i])
			S.emplace(i,j);
	for(auto[i,j]:S)
		if(S.find({j,i})==S.end())
			return false;
	return true;
}

pair<int*,int*> weighted_embad_unit(int n,vector<int>* grr,int w,int h){
	int* x=new int[n];
	int* y=new int[n];
	if(is_tree(n,grr))
		embad_tree(n,grr,w,h,x,y);
	else if(is_cactus(n,grr))
		weighted_embad_cactus(n,grr,w,h,x,y);
	else if(is_planar(n,grr))
		weighted_embad_planar(n,grr,w,h,x,y);
	else
		weighted_embad_general(n,grr,w,h,x,y);
	return {x,y};
}

void weighted_dfs_con(int x,vector<int>* arr,int* vit,vector<int>& out){
	vit[x]=1;
	out.push_back(x);
	for(int y:arr[x])if(!vit[y])
		weighted_dfs_con(y,arr,vit,out);
}

void weighted_graph_visualization(int n,vector<pair<int,int>>* arr,string filename,int w,int h){
	int* x=new int[n];
	int* y=new int[n];
	vector<int>* grr=weighted_undirectionalize(n,arr);
	int* vit=new int[n]; memset(vit,0,n*sizeof(int));
	int prev=0;
	for(int i=0;i<n;i++){
		if(vit[i])continue;
		vector<int> uv;
		weighted_dfs_con(i,grr,vit,uv);
		
		vector<int>* unit=new vector<int>[uv.size()];
		map<int,int> inv_uv;
		for(int i=0;i<uv.size();i++)
			inv_uv[uv[i]]=i;
		for(int u:uv)
			for(int v:grr[u])
				unit[inv_uv[u]].push_back(inv_uv[v]);
		auto[ux,uy]=weighted_embad_unit(uv.size(),unit,w*uv.size()/n,h);
		for(int i=0;i<uv.size();i++){
			x[uv[i]]=ux[i]+prev;
			y[uv[i]]=uy[i];
		}
		delete[] ux;
		delete[] uy;
		delete[] unit;
		prev+=w*uv.size()/n;
	}
	
	delete [] vit;
	delete [] grr;
	if(weighted_is_undirected(n,arr))
		weighted_make_svg_undirected(filename,w,h,n,arr,x,y);
	else
		weighted_make_svg(filename,w,h,n,arr,x,y);
	delete [] x;
	delete [] y;
}
