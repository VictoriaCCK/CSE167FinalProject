//
//  creature.cpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/6.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#include "creature.hpp"

Creature::Creature(std::string objFilename, GLfloat pointSize)
: pointSize(pointSize)
{
    FILE* fp = std::fopen(objFilename.c_str(), "rb");
    float x, y, z;
    float r, g, b;
    int f1, f2, f3;
    int c1, c2;
    if(fp == NULL){
        perror("err:");
        exit(-1);
    }
    
    do
    {
        c1 = fgetc(fp);
        c2 = fgetc(fp);
        if (c1 == 'v' && c2 == ' '){
            fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
            points.push_back(glm::vec3(x, y, z));
        }
        else{
            if(c1 == 'v' && c2 == 'n'){
                fscanf(fp, "%f %f %f", &x, &y, &z);
                normals.push_back(glm::vec3(x, y, z));
            }else{
                if(c1 == 'f' && c2 == ' '){
                    fscanf(fp, "%u//%u %u//%u %u//%u", &f1, &f1, &f2, &f2, &f3, &f3);
                    faces.push_back(glm::uvec3(f1-1, f2-1, f3-1));
                }
            }
        }
    }while(c1 != EOF && c2!=EOF );
    fclose(fp);
    /*
     * TODO: Section 4, you will need to normalize the object to fit in the
     * screen.
     */
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);
    model = glm::scale(model, glm::vec3(5,5,5));
    model = glm::rotate(model, glm::radians(28.f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model,glm::vec3(0,0,-10));
    // Set the color.
    color = glm::vec3(1.0f, 0.45f, 0.0f);
    
    // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    
    // Bind to the VAO.
    // This tells OpenGL which data it should be paying attention to
    glBindVertexArray(vao);
    
    // Bind to the first VBO. We will use it to store the points.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(),
                 points.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    /*
     * TODO: Section 2 and 3.
     * Following the above example but for vertex normals,
     * 1) Generate a new vertex bufferbuffer,
     * 2) Bind it as a GL_ARRAY_BUFFER type,
     * 3) Pass in the data
     * 4) Enable the next attribute array (which is 1)
     * 5) Tell it how to process each vertex using glVertexAttribPointer
     */
    
    // Generate a vertex buffer objects (VBO).
    glGenBuffers(1, &vbo);
    
    // Bind to the second VBO. We will use it to store the points.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(),
                 normals.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access points through it.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    
    // Unbind from the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

Creature::~Creature()
{
    // Delete the VBO and the VAO.
    // Failure to delete your VAOs, VBOs and other data given to OpenGL
    // is dangerous and may slow your program and cause memory leaks
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Creature::draw()
{
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Set point size.
    glPointSize(pointSize);
    // Draw points
    glDrawArrays(GL_POINTS, 0, points.size());
    // Unbind from the VAO.
    glBindVertexArray(0);
}

void Creature::update()
{
    // Spin the cube by 1 degree.
    spin(0.1f);
    /*
     * TODO: Section 3: Modify this function to spin the dragon and bunny about
     * different axes. Look at the spin function for an idea
     */
}

void Creature::updatePointSize(GLfloat size)
{
    /*
     * TODO: Section 3: Implement this function to adjust the point size.
     */
}

void Creature::spin(float deg)
{
    // Update the model matrix by multiplying a rotation matrix
    model = glm::rotate(model, glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

