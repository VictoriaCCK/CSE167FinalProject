//
//  Leaves.cpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/13.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#include "Leaves.hpp"

Leaves::Leaves(std::vector<Trunk> t)
{
    for (int i = 0; i<t.size(); i++) {
        vertices.push_back(t[i].pos1);
        vertices.push_back(t[i].pos2);
    }
    
    for (int i = 0; i<vertices.size(); i++) {
        indices.push_back(i);
    }
    // Generate a vertex array (VAO) and two vertex buffer objects (VBO).
    glGenVertexArrays(1, &vao);
    glGenBuffers(2, vbos);
    
    // Bind to the VAO.
    glBindVertexArray(vao);
    
    // Bind to the first VBO. We will use it to store the vertices.
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    // Pass in the data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);
    // Enable vertex attribute 0.
    // We will be able to access vertices through it.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind to the second VBO. We will use it to store the indices.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]);
    // Pass in the data.
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
    
    // Unbind from the VBOs.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind from the VAO.
    glBindVertexArray(0);
}

Leaves::~Leaves()
{
    // Delete the VBOs and the VAO.
    glDeleteBuffers(2, vbos);
    glDeleteVertexArrays(1, &vao);
}

void Leaves::draw()
{
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // elemnt array buffer.
    glLineWidth(10);
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    
    // Unbind from the VAO.
    glBindVertexArray(0);
}
