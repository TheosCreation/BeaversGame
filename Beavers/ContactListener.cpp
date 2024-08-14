#include "ContactListener.h"
#include "GameObject.h"

/*
	Contact Listener Callback Function
	Called when 2 entities collide with each other

	@author Jamuel Bocacao
	@param b2Contact*: Contact Data
*/
void ContactListener::BeginContact(b2Contact* _contact)
{
	ContactEvent(_contact, true);
}

/*
	Contact Listener Callback Function
	Called when 2 entities stop colliding with each other

	@author Jamuel Bocacao
	@param b2Contact*: Contact Data
*/
void ContactListener::EndContact(b2Contact* _contact)
{
	ContactEvent(_contact, false);
}

/*
	Triggers Colliding Objects' Contact Events

	@author Jamuel Bocacao
	@param b2Contact*: Contact Data
	@param bool: Event is Begin Contact Event
*/
void ContactListener::ContactEvent(b2Contact* _contact, bool _bStartOverlap)
{
	b2Fixture* fixtureA = _contact->GetFixtureA();
	b2Fixture* fixtureB = _contact->GetFixtureB();

	// Process Non-Sensor Overlapping Event (Only one Fixture must be a sensor)
	if (fixtureA->IsSensor() != fixtureB->IsSensor())
	{
		// Get Physics Body that has Sensor
		b2Body* bodyA = fixtureA->GetBody();
		b2Body* bodyB = fixtureB->GetBody();
		b2Body* interactBody = (fixtureA->IsSensor()) ? bodyA : bodyB;
		b2Body* otherBody = (fixtureA->IsSensor()) ? bodyB : bodyA;

		// Extract Object instances from Physics Bodies
		auto userData = interactBody->GetUserData();
		GameObject* objectA = (GameObject*)userData.pointer;

		userData = otherBody->GetUserData();
		GameObject* objectB = (GameObject*)userData.pointer;

		// Trigger Contact Events in Game Objects
		if (_bStartOverlap)
		{
			objectA->OnBeginContact(objectB);
		}
		else
		{
			objectB->OnEndContact(objectB);
		}
	}
}
