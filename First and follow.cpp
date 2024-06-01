#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using namespace std;

int main(){
    unordered_map<string, string> grammer;
    unordered_map<string, string> first;
    grammer["S"] = "aAa|Bb";
    grammer["A"] = "a|Cb";
    grammer["B"] = "d|C";
    grammer["C"] = "e|f";

    vector<string> terminals{"S", "A", "B", "C"};
   
    for(int i=0; i<terminals.size(); i++){
        string s = grammer[terminals[i]];
        int j = 0;
        vector<char> stack;
       
        while(j<s.size()){
            if(int(s[j]) >= 65 && int(s[j]) <= 90)
                stack.push_back(s[j]);
    
            else
                first[terminals[i]] += s[j];
           
            while(s[j] != '|' && j < s.size())
                j++;
            j++;
        }
       
        for (auto it = stack.begin(); it != stack.end(); ++it){
            string t;
            t.append(1, *it);

            string temp = grammer[t];
            int k = 0;
           
            while(k<temp.size()){
                if(int(temp[k]) >= 65 && int(temp[k]) <= 90)
                    stack.push_back(temp[k]);
                
                else
                    first[terminals[i]] += temp[k];
               
                while(temp[k] != '|' && k < temp.size())
                    k++;
                k++;
            }
        }
        stack.clear();
    }
   
    for(auto it = first.begin(); it != first.end(); it++){
        string temp = it->second;
        unordered_set<char> s;
        int i=0;
        while(i<temp.size())
            s.insert(temp[i++]);
        cout<<"First of "<<it->first<<" is: ";
        auto itt = s.begin();
        while(itt != s.end()){
            cout<<*(itt)<<" ";
            itt++;
        }
        cout<<endl;
    }
    return 0;
}
