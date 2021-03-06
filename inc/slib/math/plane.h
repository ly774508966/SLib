/*
 *  Copyright (c) 2008-2017 SLIBIO. All Rights Reserved.
 *
 *  This file is part of the SLib.io project.
 *
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this
 *  file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef CHECKHEADER_SLIB_MATH_PLANE
#define CHECKHEADER_SLIB_MATH_PLANE

#include "definition.h"

#include "vector3.h"
#include "line3.h"
#include "matrix4.h"

/*
	ax + by + cz + d = 0
 */

namespace slib
{

	template <class T>
	class SLIB_EXPORT PlaneT
	{
	public:
		T a;
		T b;
		T c;
		T d;

	public:
		SLIB_INLINE PlaneT() = default;

		constexpr PlaneT(const PlaneT<T>& other):
		 a(other.a), b(other.b), c(other.c), d(other.d)
		{}

		template <class O>
		constexpr PlaneT(const PlaneT<O>& other):
		 a((T)(other.a)), b((T)(other.b)), c((T)(other.c)), d((T)(other.d))
		{}

		constexpr PlaneT(T _a, T _b, T _c, T _d):
		 a(_a), b(_b), c(_c), d(_d)
		{}

		PlaneT(const Vector3T<T>& point, const Vector3T<T>& normal);

	public:
		Vector3T<T> getNormal() const;

		Vector3T<T> projectOriginOnNormalized() const;

		Vector3T<T> projectOrigin() const;

		T getDistanceFromPointOnNormalized(const Vector3T<T>& pos) const;

		T getDistanceFromPoint(const Vector3T<T>& pos) const;

		Vector3T<T> projectPointOnNormalized(const Vector3T<T>& pos) const;

		Vector3T<T> projectPoint(const Vector3T<T>& pos) const;

		void setFromPointAndNormal(const Vector3T<T>& point, const Vector3T<T>& normal);

		void normalize();

		void transform(const Matrix4T<T>& mat);

		// return sl_true when the plane intersects to the line segment
		sl_bool intersectLine(
			const Line3T<T>& line,
			Vector3T<T>* outIntersectPoint = sl_null,
			sl_bool* pFlagParallel = sl_null,
			sl_bool* pFlagExtendPoint1 = sl_null,
			sl_bool* pFlagExtendPoint2 = sl_null) const;

		sl_bool intersectPlane(const PlaneT<T>& plane, Line3T<T>* outIntersectLine = sl_null, sl_bool* pFlagParallel = sl_null) const;

	public:
		PlaneT<T>& operator=(const PlaneT<T>& other) = default;

		template <class O>
		PlaneT<T>& operator=(const PlaneT<O>& other);
	
	};
	
	extern template class PlaneT<float>;
	extern template class PlaneT<double>;
	typedef PlaneT<sl_real> Plane;
	typedef PlaneT<float> Planef;
	typedef PlaneT<double> Planelf;

}

#include "detail/plane.h"

#endif
