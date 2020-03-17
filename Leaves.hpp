//
//  Leaves.hpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/13.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef Leaves_hpp
#define Leaves_hpp
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <stdio.h>
#include "LSystem.hpp"


class Leaves
{
public:
    int l = 0;
    glm::mat4 model;
    GLuint vao;
    GLuint vbos[2];
    std::vector<State> leaves;
    std::vector<glm::vec3> vertices;
    std::vector<int> indices;
    Leaves(std::vector<Trunk> t);
    ~Leaves();
    void draw();
};

#endif /* Leaves_hpp */
