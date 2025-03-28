#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include <cmath>
#include <iostream>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class t> struct Vec2 {
	union {
		struct {t u, v;};
		struct {t x, y;};
		t raw[2];
	};
	Vec2() : u(0), v(0) {}
	Vec2(t _u, t _v) : u(_u),v(_v) {}
	inline Vec2<t> operator +(const Vec2<t> &V) const { return Vec2<t>(u+V.u, v+V.v); }
	inline Vec2<t> operator -(const Vec2<t> &V) const { return Vec2<t>(u-V.u, v-V.v); }
	inline Vec2<t> operator *(float f)          const { return Vec2<t>(u*f, v*f); }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec2<t>& v);
};

template <class t> struct Vec3 {
	union {
		struct {t x, y, z;};
		struct { t ivert, iuv, inorm; };
		t raw[3];
	};
	Vec3() : x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x),y(_y),z(_z) {}
	inline Vec3<t> operator ^(const Vec3<t> &v) const { return Vec3<t>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
	inline Vec3<t> operator +(const Vec3<t> &v) const { return Vec3<t>(x+v.x, y+v.y, z+v.z); }
	inline Vec3<t> operator -(const Vec3<t> &v) const { return Vec3<t>(x-v.x, y-v.y, z-v.z); }
	inline Vec3<t> operator *(float f)          const { return Vec3<t>(x*f, y*f, z*f); }
	inline Vec3<t> operator *(const Vec3<t> &v) const { return Vec3<t>(x*v.x, y*v.y, z*v.z); }
	// inline t       operator *(const Vec3<t> &v) const { return x*v.x + y*v.y + z*v.z; }
	float norm () const { return std::sqrt(x*x+y*y+z*z); }
	Vec3<t> & normalize(t l=1) { *this = (*this)*(l/norm()); return *this; }
	template <class > friend std::ostream& operator<<(std::ostream& s, Vec3<t>& v);
};

template <class t> struct Mat3 {
	Vec3<Vec3<t>> m;
	Mat3() : m(Vec3<Vec3<t>>(Vec3<t>(), Vec3<t>(), Vec3<t>())){};
	Mat3(const Vec3<t> &a, const Vec3<t> &b, const Vec3<t> &c): m(Vec3<Vec3<t>>(a, b, c)){};
	inline Mat3<t> operator +(const Mat3<t> &v) const {
		return Mat3<t>(m.x+v.m.x, m.y+v.m.y, m.z+v.m.z);
	}
	inline Mat3<t> operator -(const Mat3<t> &v) const {
		return Mat3<t>(m.x-v.m.x, m.y-v.m.y, m.z-v.m.z);
	}
	inline Mat3<t> operator *(float f) const {
		return Mat3<t>(m.x*f, m.y*f, m.z*f);
	}
	inline Mat3<t> transpose() const {
		return Mat3<t>(Vec3<t>(m.x.x, m.y.x, m.z.x), Vec3<t>(m.x.y, m.y.y, m.z.y), Vec3<t>(m.x.z, m.y.z, m.z.z));
	}
	inline Mat3<t> operator *(Mat3<t> v) const {
		auto v_t = v.transpose();
		return Mat3<t>(Vec3<t>(dot(m.x, v_t.m.x), dot(m.x, v_t.m.y), dot(m.x, v_t.m.z)),
					   Vec3<t>(dot(m.y, v_t.m.x), dot(m.y, v_t.m.y), dot(m.y, v_t.m.z)),
					   Vec3<t>(dot(m.z, v_t.m.x), dot(m.z, v_t.m.y), dot(m.z, v_t.m.z)));
	}
};

template <class t> t dot_product(const Vec3<t> &a, const Vec3<t> &b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

template <class t> Vec3<t> dot_product(const Mat3<t> &a, const Vec3<t> &b) {
	return Vec3<t>(dot(a.m.x, b), dot(a.m.y, b), dot(a.m.z, b));
}

template <class t> Vec3<t> cross_product(const Vec3<t> &a, const Vec3<t> &b) {
	return Vec3<t>(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x);
}


typedef Vec2<float> Vec2f;
typedef Vec2<int>   Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;
typedef Mat3<float> Mat3f;
typedef Mat3<int> Mat3i;

template <class t> std::ostream& operator<<(std::ostream& s, Vec2<t>& v) {
	s << "(" << v.x << ", " << v.y << ")\n";
	return s;
}

template <class t> std::ostream& operator<<(std::ostream& s, Vec3<t>& v) {
	s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
	return s;
}

#endif //__GEOMETRY_H__