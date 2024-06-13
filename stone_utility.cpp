#include "stone_internal_header.h"
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
ll cactus_objective(int n,vector<pair<int,int>>&edges,
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
	res*=1000000;
	for(int j=0;j<n;j++)if(u!=j)
		if(abs(x[u]-x[j])+abs(y[u]-y[j])<10){
			res+=(10-abs(x[u]-x[j])-abs(y[u]-y[j]));
		}
	
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
ll planar_objective(int n,vector<pair<int,int>>&edges,
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
	res*=1000000;
	for(int j=0;j<n;j++)if(u!=j)
		if(abs(x[u]-x[j])+abs(y[u]-y[j])<10){
			res+=(10-abs(x[u]-x[j])-abs(y[u]-y[j]));
		}
	
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
ll general_objective(int n,vector<pair<int,int>>&edges,
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
