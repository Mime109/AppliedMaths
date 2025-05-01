#pragma once

#include "core.h"

////////////////////////////////////////////////////////
// The emitter is simply a container to hold a number of particles
////////////////////////////////////////////////////////
class cEmitter
{
public:
	int m_num_particles;
	class cParticle* m_list;
};