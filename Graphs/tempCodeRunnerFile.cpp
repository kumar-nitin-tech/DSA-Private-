vector<int>ans;
    ans = bfsTraversal(edges,adjList);
    for(auto i:ans){
        cout<<i<<" ";
    }