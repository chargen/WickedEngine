#ifndef _SHADERINTEROP_EMITTEDPARTICLE_H_
#define _SHADERINTEROP_EMITTEDPARTICLE_H_

#include "ShaderInterop.h"

struct Particle
{
	float3 position;
	float rotationalVelocity;
	float3 velocity;
	float maxLife;
	float life;
	uint color_mirror;
	float2 sizeBeginEnd;
};

struct ParticleCounters
{
	uint aliveCount;
	uint deadCount;
	uint realEmitCount;
	uint aliveCount_afterSimulation;
};

CBUFFER(EmittedParticleCB, CBSLOT_OTHER_EMITTEDPARTICLE)
{
	float4x4	xEmitterWorld;

	uint		xEmitCount;
	uint		xEmitterMeshIndexCount;
	uint		xEmitterMeshVertexPositionStride;
	float		xEmitterRandomness;

	float		xParticleSize;
	float		xParticleScaling;
	float		xParticleRotation;
	uint		xParticleColor;

	float		xParticleRandomFactor;
	float		xParticleNormalFactor;
	float		xParticleLifeSpan;
	float		xParticleLifeSpanRandomness;

	float		xParticleMotionBlurAmount;
	float		xEmitterOpacity;
	float2		xPadding_EmitterCB;
};

CBUFFER(SortConstants, 0)
{
	int4 job_params;
};
#define SORT_SIZE 512

#define THREADCOUNT_EMIT 256
#define THREADCOUNT_SIMULATION 256

static const uint ARGUMENTBUFFER_OFFSET_DISPATCHEMIT = 0;
static const uint ARGUMENTBUFFER_OFFSET_DISPATCHSIMULATION = ARGUMENTBUFFER_OFFSET_DISPATCHEMIT + (3 * 4);
static const uint ARGUMENTBUFFER_OFFSET_DRAWPARTICLES = ARGUMENTBUFFER_OFFSET_DISPATCHSIMULATION + (3 * 4);
static const uint ARGUMENTBUFFER_OFFSET_DISPATCHSORT = ARGUMENTBUFFER_OFFSET_DRAWPARTICLES + (4 * 4);


#endif // _SHADERINTEROP_EMITTEDPARTICLE_H_

