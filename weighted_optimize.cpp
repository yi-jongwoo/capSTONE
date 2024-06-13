#include "stone_internal_header.h"

int weighted_dfs_pre_embad_cactus(int x,int p,vector<int>* arr,int* vit){
	vit[x]=p==NOTHING?1:vit[p]+1;;
	int res=NOTHING;
	int yy=NOTHING;
	for(int y:arr[x])if(y!=p&&vit[y]<vit[x]){
		int yret=vit[y] ? y : weighted_dfs_pre_embad_cactus(y,x,arr,vit);
		if(yret!=NOTHING && yret!=x){
			res=yret;
			if(yret!=y)
				yy=y;
		}
	}
	if(yy!=NOTHING){
		for(int i=0;i<arr[x].size();i++)
			if(arr[x][i]==yy){
				swap(arr[x][i],arr[x].back());
				break;
			}
	}
	return res;
}

void weighted_dfs_embad_cactus(int x,vector<int>* arr,int* vit,vector<int>& res){
	res.push_back(x);
	vit[x]=1;
	for(int y:arr[x])if(!vit[y])
		weighted_dfs_embad_cactus(y,arr,vit,res);
}

inline ll point_edge_dist(ll xx,ll yy,ll x0,ll y0,ll x1,ll y1){
	ll dx=x1-x0;
	ll dy=y1-y0;
	ll a=x0*dx+y0*dy;
	ll b=x1*dx+y1*dy;
	ll c=xx*dx+yy*dy;
	ll r=0;
	if(a<c ^ c<b)
		r=min((xx-x0)*(xx-x0)+(yy-y0)*(yy-y0),
		  (xx-x1)*(xx-x1)+(yy-y1)*(yy-y1))*100;
	else{
		ll d=dy*x0-dx*y0;
		ll e=dy*xx-dx*yy;
		if(dx==0&&dy==0)
			r=0;
		else
			r=(d-e)*(d-e)*100/(dx*dx+dy*dy);
	}
	return r==0?2000:5000/r;
}

inline ll weighted_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y,int u,vector<pair<int,int>>& adj){
  	ll res=0;
  	
	int m=edges.size();
	for(int i=0;i<m;i++)
		for(auto[u,v]:adj){
			if(edges[i].first==u&&edges[i].second==v)
				continue;
			if(edges[i].first==v&&edges[i].second==u)
				continue;
			
			int u_=edges[i].first;
			int v_=edges[i].second;
			
			res+=point_edge_dist(x[u]+x[v]>>1,y[u]+y[v]>>1,x[u_],y[u_],x[v_],y[v_]);
			res+=point_edge_dist(x[u_]+x[v_]>>1,y[u_]+y[v_]>>1,x[u],y[u],x[v],y[v]);
		}
	return res;
}

