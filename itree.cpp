#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long ll;
#define ri register int
#define N 300010
int n,tot,hd[N],t[N<<1],nxt[N<<1];
inline void add_edge(ri u,ri v){nxt[++tot]=hd[u],t[tot]=v,hd[u]=tot;}
inline void insert(int u,int v){add_edge(u,v); add_edge(v,u);}
inline void init(){
    int ta,tb;
    scanf("%d",&n);
    for(ri i=1;i<n;i++)
        scanf("%d %d",&ta,&tb),add_edge(ta,tb),add_edge(tb,ta);
}
int fa[N][20],sz[N],dep[N],dfn[N],cnt;
void dfs(ri u,ri ff){
    fa[u][0]=ff,sz[u]=1,dep[u]=dep[ff]+1,dfn[u]=++cnt;
    for(ri i=1;(1<<i)<dep[u];++i)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    for(ri p=hd[u],v;p;p=nxt[p]) if((v=t[p])!=ff)
        dfs(v,u),sz[u]+=sz[v];
}
inline int LCA(ri u,ri v){
    if(dep[u]<dep[v]) swap(u,v);
    ri delta=dep[u]-dep[v];
    for(ri i=0;i<20;i++) if(delta&(1<<i))
        u=fa[u][i];
    if(u==v) return u;
    for(ri i=19;i>=0;i--) if(fa[u][i]!=fa[v][i])
        u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int st,top,stk[N<<1],a[N],q,m;
inline bool cmp(int x,int y){return dfn[x]<dfn[y];} 
inline void insert(ri x){
    if(top==1) {
        stk[++top]=x;
        return;
    }
    ri lca=LCA(x,stk[top]);
    while(top>1&&dfn[stk[top-1]]>=dfn[lca]) add_edge(stk[top-1],stk[top]),top--;
    if(stk[top]!=lca) add_edge(lca,stk[top]),stk[top]=lca;
    stk[++top]=x; 
}
inline void solve(){
    init(),dfs(1,0);scanf("%d",&q);tot=0,memset(hd,0,sizeof(hd));
    while(q--){
        scanf("%d",&m);
        for(ri i=1;i<=m;++i)
            scanf("%d",&a[i]);
        sort(a+1,a+1+m,cmp);stk[top=1]=1;
        if(a[1]==1) st=2;else st=1;
        for(ri i=st;i<=m;++i)
            insert(a[i]);
        while(top>1){add_edge(stk[top-1],stk[top]);--top;}
        /*
        */
        hd[1]=0;
        for(ri i=1;i<=m;++i)
            hd[a[i]]=0;
        tot=0;
    }
}