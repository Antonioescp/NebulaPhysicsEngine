#pragma once

#include <random>

import Core;

std::random_device randomDevice{};
std::default_random_engine randomEngine{ randomDevice() };

Nebula::real GetRandomRange(Nebula::real min, Nebula::real max)
{
	if (min > max) std::swap(min, max);

	std::uniform_real_distribution realDistribution{ min, max };
	return realDistribution(randomEngine);
}

Nebula::Core::Vector3 GetRandomVector(const Nebula::Core::Vector3& minVector, const Nebula::Core::Vector3& maxVector)
{
	Nebula::real randomX = GetRandomRange(minVector.x, maxVector.x);
	Nebula::real randomY = GetRandomRange(minVector.y, maxVector.y);
	Nebula::real randomZ = GetRandomRange(minVector.z, maxVector.z);
	return { randomX, randomY, randomZ };
}
