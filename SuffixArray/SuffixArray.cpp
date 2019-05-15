#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class SuffixArray {
private:
    struct Suffix {
        int idx,rank[2];
        Suffix(int id,int r1,int r2){
           idx=id;
           rank[0]=r1;
           rank[1]=r2;
        }
    };
    struct comparator {
        inline bool operator() (const Suffix& sf1,const Suffix& sf2){
            if (sf1.rank[0]<sf2.rank[0] || 
               (sf1.rank[0]==sf2.rank[0] && sf1.rank[1]<sf2.rank[1])){
               return true;
               }
            return false;
        }
    };
public:
    /*
     * Get the rank array from a string
     * rank[i] means the position of suffix s[i:] in suffix array
    */
    vector<int> getRank(string s) {
        int N=s.length();
        vector<Suffix> v;
        for (int i=0;i<N;i++){
            v.push_back(Suffix(i,(int)(s[i]-'a'),-1));
        }
        sort(v.begin(),v.end(),comparator());
        vector<int> rank;
        for (int i=0;i<N;i++) rank.push_back(0);
        int idx=0;
        rank[v[0].idx]=0;
        for (int i=1;i<N;i++){
            if (v[i].rank[0]!=v[i-1].rank[0]){
                idx++;
            }
            rank[v[i].idx]=idx;
        }
        int k=0;
        while ((1<<k)<=2*N){
            v.clear();
            for (int i=0;i<N;i++){
                int j=i+(1<<k);
                if (j<N){
                    v.push_back(Suffix(i,rank[i],rank[j]));
                }else{
                    v.push_back(Suffix(i,rank[i],-1));
                }
            }
            sort(v.begin(),v.end(),comparator());
            rank[v[0].idx]=0;
            idx=0;
            for (int i=1;i<N;i++){
                if (v[i].rank[0]!=v[i-1].rank[0] || v[i].rank[1]!=v[i-1].rank[1]){
                    idx++;
                }
                rank[v[i].idx]=idx;
            }
            k++;
        }
        return rank;
    }
    /*
     * Get the height array of a string
     * height[i] means the length of longest common prefix of s[rank[i]:] and s[rank[i]-1:]
    */
    vector<int> getHeight(vector<int> rank,string s){
        int N=s.length();
        vector<int> sa;
        for (int i=0;i<N;i++) sa.push_back(0);
        for (int i=0;i<N;i++) sa[rank[i]]=i;
        int k=0;
        vector<int> height;
        for (int i=0;i<N;i++) height.push_back(0);
        for (int i=0;i<N;i++) {
            if (rank[i]-1<0) continue;
            k=max(0,k-1);
            int j=sa[rank[i]-1];
            while (i+k<N && j+k<N && s[i+k]==s[j+k])
                k++;
            height[rank[i]]=k;
        }
        return height;
    }
};

