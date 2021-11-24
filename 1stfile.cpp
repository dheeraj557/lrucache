#include<iostream>
#include<list>
#include<unordered_map>

using namespace std;

class node{
    public:
    string key;
    int value;
    node(string key,int value)
    {
        this->key=key;
        this->value=value;
    }
};

class LRUcache{
    public:
    int maxSize;
    list<node>l;
    unordered_map<string,list<node>::iterator>m;
    LRUcache(int maxSize)
    {
        this->maxSize= maxSize > 1 ? maxSize : 1;
    }
    void insertKeyValue(string key,int value){
        if(m.count(key)!=0){
            auto it=m[key];
            it->value=value;
        }
        else
        {
            if(l.size()==maxSize){
                node last=l.back();
                m.erase(last.key);
                l.pop_back();
            }
            node n(key,value);
            l.push_front(n);
            m[key]=l.begin();
        }
    }
    int* getValue(string key){
        if(m.count(key)!=0){
            auto it=m[key];
            int value=it->value;
            l.push_front(*it);
            l.erase(it);
            m[key]=l.begin();
            return &l.begin()->value;
        }
        return NULL;
    }
    string mostRecentKey(){
        return l.front().key;
    }
};

int main()
{
    LRUcache lru(3);
    lru.insertKeyValue("mango",10);
    lru.insertKeyValue("apple",20);
    lru.insertKeyValue("guava",30);
    cout<<lru.mostRecentKey()<<endl;
    lru.insertKeyValue("mango",40);
    cout<<lru.mostRecentKey()<<endl;
    lru.insertKeyValue("banana",20);
    if(lru.getValue("apple")==NULL)
    {
        cout<<"apple doesn't exist";
    }
    if(lru.getValue("guava")==NULL)
    {
        cout<<"guava doesn't exist";
    }
    if(lru.getValue("banana")==NULL)
    {
        cout<<"banana doesn't exist";
    }    
    return 0;
}
