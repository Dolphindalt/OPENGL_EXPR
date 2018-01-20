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
#include <map>
#include <string.h>

using namespace std;

struct PackedVertex {
    glm::vec3 position;
    glm::vec2 uv;
    glm::vec3 normal;
    bool operator<(const PackedVertex that) const{
        return memcmp((void *)this, (void *)&that, sizeof(PackedVertex))>0;
    };
};

static inline bool get_similar_vertex_index(PackedVertex &packed, map<PackedVertex, unsigned short> &vertex_to_out_index, unsigned short &result)
{
    auto it = vertex_to_out_index.find(packed);
    if(it == vertex_to_out_index.end())
        return false;
    else
    {
        result = it->second;
        return true;
    }
}

static inline void index_vbo(vector<glm::vec3> &in_vertices, vector<glm::vec2> &in_uvs, vector<glm::vec3> &in_normals,
vector<unsigned short> &out_indices, vector<glm::vec3> &out_vertices, vector<glm::vec2> &out_uvs, vector<glm::vec3> &out_normals)
{
    map<PackedVertex, unsigned short> vertex_to_out_index;
    for(unsigned int i = 0; i < in_vertices.size(); i++)
    {
        PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};
        unsigned short index;
        bool found = get_similar_vertex_index(packed, vertex_to_out_index, index);
        if(found)
            out_indices.push_back(index);
        else
        {
            out_vertices.push_back(in_vertices[i]);
            out_uvs.push_back(in_uvs[i]);
            out_normals.push_back(in_normals[i]);
            unsigned short new_index = (unsigned short)out_vertices.size() - 1;
            out_indices.push_back(new_index);
            vertex_to_out_index[packed] = new_index;
        }
    }
}

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
            int matches = fscanf(obj_file, "%d/%d/%d %d/%d/%d %d/%d/%d", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2]);
            if(matches != 9)
            {
                printf("Failed to load obj file %s\nExported wrong %d\n", path.c_str(), matches);
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
        unsigned int vertex_index = vertex_indices[i],
        uv_index = uv_indices[i], normal_index = normal_indices[i];
        glm::vec3 vertex = temp_vertices[vertex_index-1];
        glm::vec2 uv = temp_uvs[uv_index-1];
        glm::vec3 normal = temp_normals[normal_index-1];
        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(normal);
    }

    vector<unsigned short> indices;
    vector<glm::vec3> indexed_vertices, indexed_normals;
    vector<glm::vec2> indexed_uvs;
    index_vbo(out_vertices, out_uvs, out_normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

    fclose(obj_file);

    return load_attribs_to_vao(indexed_vertices, indexed_uvs, indexed_normals, indices);
}

#endif