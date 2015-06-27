#include "pch.hpp"
#include "File.hpp"
using Vajra::File::BaseFile;

bool BaseFile::Exists( const std::string& name )
{
    std::ifstream file( name.c_str() );
    if( !file.is_open() )
        return false;
    file.close();
    return true;
}
