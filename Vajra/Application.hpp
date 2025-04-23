#pragma once

#ifndef _VAJRA_VERSION_2_APPLICATION_HPP_
#define _VAJRA_VERSION_2_APPLICATION_HPP_

#include <string>
#include "Timer.hpp"

namespace Vajra
{
    namespace Core
    {
        class Application
        {
        public:
            virtual ~Application(void);

            void Initialize( const std::string& appName, const int& windowWidth, const int& windowHeight, const bool& isFullscreen = false );
            const std::string& GetAppName(void) const;
            const int& GetWindowWidth(void) const;
            const int& GetWindowHeight(void) const;

            virtual void SetTitle( const std::string& title ) = 0;

            virtual void Run( const Vajra::Core::Timer* const timer ) = 0;

            virtual void Shutdown(void) = 0;

            void (*RunFrame)( float delta );

        protected:
            Application(void);
            Application( const Application& app ) { }
            Application& operator = ( const Application& app ) { }

            virtual void Initialize( const bool& isFullscreen ) = 0;

        protected:
            std::string m_appName;
            int m_width;
            int m_height;
        };

        class ApplicationManager
        {
        public:
            static Application& GetApplication(void);

        private:
            explicit ApplicationManager(void) { }
            explicit ApplicationManager( const ApplicationManager& am ) { }
            ~ApplicationManager(void) { }
            ApplicationManager& operator = ( const ApplicationManager& am ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_APPLICATION_HPP_
