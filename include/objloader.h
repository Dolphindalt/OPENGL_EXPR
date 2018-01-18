#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <model.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <glm/glm.hpp>

using namespace std;

static inline NakedModel loadOBJFile(const string &path)
{
    ifstream obj_file(path.c_str());
    if(!obj_file.fail())
    {
        printf("Failed to load OBJ file: %s\n", path.c_str());
        exit(1);
    }
    vector<glm::vec3> vertices, normals;
    vector<glm::vec2> uv;
    vector<GLuint> _indices;
    vector<GLfloat> _vertices, _uv, _normals;

    string line;
    int last = 0;
    while(getline(obj_file, line))
    {
        vector<string> tokens = split(line, " ");
        if(tokens.empty()) continue;
        if(tokens[0] == "v")
            vertices.push_back(glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
        else if(tokens[0] == "vt")
            uv.push_back(glm::vec2(stof(tokens[1]), stof(tokens[2])));
        else if(tokens[0] == "vn")
            normals.push_back(glm::vec3(stof(tokens[1]), stof(tokens[2]), stof(tokens[3])));
        else if(tokens[0] == "f")
        {
            obj_file.seekg(last);
            _vertices = vector<GLfloat>(3 * vertices.size());
            _uv = vector<GLfloat>(2 * vertices.size());
            _normals = vector<GLfloat>(3 * vertices.size());
            break;
        }
        last = obj_file.tellg();
    }

    while(getline(obj_file, line))
    {
        vector<string> face = split(line, " ");
        if(face.empty() || face[0] != "f") continue;
        vector<string> v1 = split(face[1], "/");
        vector<string> v2 = split(face[2], "/");
        vector<string> v3 = split(face[3], "/");
        process_vertex(v1, vertices, uv, normals, _indices, _vertices, _uv, _normals);
        process_vertex(v2, vertices, uv, normals, _indices, _vertices, _uv, _normals);
        process_vertex(v3, vertices, uv, normals, _indices, _vertices, _uv, _normals);
    }

    return load_attribs_to_vao(_vertices, _uv, _normals, _indices);
}

static inline void process_vertex(const vector<string> &vertex_data, const vector<glm::vec3> &vertices, const vector<glm::vec2> &uv,
const vector<glm::vec3> &normals, vector<GLuint> &_indices, vector<GLfloat> &_vertices, vector<GLfloat> &_uv, vector<GLfloat> &_normals)
{
    GLuint idx = stoi(vertex_data[0]) - 1;
    _indices.push_back(idx);

    glm::vec3 vertex = vertices[stoi(vertex_data[0]) - 1];
    _vertices[idx * 3] = vertex.x;
    _vertices[idx * 3 + 1] = vertex.y;
    _vertices[idx * 3 + 2] = vertex.z;

    glm::vec2 tc = uv[stoi(vertex_data[1]) - 1];
    _uv[idx * 2] = tc.x;
    _uv[idx * 2 + 1] = 1 - tc.y;

    glm::vec3 normal = normals[stoi(vertex_data[2]) - 1];
    _normals[idx * 3] = normal.x;
    _normals[idx * 3 + 1] = normal.y;
    _normals[idx * 3 + 2] = normal.z;
}

static inline vector<string> split(const string &str, const string &delimiter)
{
    vector<string> parsed;
    char *cstr = const_cast<char *>(str.c_str()), *token;
    token = strtok(cstr, delimiter.c_str());
    while(token)
    {
        parsed.push_back(token);
        token = strtok(NULL, delimiter.c_str());
    }
    return parsed;
}

#endif