void weighted_stone_huristic(int n,vector<int>* arr,int w,int h,int* out_x,int* out_y,
  ll(*objective)(int,vector<pair<int,int>>&,int*,int*,int,vector<pair<int,int>>&),
  bool flag=true
){
	vector<pair<int,int>> edges; // contain all the edges.
	for(int i=0;i<n;i++)
		for(int j:arr[i])
			if(i<j)
				edges.emplace_back(i,j);
			else if(i>j)
				edges.emplace_back(j,i);
	sort(edges.begin(),edges.end());
	edges.resize(unique(edges.begin(),edges.end())-edges.begin());
	vector<vector<pair<int,int>>> adjs(n);
	for(auto[u,v]:edges){
		adjs[u].emplace_back(u,v);
		adjs[v].emplace_back(u,v);
	}
	ll wweight =0;
	for(int t=0;t<100;t++){
		wweight++;
		for(int v=0;v<n;v++){
			ll z=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			int x=out_x[v]; 
			int rx=max(0,x-10),ry=min(w,x+10);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-10),ry=min(h,y+10);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;;
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
	}
	if(!flag)return;
	for(int t=0;t<30;t++){
		wweight++;
		for(int v=0;v<n;v++){
			ll z=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			int x=out_x[v]; out_x[v]=rand()%w;
			int y=out_y[v]; out_y[v]=rand()%h;
			ll nz=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			int u=rand()%n;
			ll z=objective(n,edges,out_x,out_y,u,adjs[u])
			  +weighted_objective(n,edges,out_x,out_y,u,adjs[u])*wweight;
			int xu=out_x[u],yu=out_y[u];
			out_x[u]=out_x[v]; out_y[u]=out_y[v];
			ll nz=objective(n,edges,out_x,out_y,u,adjs[u])
			  +weighted_objective(n,edges,out_x,out_y,u,adjs[u])*wweight;
			z+=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			out_x[v]=xu; out_y[v]=yu;
			nz+=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
	for(int t=0;t<30;t++){
		wweight++;
		for(int v=0;v<n;v++){
			ll z=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			int x=out_x[v]; 
			int rx=max(0,x-100),ry=min(w,x+100);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-100),ry=min(h,y+100);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
	}
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			int x=out_x[v]; 
			int rx=max(0,x-10),ry=min(w,x+10);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-10),ry=min(h,y+10);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			if(arr[v].empty())
				continue;
			int u=arr[v][rand()%arr[v].size()];
			ll z=objective(n,edges,out_x,out_y,u,adjs[u])
			  +weighted_objective(n,edges,out_x,out_y,u,adjs[u])*wweight;
			int xu=out_x[u],yu=out_y[u];
			out_x[u]=out_x[v]; out_y[u]=out_y[v];
			ll nz=objective(n,edges,out_x,out_y,u,adjs[u])
			  +weighted_objective(n,edges,out_x,out_y,u,adjs[u])*wweight;
			z+=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			out_x[v]=xu; out_y[v]=yu;
			nz+=objective(n,edges,out_x,out_y,v,adjs[v])
			  +weighted_objective(n,edges,out_x,out_y,v,adjs[v])*wweight;
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
}

void weighted_embad_cactus(int n,vector<int>* grr,int w,int h,int* x,int* y){
	vector<int> cir;
	
	int*vit=new int[n]; memset(vit,0,n*sizeof(int));
	bool res=weighted_dfs_pre_embad_cactus(0,-1,grr,vit); memset(vit,0,n*sizeof(int));
	weighted_dfs_embad_cactus(0,grr,vit,cir);
	delete[] vit;
	
	for(int i=0;i<n;i++){
		int j=cir[i];
		x[j]= w/2. + w/2. * cos(6.28318*i/n);
		y[j]= h/2. + h/2. * sin(6.28318*i/n);
	}
	
	weighted_stone_huristic(n,grr,w,h,x,y,planar_objective,false);
}

void weighted_embad_planar(int n,vector<int>* arr,int w,int h,int* x,int* y){
	using namespace boost;
	typedef adjacency_list<vecS,vecS,undirectedS,property<vertex_index_t, int>,property<edge_index_t, int>> graph_t;
	typedef std::vector< graph_traits<graph_t>::edge_descriptor > vec_t;
	typedef vector< vector< graph_traits<graph_t>::edge_descriptor >> storage_t;
	typedef iterator_property_map< storage_t::iterator,property_map<graph_t, vertex_index_t>::type> embedding_t;
	typedef std::vector< coord_t > straight_line_drawing_storage_t;
	typedef boost::iterator_property_map<straight_line_drawing_storage_t::iterator,property_map<graph_t, vertex_index_t>::type > drawing_t;
	graph_t g(n);
	for(int i=0;i<n;i++)
		for(int j:arr[i])if(i<j)
			add_edge(i,j,g);
	
	property_map<graph_t, edge_index_t>::type e_index = get(edge_index, g);
	graph_traits<graph_t>::edges_size_type edge_count = 0;
	graph_traits<graph_t>::edge_iterator ei, ei_end;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		put(e_index, *ei, edge_count++);
	
	std::vector<vec_t> embedding(num_vertices(g));
	
	assert(boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding =&embedding[0]));
	make_biconnected_planar(g, &embedding[0]);
	
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		put(e_index, *ei, edge_count++);
	
	assert(boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding =&embedding[0]));
	make_maximal_planar(g, &embedding[0]);
	
	edge_count = 0;
	for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		put(e_index, *ei, edge_count++);
	
	assert(boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding =&embedding[0]));
	
	storage_t planar_embedding_storage(num_vertices(g));
	embedding_t planar_embedding(planar_embedding_storage.begin(),get(vertex_index, g));
	boost::boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g,boyer_myrvold_params::embedding = planar_embedding);
	
	std::vector<graph_traits<graph_t>::vertex_descriptor> ordering;
	planar_canonical_ordering(g, planar_embedding, std::back_inserter(ordering));
	straight_line_drawing_storage_t straight_line_drawing_storage(num_vertices(g));
	drawing_t straight_line_drawing(straight_line_drawing_storage.begin(), get(vertex_index,g));
    chrobak_payne_straight_line_drawing(g,planar_embedding, ordering.begin(),ordering.end(),straight_line_drawing);
	
	graph_traits<graph_t>::vertex_iterator vi, vi_end;
	for(tie(vi,vi_end) = vertices(g); vi != vi_end; ++vi){
      	coord_t coord(get(straight_line_drawing,*vi));
      	x[*vi]=coord.x;
      	y[*vi]=coord.y;
    }
	
	int xmax=-1987654321,xmin=1987654321;
	int ymax=-1987654321,ymin=1987654321;
	
	for(int i=0;i<n;i++){
		xmax=max(xmax,x[i]);xmin=min(xmin,x[i]);
		ymax=max(ymax,y[i]);ymin=min(ymin,y[i]);
	}
	
	for(int i=0;i<n;i++){
		x[i]=ll(x[i]-xmin)*w/(xmax-xmin);
		y[i]=ll(y[i]-ymin)*h/(ymax-ymin);
	}	
	
	weighted_stone_huristic(n,arr,w,h,x,y,planar_objective);
}
void weighted_embad_general(int n,vector<int>* grr,int w,int h,int* x,int* y){
	for(int v=0;v<n;v++){
		x[v]=rand()%w;
		y[v]=rand()%h;
	}
	weighted_stone_huristic(n,grr,w,h,x,y,general_objective);
}
