#ifndef SFE_SCENE_SCENEMANAGER_HPP_
#define SFE_SCENE_SCENEMANAGER_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <cassert>
#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include "Scene.hpp"

namespace sfe {

  class SceneManager {
    public:
      SceneManager()
      : mWindow(nullptr)
      , mCurrentScene(nullptr)
      , mPreviousScene(nullptr)
      , mSwitch(0)
      , mIndex(0)
      {}

      ~SceneManager() {}

      Scene* getScene() {
        return mCurrentScene.get();
      }

      void loadScene(const std::string& sceneName) {
        mNextScene = sceneName;
        mSwitch = true;
        switchState();
        mCurrentScene.get()->setWindow(mWindow);
        mCurrentScene.get()->load();
        mWindow->setTitle(mCurrentScene.get()->getTitle());
        std::vector<std::string>::iterator it = std::find(mSceneNames.begin(), mSceneNames.end(), sceneName);
        if(it != mSceneNames.end()) {
            mIndex = it - mSceneNames.begin();
        }
      }

      void loadScene(const std::size_t& idx) {
        if(idx <= mSceneNames.size() -1) {
          loadScene(mSceneNames[idx]);
        }
      }

      Scene* next() {
        if(mIndex + 1 > mSceneNames.size() - 1) {
          mIndex = 0;
        } else {
          mIndex++;
        }

        loadScene(mSceneNames[mIndex]);
        return mCurrentScene.get();
      }

      Scene* previous() {
        if(static_cast<int>(mIndex - 1) < 0) {
          mIndex = mSceneNames.size() - 1;
        } else {
          mIndex--;
        }

        loadScene(mSceneNames[mIndex]);
        return mCurrentScene.get();
      }

      const std::size_t count() const {
        return mSceneNames.size();
      }

      void setWindow(sf::RenderWindow* renderWindow) {
        mWindow = renderWindow;
      }

      template<typename T>
        void registerScene(const std::string& sceneName);

    private:
      sf::RenderWindow *mWindow;
      Scene::ScenePtr mCurrentScene;
      Scene::ScenePtr mPreviousScene;
      std::string mNextScene;
      bool mSwitch;
      std::size_t mIndex;
      std::vector<std::string> mSceneNames;
      std::unordered_map<std::string, std::function<Scene::ScenePtr()>> mScenes;

      Scene::ScenePtr createScene(const std::string& sceneName) {
        auto found = mScenes.find(sceneName);
        assert(found != mScenes.end());
        return found->second();
      }

      void switchState() {
        mCurrentScene.reset();
        if(mPreviousScene != nullptr && mPreviousScene->getTitle() == mNextScene)
          mCurrentScene = std::move(mPreviousScene);
        else
          mCurrentScene = std::move(createScene(mNextScene));

        mSwitch = false;
      }

  };

  template<typename T>
    void SceneManager::registerScene(const std::string& sceneName) {
      mSceneNames.emplace_back(sceneName);
      mScenes[sceneName] = [this]() {
        Scene::ScenePtr scenePtr(new T());
        scenePtr.get()->setTitle(mNextScene);
        return scenePtr;
      };
    }

}

#endif /* SFE_SCENE_SCENEMANAGER_HPP_ */
