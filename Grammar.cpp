//
//  Grammar.cpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/10.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#include "Grammar.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

Grammar::Grammar(string origin, int levels)
{
    gram = origin;
//    d['F'].push_back("F[+F]F[-F]F");
//    d['F'].push_back("F[+F]F[-F[+F]]");
//    d['F'].push_back("FF+[+F+F]-[+F]");
    d['F'].push_back("F");
    d['X'].push_back("F[$$$[*X][/X]]");
    d['X'].push_back("F[%%%[/X][*X]]");
    d['X'].push_back("F[$[*X][/X]]");
    d['X'].push_back("F[%%[*X][/X]]");
    
    l = levels;
    string result = gram;
    for (int i = 0; i < levels; i ++) {
        string tmp = "";
        for (int j = 0; j < result.size(); j++) {
            tmp += search(result[j]);
        }
        result = tmp;
    }
    gram = result;
}


Grammar::~Grammar()
{
    
}

string Grammar:: search(char target)
{
    if (d.find(target) == d.end()) {
        string ret;
        ret.push_back(target);
        return ret;
    }
    
    int num = rand()%d[target].size();

    return d[target][num];
}

