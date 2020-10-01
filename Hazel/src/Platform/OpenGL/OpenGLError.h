#pragma once

namespace Hazel
{
	void OpenGLClearErrors();
	void OpenGLLogErrors(const std::string& file, unsigned int line);
}

//If Debug is ON.
#ifdef HZ_DEBUG
	#define HZ_GLCALL(code) Hazel::OpenGLClearErrors(); code; Hazel::OpenGLLogErrors(__FILE__, __LINE__)

//Else, just copy the code as it is.
#else 
	#define HZ_GLCALL(code) code

#endif
