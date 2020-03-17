//
//  Trunks.hpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/14.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef Trunks_hpp
#define Trunks_hpp

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


class Trunks
{
public:
    int l = 0;
    glm::mat4 model;
//    GLuint cubemapTexture;
    GLuint vao;
    GLuint vbos[2];
    std::vector<State> leaves;
    std::vector<glm::vec3> vertices;
    std::vector<int> indices;
    Trunks(std::vector<Trunk> t);
    ~Trunks();
//    GLuint loadCubemap(GLuint texture);
    void draw();
};
#endif /* Trunks_hpp */
