#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <array>

int main(){
    std::vector<std::string> sv;
    sv.push_back("one");
    sv.push_back("two");
    sv.push_back("three");
    std::array<int, 3> a = { {3, 2, 1} };
    std::sort(sv.begin(), sv.end());
    std::sort(a.begin(), a.end());
    std::cout << "vector sorted:\n";
    for(std::vector<std::string>::iterator i = sv.begin(); i != sv.end(); ++i){
        std::cout << *i << "\n";
    }
    std::cout << "array sorted:\n";
    for(int i = 0; i < a.size(); ++i){
        std::cout << a[i] << "\n";
    }
    std::list<int> l;
    auto it = std::back_insert_iterator<std::list<int>>(l);
    for(auto ait = a.begin(); ait != a.end(); ++ait){
        *it = *ait;
        ++it;
    }
    std::cout << "unsorted list:\n";
    for(auto iit = l.begin(); iit != l.end(); ++iit){
        std::cout << *iit << "\n";
    }
    l.sort();
    std::cout << "sorted list:\n";
    for(auto lit = l.begin(); lit != l.end(); ++lit){
        std::cout << *lit << "\n";
    }
    std::map<std::string, int> m;
    int index = 0;
    for(auto sit = sv.begin(); sit != sv.end(); ++sit){
        m.insert(std::pair<std::string,int>(*sit, index));
        ++index;
    }
    std::cout << "map (key,value):\n";
    for(auto mit = m.begin(); mit != m.end(); ++mit){
        std::cout << mit->first << "," << mit->second << "\n";
    }
}
