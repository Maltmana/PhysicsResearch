#pragma once
// STD
// MINE SAFE
#include "Particle.h"

namespace ParticleSim
{
	// main entry point for particle simulation
	void ParticleSim_main()
	{

		// INIT PARTICLE
		std::vector<Particle> particles;
		RNG rng;
		for (size_t i = 0; i < 200; i++)
		{
			particles.emplace_back(Particle{ {rng.rand(-200.f, 200.f), 200 }, { rng.rand(-100.f, 100.f), rng.rand(-1000.f, 1000.f) } });
		}

		Clock clock;

		while (true)
		{
			std::chrono::duration<float> dtdura = clock.tick(); // tick
			float dt = dtdura.count();

			// update
			for (auto& p : particles)
			{
				p.update(dt);
			}

			// draw between these
			AppWindow::instance().start_frame();
			for (auto & p : particles)
			{
				p.draw();
			}

			AppWindow::instance().end_frame();

		}
	}
}