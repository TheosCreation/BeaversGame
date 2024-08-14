#pragma once
#include <Box2D/box2d.h>
#include <Box2D/b2_world_callbacks.h>

class ContactListener : public b2ContactListener
{
public:
	ContactListener() = default;

	void BeginContact(b2Contact* _contact) override;
	void EndContact(b2Contact* _contact) override;

private:
	void ContactEvent(b2Contact* _contact, bool _bStartOverlap);
};
