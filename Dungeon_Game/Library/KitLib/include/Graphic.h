#pragma once

//---------------------------------------------------------------------------------------------------
//
// �`��Ɋւ����{�ݒ�
// TODO:OpenGL,DirectX�����ɑΉ����郉�C�u�������쐬
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



	// 2�����ł̕`��Ɋւ���ݒ�
	// 2D �_
	class Point2D:public float2 {
	public:
		Point2D();
		Point2D(const float &_x, const float &_y);
		~Point2D();

		Point2D& operator= (const float2 &_float2);
	};

	// 2D ����
	class Line2D {
	public:
		Point2D mp_start;	// �n�_
		vec2 mv_vec;		// �����x�N�g��

		Line2D();
		Line2D(const Point2D &_p, const vec2 &_vec);
		~Line2D();

		// ����̍��W���擾
		// value = �x�N�g���Ɋ|���Z����W��
		float2 GetPoint(const float &_value) const;
	};


	// 2D ����
	class Segment2D :public Line2D {
	public:
		Segment2D();
		Segment2D(const Point2D &_p, const vec2 &_vec);
		Segment2D(const Point2D &_p1, const Point2D &_p2);

		// �I�_���擾
		float2 GetEndPoint() const;
	};


	// 2D �~
	class Circle2D {
	public:
		Point2D mp_center;
		float mf_radius;

		Circle2D();
		Circle2D(const Point2D &_p, const float _r);
		~Circle2D();
	};

	// �J�v�Z��
	class Capsule2D {
	public:
		Segment2D m_segment;
		float mf_radius;
		Capsule2D();
		Capsule2D(const Segment2D &_seg, const float &_r);
		Capsule2D(const Point2D &_point1, const Point2D &_point2, const float &_r);
		~Capsule2D();
	};

	// 2D �O�p�`
	class Triangle2D {
	public:
		Point2D m_point[3]; // ���_���W

		Triangle2D();
		~Triangle2D();

		// �Ӄx�N�g���i�񐳋K���j���擾
		inline vec2 Vec(const int &_i) const {
			int idx[] = { 1,2,0,1 };
			return m_point[idx[_i + 1]] - m_point[idx[_i]];
		}

		// �ӂ̒������擾
		inline float Length(int &_i) const {
			return Vec(_i).Length();
		}
	};

	// 2D �l�p�`
	class Quadrangle2D {
	public:
		Point2D mp_center;
		Point2D m_point[4]; // ���_���W

		Quadrangle2D();
		~Quadrangle2D();

		// �Ӄx�N�g���i�񐳋K���j���擾
		inline vec2 Vec(const int &_i) const {
			int idx[] = { 1,2,3,0,1 };
			return m_point[idx[_i + 1]] - m_point[idx[_i]];
		}

		// �ӂ̒������擾
		inline float Length(const int &_i) const {
			return Vec(_i).Length();
		}

	};


	// 3D�_
	class Point :public float3 {
	public:
		Point();
		Point(const float &_x, const float &_y, const float &_z);
		~Point();

		Point& operator= (const float3 &_float3);
	};

	// 3D����
	class Line {
	public:
		Point mp_start;
		vec3 mv_vec;
		Line();
		Line(const Point &_pstart, const vec3 &_vec);
		~Line();

		float3 GetPoint(const float &_value) const;
	};

	// 3D����
	class Segment :public Line {
	public:
		Segment();
		Segment(const Point &_pstart, const vec3 &_vec);
		Segment(const Point &_pstart, const Point &_pend);
		~Segment();

		float3 GetEndPoint() const;
	};

	// 3D��
	class Sphere {
		Point mp_center;
		float mf_radius;
		Sphere();
		Sphere(const Point &_center, const float &_radius);
		~Sphere();
	};

	// 3D�J�v�Z��
	class Capsule {
		Segment m_segment;
		float mf_radius;
		Capsule();
		Capsule(const Segment &_seg, const float &_radius);
		Capsule(const Point &_pstart, const Point &_pend, const float &_radius);
		~Capsule();
	};
}