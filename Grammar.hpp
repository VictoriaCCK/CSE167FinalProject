//
//  Grammar.hpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/10.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef Grammar_hpp
#define Grammar_hpp

#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

class Grammar
{
public:
    int l = 0;
    map<char, std::vector<string>> d;
    string gram;
    Grammar(string origin, int levels);
    ~Grammar();
    string search(char target);
};
#endif /* Grammar_hpp */
