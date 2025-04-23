#include "pch.hpp"
#include "ScriptManager.hpp"
using Vajra::Scripts::Script;
using Vajra::Scripts::ScriptSystem;

#include "Logger.hpp"

/******************************************************************************
******************************************************************************/

Vajra::Scripts::LuaStackRestorer::LuaStackRestorer(void)
{
    m_state = ScriptSystem::GetInstance().GetLuaState();
    m_top = lua_gettop( m_state );
}

Vajra::Scripts::LuaStackRestorer::~LuaStackRestorer(void)
{
    lua_settop( m_state, m_top );
}

/******************************************************************************
******************************************************************************/

Vajra::Scripts::LuaThis::LuaThis( const int& reference )
: m_oldReference( 0 )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state != NULL )
    {
        // Save the old "this" table
        lua_getglobal( state, "this" );
        m_oldReference = luaL_ref( state, LUA_REGISTRYINDEX );

        // Replace it with our new "this" table
        lua_rawgeti( state, LUA_REGISTRYINDEX, reference );
        lua_setglobal( state, "this" );
    }
}

Vajra::Scripts::LuaThis::~LuaThis(void)
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state != NULL )
    {
        if( m_oldReference > 0 )
        {
            // Replace the old "this" table
            lua_rawgeti( state, LUA_REGISTRYINDEX, m_oldReference );
            lua_setglobal( state, "this" );
            luaL_unref( state, LUA_REGISTRYINDEX, m_oldReference );
        }
    }
}

/******************************************************************************
******************************************************************************/

int ScriptSystem::PrintMessage( lua_State* state )
{
#ifdef _DEBUG
    assert( lua_isstring( state, 1 ) );

    const char* message = lua_tostring( state, 1 );
    lua_Debug ar;
    memset( &ar, 0, sizeof( ar ) );
    lua_getstack( state, 1, &ar );
    lua_getinfo( state, "Snl", &ar );

    const char* str = ar.source;
    Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Script: %s -- at %s(%d)", message, str, ar.currentline );
#else
	Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "In Script" );
#endif
	return 0;
}

void ScriptSystem::Panic( lua_State* state )
{
}

ScriptSystem::ScriptSystem(void)
: Vajra::Core::Singleton< ScriptSystem >()
, m_state( luaL_newstate() )
{
}

ScriptSystem::~ScriptSystem(void)
{
    if( m_state != NULL )
    {
        lua_close( m_state );
        m_state = NULL;
    }
}

void ScriptSystem::Initialize(void)
{
    if( m_state == NULL )
        return;
	
	luaL_openlibs( m_state );

#if defined( _DEBUG )
	lua_pushcfunction( m_state, luaopen_debug );
	lua_pushliteral( m_state, LUA_DBLIBNAME );
	lua_call( m_state, 1, 0 );
#endif

    lua_pushcclosure( m_state, ( lua_CFunction ) ScriptSystem::PrintMessage, 0 );
    lua_setglobal( m_state, "trace" );
    lua_atpanic( m_state, ( lua_CFunction ) ScriptSystem::Panic );
}

bool ScriptSystem::RunScript( const std::string& scriptFileName )
{
    if( luaL_loadfile( m_state, scriptFileName.c_str() ) == 0 )
    {
        if( lua_pcall( m_state, 0, LUA_MULTRET, 0 ) == 0 )
            return true;
        else
            ScriptSystem::PrintMessage( m_state );
    }

    return false;
}

bool ScriptSystem::RunBuffer( const unsigned char* buffer, const unsigned int& bufferLength, const char* strName /* = 0 */ )
{
    if( strName == NULL )
        strName = "Temp";

    if( luaL_loadbuffer( m_state, ( const char* )buffer, bufferLength, strName ) == 0 )
    {
        if( lua_pcall( m_state, 0, LUA_MULTRET, 0 ) == 0 )
            return true;
        else
            ScriptSystem::PrintMessage( m_state );
    }

    return false;
}

bool ScriptSystem::CallFunction( int numberOfArguments, int numberOfReturns /* = 0 */ )
{
    if( lua_isfunction( m_state, -numberOfArguments - 1 ) )
    {
        if( lua_pcall( m_state, numberOfArguments, numberOfReturns, 0 ) == 0 )
            return true;
    }

    ScriptSystem::PrintMessage( m_state );
    return false;
}

