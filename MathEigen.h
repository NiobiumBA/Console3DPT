#undef min
#undef max

#pragma once
#ifndef __MathEigen
#define __MathEigen
#define _USE_MATH_DEFINES
#include "Eigen/Eigen"
#include <math.h>

namespace MathEigen
{
	using Eigen::Vector3f;
	using Eigen::Matrix4f;
	using Eigen::AngleAxisf;
	using Eigen::Quaternionf;

	constexpr float DegToRad = (float)(M_PI / 180.0f);
	constexpr float RadToDeg = (float)(180.0f / M_PI);

#define FUNCNAME abs
#define NMSPC ABS
#define FUNCEXPR return std::abs(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME sqrt
#define NMSPC SQRT
#define FUNCEXPR return std::sqrt(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME ceil
#define NMSPC CEIL
#define FUNCEXPR return std::ceil(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME exp
#define NMSPC EXP
#define FUNCEXPR return std::exp(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME exp2
#define NMSPC EXP2
#define FUNCEXPR return std::exp2(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME floor
#define NMSPC FLOOR
#define FUNCEXPR return std::floor(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME frac
#define NMSPC FRAC
//#define FUNCEXPR return std::fmod(a, 1);
#define FUNCEXPR \
	int intpart; \
	return std::modf(a, &intpart);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME log
#define NMSPC LOG
#define FUNCEXPR return std::log(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME log2
#define NMSPC LOG2
#define FUNCEXPR return std::log2(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME log10
#define NMSPC LOG10
#define FUNCEXPR return std::log10(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME round
#define NMSPC ROUND
#define FUNCEXPR return std::round(a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME saturate
#define NMSPC SATURATE
#define FUNCEXPR return std::clamp<Scalar>(a, 0, 1);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME sign
#define NMSPC SIGN
#define FUNCEXPR return (a > 0) - (a < 0);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME smoothstep
#define NMSPC SMOOTHSTEP
#define FUNCEXPR return a * a * ((Scalar)3 - (Scalar)2 * a);
#include "InternalUnaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC



// Binary functions
#define FUNCNAME min
#define NMSPC MIN
#define FUNCEXPR return std::min(a, b);
#include "InternalBinaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME max
#define NMSPC MAX
#define FUNCEXPR return std::max(a, b);
#include "InternalBinaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME pow
#define NMSPC POW
#define FUNCEXPR return std::pow(a, b);
#include "InternalBinaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

#define FUNCNAME step
#define NMSPC STEP
#define FUNCEXPR return b >= a;
#include "InternalBinaryMathEigen.h"
#undef FUNCNAME
#undef FUNCEXPR
#undef NMSPC

	template<typename ValueType, typename MinType, typename MaxType>
	Eigen::Matrix<typename ValueType::Scalar, ValueType::RowsAtCompileTime, ValueType::ColsAtCompileTime>
	clamp(const ValueType& value, const MinType& min_, const MaxType& max_)
	{
		return min(max(value, min_), max_);
	}

	template<typename T>
	Eigen::Matrix<typename T::Scalar, T::RowsAtCompileTime, T::ColsAtCompileTime>
	lerp(const T& a, const T& b, float t)
	{
		return a + (b - a) * t;
	}

	Quaternionf EulerToQuaternion(const Vector3f& eulerAngles);

	Matrix4f QuaternionToMatrix4f(const Quaternionf& q);

	Matrix4f TranslationMatrix4f(const Vector3f& translation);
} // namespace

#endif //__MathEigen
