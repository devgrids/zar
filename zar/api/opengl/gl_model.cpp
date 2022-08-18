#include "gl_model.h"

#include "data/assimp_glm_helpers.h"

zar::GLModel::GLModel(const bool gamma)
    : gamma_correction(gamma)
{

}

void zar::GLModel::draw(const zar::GLShader& shader) const
{
    for (auto& mesh : meshes)
        mesh.draw(shader);
}

std::unordered_map<std::string, zar::BoneInfo>& zar::GLModel::get_bone_info_map()
{
    return m_bone_info_map_;
}

int& zar::GLModel::get_bone_count()
{
    return m_bone_counter_;
}

void zar::GLModel::set_vertex_bone_data_to_default(Vertex& vertex)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.bones[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

zar::GLMesh zar::GLModel::process_mesh(aiMesh* mesh)
{
    auto vertices = get_vertices(mesh);
    auto indices = get_indices(mesh);
    auto textures = process_materials(mesh);
    extract_bone_weight_for_vertices(vertices, mesh);
    return {vertices, indices, textures};
}

std::vector<zar::Vertex> zar::GLModel::get_vertices(const aiMesh* mesh)
{
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        set_vertex_bone_data_to_default(vertex);
        vertex.position = AssimpGLMHelpers::get_glm_vec(mesh->mVertices[i]);
        vertex.normal = AssimpGLMHelpers::get_glm_vec(mesh->mNormals[i]);

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.text_coords = vec;
        }
        else
            vertex.text_coords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    return vertices;
}

std::vector<unsigned> zar::GLModel::get_indices(const aiMesh* mesh)
{
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return indices;
}

std::vector<zar::Material> zar::GLModel::process_materials(aiMesh* mesh)
{
    return {};
}


void zar::GLModel::set_vertex_bone_data(zar::Vertex& vertex, const int bone_id, const float weight)
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
    {
        if (vertex.bones[i] < 0)
        {
            vertex.weights[i] = weight;
            vertex.bones[i] = bone_id;
            break;
        }
    }
}

void zar::GLModel::extract_bone_weight_for_vertices(std::vector<Vertex>& vertices, const aiMesh* mesh)
{
    auto& bone_info_map = m_bone_info_map_;
    int& bone_count = m_bone_counter_;

    for (int bone_index = 0; bone_index < mesh->mNumBones; ++bone_index)
    {
        int bone_id;
        std::string boneName = mesh->mBones[bone_index]->mName.C_Str();
        if (bone_info_map.find(boneName) == bone_info_map.end())
        {
            BoneInfo new_bone_info;
            new_bone_info.id = bone_count;
            new_bone_info.offset = zar::AssimpGLMHelpers::convert_matrix_to_glm_format(
                mesh->mBones[bone_index]->mOffsetMatrix);
            bone_info_map[boneName] = new_bone_info;
            bone_id = bone_count;
            bone_count++;
        }
        else
        {
            bone_id = bone_info_map[boneName].id;
        }
        assert(bone_id != -1);
        const auto weights = mesh->mBones[bone_index]->mWeights;
        const int num_weights = mesh->mBones[bone_index]->mNumWeights;

        for (int weight_index = 0; weight_index < num_weights; ++weight_index)
        {
            const int vertex_id = weights[weight_index].mVertexId;
            const float weight = weights[weight_index].mWeight;
            assert(vertex_id <= vertices.size());
            set_vertex_bone_data(vertices[vertex_id], bone_id, weight);
        }
    }
}
