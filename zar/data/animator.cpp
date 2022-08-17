#include "animator.h"

zar::Animator::Animator(Animation* animation)
{
    m_current_time_ = 0.0;
    m_current_animation_ = animation;

    m_final_bone_matrices_.reserve(100);

    for (int i = 0; i < 100; i++)
        m_final_bone_matrices_.push_back(glm::mat4(1.0f));
}

void zar::Animator::update_animation(const float dt)
{
    m_delta_time_ = dt;
    if (m_current_animation_)
    {
        m_current_time_ += m_current_animation_->get_ticks_per_second() * dt;
        m_current_time_ = fmod(m_current_time_, m_current_animation_->get_duration());
        calculate_bone_transform(&m_current_animation_->get_root_node(), glm::mat4(1.0f));
    }
}

void zar::Animator::play_animation(Animation* p_animation)
{
    m_current_animation_ = p_animation;
    m_current_time_ = 0.0f;
}

void zar::Animator::calculate_bone_transform(const AssimpNodeData* node, glm::mat4 parentTransform)
{
    const std::string node_name = node->name;
    glm::mat4 node_transform = node->transformation;
    zar::Bone* bone = m_current_animation_->find_bone(node_name);

    if (bone)
    {
        bone->update(m_current_time_);
        node_transform = bone->get_local_transform();
    }

    const glm::mat4 global_transformation = parentTransform * node_transform;

    auto bone_info_map = m_current_animation_->get_bone_id_map();
    if (bone_info_map.find(node_name) != bone_info_map.end())
    {
        const int index = bone_info_map[node_name].id;
        const glm::mat4 offset = bone_info_map[node_name].offset;
        m_final_bone_matrices_[index] = global_transformation * offset;
    }

    for (int i = 0; i < node->children_count; i++)
        calculate_bone_transform(&node->children[i], global_transformation);
}

std::vector<glm::mat4> zar::Animator::get_final_bone_matrices() const
{
    return m_final_bone_matrices_;
}
