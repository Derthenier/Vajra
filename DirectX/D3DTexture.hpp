#pragma once

#ifndef _VAJRA_VERSION_2_D3DTEXTURE_HPP_
#define _VAJRA_VERSION_2_D3DTEXTURE_HPP_

#include "../Texture.hpp"

struct IDirect3DTexture9;

namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            class D3DTexture : public Vajra::Graphics::Texture
            {
            public:
                D3DTexture( const std::string& name );
                virtual ~D3DTexture(void);

                virtual const unsigned int& Width(void) const;
                virtual const unsigned int& Height(void) const;
                virtual void Load(void);

                IDirect3DTexture9* Data(void) const { return m_texture; }

            private:
                IDirect3DTexture9* m_texture;
                unsigned int m_width;
                unsigned int m_height;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_D3DTEXTURE_HPP_
