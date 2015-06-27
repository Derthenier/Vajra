#pragma once

#ifndef _VAJRA_VERSION_2_GLTEXTURE_HPP_
#define _VAJRA_VERSION_2_GLTEXTURE_HPP_

#include "../Texture.hpp"
//#include <GL/gl.h>
//#include <GL/glu.h>

namespace Vajra
{
    namespace Graphics
    {
        namespace OpenGL
        {
            class GLTexture : public Texture
            {
            public:
                GLTexture( const std::string& name );
                virtual ~GLTexture(void);

                virtual void Load(void);
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_GLTEXTURE_HPP_
