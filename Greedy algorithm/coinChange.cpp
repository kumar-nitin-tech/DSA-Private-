#include<bits/stdc++.h>
using namespace std;

vector<int> rupee = {1,2,5,10,20,50,100,200,500,2000};

int main(){
    int x;
    cin>>x;
    sort(rupee.begin(), rupee.end(), greater<int>());
    int ans = 0;
    for(int i=0;i<rupee.size();i++){
        ans += x/rupee[i];
        x -= x/rupee[i] * rupee[i];
    }
    cout<<ans;
    
    return 0;
}