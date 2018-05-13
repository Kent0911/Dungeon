#pragma once

//---------------------------------------------------------------------------------------------------
//
// 描画に関する基本設定
// TODO:OpenGL,DirectX両方に対応するライブラリを作成
//
//---------------------------------------------------------------------------------------------------

#include "Vec2.h"
#include "Vec3.h"

namespace kit {

	//vertex class
	class vertex {
	public:
		float x, y, z;
	};

	//normal class
	class normal {
	public:
		float x, y, z;
	};

	//index class
	class index {
	public:
		unsigned int nom0, nom1, nom2;
	};

	//texture class
	class texture {
	public:
		float x, y;
	};



	// 2次元での描画に関する設定
	// 2D 点
	class Point2D:public float2 {
	public:
		Point2D();
		Point2D(const float &_x, const float &_y);
		~Point2D();

		Point2D& operator= (const float2 &_float2);
	};

	// 2D 直線
	class Line2D {
	public:
		Point2D mp_start;	// 始点
		vec2 mv_vec;		// 方向ベクトル

		Line2D();
		Line2D(const Point2D &_p, const vec2 &_vec);
		~Line2D();

		// 線上の座標を取得
		// value = ベクトルに掛け算する係数
		float2 GetPoint(const float &_value) const;
	};


	// 2D 線分
	class Segment2D :public Line2D {
	public:
		Segment2D();
		Segment2D(const Point2D &_p, const vec2 &_vec);
		Segment2D(const Point2D &_p1, const Point2D &_p2);

		// 終点を取得
		float2 GetEndPoint() const;
	};


	// 2D 円
	class Circle2D {
	public:
		Point2D mp_center;
		float mf_radius;

		Circle2D();
		Circle2D(const Point2D &_p, const float _r);
		~Circle2D();
	};

	// カプセル
	class Capsule2D {
	public:
		Segment2D m_segment;
		float mf_radius;
		Capsule2D();
		Capsule2D(const Segment2D &_seg, const float &_r);
		Capsule2D(const Point2D &_point1, const Point2D &_point2, const float &_r);
		~Capsule2D();
	};

	// 2D 三角形
	class Triangle2D {
	public:
		Point2D m_point[3]; // 頂点座標

		Triangle2D();
		~Triangle2D();

		// 辺ベクトル（非正規化）を取得
		inline vec2 Vec(const int &_i) const {
			int idx[] = { 1,2,0,1 };
			return m_point[idx[_i + 1]] - m_point[idx[_i]];
		}

		// 辺の長さを取得
		inline float Length(int &_i) const {
			return Vec(_i).Length();
		}
	};

	// 2D 四角形
	class Quadrangle2D {
	public:
		Point2D mp_center;
		Point2D m_point[4]; // 頂点座標

		Quadrangle2D();
		~Quadrangle2D();

		// 辺ベクトル（非正規化）を取得
		inline vec2 Vec(const int &_i) const {
			int idx[] = { 1,2,3,0,1 };
			return m_point[idx[_i + 1]] - m_point[idx[_i]];
		}

		// 辺の長さを取得
		inline float Length(const int &_i) const {
			return Vec(_i).Length();
		}

	};


	// 3D点
	class Point :public float3 {
	public:
		Point();
		Point(const float &_x, const float &_y, const float &_z);
		~Point();

		Point& operator= (const float3 &_float3);
	};

	// 3D直線
	class Line {
	public:
		Point mp_start;
		vec3 mv_vec;
		Line();
		Line(const Point &_pstart, const vec3 &_vec);
		~Line();

		float3 GetPoint(const float &_value) const;
	};

	// 3D線分
	class Segment :public Line {
	public:
		Segment();
		Segment(const Point &_pstart, const vec3 &_vec);
		Segment(const Point &_pstart, const Point &_pend);
		~Segment();

		float3 GetEndPoint() const;
	};

	// 3D球
	class Sphere {
		Point mp_center;
		float mf_radius;
		Sphere();
		Sphere(const Point &_center, const float &_radius);
		~Sphere();
	};

	// 3Dカプセル
	class Capsule {
		Segment m_segment;
		float mf_radius;
		Capsule();
		Capsule(const Segment &_seg, const float &_radius);
		Capsule(const Point &_pstart, const Point &_pend, const float &_radius);
		~Capsule();
	};
}