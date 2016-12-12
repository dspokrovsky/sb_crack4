#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
using namespace std;

bool check(std::string login, std::vector<char> pass, int start){
    std::vector<char> w(pass.size());
    std::vector<char> pass_cop(pass);
    for(int i = 0; i <pass.size() ; i++){
        auto r = std::min_element(pass_cop.begin(),pass_cop.end());
        auto d = std::distance(pass_cop.begin(), r);
        w[d] = i;
        *r = 127;
    }
    int ptr = start;
    std::string res ="";
    for(int i = pass.size()-1; i >=0; i--){
        res = pass[ptr] + res;
        ptr = w[ptr];
    }
    //std::cout << res<<'\n';
    return login == res;
}

std::vector <char>  shu(const std::map <char, std::vector <int> > &wght,const std::string &login,char pr,
                                                    std::vector <char>  &result2, int & st, const std::string &login_zer){
    std::vector <char>  result = result2;
    bool flg = false;
    //std::cout << login<<std::endl;
    //std::for_each(result.begin(),result.end(),[](char c){std::cout << c;});
    //std::cout <<'!'<<st<<std::endl;
    if(login.size()==0) return result;//check(login_zer,result, st));
    for(int i = login.size()-1; i >=0 ;i--){
        if (wght.at(pr).size() ==1){
            result2[wght.at(pr).at(0)] = login.at(i);
            pr = login.at(i);
        }else{
            result = result2;
            for (int k = 0; k < wght.at(pr).size();k++){
                result = result2;
                result[wght.at(pr).at(k)] = login.at(i);
                std::string new_login = login.substr(0,i);
                std::map <char, std::vector <int> > wght2 = wght;
                wght2.at(pr).erase(wght2.at(pr).begin()+k,wght2.at(pr).begin()+k+1);
                //std::cout << new_login <<std::endl;
                std::vector <char>  d = shu(wght2,new_login,login.at(i), result,st,login_zer);
                if (check(login_zer,d,st)){
                    return d;
                };
            }
            //if (flg == true) break;
        }
    }
    return result2;
    //return (check(login_zer,result, st));

}


int main()
{
    std::string login = "zbasdfa";
    //std::cin >> login;
    std::vector<char> result(login.size());
    std::vector<std::pair<char, char> > w;
    std::string str = login;

    std::sort(str.begin(),str.end());
//culculate weight
    std::map <char, std::vector <int> > wght;
    for (int i =0; i < str.size(); i ++){
        auto buf = wght.find(str[i]);
        if (buf != wght.end()){
            wght.at(str[i]).push_back(i);
        }else{
            wght.emplace(std::make_pair(str[i], std::vector<int>{i}));
        }
    }
    int st = wght.at(*login.begin()).at(0);
    //result =  shu(wght, login, *login.begin(), result, st, login);
    //std::cout << check(login,result,wght.at(*login.begin()).at(0));
    for(int i = 0; i < login.size(); i++){
        st = wght.at(login[i]).at(0);
        result =  shu(wght, login, login[i], result, st, login);
        if( check(login,result,wght.at(*login.begin()).at(0))) break;
    }


    std::for_each(result.begin(),result.end(),[](char c){std::cout << c;});

    std::cout<<std::endl;
    std::cout.unsetf(ios::dec);
    std::cout.setf(ios::hex);
    std::for_each(result.begin(),result.end(),[](char c){std::cout << (int)c;});
    if (st<15){
        std::cout << 0<<(int)st;}
    else{
        std::cout <<(int)st;
    }
    std::cout<< std::endl;

    return 0;
}
