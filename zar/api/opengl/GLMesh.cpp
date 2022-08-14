#include "GLMesh.h"

zar::GLMesh::GLMesh(Vertices& vertices, Indices& indices, const bool enable_bones)
{
    vertex_count_ = vertices.size();
    element_count_ = indices.size();

    glGenVertexArrays(1, &buffer_object_);
    glBindVertexArray(buffer_object_);

    uint32_t vertexBufferID = 0;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertex_count_ * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    uint32_t elementBufferID = 0;
    glGenBuffers(1, &elementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_count_ * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

    // normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    // texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, text_coords));

    // tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    // bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    // bones & weight
    if (enable_bones) {				
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, bones));
				
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weights));
    }

    glBindVertexArray(0);
}

void zar::GLMesh::set_name(const char* name)
{
    name_ = name;
}

const std::string& zar::GLMesh::name()
{
    return name_;
}

void zar::GLMesh::set_material_index(uint32_t index)
{
    material_index_ = index;
}

int zar::GLMesh::material_index()
{
    return material_index_;
}

void zar::GLMesh::destroy_buffer()
{
    glDeleteVertexArrays(1, &buffer_object_);
}

void zar::GLMesh::draw_elements(GLenum mode)
{
    glBindVertexArray(buffer_object_);
    glDrawElements(mode, element_count_, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void zar::GLMesh::draw_arrays(GLenum mode)
{
    glBindVertexArray(buffer_object_);
    glDrawArrays(mode, 0, vertex_count_);
    glBindVertexArray(0);
}
