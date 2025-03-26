#pragma once

#include <string>
#include <vector>
#include <memory>

class DraggableElement {
public:
    DraggableElement(float x, float y, float width, float height, const std::string& label)
        : mPosX(x), mPosY(y), mWidth(width), mHeight(height), mLabel(label), mIsDragging(false) {}

    void draw(); // Метод для отрисовки элемента

private:
    float mPosX, mPosY, mWidth, mHeight;
    std::string mLabel;
    bool mIsDragging;
};

class HUDManager {
public:
    static HUDManager& getInstance() {
        static HUDManager instance;
        return instance;
    }

    void addDraggableElement(std::shared_ptr<DraggableElement> element) {
        mElements.push_back(element);
    }

    void render() {
        for (auto& element : mElements) {
            element->draw();
        }
    }

    bool isEditorActive() const {
        return mEditorActive;
    }

    void toggleEditor() {
        mEditorActive = !mEditorActive;
    }

private:
    HUDManager() : mEditorActive(false) {}

    bool mEditorActive;  // Флаг активации HUD Editor
    std::vector<std::shared_ptr<DraggableElement>> mElements;
};