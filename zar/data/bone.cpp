#include "bone.h"

zar::Bone::Bone(std::string name, int id, const aiNodeAnim* channel)
    :
    m_local_transform_(1.0f),
    m_name_(std::move(name)),
    m_id_(id)
{
    m_num_positions_ = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < m_num_positions_; ++positionIndex)
    {
        aiVector3D ai_position = channel->mPositionKeys[positionIndex].mValue;
        float time_stamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::get_glm_vec(ai_position);
        data.timeStamp = time_stamp;
        m_positions_.push_back(data);
    }

    m_num_rotations_ = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < m_num_rotations_; ++rotationIndex)
    {
        aiQuaternion ai_orientation = channel->mRotationKeys[rotationIndex].mValue;
        float time_stamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::get_glm_quat(ai_orientation);
        data.timeStamp = time_stamp;
        m_rotations_.push_back(data);
    }

    m_num_scalings_ = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < m_num_scalings_; ++keyIndex)
    {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float time_stamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::get_glm_vec(scale);
        data.timeStamp = time_stamp;
        m_scales_.push_back(data);
    }
}

void zar::Bone::update(const float animation_time)
{
    const glm::mat4 translation = interpolate_position(animation_time);
    const glm::mat4 rotation = interpolate_rotation(animation_time);
    const glm::mat4 scale = interpolate_scaling(animation_time);
    m_local_transform_ = translation * rotation * scale;
}

glm::mat4 zar::Bone::get_local_transform() const
{
    return m_local_transform_;
}

int zar::Bone::get_bone_id() const
{
    return m_id_;
}

int zar::Bone::get_position_index(const float animation_time) const
{
    for (int index = 0; index < m_num_positions_ - 1; ++index)
    {
        if (animation_time < m_positions_[index + 1].timeStamp)
            return index;
    }
    assert(0);
    return 0;
}

int zar::Bone::get_rotation_index(const float animation_time) const
{
    for (int index = 0; index < m_num_rotations_ - 1; ++index)
    {
        if (animation_time < m_rotations_[index + 1].timeStamp)
            return index;
    }
    assert(0);
    return 0;
}

int zar::Bone::get_scale_index(const float animation_time) const
{
    for (int index = 0; index < m_num_scalings_ - 1; ++index)
    {
        if (animation_time < m_scales_[index + 1].timeStamp)
            return index;
    }
    assert(0);
    return 0;
}

float zar::Bone::get_scale_factor(const float last_time_stamp, const float next_time_stamp, const float animation_time)
{
    float scale_factor = 0.0f;
    const float mid_way_length = animation_time - last_time_stamp;
    const float frames_diff = next_time_stamp - last_time_stamp;
    scale_factor = mid_way_length / frames_diff;
    return scale_factor;
}

glm::mat4 zar::Bone::interpolate_position(const float animation_time)
{
    if (1 == m_num_positions_)
        return glm::translate(glm::mat4(1.0f), m_positions_[0].position);

    const int p0_index = get_position_index(animation_time);
    const int p1_index = p0_index + 1;
    const float scale_factor = get_scale_factor(m_positions_[p0_index].timeStamp,
                                               m_positions_[p1_index].timeStamp, animation_time);
    const glm::vec3 final_position = glm::mix(m_positions_[p0_index].position, m_positions_[p1_index].position
                                             , scale_factor);
    return glm::translate(glm::mat4(1.0f), final_position);
}

glm::mat4 zar::Bone::interpolate_rotation(const float animation_time)

{
    if (1 == m_num_rotations_)
    {
        const auto rotation = glm::normalize(m_rotations_[0].orientation);
        return glm::toMat4(rotation);
    }

    const int p0_index = get_rotation_index(animation_time);
    const int p1_index = p0_index + 1;
    const float scale_factor = get_scale_factor(m_rotations_[p0_index].timeStamp,
                                               m_rotations_[p1_index].timeStamp, animation_time);
    glm::quat final_rotation = glm::slerp(m_rotations_[p0_index].orientation, m_rotations_[p1_index].orientation
                                         , scale_factor);
    final_rotation = glm::normalize(final_rotation);
    return glm::toMat4(final_rotation);
}

glm::mat4 zar::Bone::interpolate_scaling(const float animation_time)
{
    if (1 == m_num_scalings_)
        return glm::scale(glm::mat4(1.0f), m_scales_[0].scale);

    const int p0_index = get_scale_index(animation_time);
    const int p1_index = p0_index + 1;
    const float scale_factor = get_scale_factor(m_scales_[p0_index].timeStamp,
                                               m_scales_[p1_index].timeStamp, animation_time);
    const glm::vec3 final_scale = glm::mix(m_scales_[p0_index].scale, m_scales_[p1_index].scale
                                          , scale_factor);
    return glm::scale(glm::mat4(1.0f), final_scale);
}
