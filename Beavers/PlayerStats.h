#pragma once

struct PlayerStats {
	int m_iDamage = 0;
	int m_iCapacity = 0;
	int m_iSpeed = 64;

	PlayerStats operator+=(PlayerStats const& other) {
		PlayerStats newVar = other;
		newVar.m_iDamage += m_iDamage;
		newVar.m_iCapacity += m_iCapacity;
		newVar.m_iSpeed += m_iSpeed;

		return newVar;
	}
};