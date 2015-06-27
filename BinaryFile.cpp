#include "pch.hpp"
#include "Definitions.hpp"
#include "Logger.hpp"
#include "BinaryFile.hpp"
using Vajra::File::BinaryFile;
using Vajra::File::OpenMode;

BinaryFile::BinaryFile( const std::string& name, const bool& manageMe )
: BaseFile( name, manageMe )
{
}

BinaryFile::~BinaryFile(void)
{
    if( m_file.is_open() )
        m_file.close();
}

void BinaryFile::Open( OpenMode mode )
{
    m_mode = mode;

    switch( mode )
    {
    case READ:
        m_file.open( m_name.c_str(), std::ios::in | std::ios::binary );
        break;

    case WRITE:
        m_file.open( m_name.c_str(), std::ios::out | std::ios::binary );
        break;

    default:
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Invalid mode specified in BinaryFile::Open." );
        break;
    }
}

void BinaryFile::Close(void)
{
    if( m_file.is_open() )
        m_file.close();
}

bool BinaryFile::IsOpen(void) const
{
    return m_file.is_open();
}

unsigned int BinaryFile::GetSize(void)
{
    if( READ != m_mode )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogWarning, "Trying to get size of a file opened in write mode" );
        return static_cast< unsigned int >( -1 );
    }

    std::fstream::pos_type curPos = m_file.tellg();
    m_file.seekg( 0, std::ios::beg );
	std::streamoff begin = m_file.tellg();
    m_file.seekg( 0, std::ios::end );
	std::streamoff end = m_file.tellg();
	std::streamoff size = end - begin;

    m_file.seekg( curPos );

    return static_cast< unsigned int >( size );
}
