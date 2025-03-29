#include "types.h"

/*
==============
G_DebugLine
==============
*/
void G_DebugLine(const float *start, const float *end, const float *color, int depthTest)
{
	CL_AddDebugLine(start, end, color, depthTest, 0);
}

/*
==============
CG_DebugLine
==============
*/
void CG_DebugLine(const float *start, const float *end, const float *color, int depthTest, int duration)
{
	CL_AddDebugLine(start, end, color, depthTest, duration);
}

/*
==============
CG_DebugStar
==============
*/
void CG_DebugStar(clientDebugLineInfo_t *a1, const vec3_t *point, const vec4_t *color, int duration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugStarWithText
==============
*/
void G_DebugStarWithText(clientDebugLineInfo_t *a1, const vec3_t *point, const vec4_t *starColor, const vec4_t *textColor, const char *string, float fontsize)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugSphere
==============
*/
void G_DebugSphere(const float *center, float radius, const float *floatColor, int sideCount, int depthTest, int duration)
{
	CL_AddDebugSphere(center, radius, floatColor, sideCount, depthTest, duration);
}

/*
==============
CG_DebugCircle
==============
*/
void CG_DebugCircle(const vec3_t *center, float radius, const vec3_t *dir, const vec4_t *color, int depthTest)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugArc
==============
*/
void G_DebugArc(const vec3_t *center, float radius, float angle0, float angle1, const vec4_t *color, int depthTest)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
DrawBrushPoly
==============
*/
void DrawBrushPoly(int numPoints, vec3_t *points, const vec4_t *color)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugDrawBrush_r
==============
*/
void G_DebugDrawBrush_r(cLeafBrushNode_s *node, const vec4_t *color)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugDrawBrushModel
==============
*/
void G_DebugDrawBrushModel(gentity_t *entity, const vec4_t *color, int depthTest, int duration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

/*
==============
G_DebugCircle
==============
*/
void G_DebugCircle(const vec3_t *center, float radius, const vec4_t *color, int depthTest, int onGround, int duration)
{
	UNIMPLEMENTED(__FUNCTION__);
}

