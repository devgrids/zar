#pragma once

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include "anim_data.h"
#include "bone.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

namespace zar
{
    struct AssimpNodeData
    {
        glm::mat4 transformation;
        std::string name;
        int children_count;
        std::vector<AssimpNodeData> children;
    };

    class ZAR_API Animation
    {
    public:
        Animation() = default;
        Animation(const std::string& animation_path, std::unordered_map<std::string, zar::BoneInfo>& bone_info_map,
                  int& bone_count);
        ~Animation();

        zar::Bone* find_bone(const std::string& name);
        ZAR_INLINE float get_ticks_per_second() const;
        ZAR_INLINE float get_duration() const;
        ZAR_INLINE const AssimpNodeData& get_root_node();
        ZAR_INLINE const std::unordered_map<std::string, zar::BoneInfo>& get_bone_id_map();
    private:
        void read_missing_bones(const aiAnimation* animation,
                              std::unordered_map<std::string, zar::BoneInfo>& bone_info_map,
                              int& bone_count);
        void read_heirarchy_data(AssimpNodeData& dest, const aiNode* src);

        float m_duration_;
        int m_ticks_per_second_;
        std::vector<zar::Bone> m_bones_;
        AssimpNodeData m_root_node_;
        std::unordered_map<std::string, zar::BoneInfo> m_bone_info_map_;
    };
}
