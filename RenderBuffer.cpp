#include "RenderBuffer.h"
#include <iostream>

RenderBuffer::RenderBuffer(Vector2i size) : _size(size)
{
	_ptr = new CHAR_INFO[size.x() * size.y()];
}

RenderBuffer::~RenderBuffer()
{
	delete[] _ptr;
}

Vector2i RenderBuffer::GetSize() const
{
	return _size;
}

CHAR_INFO* RenderBuffer::GetPtr() const
{
	return _ptr;
}

CHAR_INFO& RenderBuffer::operator[](const Vector2i& pos)
{
	return _ptr[pos.y() * _size.x() + pos.x()];
}
