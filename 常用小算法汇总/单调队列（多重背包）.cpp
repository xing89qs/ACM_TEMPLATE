#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int a[105],c[105];
bool dp[100005];
int q[100005];

int main(void){
    int n,m;
    while(scanf("%d %d",&n,&m),n+m){
        for(int i = 0;i<n;i++) scanf("%d",&a[i]);
        for(int i = 0;i<n;i++) scanf("%d",&c[i]);
        for(int i = 1;i<=m;i++) dp[i] = false;
        dp[0] = true;
        int ans = 0;
        for(int i = 0;i<n;i++){
            int mx = a[i]*c[i];
            if(c[i]==1){
                for(int j = m;j>=a[i];j--)
                    if(dp[j-a[i]]) dp[j] = true;
            }else if(mx>=m){
                for(int j = a[i];j<=m;j++)
                    if(dp[j-a[i]]) dp[j] = true;
            }else{
                for(int md = 0;md<a[i];md++){
                    int head = 0,tail = -1;
                    for(int j = md;j<=m;j+=a[i]){
                        while(head<=tail&&j-q[head]>mx) head++;
                        if(dp[j]) q[++tail] = j;
                        else if(head<=tail) dp[j] = true;
                    }
                }
            }
        }
        for(int i = 1;i<=m;i++) if(dp[i]) ans++;
        printf("%d\n",ans);
    }
}