#include "AABB.h"

AABB AABB::FromPositionSize(glm::vec2 position, glm::vec2 size)
{
    return AABB(
        position - size * 0.5f,
        position + size * 0.5f
    );
}

bool aabbOverlap(AABB a, AABB b)
{
    return 
        a._max.x >= b._min.x && 
        b._max.x >= a._min.x &&
        a._max.y >= b._min.y && 
        b._max.y >= a._min.y;
}
