#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
typedef long long ll;
#define ri register int
#define N 1000010
struct acam{
	queue<int> q;
	int trans[N][26],fail[N],val[N],cnt;
	void ins(char *s){
		ri len=strlen(s),now=0;
		for(ri i=0,u;i<len;++i){
			u=s[i]-'a';
			if(!trans[now][u]) trans[now][u]=++cnt;
			now=trans[now][u];
		}
		++val[now];
	}
	void build(){
		for(ri i=0;i<26;++i) if(trans[0][i])
			q.push(trans[0][i]);
		while(!q.empty()){
			ri u=q.front();q.pop();
			for(ri i=0;i<26;++i)
				if(trans[u][i]) fail[trans[u][i]]=trans[fail[u]][i],q.push(trans[u][i]);
				else trans[u][i]=trans[fail[u]][i];
		}
	}
	int query(char *s){
		ri len=strlen(s),now=0,ans=0;
		for(ri i=0;i<len;++i){
			now=trans[now][s[i]-'a'];
			for(ri j=now;j && (~val[j]);j=fail[j])
				ans+=val[j],val[j]=-1;
		}
		return ans;
	}
}T;