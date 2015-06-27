#pragma once

#ifndef _VAJRA_VERSION_2_VIDEOSYSTEM_HPP_
#define _VAJRA_VERSION_2_VIDEOSYSTEM_HPP_

#include <string>
#include <map>

namespace Vajra
{
	namespace Video
	{
		class VideoSystem
		{
		public:
			VideoSystem(void);
			virtual ~VideoSystem(void);

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;

			virtual void Load( const std::string& loadFile = "" );

			virtual void Play( const std::string& name ) = 0;
			virtual void Pause(void) = 0;
			virtual void Resume(void) = 0;
			virtual void Stop(void) = 0;

		protected:
			std::map< std::string, std::string > m_videos;
			bool m_ready;
		};

		class VideoManager
		{
		public:
			static VideoSystem& GetVideoSystem(void);

		private:
			VideoManager(void);
			~VideoManager(void);
			VideoManager( const VideoManager& ss ) { }
			VideoManager& operator = ( const VideoManager& ss ) { }
		};
	}
}

#endif //_VAJRA_VERSION_2_VIDEOSYSTEM_HPP_
