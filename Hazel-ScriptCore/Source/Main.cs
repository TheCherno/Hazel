using System;
using System.Runtime.CompilerServices;

namespace Hazel
{

	public struct Vector3
	{
		public float X, Y, Z;

		public Vector3(float x, float y, float z)
		{
			X = x;
			Y = y;
			Z = z;
		}
	}

	public static class InternalCalls
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void NativeLog(string text, int parameter);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void NativeLog_Vector(ref Vector3 parameter, out Vector3 result);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static float NativeLog_VectorDot(ref Vector3 parameter);
	}

	public class Entity
	{
		public float FloatVar { get; set; }

		public Entity()
		{
			Console.WriteLine("Main constructor!");
			Log("AAstroPhysiC", 8058);

			Vector3 pos = new Vector3(5, 2.5f, 1);
			Vector3 result = Log(pos);
			Console.WriteLine($"{result.X}, {result.Y}, {result.Z}");
			Console.WriteLine("{0}", InternalCalls.NativeLog_VectorDot(ref pos));
		}

		public void PrintMessage()
		{
			Console.WriteLine("Hello World from C#!");
		}

		public void PrintInt(int value)
		{
			Console.WriteLine($"C# says: {value}");
		}

		public void PrintInts(int value1, int value2)
		{
			Console.WriteLine($"C# says: {value1} and {value2}");
		}

		public void PrintCustomMessage(string message)
		{
			Console.WriteLine($"C# says: {message}");
		}

		private void Log(string text, int parameter)
		{
			InternalCalls.NativeLog(text, parameter);

		}
		private Vector3 Log(Vector3 parameter)
		{
			InternalCalls.NativeLog_Vector(ref parameter, out Vector3 result);
			return result;
		}

	}

}
