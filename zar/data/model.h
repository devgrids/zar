#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include <string>
#include <fstream>

#include <iostream>

#include <vector>

#include "anim_data.h"
#include "assimp_glm_helpers.h"
#include "Mesh.h"


using namespace std;

namespace zar
{
    class ZAR_API Model
    {
    public:
        virtual ~Model() = default;
        ZAR_INLINE explicit Model(bool gamma = false);
        ZAR_INLINE void draw(zar::GLShader& shader);
        ZAR_INLINE std::unordered_map<std::string, BoneInfo>& get_bone_info_map();
        ZAR_INLINE int& get_bone_count();

    protected:
        
        ZAR_INLINE void set_vertex_bone_data_to_default(Vertex& vertex);
        ZAR_INLINE virtual Mesh process_mesh(aiMesh* mesh);
        ZAR_INLINE vector<Vertex> get_vertices(const aiMesh* mesh);
        ZAR_INLINE vector<unsigned int> get_indices(const aiMesh* mesh);
        ZAR_INLINE virtual vector<Material> process_materials(aiMesh* mesh);
        ZAR_INLINE void set_vertex_bone_data(Vertex& vertex, int bone_id, float weight);
        ZAR_INLINE void extract_bone_weight_for_vertices(std::vector<Vertex>& vertices, const aiMesh* mesh);

    public:
        // vector<zar::Material> materials;
        vector<Mesh> meshes;
        string directory;
        bool gamma_correction;
        const aiScene* scene{};
        // vector<zar::Material> &materials;

    private:
        std::unordered_map<std::string, BoneInfo> m_bone_info_map_;
        int m_bone_counter_ = 0;
    };
}
