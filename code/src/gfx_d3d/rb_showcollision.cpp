#include "types.h"

struct cplane_s
{
	float normal[3];
	float dist;
	unsigned __int8 type;
	unsigned __int8 signbits;
	unsigned __int8 pad[2];
};

struct GfxPointVertex
{
	float xyz[3];
	unsigned __int8 color[4];
};

GfxPointVertex debugLineVerts[1];

/*
==============
TRACK_rb_showcollision
==============
*/
void TRACK_rb_showcollision()
{
	track_static_alloc_internal(debugLineVerts, 16, "debugLineVerts", 0);
}

/*
==============
BuildFrustumPlanes
==============
*/
void BuildFrustumPlanes(const GfxViewParms *viewParms, cplane_s *frustumPlanes)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
RB_DrawCollisionPoly
==============
*/
void RB_DrawCollisionPoly(int numPoints, vec3_t *points, const vec4_t *colorFloat)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
RB_ShowCollision
==============
*/
void RB_ShowCollision(const GfxViewParms *viewParms)
{
	assert(viewParms);

	if (!r_showCollision->current.integer)
	{
		return;
	}

	cplane_s frustumPlanes[6];
	BuildFrustumPlanes(viewParms, frustumPlanes);

	frustumPlanes[5].normal[0] = -1.0 * frustumPlanes[4].normal[0];
    frustumPlanes[5].normal[1] = -1.0 * frustumPlanes[4].normal[1];
    frustumPlanes[5].normal[2] = -1.0 * frustumPlanes[4].normal[2];
    frustumPlanes[5].dist = -frustumPlanes[4].dist - r_showCollisionDist->current.value;

	unsigned __int8 type;
	if ((-1.0f * frustumPlanes[4].normal[0]) == 1.0f)
	{
		type = 0;
	}
	else
	{
		if (frustumPlanes[5].normal[1] == 1.0f)
		{
			type = 1;
		}
		else
		{
			if (frustumPlanes[5].normal[2] == 1.0f)
			{
				type = 2;
			}
			else
			{
				type = 3;
			}
		}
	}

	frustumPlanes[5].type = type;
	SetPlaneSignbits(&frustumPlanes[5]);

	if (r_showCollisionGroups->current.integer <= 1)
	{
		CM_ShowBrushCollision(showCollisionContentMasks[r_showCollision->current.integer];, frustumPlanes, 6, RB_DrawCollisionPoly);
	}

	if (tess.indexCount)
	{
		RB_EndTessSurface();
	}
}

