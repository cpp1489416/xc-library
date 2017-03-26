#pragma once

#include <GL/glew.h>
#include <Core/Core.h>

XC_BEGIN_NAMESPACE_1(XC)
{
	static void InitializeOpenGL()
	{
		glewInit();
	}
};