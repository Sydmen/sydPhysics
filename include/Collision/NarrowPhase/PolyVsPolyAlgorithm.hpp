#ifndef SYDPHYS_POLYVSPOLYALGO_H
#define SYDPHYS_POLYVSPOLYALGO_H

#include <Collision/NarrowPhase/NarrowPhaseAlgorithm.hpp>
#include <Collision/Shapes/PolygonShape.hpp>

namespace SydPhysics
{
	class PolyVsPolyAlgorithm : public NarrowPhaseAlgorithm
	{
	public:
		PolyVsPolyAlgorithm()=default;
		~PolyVsPolyAlgorithm();
		
		static bool Collides(PolygonShape& A, PolygonShape& B);
	};
}

#endif