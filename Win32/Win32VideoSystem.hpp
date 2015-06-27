#pragma once

#ifndef _VAJRA_VERSION_2_WIN32VIDEOSYSTEM_HPP_
#define _VAJRA_VERSION_2_WIN32VIDEOSYSTEM_HPP_

#include "../Singleton.hpp"
#include "../VideoManager.hpp"

struct IGraphBuilder;
struct IMediaControl;
struct IVideoWindow;

namespace Vajra
{
	namespace Video
	{
		namespace Win32
		{
			class Win32VideoSystem : public Vajra::Core::Singleton< Win32VideoSystem >, public Vajra::Video::VideoSystem
			{
				friend class Vajra::Core::Singleton< Win32VideoSystem >;

			public:
				virtual ~Win32VideoSystem(void);

				virtual void Initialize(void);
				virtual void Shutdown(void);
				
				virtual void Play( const std::string& name );
				virtual void Pause(void);
				virtual void Resume(void);
				virtual void Stop(void);

			private:
				Win32VideoSystem(void);
				explicit Win32VideoSystem( const Win32VideoSystem& wvs ) { }
				Win32VideoSystem& operator = ( const Win32VideoSystem& wvs ) { }

			private:
				IGraphBuilder* m_graph;
				IMediaControl* m_control;
				IVideoWindow* m_vw;

				bool m_isPlaying;
			};
		}
	}
}

#endif // _VAJRA_VERSION_2_WIN32VIDEOSYSTEM_HPP_
