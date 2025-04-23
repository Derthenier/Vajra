#pragma once

#ifndef _VAJRA_VERSION_2_EVENT_MANAGER_HPP_
#define _VAJRA_VERSION_2_EVENT_MANAGER_HPP_

#include "Singleton.hpp"
#include <string>

namespace Vajra
{
	namespace Core
	{
		class Event
		{
		public:
			Event( const unsigned long& eventId );
			virtual ~Event(void);

		protected:
			unsigned long m_eventId;
			std::string m_firer;

		};

		class EventSystem
		{
		};

		class EventManager : public Vajra::Core::Singleton< EventManager >
		{
			friend class Vajra::Core::Singleton< EventManager >;

		public:
			virtual ~EventManager(void);

			void Initialize(void);
			void Shutdown(void);

		private:
			EventManager(void) { }
			EventManager( const EventManager& e ) { }
			EventManager& operator = ( const EventManager& e ) { }

		private:

		};
	}
}

#endif // _VAJRA_VERSION_2_EVENT_MANAGER_HPP_

