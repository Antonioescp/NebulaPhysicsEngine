#include "../BaseApplication/Application.h"
#include <ParticleSpring.h>
#include <ParticleGravity.h>

using namespace Nebula;
using namespace ForceGenerators;

class SpringDemo : public Application
{
private:

	Particle mAnchor{};
	Particle mParticle{};
	ParticleSpring mSpring{ mAnchor, 20.0f, 10.0f };
	ParticleGravity mEarthGravity{ {0.0f, -9.8f, 0.0f} };

public:

	SpringDemo(int width, int height, std::string_view title)
		: Application(width, height, title)
	{}

	virtual void Setup() override
	{
		Application::Setup();

		mAnchor.SetInverseMass(0.0f);
		mAnchor.SetPosition(0.0f, 10.0f, 0.0f);
		mDrawableParticles.push_back({ &mAnchor, { 1.0f, 0.64f, 0.0f } });

		mParticle.SetDamping(0.70f);
		mDrawableParticles.push_back({ &mParticle, { 1.0f, 1.0f, 1.0f } });

		mRegistry.Add(mParticle, mSpring);
		mRegistry.Add(mParticle, mEarthGravity);
	}
};

Application* GetApplication()
{
	return new SpringDemo{ 800, 600, "Spring demo" };
}