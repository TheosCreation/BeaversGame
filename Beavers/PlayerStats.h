#pragma once
#include <iostream>
struct PlayerStats {
	int m_iDamage = 10;
	int m_iCapacity = 0;
	int m_iSpeed = 64;

	PlayerStats operator+=(PlayerStats const& other) {
		PlayerStats newVar = other;
		newVar.m_iDamage += m_iDamage;
		newVar.m_iCapacity += m_iCapacity;
		newVar.m_iSpeed += m_iSpeed;
		std::cout << "add " << m_iDamage << std::endl;
		return newVar;
	}
};