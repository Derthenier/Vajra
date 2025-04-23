#pragma once

#ifndef _VAJRA_VERSION_2_RENDERER_HPP_
#define _VAJRA_VERSION_2_RENDERER_HPP_

#include "Vector.hpp"
using Vajra::Math::Vector;

#include "Texture.hpp"
using Vajra::Graphics::Texture;

#include <string>

namespace Vajra
{
    namespace Graphics
    {
        class Renderer
        {
        public:
            virtual ~Renderer(void);

            virtual void Initialize( const unsigned int& screenWidth, const unsigned int& screenHeight, const unsigned int& screenBpp = 32, const bool& isFullscreen = false ) = 0;
            virtual void Setup( const float& fieldOfViewInDegrees, const float& zNear, const float& zFar ) = 0;

            virtual void BeginFrame(void) = 0;
            virtual void EndFrame(void) = 0;

            virtual void DrawPoint( const Vector& position ) = 0;
            virtual void DrawLine( const Vector& start, const Vector& end ) = 0;
            virtual void DrawTriangle( const Vector& v1, const Vector& v2, const Vector& v3, const Vector& scale = Vector::One, const float& rotation = 0.0f ) = 0;
            virtual void DrawCircle( const Vector& center, const float& radius, const int& numSegments = 10 ) = 0;
            virtual void DrawRectangle( const Vector& topLeft, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f );
            virtual void DrawRectangle( const Vector& topLeft, const Vector& bottomRight, const Vector& scale = Vector::One, const float& rotation = 0.0f );
            virtual void DrawRectangle( const float& x, const float& y, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f ) = 0;

            virtual void DrawTexturedRectangle( const Texture* texture, const Vector& topLeft, const Vector& bottomRight, const Vector& scale = Vector::One, const float& rotation = 0.0f );
            virtual void DrawTexturedRectangle( const Texture* texture, const Vector& topLeft, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f );
            virtual void DrawTexturedRectangle( const Texture* texture, const float& x, const float& y, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f ) = 0;

            virtual void DrawString( const std::string& text, const float& x, const float& y, const int& size = 10 ) = 0;

            virtual const unsigned int& GetWidth(void) const = 0;
            virtual const unsigned int& GetHeight(void) const = 0;

        protected:
            Renderer(void);
            Renderer( const Renderer& renderer ) { }
            Renderer& operator = ( const Renderer& renderer ) { }
        };

        class RenderManager
        {
        public:
            static Renderer& GetRenderer(void);

        private:
            RenderManager(void) { }
            explicit RenderManager( const RenderManager& rm ) { }
            ~RenderManager(void) { }
            RenderManager& operator = ( const RenderManager& rm ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_RENDERER_HPP_
