#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef long long ll;
#define N 10010
#define M 100010
#define rl register long long
ll hd[N],nxt[M<<1],T[M<<1],w[M<<1],c[M<<1],cnt=1,n,m,h[N],d[N],max_flow,min_cost,prp[N],s,t;const ll inf=2e17;
struct nd{ll id,nm;};
inline bool operator>(const nd &a,const nd &b){return a.nm>b.nm;}
inline void add_edge(rl a,rl b,rl c0,rl d){nxt[++cnt]=hd[a],T[cnt]=b,w[cnt]=c0,c[cnt]=d,hd[a]=cnt;}
void mcmf(){
	priority_queue<nd, vector<nd>, greater<nd> > pq;
	while(true){
		fill(d+1,d+1+n,inf);
		d[s]=0;pq.push((nd){s,0});
		while(!pq.empty()){
			register nd u=pq.top();pq.pop();
			if(u.nm>d[u.id]) continue;
			for(rl p=hd[u.id],v,co;p;p=nxt[p]) if((v=T[p]) && w[p]){
				co=c[p]-h[v]+h[u.id];
				if(co+d[u.id]<d[v])	d[v]=co+d[u.id],pq.push((nd){v,d[v]}),prp[v]=p;
			}
		}
		for(rl i=1;i<=n;++i)
			h[i]+=d[i];
		if(d[t]>=inf) break;
		rl cap=inf;
		for(rl u=t;u!=s;u=T[prp[u]^1])
			cap=min(cap,w[prp[u]]);
		for(rl u=t;u!=s;u=T[prp[u]^1])
			w[prp[u]]-=cap,w[prp[u]^1]+=cap;
		max_flow+=cap,min_cost+=cap*h[t];
	}
}