/******************************************************************************
******************************************************************************/
int Script::LuaCallback( lua_State* state )
{
    int numberIdx = lua_upvalueindex( 1 );
    int numberReturnsOnStack = 0;

    bool success = false;

    // Check for the "this" table
    if( lua_istable( state, 1 ) )
    {
        lua_rawgeti( state, 1, 0 );
        if( lua_islightuserdata( state, -1 ) )
        {
            Script* script = (Script*) lua_touserdata( state, -1 );

            int methodIdx = static_cast< int >( lua_tonumber( state, numberIdx ) ); 

            assert( !( methodIdx > script->NumberOfMethods() ) );

            // Reformat the stack so the parameters are correct
            lua_remove( state, 1 );
            lua_remove( state, -1 );

            numberReturnsOnStack = script->ScriptCalling( methodIdx );

            success = true;
        }
    }

    if( !success )
    {
        lua_pushstring( state, "LuaCallback: Failed to call the class function." );
        lua_error( state );
    }

    return numberReturnsOnStack;
}

Script::Script( const std::string& name )
: m_numMethods( 0 )
, m_numArguments( 0 )
, m_thisReference( 0 )
, m_scriptFilename( name )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return;

    lua_newtable( state );
    m_thisReference = luaL_ref( state, LUA_REGISTRYINDEX );

    // Save "this" table
    Vajra::Scripts::LuaStackRestorer res;
    {
        lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );
        lua_pushlightuserdata( state, ( void* )this );
        lua_rawseti( state, -2, 0 );
    }
}

Script::~Script(void)
{
    Vajra::Scripts::LuaStackRestorer res;
    {
        lua_State* state = ScriptSystem::GetInstance().GetLuaState();
        if( state != NULL )
        {
            lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );
            lua_pushnil( state );
            lua_rawseti( state, -2, 0 );
        }
    }
}

void Script::CompileScript(void)
{
    LuaThis luaThis( m_thisReference );
    ScriptSystem::GetInstance().RunScript( m_scriptFilename );
}

int Script::RegisterMethod( const std::string& exposedMethodName )
{
    int methodIdx = -1;
    Vajra::Scripts::LuaStackRestorer res;
    {
        methodIdx = ++m_numMethods;

        lua_State* state = ScriptSystem::GetInstance().GetLuaState();
        if( state == NULL )
            return methodIdx;

        lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );
        lua_pushstring( state, exposedMethodName.c_str() );
        lua_pushnumber( state, static_cast< lua_Number >( methodIdx ) );
        lua_pushcclosure( state, Script::LuaCallback, 1 );
        lua_settable( state, -3 );
    }

    return methodIdx;
}

bool Script::SelectScriptFunction( const std::string& functionName )
{
    if( functionName.empty() )
        return false;

    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return false;

    lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );
    lua_pushstring( state, functionName.c_str() );
    lua_rawget( state, -2 );
    lua_remove( state, -2 );

    lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );

    if( !lua_isfunction( state, -2 ) )
    {
        lua_pop( state, 2 );
        return false;
    }
    else
    {
        m_currentScriptFunction.clear();
        m_currentScriptFunction = functionName;
        m_numArguments = 0;
    }

    return true;
}

bool Script::HasFunction( const std::string& functionName ) const
{
    if( functionName.empty() )
        return false;

    LuaStackRestorer rs;
    {
        lua_State* state = ScriptSystem::GetInstance().GetLuaState();
        if( state == NULL )
            return false;

        lua_rawgeti( state, LUA_REGISTRYINDEX, m_thisReference );
        lua_pushstring( state, functionName.c_str() );
        lua_rawget( state, -2 );
        lua_remove( state, -2 );

        if( lua_isfunction( state, -1 ) )
            return true;
    }

    return false;
}

void Script::AddParam( const int& param )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return;

    lua_pushnumber( state, param );
    ++m_numArguments;
}

void Script::AddParam( const float& param )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return;

    lua_pushnumber( state, param );
    ++m_numArguments;
}

void Script::AddParam( const char* param )
{
    if( param == NULL )
        return;

    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return;

    lua_pushstring( state, param );
    ++m_numArguments;
}

int Script::GetIntParam( const int& paramPosition )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return 0;

    int number = static_cast< int >( lua_tonumber( state, -paramPosition - 1 ) );
    return number;
}

float Script::GetFloatParam( const int& paramPosition )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return 0;

    float number = static_cast< float >( lua_tonumber( state, -paramPosition - 1 ) );
    return number;
}

std::string Script::GetStringParam( const int& paramPosition )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return 0;

    std::string str( lua_tostring( state, -paramPosition - 1 ) );
    return str;
}

bool Script::Run( int numberOfReturnValues /* = 0 */ )
{
    lua_State* state = ScriptSystem::GetInstance().GetLuaState();
    if( state == NULL )
        return false;

    bool success = ScriptSystem::GetInstance().CallFunction( m_numArguments + 1, numberOfReturnValues );
    if( success && numberOfReturnValues > 0 )
    {
        HandleReturns( m_currentScriptFunction );
        lua_pop( state, numberOfReturnValues );
    }

    return success;
}
