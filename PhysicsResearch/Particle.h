#pragma once

class Particle
{
	// kinematics
	sf::Vector2f position;
	sf::Vector2f velocity;

	// dynamics
	float mass;

	// visuals
	sf::CircleShape graphic;

public:
	void update(float dt)
	{
		position.y += velocity.y * dt;
		position.x += velocity.x * dt;

		// bounded to screen
		if (position.x < 0 || position.x > AppWindow::instance().getAppWindow().getSize().x)
		{
			velocity.x = -velocity.x;
		}
		if (position.y < 0 || position.y > AppWindow::instance().getAppWindow().getSize().y)
		{
			velocity.y = -velocity.y;
		}
	}

	void draw()
	{
		graphic.setPosition({ position.x, position.y });
		AppWindow::instance().getAppWindow().draw(graphic);
	}

	Particle(sf::Vector2f pos, sf::Vector2f vel)
		: position{pos},
		velocity{vel},
		mass{ 0 }
	{
		graphic.setFillColor(sf::Color::Red);
		graphic.setRadius(10);
		graphic.setOrigin({ graphic.getRadius() / 2, graphic.getRadius() / 2 });
	}
};