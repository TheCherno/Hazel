#pragma once

#ifdef HZ_DEBUG
#ifdef _MSC_VER
	#define HZ_DEBUGBREAK() __debugbreak()
#else

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_BREAK_USE_TRAP_INSTRUCTION 1
#define DEBUG_BREAK_USE_BULTIN_TRAP      2
#define DEBUG_BREAK_USE_SIGTRAP          3

#if defined(__i386__) || defined(__x86_64__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__inline__ static void trap_instruction(void)
	{
		__asm__ volatile("int $0x03");
	}
#elif defined(__thumb__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__attribute__((gnu_inline, always_inline))
		__inline__ static void trap_instruction(void)
	{
		/* See 'arm-linux-tdep.c' in GDB source.
		 * Both instruction sequences below work. */
#if 1
		 /* 'eabi_linux_thumb_le_breakpoint' */
		__asm__ volatile(".inst 0xde01");
#else
		 /* 'eabi_linux_thumb2_le_breakpoint' */
		__asm__ volatile(".inst.w 0xf7f0a000");
#endif
	}

#elif defined(__arm__) && !defined(__thumb__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__attribute__((gnu_inline, always_inline))
		__inline__ static void trap_instruction(void)
	{
		/* See 'arm-linux-tdep.c' in GDB source,
		 * 'eabi_linux_arm_le_breakpoint' */
		__asm__ volatile(".inst 0xe7f001f0");
	}
#elif defined(__aarch64__) && defined(__APPLE__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_BULTIN_TRAP
#elif defined(__aarch64__)
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__attribute__((gnu_inline, always_inline))
		__inline__ static void trap_instruction(void)
	{
		/* See 'aarch64-tdep.c' in GDB source,
		 * 'aarch64_default_breakpoint' */
		__asm__ volatile(".inst 0xd4200000");
	}
#elif defined(__powerpc__)
	/* PPC 32 or 64-bit, big or little endian */
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__attribute__((gnu_inline, always_inline))
		__inline__ static void trap_instruction(void)
	{
		/* See 'rs6000-tdep.c' in GDB source,
		 * 'rs6000_breakpoint' */
		__asm__ volatile(".4byte 0x7d821008");
	}
#else
#define DEBUG_BREAK_IMPL DEBUG_BREAK_USE_SIGTRAP
#endif

	/* Implementation */
#if DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_TRAP_INSTRUCTION
	__attribute__((gnu_inline, always_inline))
		__inline__ static void HZ_DEBUGBREAK(void)
	{
		trap_instruction();
	}
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_BULTIN_TRAP
	__attribute__((gnu_inline, always_inline))
		__inline__ static void HZ_DEBUGBREAK(void)
	{
		__builtin_trap();
	}
#elif DEBUG_BREAK_IMPL == DEBUG_BREAK_USE_SIGTRAP
#include <signal.h>
	__attribute__((gnu_inline, always_inline))
		__inline__ static void HZ_DEBUGBREAK(void)
	{
		raise(SIGTRAP);
	}
#endif

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif // !_MSC_VER

#else
	#define HZ_DEBUGBREAK()
#endif //! HZ_DEBUG