#pragma once

#ifndef _VAJRA_VERSION_2_BINARYFILE_HPP_
#define _VAJRA_VERSION_2_BINARYFILE_HPP_

#include "File.hpp"

namespace Vajra
{
    namespace File
    {
        class BinaryFile : public BaseFile
        {
        public:
            static BinaryFile* Create( const std::string& name, const bool& manageMe = true ) { return new BinaryFile( name, manageMe ); }

        public:
            BinaryFile( const std::string& name, const bool& manageMe = true );
            virtual ~BinaryFile(void);

            virtual void Load(void) { }

            virtual void Open( OpenMode mode );
            virtual void Close(void);

            virtual bool IsOpen(void) const;

            virtual unsigned int GetSize(void);
            virtual const std::string& GetFilename(void) const { return m_name; }

        private:
            OpenMode m_mode;
            std::fstream m_file;
        };
    }
}

#endif //_VAJRA_VERSION_2_BINARYFILE_HPP_
