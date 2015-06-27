#include "pch.hpp"
#include "D3DRenderer.hpp"
#include "D3DVertexBuffer.hpp"
using Vajra::Graphics::DirectX::D3DRenderer;

#include <d3d9.h>
#include <d3dx9.h>

D3DRenderer::D3DVertexBuffer::D3DVertexBuffer( const D3DRenderer& renderer )
: m_renderer( renderer )
, m_vb( NULL )
{
}

D3DRenderer::D3DVertexBuffer::~D3DVertexBuffer(void)
{
    if( NULL != m_vb )
    {
        m_vb->Release();
        m_vb = NULL;
    }
}

LPDIRECT3DVERTEXBUFFER9 D3DRenderer::D3DVertexBuffer::GetVertexBuffer( const unsigned int& numVertices, D3DVertex* vertices )
{
    HRESULT hr = m_renderer.GetDevice()->CreateVertexBuffer( sizeof( D3DVertex ) * numVertices, D3DUSAGE_WRITEONLY, D3DTextured_Vertex, D3DPOOL_MANAGED, &m_vb, NULL );
    if( FAILED( hr ) )
        return NULL;

    unsigned char* pVertices = NULL;

    hr = m_vb->Lock( 0, sizeof( D3DVertex ), ( void** )&pVertices, 0 );
    if( FAILED( hr ) )
    {
        m_vb->Unlock();
        return NULL;
    }

    CopyMemory( pVertices, vertices, sizeof( D3DVertex ) * numVertices );

    m_vb->Unlock();
    return m_vb;
}

void D3DRenderer::D3DVertexBuffer::Release(void)
{
    if( NULL != m_vb )
    {
        m_vb->Release();
        m_vb = NULL;
    }
}
