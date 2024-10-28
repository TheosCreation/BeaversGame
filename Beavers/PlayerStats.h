#pragma once
#include <iostream>
struct PlayerStats {
	float m_fDamage = 10;
	float m_fCapacity = 100;
	int m_iSpeed = 96;

	void operator+=(PlayerStats const& other) {

		m_fDamage *= other.m_fDamage;
		m_fCapacity *= other.m_fCapacity;
		m_iSpeed += other.m_iSpeed;
	}
};