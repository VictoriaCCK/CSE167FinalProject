//
//  LSystem.hpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/11.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef LSystem_hpp
#define LSystem_hpp
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <stdio.h>
#include "Grammar.hpp"
#define _USE_MATH_DEFINES
#include <math.h>

class State
{
public:
    glm::vec3 pos;
    glm::vec3 dir;
    double radius;
    int level;
};

class Trunk
{
public:
    glm::vec3 pos1;
    glm::vec3 pos2;
    double radius;
    int level;
};

class FractalSystem
{
public:
    int l = 0;
    glm::mat4 model;
    GLuint vao;
    GLuint vbos[2];
    double direction = 90, angle = 15;
    double dx = 90.f, dy =120.f, dz = 99.f;
    double length = 3;
    double length_factor = 0.998;
    double radius = 1;
    double radius_factor = 0.72;
    State cur_state;
    double leaf_radius = 0.4;
    Grammar* g;
    std::vector<Trunk> trunks;
    std::vector<std::vector<State>> leaves;
    std::vector<glm::ivec3> indice;
    std::vector<glm::vec3> vertices;
    std::vector<int> indices;
    FractalSystem();
    ~FractalSystem();
    void generateTree();
    void draw();
    void spin(float deg);
};

#endif /* LSystem_hpp */
