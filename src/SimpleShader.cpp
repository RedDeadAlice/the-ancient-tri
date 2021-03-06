/*
the-ancient-tri A low level OpenGL render engine
Copyright (C) 2021 Mohammad Issawi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <SimpleShader.h>
using namespace tat;
using namespace glm;
using namespace std;
using namespace gl;
const char *__simple_vertex_shader = R"(
#version 330
layout(location=0) in vec3 position_model;
layout(location=1) in vec3 color;
layout(location=2) in vec2 uv;
out vec3 color_out;
uniform mat4 VP=mat4(1);
uniform mat4 model=mat4(1);
void main(){
  gl_Position=VP*model*vec4(position_model,1);
  color_out=color;
}
)";
const char *__simple_fragment_shader = R"(
#version 330
in vec3 color_out;
out vec4 color;
void main(){
  color=vec4(color_out,1);
}
)";
GLuint SimpleShader::createVAO(const vector<Vertex> &vertices, const vector<unsigned> &indices)
{
  GLuint VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * indices.size(), indices.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(vec3));
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(sizeof(vec3) * 2));
  return VAO;
}
SimpleShader::SimpleShader() : Shader(__simple_vertex_shader, __simple_fragment_shader, false)
{
  glUseProgram(id);
  modelLocation = glGetUniformLocation(id, "model");
  VPLocation = glGetUniformLocation(id, "VP");
}
SimpleShader &SimpleShader::instance()
{
  static SimpleShader simpleShader;
  return simpleShader;
}
void SimpleShader::setModel(mat4 model)
{
  glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
}
void SimpleShader::setVP(mat4 VP)
{
  glUniformMatrix4fv(VPLocation, 1, GL_FALSE, &VP[0][0]);
}
