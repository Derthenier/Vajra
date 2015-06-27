#pragma once

#ifndef _VAJRA_VERSION_2_IDMANAGER_HPP_
#define _VAJRA_VERSION_2_IDMANAGER_HPP_

#include <map>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace Vajra
{
    namespace Core
    {
        class IdManager
        {
        public:
            typedef std::map< std::string, std::string > NameIdMap;

            static const std::string& GetId( const std::string& name );

        private:
            IdManager(void);
            IdManager( const IdManager& manager ) { }
            IdManager& operator = ( const IdManager& manager ) { }
            ~IdManager(void);

            static std::string CreateId( const std::string& name );

            static NameIdMap s_ids;
        };
    }
}

#endif //_VAJRA_VERSION_2_IDMANAGER_HPP_
