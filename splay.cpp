#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define ri register int
#define N 200010
struct Splay{
	#define N 200010
	struct node{int v,cnt,sum,ch[2],fa;}t[N];
	int sz,rot;
	Splay(){sz=rot=0;}
	inline void update(ri x){if(x) t[x].sum=t[t[x].ch[0]].sum+t[t[x].ch[1]].sum+t[x].cnt;}
	inline void pushup(ri x){for(;x;x=t[x].fa) update(x);}
	inline void rtt(ri x){
		ri y=t[x].fa,z=t[y].fa,k=(t[y].ch[1]==x),g=(t[z].ch[1]==y);
		if(y==rot) rot=x;
		t[z].ch[g]=x,t[x].fa=z,t[y].ch[k]=t[x].ch[k^1],t[x].ch[k^1]=y,t[y].fa=x,t[t[y].ch[k]].fa=y;
		update(y),update(x);
	}
	inline void splay(ri x,ri goal){
		ri y,z;
		while(t[x].fa!=goal){
			y=t[x].fa,z=t[y].fa;
			if(z!=goal) ((t[z].ch[0]==y)^(t[y].ch[0]==x))?rtt(x):rtt(y);
			rtt(x);
		}
		if(goal==0) rot=x;
	}
	inline void insert(ri x){
		ri fa=0,u=rot;
		while(u && t[u].v!=x) fa=u,u=t[u].ch[x>t[u].v];
		if(u!=0) ++t[u].cnt,pushup(u);
		else{
			u=(++sz);
			if(fa==0) rot=u;
			else t[fa].ch[x>t[fa].v]=u;
			t[u].v=x,t[u].cnt=1,t[u].sum=1,t[u].fa=fa;
			pushup(fa);
		}
		splay(u,0);
	}
	inline void find(ri x){
		ri u=rot;
		while(t[u].ch[x>t[u].v] && x!=t[u].v) u=t[u].ch[x>t[u].v];
		splay(u,0);
	}
	inline int pre(ri x){
		find(x);
		ri u=t[rot].ch[0];
		if(!u) return -1;
		while(t[u].ch[1]) u=t[u].ch[1];
		return u;
	}
	inline int nxt(ri x){
		find(x);
		ri u=t[rot].ch[1];
		if(!u) return -1;
		while(t[u].ch[0]) u=t[u].ch[0];
		return u;
	}
	inline void del(ri x){
		ri pr=pre(x),nx=nxt(x),u;
		if(pr==-1 && nx==-1){
			if(t[rot].cnt>1) --t[rot].sum,--t[rot].cnt;
			else rot=0;
		}
		else if(pr==-1){
			splay(nx,0);
			u=t[nx].ch[0];
			if(t[u].cnt>1) --t[u].cnt,--t[u].sum,pushup(u),splay(u,0);
			else t[nx].ch[0]=0,pushup(nx);
		}
		else if(nx==-1){
			splay(pr,0);
			u=t[pr].ch[1];
			if(t[u].cnt>1) --t[u].cnt,--t[u].sum,pushup(u),splay(u,0);
			else t[pr].ch[1]=0,pushup(pr);
		}
		else {
			splay(pr,0),splay(nx,rot);
			u=t[nx].ch[0];
			if(t[u].cnt>1) --t[u].cnt,--t[u].sum,pushup(u),splay(u,0);
			else t[nx].ch[0]=0,pushup(nx);
		}
	}
	inline int kth(ri x){
		ri u=rot;
		while(1){
			if(x<=t[t[u].ch[0]].sum) u=t[u].ch[0];
			else if(x<=t[t[u].ch[0]].sum+t[u].cnt) return u;
			else x-=t[t[u].ch[0]].sum+t[u].cnt,u=t[u].ch[1];
		}
		return 0;
	}
	inline int rank(ri x){
		find(x);
		return t[t[rot].ch[0]].sum+1;
	}
}T;