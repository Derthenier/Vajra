#include "pch.hpp"
#include "D3DRenderer.hpp"
#include "D3DIndexBuffer.hpp"
using Vajra::Graphics::DirectX::D3DRenderer;

#include <d3d9.h>
#include <d3dx9.h>

D3DRenderer::D3DIndexBuffer::D3DIndexBuffer( const D3DRenderer& renderer )
: m_renderer( renderer )
, m_ib( NULL )
{
}

D3DRenderer::D3DIndexBuffer::~D3DIndexBuffer(void)
{
    if( NULL != m_ib )
    {
        m_ib->Release();
        m_ib = NULL;
    }
}

LPDIRECT3DINDEXBUFFER9 D3DRenderer::D3DIndexBuffer::GetIndexBuffer( const unsigned int& numIndices, short* indices )
{
    HRESULT hr = m_renderer.GetDevice()->CreateIndexBuffer( sizeof( short ) * numIndices, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_ib, NULL );
    if( FAILED( hr ) )
        return NULL;

    unsigned char* pIndices = NULL;

    hr = m_ib->Lock( 0, 0, ( void** )&pIndices, 0 );
    if( FAILED( hr ) )
    {
        m_ib->Release();
        return NULL;
    }

    CopyMemory( pIndices, indices, sizeof( short ) * numIndices );

    m_ib->Unlock();
    return m_ib;
}

void D3DRenderer::D3DIndexBuffer::Release(void)
{
    if( NULL != m_ib )
    {
        m_ib->Release();
        m_ib = NULL;
    }
}
