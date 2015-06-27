#pragma once

#ifndef _VAJRA_VERSION_2_OBJECT_HPP_
#define _VAJRA_VERSION_2_OBJECT_HPP_

#include <string>
#include <map>
#include "Singleton.hpp"

namespace Vajra
{
    namespace Graphics
    {
        class Object
        {
        public:
            Object( const std::string& id );
            virtual ~Object(void);

            virtual const std::string& GetId(void) const;

            virtual const bool& IsVisible(void) const;

            virtual void Update( float delta ) = 0;
            virtual void Render( float delta ) = 0;

        protected:
            std::string m_id;

            bool m_visible; // whether this object is visible for GameScreen to update and render?
        };

        class ObjectManager : public Vajra::Core::Singleton< ObjectManager >
        {
            friend class Vajra::Core::Singleton< ObjectManager >;

        public:
            virtual ~ObjectManager(void);

            void AddGameObject( Object& obj );
            void RemoveGameObject( const std::string& objId );
            Object* GetGameObject( const std::string& objId );

        private:
            ObjectManager(void);

        private:
            std::map< std::string, Object* > m_gameObjects;
        };
    }
}

#endif //_VAJRA_VERSION_2_OBJECT_HPP_
