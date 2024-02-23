#ifndef SYDPHYSICS_PHYSICSSETTINGS_H
#define SYDPHYSICS_PHYSICSSETTINGS_H

using namespace std;

#include <Math/Mathematics.hpp>

namespace SydPhysics
{
    struct WorldSettings
    {
        string worldName;
        Vector2f gravity;
        float frameDamping;
        float restitutionCoeffectient;
        float awakeEpsilon;

        WorldSettings()
        {
            worldName = "Unnamed world";
            gravity = Vector2f(0,10);
            frameDamping = 0;
            restitutionCoeffectient = 0.5f;
            awakeEpsilon = 0.1;
        }

        ~WorldSettings() = default;
    };
}

#endif