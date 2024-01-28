#pragma once

#include "IComponent.h"

#include <SFML/Graphics.hpp>
#include <list>
#include <string>
#include "ObjectTypes.h"
#include <utility>

namespace mmt_gd
{
    class GameObject final : public sf::Transformable
    {
    public:
        using Ptr = std::shared_ptr<GameObject>;

        explicit GameObject(std::string id) : m_id(std::move(id))
        {
        }

        /**
         * \brief Add a component to the game object. Internally the game object
         * identifies if it's a drawable component to call it's draw
         * function or a general update component to call it's update
         * function.
         */
        void addComponent(const IComponent::Ptr& component);

        /**
         * \brief Remove a component from the game object.
         */
        void removeComponent(const IComponent::Ptr& component);

        /**
         * \brief Get a component of the game object by it's type.
         * \return nullptr if no component of the given type was found.
         */
        template <typename TComponent>
        std::shared_ptr<TComponent> getComponent()
        {
            for (auto& component : m_componentList)
            {
                if (auto cmp = std::dynamic_pointer_cast<TComponent>(component))
                    return cmp;
            }
            return nullptr;
        }

        /**
         * \brief Get a component of the game object by it's type.
         * \return empty vector if no component of the given type was found.
         */
        template <typename TComponent>
        std::vector<std::shared_ptr<TComponent>> getComponents()
        {
            std::vector<std::shared_ptr<TComponent>> result{};
            for (auto& component : m_componentList)
            {
                if (std::shared_ptr<TComponent> cmp = std::dynamic_pointer_cast<TComponent>(component))
                {
                    result.push_back(cmp);
                }
            }
            return std::move(result);
        }

        bool init() const;

        void update(float deltaTime) const;
        void draw() const;

        bool isMarkedForDelete() const
        {
            return m_wantToDie;
        }

        void markForDelete()
        {
            m_wantToDie = true;
        }

        bool isActive() const
        {
            return m_isActive;
        }

        void setActive(const bool isActive)
        {
            m_isActive = isActive;
        }

        std::string getId() 
        {
            return m_id;
        }

        void setId(const std::string& id)
        {
            m_id = id;
        }

        int getPlayerIdx() const
        {
            return m_idx;
        }

        void setPlayerIdx(const int& idx)
        {
            m_idx = idx;
        }

        ObjectType getType() const
        {
            return m_type;
        }

        void setType(const ObjectType& type)
        {
            m_type = type;
        }

    protected:
        std::string m_id = "unnamed"; ///< unique name of object, e.g. player
        int m_idx = 0; ///< unique name of object, e.g. player
        bool        m_wantToDie = false;
        bool        m_isActive = true;
        ObjectType m_type = Default;

        std::vector<IComponent::Ptr> m_componentList;
    };
}

