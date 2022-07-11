#pragma once

#include <optional>
#include <vector>
#include "Utils.h"
#include <numbers>

import Core;

// A firework that can fly and explode into different fireworks
class Firework : public Nebula::Core::Particle
{
public:
	// Rules that can be applied to parent and child fireworks
	struct Rule
	{
		// Amount of child fireworks to create after explosion
		unsigned int payloadCount{};
		
		// Minimum time for the current firework explosion
		Nebula::real minAge{};

		// Maximum time for the current firework explosion
		Nebula::real maxAge{};
		
		// Minimum velocity on spawn
		Nebula::real minSpeed{};

		// Maximum velocity on spawn
		Nebula::real maxSpeed{};

		Nebula::real minDamping;
		Nebula::real maxDamping;
		
		// Rule to apply to children fireworks
		Rule* childrenRule{ nullptr };

		Rule(
			unsigned int payloadCount, 
			Nebula::real minAge, 
			Nebula::real maxAge, 
			Nebula::real minSpeed, 
			Nebula::real maxSpeed,
			Nebula::real minDamping,
			Nebula::real maxDamping,
			std::optional<Rule> childrenRule
		)
			: payloadCount{payloadCount}
			, minAge{minAge}
			, maxAge{maxAge}
			, minSpeed{minSpeed}
			, maxSpeed{maxSpeed}
			, minDamping{minDamping}
			, maxDamping{ maxDamping }
			, childrenRule{ nullptr }
		{
			if (childrenRule.has_value()) this->childrenRule = new Rule{ std::move(*childrenRule) };
		}

		Rule(Rule&& rhs)
		{
			payloadCount = rhs.payloadCount;
			minAge = rhs.minAge;
			maxAge = rhs.maxAge;
			minSpeed = rhs.minSpeed;
			maxSpeed = rhs.maxSpeed;
			minDamping = rhs.minDamping;
			maxDamping = rhs.maxDamping;
			childrenRule = rhs.childrenRule;
			rhs.childrenRule = nullptr;
		}

		~Rule()
		{
			delete childrenRule;
		}
	};

	// Applies the rule to children
	Firework(
		const unsigned int payload = 0U,
		const Nebula::real age = 1.0f, 
		Rule* childrenRule = nullptr
	)
		: mPayload{ payload }
		, mAge{ age }
		, mBaseFuseTime{ mAge }
		, mChildrenRule{ childrenRule }
		, mShouldExplode{ false }
		, mHasExploded{ false }
	{}

	// Applies the rule to the firework itself 
	Firework(const Rule& fireworkRule)
		: mPayload{ fireworkRule.payloadCount }
		, mAge { GetRandomRange(fireworkRule.minAge, fireworkRule.maxAge) }
		, mBaseFuseTime{ mAge }
		, mChildrenRule{ fireworkRule.childrenRule }
		, mShouldExplode{ false }
		, mHasExploded{ false }
	{
		SetDamping(GetRandomRange(fireworkRule.minDamping, fireworkRule.maxDamping));

		Nebula::real randomX{ GetRandomRange(0.0f, std::numbers::pi * 2.0f) };
		Nebula::real randomY{ GetRandomRange(0.0f, std::numbers::pi * 2.0f) };
		Nebula::Core::Vector3 randomVelocity{ cos(randomX), sin(randomY), 0.0f };
		randomVelocity.Normalize();
		randomVelocity *= GetRandomRange(fireworkRule.minSpeed, fireworkRule.maxSpeed);

		SetVelocity(randomVelocity);
	}

	// Updates physics and firework behaviour
	void Update(Nebula::real duration)
	{
		Integrate(duration);

		if (mAge > 0.0f)
		{
			mAge -= duration;
			if (mAge <= 0.0f && !mShouldExplode)
			{
				mShouldExplode = true;
			}
		}
	}

	// Explodes firework and returns children fireworks
	[[nodiscard]]
	std::vector<Firework> Explode()
	{
		using namespace Nebula;
		using namespace Nebula::Core;

		mHasExploded = true;
		if (mPayload <= 0) return {};
		if (!mChildrenRule) return {};

		std::vector<Firework> children{};

		for (int i = 0; i < mPayload; i++)
		{
			Firework child{*mChildrenRule};
			child.SetPosition(GetPosition());
			child.SetMass(1.0f);
			child.SetAcceleration(Nebula::Core::Vector3::Gravity * 10.0f);
			children.push_back(child);
		}

		return children;
	}

	bool ShouldExplode() const
	{
		return mShouldExplode;
	}

	bool HasExploded() const
	{
		return mHasExploded;
	}

	Nebula::real GetAge() const
	{
		return mAge;
	}

	Nebula::real GetBaseAge() const
	{
		return mBaseFuseTime;
	}
	
private:

	// Particles after explosion
	unsigned int mPayload;

	// Time before explosion
	Nebula::real mAge;
	Nebula::real mBaseFuseTime;

	// Rule to apply to the firework children if any
	Rule* mChildrenRule;

	// True if fuse time is reached
	bool mShouldExplode;

	// Keeps track of detonation status
	bool mHasExploded;
};
