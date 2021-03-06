#pragma once

//---------------------------------------------------------------------------------------------------
//
// 当たり判定に関する関数の定義
// TODO:bool型ですべて定義する
//
//---------------------------------------------------------------------------------------------------

#include "Defines.h"

#include <math.h>

#include "Vec2.h"
#include "Vec3.h"
#include "Graphic.h"

#define _OX_EPSILON_ 0.000001f //誤差

namespace kit {
	// vec2型 posとspeedでの衝突判定
	bool HitCheck(const vec2 &_mypos, const vec2 &_myspeed, const vec2 &_targetpos, const vec2 &_targetspeed);
	// vec3型 posとspeedでの衝突判定
	bool HitCheck(const vec3 &_mypos, const vec3 &_myspeed, const vec3 &_targetpos, const vec3 &_targetspeed);

	// 2D 点と線分の衝突判定
	bool HitCheck(const Point2D &_seg_start, const Point2D &_seg_end, const Point2D &_point);
	// 2D 点と線分の衝突判定
	bool HitCheck(const Segment2D &_seg, const Point2D &_point);

	// 3D 点と線分の衝突判定
	bool HitCheck(const Point &_seg_start, const Point &_seg_end, const Point &_point);
	// 3D 点と線分の衝突判定
	bool HitCheck(const Segment &_seg, const Point &_point);

	// 2D 点と円の衝突判定
	bool HitCheck(const Point2D &_point, const Point2D &_center, const float &_radius);
	// 2D 点と円の衝突判定
	bool HitCheck(const Point2D &_point, const Circle2D &_circle);

	// 2D 円と円の衝突判定
	bool HitCheck(const Point2D &_center1, const float &_radius1, const Point2D &_center2, const float &_radius2);
	// 2D 円と円の衝突判定
	bool HitCheck(const Circle2D &_circle1, const Circle2D &_circle2);

	// 2D 正方形と点の衝突判定
	bool HitCheck(const Point2D &_point, const Quadrangle2D &_quad);
	// 2D 正方形と正方形の衝突判定
	bool HitCheck(const Quadrangle2D &_quad1, const Quadrangle2D &_quad2);

	// 2D 円と線分の衝突判定
	bool HitCheck(const Point2D &_seg_start, const Point2D &_seg_end, const Point2D &_circle_center, const float &_radius);
	// 2D 円と線分の衝突判定
	bool HitCheck(const Segment2D &_seg, const Point2D &_circle_center, const float &_radius);
	// 2D 円と線分の衝突判定
	bool HitCheck(const Point2D &_seg_start, const Point2D &_seg_end, const Circle2D &_circle);
	// 2D 円と線分の衝突判定
	bool HitCheck(const Segment2D &_seg, const Circle2D &_circle);

}