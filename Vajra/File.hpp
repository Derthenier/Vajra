#pragma once

#ifndef _VAJRA_VERSION_2_FILE_HPP_
#define _VAJRA_VERSION_2_FILE_HPP_

#include <fstream>
#include <string>
#include "Resource.hpp"

namespace Vajra
{
    namespace File
    {
        enum OpenMode
        {
            READ = 1,
            WRITE = 2
        };

        class BaseFile : public Vajra::Core::Resource
        {
        public:
            BaseFile( const std::string& name, const bool& manageMe = true ) : Vajra::Core::Resource( name, manageMe ) { }
            virtual ~BaseFile(void) { };

            virtual void Load(void) = 0;

            virtual void Open( OpenMode mode ) = 0;
            virtual void Close(void) = 0;

            virtual bool IsOpen(void) const = 0;

            virtual unsigned int GetSize(void) = 0;
            virtual const std::string& GetFilename(void) const = 0;

            static bool Exists( const std::string& name );

        protected:
            BaseFile& operator = ( const BaseFile& f ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_FILE_HPP_
