#pragma once

#ifndef _VAJRA_VERSION_2_TEXTFILE_HPP_
#define _VAJRA_VERSION_2_TEXTFILE_HPP_

#include "File.hpp"
#include <vector>

namespace Vajra
{
    namespace File
    {
        class TextFile : public BaseFile
        {
        public:
            static TextFile* Create( const std::string& name, const bool& manageMe = true ) { return new TextFile( name, manageMe ); }

        public:
            TextFile( const std::string& name, const bool& manageMe = true );
            virtual ~TextFile(void);

            virtual void Load(void) { }

            virtual void Open( OpenMode mode );
            virtual void Close(void);

            virtual bool IsOpen(void) const;

            const int SetPrecision( const int newPrecision ) { return static_cast< int >( m_file.precision( newPrecision ) ); }
            const int SetWidth( const int newWidth ) { return static_cast< int >( m_file.width( newWidth ) ); }
            const char SetFill( const char& newFill ) { return m_file.fill( newFill ); }

            virtual unsigned int GetSize(void);
            virtual const std::string& GetFilename(void) const { return m_name; }

            std::vector< std::string > GetLines( std::vector< std::string >& lines );
            std::vector< std::string > GetLines(void);
            std::vector< std::string > GetContents(void) { return GetLines(); }
            std::string GetContentsAsString( std::string& contents );

            template< typename T >
            void Write( const T& data ) { m_file << data; }
            template< typename T >
            void WriteLine( const T& data ) { m_file << data << std::endl; }

            template< typename T >
            friend TextFile& operator << ( TextFile& file, const T& data ) { file.m_file << data; return file; }
            template< typename T >
            friend TextFile& operator >> ( TextFile& file, T& data ) { file.m_file >> data; return file; }

            void WriteLines( const std::vector< std::string >& lines );

        private:
            OpenMode m_mode;
            std::fstream m_file;
        };
    }
}

#endif //_VAJRA_VERSION_2_TEXTFILE_HPP_
