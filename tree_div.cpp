#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define rl register long long
#define ri register int
#define N 100010
ll dfn[N],sz[N],son[N],hd[N],nxt[N<<1],t[N<<1],cnt,cnt2,top[N],fs[N],n,m;
void add_edge(rl a,rl b){nxt[++cnt]=hd[a],t[cnt]=b,hd[a]=cnt;}
void dfs1(rl u,rl fa){
	rl tmp=0;sz[u]=1,fs[u]=fa;
	for(rl p=hd[u],v;p;p=nxt[p]) if((v=t[p])!=fa)
		dfs1(v,u),sz[u]+=sz[v],sz[v]>tmp?(tmp=sz[v],son[u]=v):1LL;
}
void dfs2(rl u,rl fa){
	dfn[u]=++cnt2;
	for(rl p=hd[u],v;p;p=nxt[p]) if((v=t[p])!=fa && v==son[u])
		top[v]=top[u],dfs2(v,u);
	for(rl p=hd[u],v;p;p=nxt[p]) if((v=t[p])!=fa && v!=son[u])
		top[v]=v,dfs2(v,u);
}
void connect(rl x){
	for(;x;x=fs[top[x]])
		/**/;
}