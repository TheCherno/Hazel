#include "hzpch.h"
#include "Hazel/Events/Event.h"

namespace Hazel
{

	EventCategory operator |(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) |
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);
	}

	EventCategory operator &(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) &
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);
	}

	EventCategory operator ^(EventCategory lhs, EventCategory rhs)
	{
		return static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) ^
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);
	}

	EventCategory operator ~(EventCategory rhs)
	{
		return static_cast<EventCategory> (
			~static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);
	}

	EventCategory& operator |=(EventCategory& lhs, EventCategory rhs)
	{
		lhs = static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) |
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);

		return lhs;
	}

	EventCategory& operator &=(EventCategory& lhs, EventCategory rhs)
	{
		lhs = static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) &
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);

		return lhs;
	}

	EventCategory& operator ^=(EventCategory& lhs, EventCategory rhs)
	{
		lhs = static_cast<EventCategory> (
			static_cast<std::underlying_type<EventCategory>::type>(lhs) ^
			static_cast<std::underlying_type<EventCategory>::type>(rhs)
			);

		return lhs;
	}

}
