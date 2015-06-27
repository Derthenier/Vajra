#pragma once

#ifndef _VAJRA_VERSION_2_D3DINDEXBUFFER_HPP_
#define _VAJRA_VERSION_2_D3DINDEXBUFFER_HPP_

struct IDirect3DIndexBuffer9;

namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            class D3DRenderer::D3DIndexBuffer
            {
            public:
                D3DIndexBuffer( const D3DRenderer& renderer );
                ~D3DIndexBuffer(void);

                IDirect3DIndexBuffer9* GetIndexBuffer( const unsigned int& numIndices, short* indices );
                void Release(void);

            private:
                const D3DRenderer& m_renderer;
                IDirect3DIndexBuffer9* m_ib;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_D3DINDEXBUFFER_HPP_
