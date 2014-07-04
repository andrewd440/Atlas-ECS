# Atlas - A Fast, Convenient C++ Entity Component System
An Entity Component System is a software technique using Composition rather than Inheritance to build 
high-performance code-architectures in modern C++ 11. Atlas was designed to take advantage of the decoupling and effeciency 
that this architecture provides.

Atlas is a simple and convenient component entity system that has influences
from the popular Java ECS Artemis
 
## Tutorial
 This simple example showcases Atlas' use of a `PositionComponent` and `VelocityComponent` in conjuction with
 a `MovementSystem` to process the movement of an `Atlas::Entity`.


## Entities
 
`Atlas::Entity`'s are essensially a container of `Atlas::Component`s. Each `Atlas::Entity` has a unique `Atlas::Entity::ID` 
that is used to represent relationships with `Atlas::Component`s. 

All entities are created internally by the `Atlas::EntityManager`. In addition `Atlas::World` provides a delegated function 
to create entities.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Atlas::World world;
Atlas::Entity& entity = world.createEntity();
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
To destroy an `Atlas::Entity`, you simply set it as inactive and it will be destroyed on the next `Atlas::EntityManager::update()`
~~~~~~~~~~~~~~~~~~~~~~~~~
entity.setActive(false);
~~~~~~~~~~~~~~~~~~~~~~~~~

Implementation Information
--------------------------
- Entities are maintained within the `Atlas::EntityManager`
- When Entities are destroyed, their ID is placed into a pool to be reused
- An `Atlas::Entity` holds two bitsets: `Atlas::Component` bits and `Atlas::System` bits
- The `Atlas::Component` bits represent the types of `Atlas::Component`s the entity has
- The `Atlas::System` bits represent the `Atlas::System`s that the entity is included in
 

## Components
 Atlas was designed for users to separate logic and data. Data is placed into components.
 All components inherit from `Atlas::Component`.

Creating a Component
--------------------
~~~~~~~~~~~~~~~~~~~~~~~~~
struct PositionComponent : public Atlas::Component
{
	PositionComponent(int positionX, int positionY) : x(positionX), y(positionY) {}
	int x, y;
}

struct VelocityComponent : public Atlas::Component
{
	VelocityComponent(float velocityX, float velocityY) : x(velocityX), y(velocityY) {}
	float x, y;
}
~~~~~~~~~~~~~~~~~~~~~~~~~

Attaching Components to Entities
--------------------------------
Components can be attached to entities through `Atlas::EntityManager::addComponent()` or `Atlas::Entity::addComponent()`.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
entity.addCompnent(Atlas::Component::Ptr(new PositionComponent(100, 100)));
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Retrieving Components
---------------------
Components can be retrieved through `Atlas::EntityManager::getComponentFor<>()` or `Atlas::Entity::getComponent<>()`. This will return a pointer to the base type for the component.
~~~~~~~~~~~~~~~~~~~~~~~~~~~
PositionComponent* position = entity.getComponent<PositionComponent>();
position->x += 10;
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Implementation Information
--------------------------
- Components are maintained within the `Atlas::EntityManager`
- When a new component type is added, it receives a unique `Atlas::ComponentIdentifier` through the `Atlas::ComponentIdentifierManager`
- Components are stored in a 2D `std::vector` using the ID from the `Atlas::ComponentIdentifier` and `Atlas::Entity::ID` as indexes to it's position in the table

## Systems
Most, if not all, logic should be placed within a System. Each system should inherit from `Atlas::System`.

All systems must implement the `Atlas::System::update()` function and each system is responsible for adding the component types that it is interested in processing.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class MovementSystem : public Atlas::System
{
public:
	MovementSystem::MovementSystem(Atlas::World& world)
		: System(world)
	{
		addComponentType<PositionComponent>();
		addComponentType<VelocityComponent>();
	}

	void MovementSystem::update(float dt)
	{
		Atlas::EntityManager& eManager = getWorld().getEntityManager();
		
		for (const Atlas::Entity::ID& id : getEntities())
		{
			PositionComponent* position = eManager.getComponentFor<PositionComponent>(id);
			VelocityComponent* velocity = eManager.getComponentFor<VelocityComponent>(id);

			position->x += velocity->x * dt;
			position->y += velocity->y * dt;
		}
	}
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
Implementation Information
--------------------------
- Systems only hold `Atlas::Entity::ID`s to refer to entities
- Each time a component is added to or removed from `Atlas::Entity`, all systems recieve a notification that checks if the entity should be processed by the system

 
## Grouping Entities
The `Atlas::GroupManager` provides a grouping mechanism for entities. This allows for entities to be assigned to and retrieved from named groups.

This can be used to process a subset of entities, such as "Enemies", "Bullets", or "Allies".
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Atlas::World world;
Atlas::GroupManager& gManager = world.getGroupManager();
Atlas::Entity& entity = world.createEntity();
 
 // Add Components
 
gManager.addToGroup("Enemies", entity);
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Retrieve and process "Enemies" only:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
for ( const Atlas::Entity::ID& enemyID : gManager.getGroup("Enemies"))
{
	// Do some processing
}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



