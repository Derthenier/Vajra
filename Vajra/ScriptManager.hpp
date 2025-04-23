#pragma once

#ifndef _VAJRA_VERSION_2_SCRIPTMANAGER_HPP_
#define _VAJRA_VERSION_2_SCRIPTMANAGER_HPP_

/***
   Copied and modified from LuaVirtualMachine.h & .cpp files
   written by Richard Shephard
   Modified because I did not like the class naming convention
   Otherwise, everything about lua c++ is exactly the same.
***/

#include "Resource.hpp"
#include "Singleton.hpp"
#include <Lua/lua.hpp>

namespace Vajra
{
    namespace Scripts
    {
        class LuaStackRestorer
        {
        public:
            LuaStackRestorer(void);
            ~LuaStackRestorer(void);

        private:
            lua_State* m_state;
            int m_top;
        };

        class LuaThis
        {
        public:
            LuaThis( const int& reference );
            ~LuaThis(void);

        private:
            int m_oldReference;
        };

        class ScriptSystem : public Vajra::Core::Singleton< ScriptSystem >
        {
            friend class Vajra::Core::Singleton< ScriptSystem >;

        public:
            virtual ~ScriptSystem(void);

            void Initialize(void);

            bool RunScript( const std::string& scriptFilename );
            bool RunBuffer( const unsigned char* buffer, const unsigned int& bufferLength, const char* str = NULL );

            bool CallFunction( int numberOfArguments, int numberOfReturns = 0 );

            lua_State* GetLuaState(void) const { return m_state; }

        private:
            ScriptSystem(void);

            static int PrintMessage( lua_State* state );
            static void Panic( lua_State* state );

        private:
            lua_State* m_state;
        };

        class Script
        {
        public:
            int RegisterMethod( const std::string& exposedMethodName );
            bool SelectScriptFunction( const std::string& functionName );

            void AddParam( const int& intVal );
            void AddParam( const float& floatVal );
            void AddParam( const char* string );

            int GetIntParam( const int& paramPosition = 0 );
            float GetFloatParam( const int& paramPosition = 0 );
            std::string GetStringParam( const int& paramPosition = 0 );

            bool Run( int numberOfReturnValues = 0 );

            const int& NumberOfMethods(void) const { return m_numMethods; }
            bool HasFunction( const std::string& functionName ) const;

            void CompileScript(void);

            virtual int ScriptCalling( const int& methodIdx ) = 0;
            virtual void HandleReturns( const std::string& function ) = 0;

        protected:
            Script( const std::string& name );
            virtual ~Script(void);

            static int LuaCallback( lua_State* state );

        protected:
            int m_numMethods;
            int m_numArguments;
            int m_thisReference;
            std::string m_scriptFilename;
            std::string m_currentScriptFunction;
        };
    }
}

#endif //_VAJRA_VERSION_2_SCRIPTMANAGER_HPP_
