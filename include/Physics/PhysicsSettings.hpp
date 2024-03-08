#ifndef SYDPHYSICS_PHYSICSSETTINGS_H
#define SYDPHYSICS_PHYSICSSETTINGS_H

using namespace std;

#include <Math/Mathematics.hpp>

namespace SydPhysics
{
    struct PhysicsWorldSettings
    {
        string worldName;
        Vector2f gravity;
        float frameDamping;
        float restitutionCoeffectient;
        float awakeEpsilon;

        PhysicsWorldSettings()
        {
            worldName = "Unnamed world";
            gravity = Vector2f(0,10);
            frameDamping = 0.005;
            restitutionCoeffectient = 0.5f;
            awakeEpsilon = 0.1;
        }
        
        ~PhysicsWorldSettings() = default;
    };
}

#endif