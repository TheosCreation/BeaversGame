#pragma once

#include "Object.h"
#include "Text.h"
#include <memory>

class Warehouse : public Object
{
public:
    Warehouse(Vec2f _position, std::weak_ptr<b2World> _sceneWorld);

    void ChangeWoodAmount(int _iAmount);
    int GetWoodAmount() const;

    std::string GetWoodAmountString() const;
    void OnBeginContact(Object* _other) override;
    void Render(sf::RenderTexture* _sceneBuffer) override;

private:
    int m_iWoodAmount = 0;
    std::unique_ptr<Text> m_woodAmountText;
};