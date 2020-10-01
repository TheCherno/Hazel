#include "hzpch.h"
#include "OpenGLError.h"
#include "Hazel/Core/Base.h"
#include <glad/glad.h>

/*
* Keep this a separate .cpp file for faster compilation.
*/

namespace Hazel
{

	//A struct to help with the 
	//info details of an error.
	struct OpenGLErrorInfo
	{
		GLenum			Errno;
		std::string		HexString;
		std::string		EnumString;
		std::string		Description;
	};



	/*
	* Get info of OpenGL Error.
	* This function gets the OpenGLErrorInfo object as a reference
	* in order to perform a little faster.
	* 
	* in  GLenum error			: The OpenGL Error.
	* in  OpenGLErrorInfo& info	: The info object reference to store the information.
	* return					: void
	*/
	void GetOpenGLErrorInfo(GLenum error, OpenGLErrorInfo& info)
	{

		switch (error)
		{

			case GL_INVALID_ENUM: 
				info.Errno			= GL_INVALID_ENUM;
				info.HexString		= "0x0500";
				info.EnumString		= "GL_INVALID_ENUM";
				info.Description	=	"Given when an enumeration parameter is not a legal\n"
										"\t\t\t\tenumeration for that function. This is given only for local problems;\n"
										"\t\t\t\tif the spec allows the enumeration in certain circumstances, where other\n"
										"\t\t\t\tparameters or state dictate those circumstances, then\n"
										"\t\t\t\tGL_INVALID_OPERATION is the result instead.\n";
				break;


			case GL_INVALID_VALUE:
				info.Errno			= GL_INVALID_VALUE;
				info.HexString		= "0x0501";
				info.EnumString		= "GL_INVALID_VALUE";
				info.Description	=	"Given when a value parameter is not a legal value for that function.\n"
										"\t\t\t\tThis is only given for local problems; if the spec allows the value\n"
										"\t\t\t\tin certain circumstances, where other parameters or state dictate those circumstances\n"
										"\t\t\t\tthen GL_INVALID_OPERATION is the result instead.\n";
				break;



			case GL_INVALID_OPERATION:
				info.Errno			= GL_INVALID_OPERATION;
				info.HexString		= "0x0502";
				info.EnumString		= "GL_INVALID_OPERATION";
				info.Description	=	"Given when the set of state for a command is not legal for the\n"
										"\t\t\t\tparameters given to that command. It is also given for commands\n"
										"\t\t\t\twhere combinations of parameters define what the legal parameters are.\n";
				break;



			case GL_STACK_OVERFLOW:
				info.Errno			= GL_STACK_OVERFLOW;
				info.HexString		= "0x0503";
				info.EnumString		= "GL_STACK_OVERFLOW";
				info.Description	=	"Given when a stack pushing operation cannot be done because it would\n"
										"\t\t\t\toverflow the limit of that stack's size.\n";
				break;


			case GL_STACK_UNDERFLOW:
				info.Errno			= GL_STACK_UNDERFLOW;
				info.HexString		= "0x0504";
				info.EnumString		= "GL_STACK_UNDERFLOW";
				info.Description	=	"Given when a stack popping operation cannot be done because\n"
										"\t\t\t\tthe stack is already at its lowest point.\n";
				break;


			case GL_OUT_OF_MEMORY:
				info.Errno			= GL_OUT_OF_MEMORY;
				info.HexString		= "0x0505";
				info.EnumString		= "GL_OUT_OF_MEMORY";
				info.Description	=	"Given when performing an operation that can allocate memory,\n"
										"\t\t\t\tand the memory cannot be allocated. The results of OpenGL functions that return\n"
										"\t\t\t\tthis error are undefined; it is allowable for partial execution of an operation\n"
										"\t\t\t\tto happen in this circumstance.\n";
				break;


			case GL_INVALID_FRAMEBUFFER_OPERATION:
				info.Errno			= GL_INVALID_FRAMEBUFFER_OPERATION;
				info.HexString		= "0x0506";
				info.EnumString		= "GL_INVALID_FRAMEBUFFER_OPERATION";
				info.Description	=	"Given when doing anything that would attempt to read from or write/render\n"
										"\t\t\t\tto a framebuffer that is not complete.\n";
				break;


			case GL_CONTEXT_LOST:
				info.Errno			= GL_CONTEXT_LOST;
				info.HexString		= " 0x0507";
				info.EnumString		= "GL_CONTEXT_LOST";
				info.Description	= "Given if the OpenGL context has been lost, due to a graphics card reset.";
				break;


			default:
				info.Errno			= GL_NONE;
				info.HexString		= "0x0";
				info.EnumString		= "Uknown Error";
				info.Description	= "An uknown error has occured! That's not good!!!";
				break;
		}
	}






	void OpenGLClearErrors()
	{

		//Make sure OpenGL Context is still alive!!!
		//If not, this is gonna stuck in an infinity loop due to the
		//profiler's thread!!!!
		if ( wglGetCurrentContext() )
		{
			while ( glGetError() );
		}
	}




	void OpenGLLogErrors(const std::string& file, unsigned int line)
	{
		OpenGLErrorInfo info;
		GLenum			error;
		bool			first = true;

		//Make sure OpenGL Context is still alive!!!
		//If not, this is gonna stuck in an infinity loop due to the
		//profiler's thread!!!!
		if ( wglGetCurrentContext() )
		{
			while (error = glGetError())
			{
				//Get the Error Information.
				GetOpenGLErrorInfo(error, info);

				//Print the following only once!!!
				if (first)
				{
					HZ_CORE_ERROR("[OpenGL Error]");
					HZ_CORE_ERROR("At File: {0}", file);
					HZ_CORE_ERROR("At Line: {0}", line);
					HZ_CORE_ERROR("Errors :");
					first = false;
				}

				//Print the error information.
				HZ_CORE_ERROR("\tErrno (dec) : {0}", info.Errno);
				HZ_CORE_ERROR("\tErrno (hex) : {0}", info.HexString);
				HZ_CORE_ERROR("\tGLenum	    : {0}", info.EnumString);
				HZ_CORE_ERROR("\tDescription : {0}", info.Description);
			}
		}
	}
}
