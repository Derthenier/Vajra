#pragma once

#ifndef _VAJRA_VERSION_2_TEXTURE_HPP_
#define _VAJRA_VERSION_2_TEXTURE_HPP_

#include "Resource.hpp"

namespace Vajra
{
    namespace Graphics
    {
        class Texture : public Vajra::Core::Resource
        {
            friend class Vajra::Core::ResourceManager;

        public:
            virtual const unsigned int& Width(void) const = 0;
            virtual const unsigned int& Height(void) const = 0;

        protected:
            Texture( const std::string& name );
            virtual ~Texture(void) { };

            virtual void Load(void) = 0;

            static Texture* Create( const std::string& name );
        };
    }
}

#endif //_VAJRA_VERSION_2_TEXTURE_HPP_
