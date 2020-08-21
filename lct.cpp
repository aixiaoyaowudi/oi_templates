#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 200010
struct lct{
	struct node{
		int v,s,fa,ch[2];
	}t[N];
	bool r[N];int st[N];
	inline bool nroot(int x){return t[t[x].fa].ch[0]==x || t[t[x].fa].ch[1]==x;}
	inline void sw(int &x,int &y){x^=y,y^=x,x^=y;}
	inline void pushup(int x){t[x].s=t[t[x].ch[0]].s^t[t[x].ch[1]].s^t[x].v;}
	inline void pushr(int x){r[x]^=1,sw(t[x].ch[0],t[x].ch[1]);}
	inline void pushdown(int x){if(r[x]){if(t[x].ch[0]) pushr(t[x].ch[0]);if(t[x].ch[1]) pushr(t[x].ch[1]);r[x]=0;}}
	inline void rtt(int x){
		int y=t[x].fa,z=t[y].fa,k=(t[y].ch[1]==x),g=t[x].ch[k^1];
		if(nroot(y)) t[z].ch[t[z].ch[1]==y]=x;
		t[x].ch[k^1]=y,t[y].ch[k]=g,t[x].fa=z,t[y].fa=x;
		if(g) t[g].fa=y;
		pushup(y),pushup(x);
	}
	inline void splay(int x){
		int y=x,z=0;
		st[++z]=y;
		while(nroot(y)) st[++z]=(y=t[y].fa);
		while(z) pushdown(st[z--]);
		while(nroot(x)){
			y=t[x].fa,z=t[y].fa;
			if(nroot(y)) ((t[y].ch[0]==x)^(t[z].ch[0]==y))?rtt(x):rtt(y);
			rtt(x);
		}
		pushup(x);
	}
	inline void access(int x){for(register int y=0;x;x=t[y=x].fa)splay(x),t[x].ch[1]=y,pushup(x);}
	inline void makeroot(int x){access(x),splay(x),pushr(x);}
	inline void split(int x,int y){makeroot(x),access(y),splay(y);}
	inline int findroot(int x){access(x),splay(x);while(t[x].ch[0]) pushdown(x),x=t[x].ch[0];splay(x);return x;}
	inline void cut(int x,int y){makeroot(x);if(findroot(y)==x && t[y].fa==x && !t[y].ch[0]){t[y].fa=t[x].ch[1]=0;pushup(x);}}
	inline void link(int x,int y){makeroot(x);if(findroot(y)!=x) t[x].fa=y;}
}T;