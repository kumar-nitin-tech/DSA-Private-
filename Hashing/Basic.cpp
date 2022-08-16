#include<bits/stdc++.h>
using namespace std;

int main(){
    //creation
    unordered_map<string,int>m;

    //Insertion
    
    //1
    pair<string,int>pair1 = make_pair("Nitin",1);
    m.insert(pair1);

    //2
    pair<string,int>pair2("Kumar",2);
    m.insert(pair2);

    //3
    m["Dhiman"] = 3;

    //if 
    m["Dhiman"] = 4;
    //what will happen
    //It will update key of the mapped value so now "Dhiman" has key of 4

    //Output 

    //1
    cout<<m["Dhiman"]<<"\n";

    //2
    cout<<m.at("Nitin")<<"\n";

    //if we try to print any unknown key which is not inserted in map what would happen
    //if print using at operation

    //cout<<m.at("Unknown")<<"\n";
    
    //It show error stating: "terminate called after throwing an instance of 'std::out_of_range'what():  _Map_base::at "
    
    //if we print using 1 method
    cout<<m["Unknown"]<<"\n";
    //It gives output as 0 Why?
    //Because in this case the unknown value id assigned by default as 0 as we not 
    //specify but while using at operation it show error because no map value was in this it create a map automatically
    cout<<m.at("Unknown")<<"\n";


    //size
    cout<<m.size()<<"\n";

    //to find that number is present or not in map
    cout<<m.count("count")<<"\n";
    //if the number is present it will print 1 or else 0

    //erase
    m.erase("Dhiman");
    cout<<m.size()<<"\n";

    //Iteration
    //1
    cout<<"\n";
    for(auto i:m){
        cout<<i.first<<" "<<i.second<<" ";
    }

    cout<<endl;
    //2
    unordered_map<string,int>::iterator it = m.begin();

    while(it != m.end()){
        cout<<it->first<<" "<<it->second<<" ";
        it++; 
    }
    return 0;
}