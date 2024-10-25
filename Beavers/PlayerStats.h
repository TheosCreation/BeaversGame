#pragma once
#include <iostream>
struct PlayerStats {
	int m_iDamage = 10;
	int m_iCapacity = 100;
	int m_iSpeed = 96;

	void operator+=(PlayerStats const& other) {

		m_iDamage += other.m_iDamage;
		m_iCapacity += other.m_iCapacity;
		m_iSpeed += other.m_iSpeed;
	}
};