﻿using System;
using System.Runtime.CompilerServices;

namespace Hazel
{
	public static class InternalCalls
	{
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Entity_HasComponent(ulong entityID, Type componentType);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static ulong Entity_FindEntityByName(string name);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static object GetScriptInstance(ulong entityID);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetTranslation(ulong entityID, out Vector3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetRotation(ulong entityID, out Vector3 rotation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_GetScale(ulong entityID, out Vector3 scale);


		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetTranslation(ulong entityID, ref Vector3 translation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetRotation(ulong entityID, ref Vector3 rotation);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void TransformComponent_SetScale(ulong entityID, ref Vector3 scale);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Rigidbody2DComponent_ApplyLinearImpulse(ulong entityID, ref Vector2 impulse, ref Vector2 point, bool wake);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Rigidbody2DComponent_GetLinearVelocity(ulong entityID, out Vector2 linearVelocity);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static Rigidbody2DComponent.BodyType Rigidbody2DComponent_GetType(ulong entityID);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Rigidbody2DComponent_SetType(ulong entityID, Rigidbody2DComponent.BodyType type);

		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static void Rigidbody2DComponent_ApplyLinearImpulseToCenter(ulong entityID, ref Vector2 impulse, bool wake);
		[MethodImplAttribute(MethodImplOptions.InternalCall)]
		internal extern static bool Input_IsKeyDown(KeyCode keycode);
	}
}
