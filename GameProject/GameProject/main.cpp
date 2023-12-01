#include "GameCore.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "json.hpp"

int main() {
    // Initialize the engine
    Engine::Instance().Initialize();

    // Load and parse the Scene01 JSON
    std::ifstream inputStream("Scenes/Scene01.json");  // Adjust the path as needed
    std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
    json::JSON scene01JSON = json::JSON::Load(str);

    // Get the SceneManager instance and load Scene01
    SceneManager& sceneManager = SceneManager::GetInstance();
    Scene* scene01 = sceneManager.LoadScene(scene01JSON);

    // Iterate over entities in Scene01 and test Transform components
    for (Entity* entity : scene01->GetEntities()) {
        Transform* transform = dynamic_cast<Transform*>(entity->GetComponent("Transform"));
        if (transform) {
            // Manipulate the Transform component
            transform->Translate(Vec2(1, 0)); // Move the entity
            transform->Rotate(15); // Rotate the entity
            transform->Scale(Vec2(1.1f, 1.1f)); // Scale the entity

            // Check the updated values of position, rotation, and scale
            Vec2 newPosition = transform->position;
            float newRotation = transform->rotation;
            Vec2 newScale = transform->scale;
            // Log or assert the new values to confirm they are as expected
        }
        else {
            // Handle the case where Transform component is not found
        }
    }

    // Test creating a new entity and attaching a Transform component
    Entity* newEntity = scene01->CreateEntity(); // Or use SceneManager to create entity
    Transform* newTransform = new Transform();
    newEntity->AddComponent(newTransform); // Assuming Entity has AddComponent method

    // Manipulate the new Transform component
    newTransform->Translate(Vec2(2, 0)); // Example manipulation
    // Verify the changes

    // Finalize the engine
    Engine::Instance().Destroy();

    return 0;
}



