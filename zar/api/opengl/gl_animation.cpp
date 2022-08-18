#include "gl_animation.h"

#include "data/anim_data.h"
#include "data/bone.h"

zar::GLAnimation::GLAnimation(const std::string& animation_path,
                              std::unordered_map<std::string, zar::BoneInfo>& bone_info_map, int& bone_count)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(animation_path, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    const auto animation = scene->mAnimations[0];
    m_duration_ = animation->mDuration;
    m_ticks_per_second_ = animation->mTicksPerSecond;
    aiMatrix4x4 global_transformation = scene->mRootNode->mTransformation;
    global_transformation = global_transformation.Inverse();
    read_heirarchy_data(m_root_node_, scene->mRootNode);
    read_missing_bones(animation, bone_info_map, bone_count);
}

zar::GLAnimation::~GLAnimation()
= default;

zar::Bone* zar::GLAnimation::find_bone(const std::string& name)
{
    const auto iter = std::find_if(m_bones_.begin(), m_bones_.end(),
                                   [&](const zar::Bone& Bone)
                                   {
                                       return Bone.get_bone_name() == name;
                                   }
    );
    if (iter == m_bones_.end()) return nullptr;
    else return &(*iter);
}

float zar::GLAnimation::get_ticks_per_second() const
{
    return m_ticks_per_second_;
}

float zar::GLAnimation::get_duration() const
{
    return m_duration_;
}

const zar::AssimpNodeData& zar::GLAnimation::get_root_node()
{
    return m_root_node_;
}

const std::unordered_map<std::string, zar::BoneInfo>& zar::GLAnimation::get_bone_id_map()
{
    return m_bone_info_map_;
}

void zar::GLAnimation::read_missing_bones(const aiAnimation* animation,
                                      std::unordered_map<std::string, zar::BoneInfo>& bone_info_map, int& bone_count)
{
    const int size = animation->mNumChannels;

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        const auto channel = animation->mChannels[i];
        std::string bone_name = channel->mNodeName.data;

        if (bone_info_map.find(bone_name) == bone_info_map.end())
        {
            bone_info_map[bone_name].id = bone_count;
            bone_count++;
        }
        m_bones_.push_back(zar::Bone(channel->mNodeName.data,
                                    bone_info_map[channel->mNodeName.data].id, channel));
    }

    m_bone_info_map_ = bone_info_map;
}

void zar::GLAnimation::read_heirarchy_data(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = zar::AssimpGLMHelpers::convert_matrix_to_glm_format(src->mTransformation);
    dest.children_count = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData new_data;
        read_heirarchy_data(new_data, src->mChildren[i]);
        dest.children.push_back(new_data);
    }
}
