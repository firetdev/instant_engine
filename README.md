# Instant Engine
### A 2D game engine with C++ and SFML
Instant Engine is a 2D game engine built with C++ and SFML.  It's designed to give you the classic pure C++ gamedev experience without having to code everything from scratch.

 
**Instant Engine v1 is not yet completed and I do not recommend attempting to create a game with the current version**

## Design and features
Instant Engine uses a hybrid of a data-oriented ECS (Entity-Component System) and an object-oriented inheritence system.  Games are made up of **Scenes**, which in turn are made up of
**Entities** (and, eventually, **UIElements**).

An **Entity** is a basic class which has some built-in functionality; however, most of the Entity's power comes through **Components**.  Components store data relating to and affecting
the Entity, and are acted on by **Systems**, where the core engine logic is contained.


Unlike in engines like Unity, your game characters are not simply Entities, they are classes inheriting from Entity.  This allows you to add any custom logic you may want to your
characters.  Additionally, rather than attaching a script to an Entity, all the Entity's code is written in C++ *within the child class*.  Here's a basic code example:

```
class Player : public Entity {
public:
    Player(int id, const std::string& name)
            : Entity(id, name) {}
    
    void update() override {
        // Run logic every frame
        getComponents<CharacterBody>()[0]->velocity.x = 0;
        
        if (getComponents<CharacterBody>()[0]->onGround == false)
            getComponents<CharacterBody>()[0]->applyGravity();
        else
            getComponents<CharacterBody>()[0]->velocity.y = 0;
        
        if (Input::inputs["w"] && getComponents<CharacterBody>()[0]->onGround == true) {
            getComponents<CharacterBody>()[0]->velocity.y = -100;
        }
        if (Input::inputs["a"]) {
            getComponents<CharacterBody>()[0]->velocity.x = -100;
        }
        if (Input::inputs["d"]) {
            getComponents<CharacterBody>()[0]->velocity.x = 100;
        }
    }

    void setup() override {
        // Create components
        auto transform = std::make_shared<Transform>();
        transform->position = {100, 100};
        transform->scale = {1.0f, 1.0f};

        auto sprite = std::make_shared<Sprite>("player.png");
        
        auto collider = std::make_shared<CollisionBox>();
        collider->size = {64, 64}; // Example size
        collider->isPhysical = true;
        
        auto body = std::make_shared<CharacterBody>();

        // Add them to the entity instance
        addComponent(transform);
        addComponent(sprite);
        addComponent(collider);
        addComponent(body);

        // Can also run custom logic here. Called only once, when the Entity is created.
        std::cout << "Player entity has been initialized.\n";
    }

    // You can also create custom variables, functions, etc. You're free to do whatever you want.
};
```

A **Scene** is a class which contains Entities and logic.  Just as with Entities, each game Scene is a separate developer-defined class inheriting from Scene.
Just as with Entities, custom logic can be run in these child classes, giving you full, absolute control over your game.

To see a full demo game, go to instantengine/Demo Game.  In order to run the demo game, you will need to create player.png or use whatever image you like.
This is intentional, as I'd like to keep the Demo Game folder as code-only.

## Project plans
I plan on adding more Components and Systems (animation, audio, etc.) and **UIElements** to ease UI design.  In terms of long-term plans, I have two main ideas:

1. **Dynamic physics system.**  The dynamic physics system will act as a physics simulation, allowing PhysicsBodies to be pulled around by the gravity of other
   PhysicsBodies.
2. **Graphical editor**.  Made with either Godot or C++, SFML, and ImGui, the graphical editor will provide devs with an easier way to design Entities and scenes.

## Project history
I made this project because I felt like it and I could.  If for some reason you're actually planning on using it, please message me (@firetdev on ***X, formerly Twitter***).
I'd love to talk, help out, and get feedback.  Message me if you want more information about future plans for the project.

If you're impressed by this project and want to hire me, great!  You still have to message me.  @firetdev on ***X, formerly Twitter***.
