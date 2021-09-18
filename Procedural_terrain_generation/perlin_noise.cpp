#include "perlin_noise.h"


perlin_noise::perlin_noise()
{

}

float perlin_noise::Perlin2D(Chunk::Vec2 point, float frequency) 
{
    point *= frequency;
    int ix0 = (int)point.x;
    int iy0 = (int)point.y;
    float tx0 = point.x - ix0;
    float ty0 = point.y - iy0;
    float tx1 = tx0 - 1.0f;
    float ty1 = ty0 - 1.0f;
    ix0 &= hashMask;
    iy0 &= hashMask;
    int ix1 = ix0 + 1;
    int iy1 = iy0 + 1;

    int h0 = hash(ix0);
    int h1 = hash(ix1);
    Chunk::Vec2 g00 = gradients2D(hash(h0 + iy0) & gMask);
    Chunk::Vec2 g10 = gradients2D(hash(h1 + iy0) & gMask);
    Chunk::Vec2 g01 = gradients2D(hash(h0 + iy1) & gMask);
    Chunk::Vec2 g11 = gradients2D(hash(h1 + iy1) & gMask);

    float v00 = Dot(g00, tx0, ty0);
    float v10 = Dot(g10, tx1, ty0);
    float v01 = Dot(g01, tx0, ty1);
    float v11 = Dot(g11, tx1, ty1);

    float tx = Smooth(tx0);
    float ty = Smooth(ty0);
    return lerp(
        lerp(v00, v10, tx),
        lerp(v01, v11, tx),
        ty) * 2.0f;
}





