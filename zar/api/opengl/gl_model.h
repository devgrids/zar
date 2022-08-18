#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "gl_mesh.h"
#include "gl_shader.h"
#include "../../data/anim_data.h"
#include "../../data/material.h"
#include "../../data/vertex.h"

namespace zar
{
    class ZAR_API GLModel
    {
    public:
        virtual ~GLModel() = default;
        ZAR_INLINE explicit GLModel(bool gamma = false);
        ZAR_INLINE void draw(const zar::GLShader& shader) const;
        ZAR_INLINE std::unordered_map<std::string, zar::BoneInfo>& get_bone_info_map();
        ZAR_INLINE int& get_bone_count();

    protected:
        ZAR_INLINE void set_vertex_bone_data_to_default(Vertex& vertex);
        ZAR_INLINE virtual GLMesh process_mesh(aiMesh* mesh);
        ZAR_INLINE std::vector<Vertex> get_vertices(const aiMesh* mesh);
        ZAR_INLINE std::vector<unsigned int> get_indices(const aiMesh* mesh);
        ZAR_INLINE virtual std::vector<Material> process_materials(aiMesh* mesh);
        ZAR_INLINE void set_vertex_bone_data(Vertex& vertex, int bone_id, float weight);
        ZAR_INLINE void extract_bone_weight_for_vertices(std::vector<Vertex>& vertices, const aiMesh* mesh);

    public:
        std::vector<GLMesh> meshes;
        std::string directory;
        bool gamma_correction;
        const aiScene* scene{};

    private:
        std::unordered_map<std::string, BoneInfo> m_bone_info_map_;
        int m_bone_counter_ = 0;
    };
}
