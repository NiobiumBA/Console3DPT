#pragma once
#include <thread>
#include <future>
#include "Eigen/Eigen"
#include "MathEigen.h"
#include "RenderBuffer.h"
#include "Screen.h"
#include "Camera.h"
#include "PathTracing.h"
#include "Scene.h"
#ifndef _MY_GRAPHICS_INCLUDE
#define _MY_GRAPHICS_INCLUDE

using Eigen::Vector2i;
using Eigen::Vector2f;
using Eigen::Vector4f;

#undef min
#undef max

namespace Graphics
{
	RenderBuffer* screenBuffer = nullptr;//(Vector2i::Ones());
	std::string colorValueGradient = " .:!/r(l1Z4H9W8$g@";
	Vector2i threadGroupSize = Vector2i(4, 4);

	struct PreFragToFrag
	{
		Vector2f uv;

		Vector3f cameraPos;
		float maxDistance;

		Vector3f viewDirBL; // Bottom left
		Vector3f viewDirTL; // Top left
		Vector3f viewDirBR; // Bottom right
		Vector3f viewDirTR; // Top right
	};

	Vector3f Bilerp(const Vector2f& offset, const Vector3f& val00, const Vector3f& val01, const Vector3f& val10, const Vector3f& val11)
	{
		return (1 - offset.x()) * (1 - offset.y()) * val00 +
				offset.x() * (1 - offset.y()) * val10 +
				(1 - offset.x()) * offset.y() * val01 +
				offset.x() * offset.y() * val11;
	}

	Vector3f GetViewDir(const Vector2f& viewport, const Matrix4f& viewportToWorld, const Vector3f& cameraPos)
	{
		Vector4f viewport4D = Vector4f(viewport.x(), viewport.y(), -1, 1);

		Vector4f rayPosOnPlane4 = viewportToWorld * viewport4D;
		Vector3f rayPosOnPlane = Vector3f(rayPosOnPlane4.x(), rayPosOnPlane4.y(), rayPosOnPlane4.z()) * (1 / rayPosOnPlane4.w());

		Vector3f rayDir = rayPosOnPlane - cameraPos;
		//rayDir.normalize();

		return rayDir;
	}

	void PreFragment(const Camera& camera, PreFragToFrag& output)
	{
		output = PreFragToFrag();
		output.cameraPos = camera.position;
		output.maxDistance = camera.GetFarClipPlane();

		// Compute view direction only for corners instead of for each pixel for optimization
		// And interpolate corner's value for each fragment
		output.viewDirBL = GetViewDir(Vector2f(-1, -1), camera.ViewportToWorld(), camera.position);
		output.viewDirTL = GetViewDir(Vector2f(-1, 1), camera.ViewportToWorld(), camera.position);
		output.viewDirBR = GetViewDir(Vector2f(1, -1), camera.ViewportToWorld(), camera.position);
		output.viewDirTR = GetViewDir(Vector2f(1, 1), camera.ViewportToWorld(), camera.position);
	}

	// Return value in RGB (each channel in [0..1])
	Vector3f Fragment(const PreFragToFrag& input, const PathTracing::RenderObject::VectorObjects& objects)
	{
		//Vector3f viewDir = GetViewDir(input.uv, input.viewportToWorld, input.cameraPos);
		Vector3f viewDir = Bilerp(input.uv, input.viewDirBL,
											input.viewDirTL,
											input.viewDirBR,
											input.viewDirTR);
		viewDir.normalize();

		PathTracing::Ray ray = { input.cameraPos, viewDir };

		return PathTracing::PathTrace(ray, objects, input.maxDistance, 3);

		//return viewDir;
		//return Vector3f(input.uv.x(), input.uv.y(), 0);
	}

	// Return value is a Vector3f
	// where x = hue [0..360),
	// y = saturate [0..1],
	// z = value [0..1]
	void RGBToHSV(const Vector3f& rgb, float& hue, float& saturate, float& value)
	{
		value = std::max(rgb.x(), std::max(rgb.y(), rgb.z()));
		float channelMin = std::min(rgb.x(), std::min(rgb.y(), rgb.z()));

		float delta = value - channelMin;

		hue = 0.0f;

		if (value != channelMin)
		{
			if (value == rgb.x())
				hue = (float)std::fmod((rgb.y() - rgb.z()) / delta + 6, 6);
			else if (value == rgb.y())
				hue = (rgb.z() - rgb.x()) / delta + 2;
			else if (value == rgb.z())
				hue = (rgb.x() - rgb.y()) / delta + 4;
		}
		hue *= 60;

		saturate = value == 0.0f ? 0 : delta / value;
	}

