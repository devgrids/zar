#include "gl_mesh.h"

zar::GLMesh::GLMesh(const std::vector<Vertex> vertices, const std::vector<unsigned> indices, const std::vector<Material>
                materials)
{
    this->vertices = vertices;
    this->indices = indices;
    this->materials = materials;

    setup_mesh();
}

void zar::GLMesh::draw(const zar::GLShader& shader) const
{
    unsigned int diffuse_nr = 1;
    for (unsigned int i = 0; i < materials.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = "texture_diffuse";
        number = std::to_string(diffuse_nr++);
        glUniform1i(glGetUniformLocation(shader.get_id(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, materials[i].diffuse_map.id);
    }
    draw_elements();
    glActiveTexture(GL_TEXTURE0);
}

void zar::GLMesh::destroy_buffer() const
{
    glDeleteVertexArrays(1, &vao);
}

void zar::GLMesh::draw_elements(const GLenum mode) const
{
    glBindVertexArray(vao);
    glDrawElements(mode, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void zar::GLMesh::draw_arrays(const GLenum mode) const
{
    glBindVertexArray(vao);
    glDrawArrays(mode, 0, static_cast<unsigned int>(vertices.size()));
    glBindVertexArray(0);
}

void zar::GLMesh::setup_mesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void*>(0));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, text_coords)));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, tangent)));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void*>(offsetof(Vertex, bitangent)));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, bones)));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, weights)));
    glBindVertexArray(0);
}
