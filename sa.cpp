#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define ri register int
#define rl register long long
#define N 100010
struct suffix_array{
	int sa[N],rk[N],x[N],y[N],c[N],n0,m,num,z[N],st[N][20],lg[(1<<20)+10],src0[N];
	void sort_pair(){
		num=1;
		for(ri i=1;i<=n0;++i) z[i]=rk[i];
		for(ri i=1;i<=n0;++i) c[y[i]]++;
		for(ri i=1;i<=m;++i) c[i]+=c[i-1];
		for(ri i=1;i<=n0;++i) x[c[y[i]]--]=i;
		for(ri i=0;i<=m;++i) c[i]=0;
		for(ri i=1;i<=n0;++i) c[z[i]]++;
		for(ri i=1;i<=m;++i) c[i]+=c[i-1];
		for(ri i=n0;i;--i) sa[c[z[x[i]]]--]=x[i];
		for(ri i=0;i<=m;++i) c[i]=0;
		rk[sa[1]]=1;
		for(ri i=2;i<=n0;++i) rk[sa[i]]=(y[sa[i]]==y[sa[i-1]] && z[sa[i]]==z[sa[i-1]]?num:++num);
	}
	void SA(ri n00,char *src){
		m=127,n0=n00;
		for(ri i=1;i<=n0;++i)
			rk[i]=src[i];
		memcpy(src0+1,rk+1,sizeof(int)*n0);
		for(ri w=1;w<n0;w<<=1){
			for(ri i=1;i<=n0-w;++i) y[i]=rk[i+w];
			for(ri i=n0-w+1;i<=n0;++i) y[i]=0;
			sort_pair();
			if(num==n0) break;m=num;
		}
		for(ri i=2;i<(1<<20);++i)
			lg[i]=lg[i>>1]+1;
		for(ri i=1,k=0,j;i<=n0;++i){
			if(rk[i]==1) continue;
			if(k) --k;j=sa[rk[i]-1];
			while(j+k<=n0 && i+k<=n0 && src0[j+k]==src0[i+k]) ++k;
			st[rk[i]][0]=k;
		}
		for(ri j=1;j<20;++j)
			for(ri i=2;i+(1<<j)-1<=n0;++i)
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	}
	inline int query(ri a,ri b){
		if(a==b) return n0-a+1;a=rk[a],b=rk[b];if(a>b) swap(a,b);
		++a;ri c=lg[b-a+1];return min(st[a][c],st[b-(1<<c)+1][c]);
	}
}saa;