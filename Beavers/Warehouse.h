#pragma once

#include "Event.h"
#include "Object.h"
#include "Text.h"
#include <memory>

class Warehouse : public Object
{
public:
	Warehouse(Vec2f _position);


    void ChangeWoodAmount(int _iAmount);
    int GetWoodAmount() const;

    std::string GetWoodAmountString() const;
    void OnBeginContact(Object* _other) override;
    void Render(sf::RenderTexture* _sceneBuffer) override;
    void SetLoadWinSceneEvent(shared_ptr<Event<void, void>> _loadWinSceneEvent);
    void SetLoadLoseSceneEvent(shared_ptr<Event<void, void>> _loadLoseSceneEvent);

private:
    int m_iWoodAmount = 0;
    std::unique_ptr<Text> m_woodAmountText;

    shared_ptr<Event<void, void>> m_loadWinSceneEvent;
    shared_ptr<Event<void, void>> m_loadLoseSceneEvent;
};