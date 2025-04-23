#pragma once

#ifndef _VAJRA_VERSION_2_GLRENDERER_HPP_
#define _VAJRA_VERSION_2_GLRENDERER_HPP_

#include "../Singleton.hpp"
#include "../Renderer.hpp"

namespace Vajra
{
    namespace Graphics
    {
        namespace OpenGL
        {
            class GLRenderer : public Vajra::Core::Singleton< GLRenderer >, public Renderer
            {
            public:
                virtual ~GLRenderer(void);

            private:
                friend class Vajra::Core::Singleton< GLRenderer >;

                GLRenderer(void);
                GLRenderer( const GLRenderer& glRenderer ) { }
                GLRenderer& operator = ( const GLRenderer& glRenderer ) { }
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_GLRENDERER_HPP_
