#pragma once

class Material
{
private:
    float ambient;
    float diffuse;
    float specular;
public:
    Material() : ambient(0.2f), diffuse(0.8f), specular(0.0f) {}
    Material(float ambient, float diffuse, float specular) : ambient(ambient), diffuse(diffuse), specular(specular) {}

    float getAmbient() const
    {
        return ambient;
    }

    float getDiffuse() const
    {
        return diffuse;
    }

    float getSpecular() const
    {
        return specular;
    }
};