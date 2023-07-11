#include "TexturedMaterial.hh"

static inline float simplePow128(float x)
{
    auto pow2 = x * x;
    auto pow4 = pow2 * pow2;
    auto pow8 = pow4 * pow4;
    auto pow16 = pow8 * pow8;
    auto pow32 = pow16 * pow16;
    auto pow64 = pow32 * pow32;
    return pow64 * pow64;
}

Color TexturedMaterial::calculateColor(const Point3 &point, const Vector3 &normal, const Light &light, const Camera &camera, const TexturePoint &uv) const
{
    const BMPBuffer &buf = *this->buffer;
    auto uvx = static_cast<int>(uv.getX() * width);
    auto uvy = static_cast<int>(uv.getY() * height);
    uvy = height - uvy - 1;
    if(uvx < 0)
    {
        uvx = 0;
    }
    if(uvx >= width)
    {
        uvx = width - 1;
    }
    if(uvy < 0)
    {
        uvy = 0;
    }
    if(uvy >= height)
    {
        uvy = height - 1;
    }
    auto vertexColor = buf(uvx, uvy);
    Vector3 lightDirection;
    lightDirection.asProduct(light.getDir(), -1.0f);
    Vector3 viewDirection;
    viewDirection.asDifference(camera.getPos(), point);
    Vector3 halfVector;
    halfVector.asSum(lightDirection, viewDirection).normalize();

    VertexColor lightColor;
    lightColor.asProduct(light.getColor(), light.getIntensity());

    auto theta = normal * lightDirection;
    VertexColor diffuse;
    diffuse.asProduct(lightColor, vertexColor).asProduct(diffuse, theta > 0.0f ? theta : 0.0f);

    auto alpha = normal * halfVector;
    if(alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    VertexColor specular;
    specular.asProduct(lightColor, this->specular).asProduct(specular, alpha > 0.0f ? simplePow128(alpha) : 0.0f);

    VertexColor ambient;
    ambient.asProduct(lightColor, this->ambient).asProduct(ambient, vertexColor);

    VertexColor color;
    color.asSum(diffuse, specular).asSum(color, ambient).restrictColor();
    return color.toColor();
}