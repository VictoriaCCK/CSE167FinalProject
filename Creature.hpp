//
//  creature.hpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/6.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#ifndef creature_hpp
#define creature_hpp

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <string>

#include "Object.h"

class Creature : public Object
{
private:
    std::vector<glm::vec3> points, normals, faces;
    GLuint vao, vbo;
    GLfloat pointSize;
public:
    glm::vec3 ambient = glm::vec3(0.25, 0.25, 0.25);
    glm::vec3 diffuse = glm::vec3(0.23f, 0.5f, 0.f);
    glm::vec3 specular = glm::vec3(0.5f, 0.6f, 0.5f);
    Creature(std::string objFilename, GLfloat pointSize);
    ~Creature();
    
    void draw();
    void update();
    
    void updatePointSize(GLfloat size);
    void spin(float deg);
};

#endif

