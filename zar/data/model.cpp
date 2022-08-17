#include "Model.h"

zar::Model::Model(const bool gamma)
    : gamma_correction(gamma)
{
}

void zar::Model::draw(zar::GLShader& shader)
{
    for (auto& mesh : meshes)
        mesh.Draw(shader);
}

std::unordered_map<std::string, zar::BoneInfo>& zar::Model::get_bone_info_map()
{
    return m_bone_info_map_;
}

int& zar::Model::get_bone_count()
{
    return m_bone_counter_;
}

auto zar::Model::set_vertex_bone_data_to_default(Vertex& vertex) -> void
{
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        vertex.bones[i] = -1;
        vertex.weights[i] = 0.0f;
    }
}

zar::Mesh zar::Model::process_mesh(aiMesh* mesh, const aiScene* scene)
{
    auto vertices = get_vertices(mesh, scene);
    auto indices = get_indices(mesh, scene);
    auto textures = process_materials(mesh, scene);
    extract_bone_weight_for_vertices(vertices, mesh, scene);
    return {vertices, indices, textures};
}

vector<zar::Vertex> zar::Model::get_vertices(const aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
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

vector<unsigned> zar::Model::get_indices(const aiMesh* mesh, const aiScene* scene)
{
    vector<unsigned int> indices;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    return indices;
}

vector<zar::Texture> zar::Model::process_materials(aiMesh* mesh, const aiScene* scene)
{
    return {};
}


void zar::Model::set_vertex_bone_data(zar::Vertex& vertex, const int bone_id, const float weight)
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

void zar::Model::extract_bone_weight_for_vertices(std::vector<Vertex>& vertices, const aiMesh* mesh, const aiScene* scene)
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
