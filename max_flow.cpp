#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
#define rl register long long
#define N 10010
#define M 100010
ll hd[N],nxt[M<<1],to[M<<1],cnt=1,n,m,s,t,w[M<<1],vis[N],dep[N],cur[N];
inline void add_edge(rl a,rl b,rl c){nxt[++cnt]=hd[a],to[cnt]=b,hd[a]=cnt,w[cnt]=c;}
const ll inf=2e17;
bool bfs(){
	memset(vis,0,sizeof(vis));
	memset(dep,0,sizeof(dep));
	queue<ll> q;
	q.push(s);vis[s]=1;
	while(!q.empty()){
		rl u=q.front();q.pop();
		for(rl p=hd[u],v;p;p=nxt[p]) if(!vis[v=to[p]] && w[p])
			dep[v]=dep[u]+1,vis[v]=true,q.push(v);
	}
	return vis[t];
}
ll dfs(rl u,rl k){
	rl fl=0;
	if(u==t) return k;
	for(rl p=cur[u],f,v;p;p=nxt[p]) if((v=to[p]) && (cur[u]=p) && w[p] && dep[v]==dep[u]+1){
		f=dfs(v,min(w[p],k));
		if(f) w[p]-=f,w[p^1]+=f,fl+=f,k-=f;
		else dep[v]=0;
		if(!k) break;
	}
	return fl;
}
ll max_flow(){
	rl ans=0;
	while(bfs()){
		memcpy(cur,hd,sizeof(hd));
		rl f=dfs(s,inf);
		if(f==0) break;
		ans+=f;
	}
	return ans;
}