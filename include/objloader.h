#ifndef OBJLOADER_H
#define OBJLOADER_H

// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#include <model.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <glm/glm.hpp>

using namespace std;

static inline NakedModel load_model(const string &path)
{
    vector<unsigned int> vertex_indices, uv_indices, normal_indices;
    vector<glm::vec3> temp_vertices, temp_normals;
    vector<glm::vec2> temp_uvs;

    FILE *obj_file = fopen(path.c_str(), "r");
    if(obj_file == NULL)
    {
        printf("Failed to open file %s\n", path.c_str());
        exit(1);
    }

    for(;;)
    {
        char line_header[128];
        int res = fscanf(obj_file, "%s", line_header);
        if(res == EOF) break;

        if(strcmp(line_header, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(obj_file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if(strcmp(line_header, "vt") == 0)
        {
            glm::vec2 uv;
            fscanf(obj_file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }
        else if(strcmp(line_header, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(obj_file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if(strcmp(line_header, "f") == 0)
        {
            string v1, v2, v3;
            unsigned int vertex_index[3], uv_index[3], normal_index[3];
            int matches = fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
            if(matches != 9)
            {
                printf("Failed to load obj file %s\nExported wrong\n", path.c_str());
                exit(1);
            }
            vertex_indices.push_back(vertex_index[0]);
            vertex_indices.push_back(vertex_index[1]);
            vertex_indices.push_back(vertex_index[2]);
            uv_indices.push_back(uv_index[0]);
            uv_indices.push_back(uv_index[1]);
            uv_indices.push_back(uv_index[2]);
            normal_indices.push_back(normal_index[0]);
            normal_indices.push_back(normal_index[1]);
            normal_indices.push_back(normal_index[2]);

        }
    }

    vector<glm::vec2> out_uvs;
    vector<glm::vec3> out_vertices, out_normals;

    for(unsigned int i = 0; i < vertex_indices.size(); i++)
    {
        unsigned int vertex_index = vertex_indices[i];
        glm::vec3 vertex = temp_vertices[vertex_index - 1];
        out_vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < normal_indices.size(); i++)
    {
        unsigned int normal_index = normal_indices[i];
        glm::vec3 normal = temp_normals[normal_index - 1];
        out_vertices.push_back(normal);
    }
    for(unsigned int i = 0; i < uv_indices.size(); i++)
    {
        unsigned int uv_index = uv_indices[i];
        glm::vec2 uv = temp_uvs[uv_index - 1];
        out_uvs.push_back(uv);
    }

    return load_attribs_to_vao(out_vertices, out_uvs, out_normals);
}

#endif