	CHAR_INFO RGBToConsoleSpace(const Vector3f& rgb)
	{
		float hue, value, saturate;
		RGBToHSV(rgb, hue, saturate, value);

		CHAR_INFO result = CHAR_INFO();

		float idChar = value * colorValueGradient.length();
		result.Char.AsciiChar = colorValueGradient[std::clamp((int)std::round(idChar), 0, (int)colorValueGradient.length() - 1)];

		WORD attributes;

		if (saturate < 1.0f / 3)
		{
			if (value < 1.0f / 3)
				attributes = FOREGROUND_INTENSITY;
			else if (value < 2.0f / 3)
				attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			else
				attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
		}
		else
		{
			attributes = 0;

			if (hue < 90 || hue > 270)
				attributes |= FOREGROUND_RED;
			if (30 < hue && hue < 210)
				attributes |= FOREGROUND_GREEN;
			if (150 < hue && hue < 330)
				attributes |= FOREGROUND_BLUE;

			if (value > 0.5f)
				attributes |= FOREGROUND_INTENSITY;
		}
		result.Attributes = attributes;

		return result;
	}

	void Init()
	{
		screenBuffer = new RenderBuffer(Screen::GetBufferSize());
	}

	void ThreadFunction(const Vector2i& group, const Vector2i& pixelsInGroup,
						PreFragToFrag linkData, RenderBuffer& buffer, const Vector2f& invBufferSize)
	{
		Vector2i start = group.cwiseProduct(pixelsInGroup);
		Vector2i end = (start + pixelsInGroup).cwiseMin(buffer.GetSize());

		for (size_t y = start.y(); y < end.y(); y++)
		{
			for (size_t x = start.x(); x < end.x(); x++)
			{
				linkData.uv = Vector2f(x, y).cwiseProduct(invBufferSize);

				Vector3f colorRGB = MathEigen::saturate(Fragment(linkData, Scene::current->renderObjects));

				buffer[Vector2i(x, buffer.GetSize().y() - 1 - y)] = RGBToConsoleSpace(colorRGB);
			}
		}
	}

	void Render(const Camera& camera, RenderBuffer& buffer)
	{
		PreFragToFrag linkData;
		PreFragment(camera, linkData);

		Vector2i bufferSize = buffer.GetSize();
		Vector2f invBufferSize = Vector2f(1.0f / bufferSize.x(), 1.0f / bufferSize.y());

		int threadsCount = threadGroupSize.x() * threadGroupSize.y();
		Vector2f pixelsInGroupFloat = Vector2f((float)bufferSize.x() / threadGroupSize.x(), (float)bufferSize.y() / threadGroupSize.y());
		Vector2i pixelsInGroup = MathEigen::ceil(pixelsInGroupFloat).cast<int>();

		std::future<void>* threads = new std::future<void>[threadsCount];

		for (size_t threadY = 0; threadY < threadGroupSize.y(); threadY++)
		{
			for (size_t threadX = 0; threadX < threadGroupSize.x(); threadX++)
			{
				threads[threadGroupSize.y() * threadX + threadY] =
					std::async(ThreadFunction, Vector2i(threadX, threadY), pixelsInGroup, linkData, std::ref(buffer), invBufferSize);
			}
		}

		//Then std::future deleting the main thread await finishing all threads;
		delete[] threads;

		/*for (size_t y = 0; y < bufferSize.y(); y++)
		{
			for (size_t x = 0; x < bufferSize.x(); x++)
			{
				linkData.uv = Vector2f(x, y).cwiseProduct(invBufferSize);

				colorRGB = MathEigen::saturate(Fragment(linkData, Scene::current->renderObjects));

				buffer[Vector2i(x, bufferSize.y() - 1 - y)] = RGBToConsoleSpace(colorRGB);
			}
		}*/
	}

	void RenderOnScreen()
	{
		Render(*Camera::main, *screenBuffer);

		Screen::Render(screenBuffer->GetPtr());
	}
}

#endif // _MY_GRAPHICS_INCLUDE
