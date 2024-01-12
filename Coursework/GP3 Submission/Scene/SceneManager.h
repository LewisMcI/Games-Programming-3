#pragma once
#include "Scene.h"

class SceneManager {
public:
    SceneManager() {
    }

    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }

    void createNewScene() {
        activeScene = std::make_unique<Scene>();
    }

    std::unique_ptr<Scene>& getActiveScene() {
        return activeScene;
    }

    void changeActiveCamera(Camera& camera) {
        activeScene->changeActiveCamera(camera);
    }
private:
    std::unique_ptr<Scene> activeScene;
    
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;
};