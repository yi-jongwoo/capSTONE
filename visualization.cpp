#include "stone_internal_header.h"

void make_svg_undirected(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y){
	ofstream fout(filename);
	fout<<"<html><body>\n";
	
	fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
	
	for(int i=0;i<n;i++)for(int j:arr[i])
		fout<<"<line x1=\""<<x[i]<<"\" y1=\""<<y[i]
			<<"\" x2=\""<<x[j]<<"\" y2=\""<<y[j]
			<<"\" style=\"stroke:red;stroke-width:2\" />\n";
	
	for(int i=0;i<n;i++)
		fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
			<<"\" r=\"4\" fill=\"blue\" />\n";
	for(int i=0;i<n;i++)
		fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
			<<"\" fill=\"black\">"<<i<<"</text>\n";
	fout<<"</svg></body></html>";
}
void make_svg(string filename,int w,int h,int n,vector<int>* arr,int* x,int* y){
	ofstream fout(filename);
	fout<<"<html><body>\n";
	
	fout<<"<svg width=\""<<w<<"\" height=\""<<h<<"\">\n";
	
	fout<<"<defs><marker id='head' orient=\"auto\"markerWidth='3' markerHeight='4'\
refX='0.1' refY='2'><path d='M0,0 V4 L2,2 Z' fill=\"black\"/></marker></defs>\n";

	for(int i=0;i<n;i++)for(int j:arr[i])
		fout<<"<path id='arrow-line' marker-end='url(#head)' stroke-width='4' \
fill='none' stroke='black' d='M"<<x[i]<<","<<y[i]<<", "<<x[j]<<" "<<y[j]<<",120'/>\n";
	for(int i=0;i<n;i++)
		fout<<"<circle cx=\""<<x[i]<<"\" cy=\""<<y[i]
			<<"\" r=\"4\" fill=\"blue\" />\n";
	for(int i=0;i<n;i++)
		fout<<"<text x=\""<<x[i]+2<<"\" y=\""<<y[i]
			<<"\" fill=\"black\">"<<i<<"</text>\n";
	fout<<"</svg></body></html>";
}
#define epoch 1000
typedef long long ll;
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
inline ll nonconvex_cross_objective(int n,vector<pair<int,int>>&edges,
  int* x,int* y){
  	ll res=0;
	int m=edges.size();
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++)if(i!=j){
			if(edges[i].first==edges[j].first)
				continue;
			if(edges[i].first==edges[j].second)
				continue;
			if(edges[i].second==edges[j].first)
				continue;
			if(edges[i].second==edges[j].second)
				continue;
			res+=is_cross(x[edges[i].first],y[edges[i].first],x[edges[i].second],y[edges[i].second],
			  x[edges[j].first],y[edges[j].first],x[edges[j].second],y[edges[j].second]);
			
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)if(i!=j)
			if(abs(x[i]-x[j])+abs(y[i]-y[j])<10){
				res+=10000*(10-abs(x[i]-x[j])-abs(y[i]-y[j]));
			}
	res*=100;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(edges[j].first!=i&&edges[j].second!=i){
				ll x0=x[edges[j].first];
				ll y0=y[edges[j].first];
				ll x1=x[edges[j].second];
				ll y1=y[edges[j].second];
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
						r=abs(d-e)/sqrt(dx*dx+dy*dy);
				}
				res+=r==0?2000:50/r;
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
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=nonconvex_cross_objective(n,edges,out_x,out_y);
			int x=out_x[v]; out_x[v]=rand()%w;
			int y=out_y[v]; out_y[v]=rand()%h;
			ll nz=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			ll z=nonconvex_cross_objective(n,edges,out_x,out_y);
			int u=rand()%n;
			std::swap(out_x[u],out_x[v]);
			std::swap(out_y[u],out_y[v]);
			ll nz=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=nonconvex_cross_objective(n,edges,out_x,out_y);
			int x=out_x[v]; 
			int rx=max(0,x-100),ry=min(w,x+100);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-100),ry=min(h,y+100);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
	}
	for(int t=0;t<30;t++){
		for(int v=0;v<n;v++){
			ll z=nonconvex_cross_objective(n,edges,out_x,out_y);
			int x=out_x[v]; 
			int rx=max(0,x-10),ry=min(w,x+10);
			out_x[v]=rand()%(ry-rx+1)+rx;
			int y=out_y[v]; 
			rx=max(0,y-10),ry=min(h,y+10);
			out_y[v]=rand()%(ry-rx+1)+rx;
			ll nz=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(z<nz){
				out_x[v]=x;
				out_y[v]=y;
			}
		}
		for(int v=0;v<n;v++){
			ll z=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(arr[v].empty())
				continue;
			int u=arr[v][rand()%arr[v].size()];
			std::swap(out_x[u],out_x[v]);
			std::swap(out_y[u],out_y[v]);
			ll nz=nonconvex_cross_objective(n,edges,out_x,out_y);
			if(z<nz){
				std::swap(out_x[u],out_x[v]);
				std::swap(out_y[u],out_y[v]);
			}
		}
	}
}
