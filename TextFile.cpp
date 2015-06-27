#include "pch.hpp"
#include "Definitions.hpp"
#include "Logger.hpp"
#include "TextFile.hpp"
using Vajra::File::TextFile;
using Vajra::File::OpenMode;


TextFile::TextFile( const std::string& name, const bool& manageMe )
: BaseFile( name, manageMe )
{
}

TextFile::~TextFile(void)
{
    if( m_file.is_open() )
        m_file.close();
}

void TextFile::Open( OpenMode mode )
{
    m_mode = mode;

    switch( mode )
    {
    case READ:
		{
			m_file.open( m_name, std::ios_base::in );
			//if( ( m_file.rdstate() & std::ifstream::failbit ) != 0 )
				//Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Couldn't open %s for reading in TextFile::Open", m_name.c_str() );
		}
        break;

    case WRITE:
		{
			m_file.open( m_name, std::ios::out );
			if( !m_file.is_open() )
				Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Couldn't open %s for writing in TextFile::Open", m_name.c_str() );
		}
        break;

    default:
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Invalid mode specified in TextFile::Open." );
        break;
    }
}

void TextFile::Close(void)
{
    if( m_file.is_open() )
        m_file.close();
}

bool TextFile::IsOpen(void) const
{
    return m_file.is_open();
}

unsigned int TextFile::GetSize(void)
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

std::vector< std::string > TextFile::GetLines( std::vector< std::string >& lines )
{
    if( WRITE == m_mode )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogWarning, "Trying to read from a write-only file" );
        return std::vector< std::string >();
    }

    std::fstream::pos_type curPos = m_file.tellg();
    m_file.seekg( 0, std::ios::beg );

    while( !m_file.eof() )
    {
        char* buffer = new char[ 1024 ];
        std::memset( buffer, 0, sizeof( char ) * 1024 );

        m_file.getline( buffer, sizeof( char ) * 1024 );
        std::string line( buffer );
        if( !line.empty() )
            lines.push_back( std::string( buffer ) );

        delete [] buffer;
    }

    m_file.seekg( curPos );

    return lines;
}

std::vector< std::string > TextFile::GetLines(void)
{
    std::vector< std::string > lines;
    lines = GetLines( lines );
    return lines;
}

std::string TextFile::GetContentsAsString( std::string& contents )
{
    contents.clear();

    std::vector< std::string > lines;
    GetLines( lines );

    std::vector< std::string >::iterator itr = lines.begin();
    std::vector< std::string >::iterator end = lines.end();

    while( itr != end )
    {
        contents.append( *itr );

        ++itr;
    }

    return contents;
}

void TextFile::WriteLines( const std::vector< std::string >& lines )
{
    std::vector< std::string >::const_iterator itr = lines.begin();
    std::vector< std::string >::const_iterator end = lines.end();

    while( itr != end )
    {
        m_file << itr->c_str();
        ++itr;
        if( itr != end )
            m_file << std::endl;
    }
}


