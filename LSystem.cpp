//
//  LSystem.cpp
//  167project
//
//  Created by Chiu Chi Kwan on 2020/3/11.
//  Copyright © 2020 ChiuChiuKwan. All rights reserved.
//

#include "LSystem.hpp"

FractalSystem::FractalSystem()
{

    model = glm::mat4(1.f);
    g = new Grammar("X", 8);
    generateTree();
    
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

FractalSystem::~FractalSystem()
{
    // Delete the VBOs and the VAO.
    glDeleteBuffers(2, vbos);
    glDeleteVertexArrays(1, &vao);
}

void FractalSystem::draw()
{
    // Bind to the VAO.
    glBindVertexArray(vao);
    // Draw triangles using the indices in the second VBO, which is an
    // elemnt array buffer.
    glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
    
    // Unbind from the VAO.
    glBindVertexArray(0);
}


void FractalSystem::generateTree()
{
    trunks.clear();
    leaves.clear();
    cur_state.pos = glm::vec3(0, 6, 0);
    cur_state.dir = glm::vec3(0, 0.2, 0);
    cur_state.level = 0;
    cur_state.radius = radius;
    vector<State> stacks;
    stacks.push_back(cur_state);
    
    for (int i = 0; i<g->gram.size(); i++) {
        char ch = g->gram[i];
        Trunk tmp;
        switch (ch) {
            case 'F':
            {
                tmp.pos1 = cur_state.pos;
                cur_state.pos.x += length*cur_state.dir.x;
                cur_state.pos.y += length*cur_state.dir.y;
                cur_state.pos.z += length*cur_state.dir.z;
                tmp.pos2 = cur_state.pos;
                tmp.radius = cur_state.radius;
                tmp.level = cur_state.level;
                trunks.push_back(tmp);
                
                vertices.push_back(tmp.pos1);

                State center;
                std::vector<State> leaf_seg;
                center.dir = tmp.pos2 - tmp.pos1;
                center.pos = tmp.pos1;
                leaf_seg.push_back(center);
                
                double deltax = 0, deltay = 0;
                State leaf_tmp;
                for (int i = 0; i < 5; i ++ ) {
                    deltax = leaf_radius * cos(i);
                    deltay = leaf_radius * sin(i);
                    leaf_tmp.pos.x = center.pos.x + deltax;
                    leaf_tmp.pos.y = center.pos.y + deltay;
                    leaf_tmp.pos.z = center.pos.z;
                    leaf_seg.push_back(leaf_tmp);
                    vertices.push_back(leaf_tmp.pos);
                    leaf_seg.push_back(center);
                    vertices.push_back(center.pos);
                }
                leaves.push_back(leaf_seg);
                
                std::vector<State>().swap(leaf_seg);
                vertices.push_back(tmp.pos2);
                center.dir = tmp.pos2 - tmp.pos1;
                center.pos = tmp.pos2;
                leaf_seg.push_back(center);
                
                deltax = 0, deltay = 0;
                for (int i = 0; i < 5; i ++ ) {
                    deltax = leaf_radius * cos(i);
                    deltay = leaf_radius * sin(i);
                    leaf_tmp.pos.x = center.pos.x + deltax;
                    leaf_tmp.pos.y = center.pos.y + deltay;
                    leaf_tmp.pos.z = center.pos.z;
                    leaf_seg.push_back(leaf_tmp);
                    vertices.push_back(leaf_tmp.pos);
                    leaf_seg.push_back(center);
                    vertices.push_back(center.pos);
                }
                leaves.push_back(leaf_seg);
                
                break;
            }
            case '+':
            {
                    cur_state.dir.x = cos(direction * M_PI / 180) * cur_state.dir.x + sin(direction * M_PI / 180) * cur_state.dir.z;
                    cur_state.dir.z = -sin(direction * M_PI / 180) * cur_state.dir.x + cos(direction * M_PI / 180) * cur_state.dir.z;
                cur_state.dir.x = cos(direction * M_PI / 180);
                cur_state.dir.y = sin(direction * M_PI / 180);
                break;
            }
            case '-':
            {
//                if(cur_state.dir.x == 0) cur_state.dir.x = cos( - direction * M_PI / 180);
//                else
//                    cur_state.dir.x = cos( - direction * M_PI / 180) * cur_state.dir.x + sin( - direction * M_PI / 180) * cur_state.dir.z;
////                if(cur_state.dir.z == 0) cur_state.dir.z = sin( - direction * M_PI / 180);
////                else
//                    cur_state.dir.z = -sin( - direction * M_PI / 180) * cur_state.dir.x + cos( - direction * M_PI / 180) * cur_state.dir.z;
//                cur_state.dir.z = -sin( - direction * M_PI / 180) * cur_state.dir.x + cos( - direction * M_PI / 180) * cur_state.dir.z;
//                cur_state.dir.x = cos( - direction * M_PI / 180);
//                cur_state.dir.y = sin( - direction * M_PI / 180);
                direction -= angle;
                break;
            }
            case '$': //y axis
            {
                cur_state.dir.x = cos(direction * M_PI / 180);
                cur_state.dir.z = sin(direction * M_PI / 180);
                direction += angle;
                break;
            }
            case '%': // -y axis
            {
                cur_state.dir.x = cos(-direction * M_PI / 180);
                cur_state.dir.z = sin(-direction * M_PI / 180);
                direction -= angle;
                break;
            }
            case '^': //x axis
            {
                cur_state.dir.y = cos(direction * M_PI / 180);
                cur_state.dir.z = sin(direction * M_PI / 180);
                direction += angle;
                break;
            }
            case '&': // -x axis
            {
                cur_state.dir.y = cos(-direction * M_PI / 180);
                cur_state.dir.z = sin(-direction * M_PI / 180);
                direction -= angle;
                break;
            }
            case '*': //z axis
            {
                cur_state.dir.x = cos(direction * M_PI / 180);
                cur_state.dir.y = sin(direction * M_PI / 180);
                direction += angle;
                break;
            }
            case '/': // -z axis
            {
                  cur_state.dir.x = cos(-direction * M_PI / 180);
                  cur_state.dir.y = sin(-direction * M_PI / 180);
                  direction -= angle;
                break;
            }
            case '[':
            {
                stacks.push_back(cur_state);
                length *= length_factor;
                radius *= radius_factor;
                l += 1;
                break;
            }
            case ']':
            {
                cur_state = stacks.at(stacks.size() - 1);
                stacks.pop_back();
                break;
            }
            default: // leaves
            {
                    tmp.pos1 = cur_state.pos;
                    cur_state.pos.x += length*cur_state.dir.x;
                    cur_state.pos.y += length*cur_state.dir.y;
                    cur_state.pos.z += length*cur_state.dir.z;
                    tmp.pos2 = cur_state.pos;
                    tmp.radius = cur_state.radius;
                    tmp.level = cur_state.level;
                    trunks.push_back(tmp);
                
                    vertices.push_back(tmp.pos1);
                
                    State center;
                    std::vector<State> leaf_seg;
                    center.dir = tmp.pos2 - tmp.pos1;
                    center.pos = tmp.pos2;
                    leaf_seg.push_back(center);
                
                    vertices.push_back(center.pos);
                
                    double deltax = 0, deltay = 0;
                    State leaf_tmp;
                    for (int i = 0; i < 25; i ++ ) {
                        deltax = leaf_radius * cos(i);
                        deltay = leaf_radius * sin(i);
                        leaf_tmp.pos.x = center.pos.x + deltax;
                        leaf_tmp.pos.y = center.pos.y + deltay;
                        leaf_tmp.pos.z = center.pos.z;
                        leaf_seg.push_back(leaf_tmp);
                        vertices.push_back(leaf_tmp.pos);
                        leaf_seg.push_back(center);
                        vertices.push_back(center.pos);
                    }
                    leaves.push_back(leaf_seg);
                
                    vertices.push_back(tmp.pos2);
                
                    std::vector<State>().swap(leaf_seg);
                    center.dir = tmp.pos2 - tmp.pos1;
                    center.pos = tmp.pos2;
                    leaf_seg.push_back(center);
                
                    vertices.push_back(center.pos);
                
                    deltax = 0, deltay = 0;
                    leaf_tmp;
                    for (int i = 0; i < 25; i ++ ) {
                        deltax = leaf_radius * cos(i);
                        deltay = leaf_radius * sin(i);
                        leaf_tmp.pos.x = center.pos.x + deltax;
                        leaf_tmp.pos.y = center.pos.y + deltay;
                        leaf_tmp.pos.z = center.pos.z;
                        leaf_seg.push_back(leaf_tmp);
                        vertices.push_back(leaf_tmp.pos);
                        leaf_seg.push_back(center);
                        vertices.push_back(center.pos);
                    }
                    leaves.push_back(leaf_seg);
                break;
            }
        }
    }
    
}


void FractalSystem::spin(float deg)
{
    // Update the model matrix by multiplying a rotation matrix
//    model = glm::rotate(glm::mat4(1), glm::radians(deg),
//                        glm::vec3(0.0f, 1.0f, 0.0f)) * model;
    model = glm::translate(model, glm::vec3(1.f, 1.f, 0.f));
}
