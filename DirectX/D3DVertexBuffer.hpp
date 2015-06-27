#pragma once

#ifndef _VAJRA_VERSION_2_D3DVERTEXBUFFER_HPP_
#define _VAJRA_VERSION_2_D3DVERTEXBUFFER_HPP_

struct IDirect3DVertexBuffer9;

namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            #define D3DTextured_Vertex ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX1 )
            #define D3DUntextured_Vertex ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | D3DFVF_TEX0 )

            struct D3DRenderer::D3DVertex
            {
                float X;
                float Y;
                float Z;
                float NormalX;
                float NormalY;
                float NormalZ;
                unsigned long Diffuse;
                unsigned long Specular;
                float U;
                float V;
            };

            class D3DRenderer::D3DVertexBuffer
            {
            public:
                D3DVertexBuffer( const D3DRenderer& renderer );
                ~D3DVertexBuffer(void);

                IDirect3DVertexBuffer9* GetVertexBuffer( const unsigned int& numVertices, D3DVertex* vertices );
                void Release(void);

            private:
                const D3DRenderer& m_renderer;
                IDirect3DVertexBuffer9* m_vb;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_D3DVERTEXBUFFER_HPP_
