#pragma once
#include "Eigen/Eigen"
#include "MathEigen.h"
#include "Windows.h"

using Eigen::Vector2i;

class RenderBuffer
{
public:
	RenderBuffer(Vector2i size);
	~RenderBuffer();

	Vector2i GetSize() const;
	CHAR_INFO* GetPtr() const;

	CHAR_INFO& operator[](const Vector2i& pos);

private:
	Vector2i _size;
	CHAR_INFO* _ptr;
};

