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
#version 330
layout(location=0) in vec3 pos_model;
layout(location=1) in vec3 normal_model;
layout(location=2) in vec2 uv;
layout(location=3) in vec3 tangent_model;
layout(location=4) in vec3 bitangent_model;
out vec3 pos_world;
out vec3 normal_world;
out vec2 uv_out;
uniform mat4 VP;
uniform vec3[50] pos_instances;
void main(){
  mat4 model=mat4(1.0);
  model[3][0]=pos_instances[gl_InstanceID].x;
  model[3][1]=pos_instances[gl_InstanceID].y;
  model[3][2]=pos_instances[gl_InstanceID].z;
  pos_world=(model*vec4(pos_model,1)).xyz;
  normal_world=(model*vec4(normal_model,0)).xyz;
  uv_out=uv;
  gl_Position=VP*vec4(pos_world,1);
}