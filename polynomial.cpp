#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define reg register
#define ri register int
using namespace std;
#define N 4194310
#define P 998244353
#define AP 332748118
#define G 3
inline int fp(ri un,ri up){ri ans=1,off=un;while(up){if(up&1) ans=1LL*ans*off%P;off=1LL*off*off%P;up>>=1;}return ans;}
int rev[N],ws[2][N],n00;
inline void mswap(ri &a,ri &b){a^=b,b^=a,a^=b;}
inline int s_m(ri a){return a>P?a-P:a;}
void NTT(int *p,ri bits,ri V){
	ri n0=(1<<bits);
	int *w=ws[V==1?0:1];
	for(ri i=0;i<n0;++i)
		if(i<(rev[i]>>(n00-bits))) mswap(p[i],p[rev[i]>>(n00-bits)]);
	ri t1,t2,i,j,mid;
	for(mid=1;mid<n0;mid<<=1)
		for(i=0;i<n0;i+=(mid<<1))
			for(j=0;j<mid;++j)
				t1=1LL*p[i+j+mid]*w[mid+j]%P,t2=p[i+j],p[i+j]=s_m(t1+t2),p[i+j+mid]=s_m(t2-t1+P);
	if(V==-1){
		ri theta=fp(n0,P-2);
		for(ri i=0;i<n0;++i)
			p[i]=1LL*p[i]*theta%P;
	}
}
void init_ws(ri len){
	ri m=0,n0=1;
	while(n0<(len<<1)) n0<<=1,++m;
	n00=m;
	// n0>>=1;
	for(ri i=0;i<n0;++i){
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(m-1));
		// if(i<rev[i]) mswap(p[i],p[rev[i]]);
	}
	for(ri i=(n0>>1);i;i>>=1)
		ws[0][i]=ws[1][i]=1;
	for(ri j1=fp(G,(P-1)/(n0<<1)),j2=fp(AP,(P-1)/(n0<<1)),i=n0;i;i>>=1,j1=1LL*j1*j1%P,j2=1LL*j2*j2%P)
		for(ri j=i+1;j!=(i<<1);++j)
			ws[0][j]=1LL*ws[0][j-1]*j1%P,ws[1][j]=1LL*ws[1][j-1]*j2%P;
}
int p3[N],pre[N];
void inv(ri len,int *p1,int *p2){
	if(len==1){p2[0]=fp(p1[0],P-2);return;}
	inv((len+1)>>1,p1,p2);
	ri n0=1,m=0;
	while(n0<(len<<1)) n0<<=1,++m;
	memcpy(p3,p1,sizeof(int)*len);
	memset(p3+len,0,sizeof(int)*(n0-len));
	NTT(p3,m,1),NTT(p2,m,1);
	for(ri i=0;i<n0;++i)
		p2[i]=(2LL-1LL*p3[i]*p2[i]%P+P)%P*p2[i]%P;
	NTT(p2,m,-1);
	memset(p2+len,0,sizeof(int)*(n0-len));
}
int p4[N];
void sqrt(ri len,int *p1,int *p2){
	if(len==1){p2[0]=1;return;}
	sqrt((len+1)>>1,p1,p2);
	ri n0=1,m=0;
	while(n0<(len<<1)) n0<<=1,++m;
	memset(p4,0,sizeof(int)*n0);
	inv(len,p2,p4);
	memcpy(p3,p1,sizeof(int)*len);
	memset(p3+len,0,sizeof(int)*(n0-len));
	NTT(p4,m,1),NTT(p3,m,1);
	for(ri i=0,inv2=fp(2,P-2);i<n0;++i)
		p4[i]=1LL*p4[i]*inv2%P*p3[i]%P;
	NTT(p4,m,-1);
	for(ri i=0,inv2=fp(2,P-2);i<len;++i)
		p2[i]=s_m(p2[i]*inv2%P+p4[i]);
	memset(p2+len,0,sizeof(int)*(n0-len));
}
void ln(ri len,int *p1,int *p2){
	inv(len,p1,p2);
	for(ri i=0;i<len-1;++i)
		p3[i]=1LL*p1[i+1]*(i+1)%P;
	ri n0=1,m=0;
	while(n0<(len<<1)) n0<<=1,++m;
	memset(p3+len-1,0,sizeof(int)*(n0-len+1));
	NTT(p3,m,1),NTT(p2,m,1);
	for(ri i=0;i<n0;++i)
		p4[i]=1LL*p2[i]*p3[i]%P;
	NTT(p4,m,-1);
	for(ri i=1;i<len;++i)
		p2[i]=1LL*p4[i-1]*pre[i]%P;
	p2[0]=0;
	memset(p2+len,0,sizeof(int)*(n0-len));
}
int p5[N];
void exp(ri len,int *p1,int *p2){
	if(len==1){p2[0]=1;return;}
	exp((len+1)>>1,p1,p2);
	ri n0=1,m=0;
	while(n0<(len<<1)) n0<<=1,++m;
	memset(p5,0,sizeof(int)*n0);
	ln(len,p2,p5);
	memset(p3+len,0,sizeof(int)*(n0-len));
	for(ri i=0;i<len;++i)
		p3[i]=s_m(-p5[i]+p1[i]+P);
	p3[0]=s_m(p3[0]+1);
	NTT(p2,m,1),NTT(p3,m,1);
	for(ri i=0;i<n0;++i)
		p2[i]=1LL*p2[i]*p3[i]%P;
	NTT(p2,m,-1);
	memset(p2+len,0,sizeof(int)*(n0-len));
}
int p6[N];
inline int mmin(ri a,ri b){return a>b?b:a;}
void div(ri len1,ri len2,int *p1,int *p2,int *p7,int *p8){
	ri len3=len1-len2+1;
	for(ri i=0;i<len3;++i)
		p5[i]=p1[len1-i-1];
	for(ri i=0;i<len3 && i<len2;++i)
		p6[i]=p2[len2-i-1];
	ri p6_len=mmin(len3,len2),n0=1,m=0;
	while(n0<(len1<<1)) n0<<=1,++m;
	memset(p6+p6_len,0,sizeof(int)*(n0-p6_len));
	memset(p5+len3,0,sizeof(int)*(n0-len3));
	memset(p7,0,sizeof(int)*n0);
	inv(len3,p6,p7);
	NTT(p7,m,1),NTT(p5,m,1);
	for(ri i=0;i<n0;++i)
		p6[i]=1LL*p7[i]*p5[i]%P;
	NTT(p6,m,-1);
	for(ri i=0;i<len3;++i)
		p7[i]=p6[len3-i-1];
	memset(p7+len3,0,sizeof(int)*(n0-len3));
	memcpy(p6,p7,sizeof(int)*n0);
	memcpy(p5,p2,sizeof(int)*len2);
	memset(p5+len2,0,sizeof(int)*(n0-len2));
	NTT(p5,m,1),NTT(p6,m,1);
	for(ri i=0;i<n0;++i)
		p6[i]=1LL*p5[i]*p6[i]%P;
	NTT(p6,m,-1);
	for(ri i=0;i<len2-1;++i)
		p8[i]=s_m(p1[i]-p6[i]+P);
	memset(p8+len2-1,0,sizeof(int)*(n0-len2+1));
}
void ksm(ri len,ri up,int *p1,int *p2){
	ri n0=1,m=0;
	while(n0<(len<<1)) n0<<=1,++m;
	ln(len,p1,p6);
	for(ri i=0;i<len;++i)
		p6[i]=1LL*p6[i]*up%P;
	exp(len,p6,p2);
}