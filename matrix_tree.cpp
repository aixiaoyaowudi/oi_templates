#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define rl register long long
#define N 110
ll n,las[N][N],m;
const ll p=1000000007;
inline ll fpow(rl dw,rl up){rl ans=1,off=dw;while(up){if(up&1) ans=ans*off%p;off=off*off%p;up>>=1;}return ans;}
inline void mswap(ll &x,ll &y){x^=y,y^=x,x^=y;}
ll matrix_tree(){
	rl ans=1;
	for(rl j=1;j<n;++j)
		for(rl k=1;k<n;++k)
			las[j][k]=(las[j][k]+p)%p;
	for(rl i=1;i<n;++i){
		rl j=i;
		for(;j<n;++j) if(las[j][i]!=0)
			break;
		if(j==n) return 0LL;
		if(j!=i){
			ans*=-1;
			for(rl k=i;k<n;++k)
				mswap(las[i][k],las[j][k]);
		}
		rl inv=fpow(las[i][i],p-2);
		for(j=i+1;j<n;++j){
			rl k=las[j][i]*inv%p;
			for(rl g=i;g<n;++g)
				las[j][g]=(las[j][g]-(las[i][g]*k)%p+p)%p;
		}
	}
	ans=(ans+p)%p;
	for(rl i=1;i<n;++i)
		ans=ans*las[i][i]%p;
	return ans;
}
/*
ll ta,tb;
int main(){
	scanf("%lld %lld",&n,&m);
	for(rl i=0;i<m;++i)
		scanf("%lld %lld",&ta,&tb),--las[ta][tb],--las[tb][ta],++las[ta][ta],++las[tb][tb];
	printf("%lld\n", matrix_tree());
	return 0;
}
*/