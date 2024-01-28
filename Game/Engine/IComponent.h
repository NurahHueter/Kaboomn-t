#pragma once
#include<string>
#include<memory>

namespace mmt_gd
{
	class GameObject;
	class IComponent
	{
	public:
		using Ptr = std::shared_ptr<IComponent>;

		explicit IComponent(GameObject& gameObject) : gameObject(gameObject) {};

		virtual ~IComponent() = default;
		IComponent(IComponent& other) = default;
		IComponent(IComponent&& other) = default;
		IComponent& operator=(IComponent& other) = delete;
		IComponent& operator=(IComponent&& other) = delete;

		GameObject& getGameObject() const
		{
			return gameObject;
		}

		const std::string& getId() const { return id; }
		void setId(const std::string& newId) { id = newId; }

		virtual bool init() = 0;
		virtual void update(float deltaTime) = 0;

	protected:
		std::string id;
		GameObject& gameObject;
	};
}