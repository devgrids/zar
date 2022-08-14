#include "Vertex.h"

void zar::Vertex::set_bone_data(const int id, const float weight)
{
    for (uint32_t i = 0; i < 4; ++i)
    {
        if (bones[i] < 0)
        {
            bones[i] = id;
            weights[i] = weight;
            return;
        }
    }
    spdlog::error("Failed to set vertex bone data!");
}
