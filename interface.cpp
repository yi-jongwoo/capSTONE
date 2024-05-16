#include "stone_internal_header.h"
#include "graph_visualization.h"

vector<int>* undirectionalize(int n,vector<int>* arr){
	vector<int>* grr=new vector<int>[n];
	int n;cin>>n;
	vector<pair<int,int>> edges;
	for(int i=0;i<n;i++)
		for(int j:arr[i])
			if(i<j)
				edges.emplace_back(i,j);
			else if(i>j)
				edges.emplace_back(j,i);
	sort(edges.begin(),edges.end());
	edges.resize(unique(edges.begin(),edges.end())-edges.begin());
	return grr; // use delete[] grr later
}

bool is_undirected(int n,vector<int>* arr){
	set<pair<int,int>> S;
	for(int i=0;i<n;i++)
		for(int j:arr[i])
			S.emplace(i,j);
	for(auto[i,j]:S)
		if(S.find({j,i})==S.end())
			return false;
	return true;
}

pair<int*,int*> embad_unit(int n,vector<int>* grr,int w,int h){
	int* x=new int[n];
	int* y=new int[n];
	if(is_tree(n,grr))
		embad_tree(n,grr,w,h);
	else if(is_cactus(n,grr))
		embad_cactus(n,grr,w,h);
	else if(is_planar(n,grr))
		embad_planar(n,grr,w,h);
	else
		embad_general(n,grr,w,h);
	return {x,y};
}

void dfs_con(int x,vector<int>* arr,int* vit,vector<int>& out){
	vit[x]=1;
	out.push_back(x);
	for(int y:arr[x])if(!vit[y])
		dfs_con(y,arr,vit,out);
}

void graph_visualization(int n,vector<int>* arr,string filename,int w,int h){
	int* x=new int[n];
	int* y=new int[n];
	vector<int>* grr=undirectionalize(n,arr);
	int* vit=new int[n];
	int prev=0;
	for(int i=0;i<n;i++){
		if(vit[i])continue;
		vector<int> uv;
		dfs_con(i,-1,grr,vit,uv);
		vector<int>* unit=new vector<int>[uv.size()];
		map<int,int> inv_uv;
		for(int i=0;i<uv.size();i++)
			inv_uv[uv[i]]=i;
		for(int u:uv)
			for(int v:grr[u])
				unit[inv_uv[u]].push_back(inv_uv[v]);
		auto[ux,uy]=embad_unit(uv.size(),unit,w*uv.size()/n,h);
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
	if(is_undirected(n,grr))
		make_svg_undirected(f,w,h,n,arr,x,y);
	else
		make_svg(f,w,h,n,arr,x,y);
	delete [] x;
	delete [] y;
}
