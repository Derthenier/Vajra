#pragma once

#ifndef _VAJRA_VERSION_2_MESH_COMPONENT_HPP_
#define _VAJRA_VERSION_2_MESH_COMPONENT_HPP_

#ifndef NULL
#define NULL 0
#endif // NULL

namespace Vajra
{
    namespace Graphics
    {
        class Texture;

        class MeshComponent
        {
        public:
            MeshComponent(void);
            virtual ~MeshComponent(void);

            virtual void SetTexture( Texture* texture = NULL ) { m_texture = texture; }
            virtual Texture* GetTexture(void) { return m_texture; }

        private:
            MeshComponent( const MeshComponent& mc ) : m_texture( mc.m_texture ) { }
            MeshComponent& operator = ( const MeshComponent& mc ) { }

        protected:
            Texture* m_texture;
        };
    }
}

#endif //_VAJRA_VERSION_2_MESH_COMPONENT_HPP_
