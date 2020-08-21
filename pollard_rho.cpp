#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define rl register long long
inline ll fp(rl a,rl b,rl c){rl ans=1,off=a;while(b){if(b&1) ans=(__int128)ans*off%c;off=(__int128)off*off%c;b>>=1;}return ans;}
inline bool miller_rabin(rl a){
	if(a==2) return true;
	if(a<2 || !(a&1)) return false;
	rl u,t;
	for(u=a-1,t=0;!(u&1);++t,u>>=1);
	for(rl i=0,x,y,j;i<3;++i){
		x=rand()%(a-2)+2;
		x=fp(x,u,a);
		for(j=0;j<t;++j){
			y=(__int128)x*x%a;
			if(y==1 && x!=1 && x!=a-1) return false;
			x=y;
		}
		if(x!=1) return false;
	}
	return true;
}
inline ll gcd(rl a,rl b){return b==0?a:gcd(b,a%b);}
inline ll pollard_rho(rl x)
{
	rl s=0,t=0,c=1LL*rand()%(x-1)+1,j=0,k=1,tmp=1;
	for(k=1;;k<<=1,s=t,tmp=1){
		for(j=1;j<=k;++j){
			t=((__int128)t*t+c)%x;
			tmp=(__int128)tmp*abs(t-s)%x;
			if((j%127)==0){
				rl d=gcd(tmp,x);
				if(d>1) return d;
			}
		}
		rl d=gcd(tmp,x);
		if(d>1) return d;
	}
	return 1;
}
ll ans=0;
void fact(rl n){
	if(n<2 || n<ans) return;
	if(miller_rabin(n)){ans=max(ans,n);return;}
	rl p=n;
	while(p>=n) p=pollard_rho(n);
	while((n%p)==0) n/=p;
	fact(n),fact(p);
}
/*
int main(){
	srand(329210);
	return 0;
}
*/