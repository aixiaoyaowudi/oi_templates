#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;
#define N 10000010
struct SAM{
	int maxlen[N],link[N],trans[N][26],sz,lst,val[N];
	SAM(){lst=sz=1;}
	inline void extend(int id){
		int cur=(++sz),p;val[cur]=1;
		maxlen[cur]=maxlen[lst]+1;
		for(p=lst;p && !trans[p][id];p=link[p])
			trans[p][id]=cur;
		if(!p) link[cur]=1;
		else{
			int q=trans[p][id];
			if(maxlen[q]==maxlen[p]+1) link[cur]=q;
			else{
				int clone=(++sz);
				maxlen[clone]=maxlen[p]+1;
				link[clone]=link[q];
				memcpy(trans[clone],trans[q],sizeof(trans[q]));
				for(;p && trans[p][id]==q;p=link[p])
					trans[p][id]=clone;
				link[q]=link[cur]=clone;
			}
		}
		lst=cur;
	}
}T;