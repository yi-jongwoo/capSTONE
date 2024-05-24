#include "stone_internal_header.h"

// reorder nodes by depth
void dfs_tree_depth(int x,int p,int d,vector<int>* arr,vector<vector<int>>&res){
	if(res.size()<=d)res.emplace_back();
	res[d].push_back(x);
	for(int y:arr[x])if(y!=p)
		dfs_tree_depth(y,x,d+1,arr,res);
}

void embad_tree(int n,vector<int>* grr,int w,int h,int* x,int* y){
	vector<vector<int>> res;
	dfs_tree_depth(0,-1,0,grr,res);
	int h_=res.size();
	for(int i=0;i<h_;i++){
		int y_= h*(1+i*2)/(2*h_);
		int w_=res[i].size();
		for(int j=0;j<w_;j++){
			int x_= w*(1+j*2)/(2*w_);
			x[res[i][j]]=x_;
			y[res[i][j]]=y_;
		}
	}
}

void embad_cactus(int n,vector<int>* grr,int w,int h,int* x,int* y){
	embad_planar(n,grr,w,h,x,y); // not implemented now
}

#define ccw(a,b,c,d,e,f) ((c-a)*(f-d)-(d-b)*(e-c))
bool is_cross(ll a,ll b,ll c,ll d,ll e,ll f,ll g,ll h){
	ll ccw1=ccw(a,b,e,f,c,d);
	ll ccw2=ccw(e,f,c,d,g,h);
	ll ccw3=ccw(c,d,g,h,a,b);
	ll ccw4=ccw(g,h,a,b,e,f);
	int x=ccw1>0|ccw2>0|ccw3>0|ccw4>0;
	int y=ccw1<0|ccw2<0|ccw3<0|ccw4<0;
	if(!x&&!y){
		pair<ll,ll> A(a,b),B(c,d),C(e,f),D(g,h);
		vector<pair<ll,ll>> V={A,B,C,D};
		sort(V.begin(),V.end());
		if(!((A==V[0]||A==V[1])&&(B==V[2]||B==V[3])||(B==V[0]||B==V[1])&&(A==V[2]||A==V[3]))){
			return 0;
		}
		return 1;
	}
	if(x&y)
		return 0;
	else{
		return 1;
	}
}

inline ll partial_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y,int u,vector<pair<int,int>>& adj){
  	ll res=0;
  	
	int m=edges.size();
	for(int i=0;i<m;i++)
		for(auto[u,v]:adj){
			if(edges[i].first==u)
				continue;
			if(edges[i].first==v)
				continue;
			if(edges[i].second==u)
				continue;
			if(edges[i].second==v)
				continue;
			res+=is_cross(x[edges[i].first],y[edges[i].first],x[edges[i].second],y[edges[i].second],
			  x[u],y[u],x[v],y[v]);
		}
	for(int j=0;j<n;j++)if(u!=j)
		if(abs(x[u]-x[j])+abs(y[u]-y[j])<10){
			res+=20000*(10-abs(x[u]-x[j])-abs(y[u]-y[j]));
		}
	res*=100;
		for(int j=0;j<m;j++)
			if(edges[j].first!=u&&edges[j].second!=u){
				ll x0=x[edges[j].first];
				ll y0=y[edges[j].first];
				ll x1=x[edges[j].second];
				ll y1=y[edges[j].second];
				ll dx=x1-x0;
				ll dy=y1-y0;
				ll a=x0*dx+y0*dy;
				ll b=x1*dx+y1*dy;
				ll c=x[u]*dx+y[u]*dy;
				ll r=0;
				if(a<c ^ c<b)
					r=min((x[u]-x0)*(x[u]-x0)+(y[u]-y0)*(y[u]-y0),
					  (x[u]-x1)*(x[u]-x1)+(y[u]-y1)*(y[u]-y1))*100;
				else{
					ll d=dy*x0-dx*y0;
					ll e=dy*x[u]-dx*y[u];
					if(dx==0&&dy==0)
						r=0;
					else
						r=(d-e)*(d-e)*100/(dx*dx+dy*dy);
				}
				res+=r==0?2000:5000/r;
			}
	for(int i=0;i<n;i++)
		for(auto[u,v]:adj)
			if(u!=i&&v!=i){
				ll x0=x[u];
				ll y0=y[u];
				ll x1=x[v];
				ll y1=y[v];
				ll dx=x1-x0;
				ll dy=y1-y0;
				ll a=x0*dx+y0*dy;
				ll b=x1*dx+y1*dy;
				ll c=x[i]*dx+y[i]*dy;
				ll r=0;
				if(a<c ^ c<b)
					r=min((x[i]-x0)*(x[i]-x0)+(y[i]-y0)*(y[i]-y0),
					  (x[i]-x1)*(x[i]-x1)+(y[i]-y1)*(y[i]-y1));
				else{
					ll d=dy*x0-dx*y0;
					ll e=dy*x[i]-dx*y[i];
					if(dx==0&&dy==0)
						r=0;
					else
						r=abs(d-e)*100/sqrt(dx*dx+dy*dy);
				}
				res+=r==0?2000:5000/r;
			}
	return res;
}


void nonconvexed_decrossing(int n,vector<int>* arr,int w,int h,int* out_x,int* out_y){
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
	
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			int x=out_x[v]; out_x[v]=rand()%w;
			int y=out_y[v]; out_y[v]=rand()%h;
			ll nz=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			int u=rand()%n;
			ll z=partial_objective(n,edges,out_x,out_y,u,adjs[u]);
			int xu=out_x[u],yu=out_y[u];
			out_x[u]=out_x[v]; out_y[u]=out_y[v];
			ll nz=partial_objective(n,edges,out_x,out_y,u,adjs[u]);
			z+=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			out_x[v]=xu; out_y[v]=yu;
			nz+=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			int x=out_x[v]; 
			int rx=max(0,x-100),ry=min(w,x+100);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-100),ry=min(h,y+100);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
	}
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			int x=out_x[v]; 
			int rx=max(0,x-10),ry=min(w,x+10);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-10),ry=min(h,y+10);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			if(arr[v].empty())
				continue;
			int u=arr[v][rand()%arr[v].size()];
			ll z=partial_objective(n,edges,out_x,out_y,u,adjs[u]);
			int xu=out_x[u],yu=out_y[u];
			out_x[u]=out_x[v]; out_y[u]=out_y[v];
			ll nz=partial_objective(n,edges,out_x,out_y,u,adjs[u]);
			z+=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			out_x[v]=xu; out_y[v]=yu;
			nz+=partial_objective(n,edges,out_x,out_y,v,adjs[v]);
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
}

struct coord_t
{
  std::size_t x;
  std::size_t y;
};
struct face_counter : public boost::planar_face_traversal_visitor
{
  face_counter() : count(0) {}
  void begin_face() { ++count; }
  int count;
};

void embad_planar(int n,vector<int>* arr,int w,int h,int* x,int* y){
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
	
	nonconvexed_decrossing(n,arr,w,h,x,y);
}
void embad_general(int n,vector<int>* grr,int w,int h,int* x,int* y){
	for(int v=0;v<n;v++){
		x[v]=rand()%w;
		y[v]=rand()%h;
	}
	nonconvexed_decrossing(n,grr,w,h,x,y);
}