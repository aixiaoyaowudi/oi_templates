#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <assert.h>
using namespace std;
namespace polynomial{
	#define ri register int
	#define rl register long long
	#define N 4194310
	#define P 998244353
	#define AP 332748118
	#define inv2 499122177
	#define G 3
	inline int fp(ri a,ri b){ri ans=1,off=a;while(b){if(b&1) ans=1ll*ans*off%P;off=1ll*off*off%P;b>>=1;}return ans;}
	typedef vector<int> poly;
	int rev[N],ws[2][N],n00,lg[N],pre[N];
	inline void mswap(ri &a,ri &b){a^=b,b^=a,a^=b;}
	inline int s_m(ri a){return a>P?a-P:a;}
	void print(const poly &a){
		for(ri i=0;i<a.size();++i)
			printf("%d ", a[i]);
		printf("\n");
	}
	static unsigned long long t[N];
	void NTT(poly &p,ri V){
		ri bits=lg[p.size()];
		p.resize(1<<bits);
		// printf("poly: ");print(p);printf("V:%d\n", V);
		ri n0=(1<<bits);
		int *w=ws[V==1?0:1];
		for(ri i=0;i<n0;++i)
			t[i]=p[rev[i]>>(n00-bits)];
		pre[1]=1;
		for(ri i=2;i<n0;++i)
			pre[i]=1ll*(P-P/i)*pre[P%i]%P;
		// for(ri i=0;i<n0;++i)
		// 	printf("%llu ",t[i]);
		// printf("\n");
			// if(i<(rev[i]>>(n00-bits))) mswap(p[i],p[rev[i]>>(n00-bits)]);
		rl t1,t2,i,j,mid;
		for(mid=1;mid<n0;mid<<=1)
			for(i=0;i<n0;i+=(mid<<1))
				for(j=0;j<mid;++j)
					t1=t[i+j+mid]*w[mid+j]%P,t2=t[i+j],t[i+j]+=t1,t[i+j+mid]=P+t2-t1;
		if(V==-1){
			rl theta=1;
			for(ri i=0;i<bits;++i)
				theta=theta*inv2%P;
			// assert(theta==(long long)fp(n0,P-2));
			for(ri i=0;i<n0;++i)
				p[i]=theta*t[i]%P;
		}
		else{
			for(ri i=0;i<n0;++i)
				p[i]=t[i]%P;
		}
		// printf("result: ");print(p);
	}
	poly operator*(poly &a,poly &b){
		ri p1=a.size(),p2=b.size();
		// while(p1 && !a[p1-1]) --p1;
		// while(p2 && !b[p2-1]) --p2;
		ri l0=lg[p1+p2],l00=(1<<l0);
		a.resize(l00),b.resize(l00);poly ret(l00);
		NTT(a,1);NTT(b,1);
		for(ri i=0;i<l00;++i)
			ret[i]=1ll*a[i]*b[i]%P;
		NTT(a,-1);NTT(b,-1);
		NTT(ret,-1);
		ret.resize(p1+p2);
		return ret;
	}
	void init_ws(){
		ri m=0,n0=1,len=(N>>5);
		while(n0<(len<<1)) n0<<=1,++m;
		n00=m;
		// printf("%lld\n", n0);
		for(ri i=2;i<=n0;++i)
			lg[i]=lg[i>>1]+1;
		for(ri i=2;i<=n0;++i) if((1<<lg[i])!=i)
			++lg[i];
		for(ri i=0;i<n0;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(m-1));
		for(ri i=(n0>>1);i;i>>=1)
			ws[0][i]=ws[1][i]=1;
		for(ri j1=fp(G,(P-1)/(n0<<1)),j2=fp(AP,(P-1)/(n0<<1)),i=n0;i;i>>=1,j1=1ll*j1*j1%P,j2=1ll*j2*j2%P)
			for(ri j=i+1;j!=(i<<1);++j)
				ws[0][j]=1ll*ws[0][j-1]*j1%P,ws[1][j]=1ll*ws[1][j-1]*j2%P;
	}
	poly p3;
	poly inv(poly &p1){
		// p1=p1*p1;
		ri len=p1.size(),l0=lg[len<<1],l00=(1<<l0);
		if(len==1){
			poly ret(1);ret[0]=fp(p1[0],P-2);
			return ret;
		}
		poly p10(p1);p10.resize((len+1)>>1);
		poly ret=inv(p10);p3=p1;p3.resize(l00);/*print(ret);*/ret.resize(l00);/*print(p3);print(p1);*/
		NTT(p3,1),NTT(ret,1);
		for(ri i=0;i<l00;++i)
			ret[i]=(2LL-1LL*p3[i]*ret[i]%P+P)%P*ret[i]%P;
		NTT(ret,-1);
		ret.resize(len);
		return ret;
	}
	poly p4;
	poly sqrt(poly &p1){
		ri len=p1.size(),l0=lg[len<<1],l00=(1<<l0);
		if(len==1){poly ret(1);ret[0]=1;return ret;}
		poly p10(p1);p10.resize((len+1)>>1);
		poly ret=sqrt(p10);ret.resize(len);p4=inv(ret);p3=p1;
		p3.resize(l00),p4.resize(l00);
		// print(p3),print(p4),print(ret);
		NTT(p3,1),NTT(p4,1);
		for(ri i=0;i<l00;++i)
			p4[i]=1ll*p4[i]*inv2%P*p3[i]%P;
		NTT(p4,-1);
		for(ri i=0;i<len;++i)
			ret[i]=s_m(1ll*ret[i]*inv2%P+p4[i]);
		return ret;
	}
	poly read(ri len){
		poly ret(len);
		for(ri i=0;i<len;++i)
			scanf("%d",&ret[i]);
		return ret;
	}
	poly ln(poly &p1){
		poly ret=inv(p1);ri len=p1.size(),l0=lg[len<<1],l00=(1<<l0);
		p3.resize(len-1);p3.resize(l00);ret.resize(l00);p4.resize(l00);
		for(ri i=0;i<len-1;++i)
			p3[i]=1ll*p1[i+1]*(i+1)%P;
		NTT(p3,1);NTT(ret,1);
		for(ri i=0;i<l00;++i)
			p4[i]=1ll*ret[i]*p3[i]%P;
		NTT(p4,-1);
		for(ri i=1;i<len;++i)
			ret[i]=1ll*p4[i-1]*pre[i]%P;
		ret[0]=0;
		ret.resize(len);
		return ret;
	}
	// poly p5;
	poly exp(poly &p1){
		ri len=p1.size(),l0=lg[len<<1],l00=(1<<l0);
		if(len==1){poly ret(1);ret[0]=1;return ret;}
		poly p10=poly(p1);p10.resize((len+1)>>1);
		poly ret=exp(p10);ret.resize(len);p3=ln(ret);
		for(ri i=0;i<len;++i)
			p3[i]=s_m(-p3[i]+p1[i]+P);
		p3[0]=s_m(p3[0]+1);ret.resize(l00),p3.resize(l00);
		NTT(p3,1);NTT(ret,1);
		for(ri i=0;i<l00;++i)
			ret[i]=1ll*ret[i]*p3[i]%P;
		NTT(ret,-1);ret.resize(len);
		return ret;
	}
};
using namespace polynomial;