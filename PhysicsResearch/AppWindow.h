#pragma once
// STD
#include <cmath>
#include <iostream>
#include <string>
#include <bitset>
#include <assert.h>
#include <cmath>
#include <cassert>

// SFML
#include "SFML/Graphics.hpp"

// ENTT
#include "entt/entt.hpp"

// ME SAFE

// ME UNSAFE

// The AppWindow is what we get from windows
// It handles all the crap that is related to the application and not the Game - the clearing. frame rate, the windows event handling.
class AppWindow
{
	////////
	//////// Data
	//// Properties
	// window
private:
	sf::RenderWindow mAppWindow{ sf::VideoMode{ 1000, 500}, "my window" };
public:
	sf::RenderWindow & getAppWindow() { return mAppWindow; };
	// font
private:
	sf::Font mFont;
public:
	sf::Font & get_font() { return mFont; };
	// keyboard state flags
private:
	std::bitset<sf::Keyboard::KeyCount> mIsKeyPressed{ false };
	std::bitset<sf::Keyboard::KeyCount> mIsKeyReleased{ false };
	std::bitset<sf::Keyboard::KeyCount> mIsKeyHeld{ false };
public:
	std::bitset<sf::Keyboard::KeyCount> const & get_IsKeyPressed() const { return mIsKeyPressed; };
	std::bitset<sf::Keyboard::KeyCount> const & get_IsKeyReleased() const { return mIsKeyReleased; };
	std::bitset<sf::Keyboard::KeyCount> const & get_IsKeyHeld() const { return mIsKeyHeld; };
	bool isKeyPressed(sf::Keyboard::Key const key) const { return mIsKeyPressed[key]; };
	bool isKeyReleased(sf::Keyboard::Key const key) const { return mIsKeyReleased[key]; };
	bool isKeyHeld(sf::Keyboard::Key const key) const { return mIsKeyHeld[key]; };

	// Text entered
private:
	std::string mEnteredText;
public:
	std::string const & getEnteredText() { return mEnteredText; };

	// mouse state flags
private:
	std::bitset<sf::Mouse::ButtonCount> mIsMousePressed{ false };
	std::bitset<sf::Mouse::ButtonCount> mIsMouseReleased{ false };
	std::bitset<sf::Mouse::ButtonCount> mIsMouseHeld{ false };
	bool mIsMouseMoved{ false };
public:
	bool isMousePressed(sf::Mouse::Button const button) const { return mIsMousePressed[button]; };
	bool isMouseReleased(sf::Mouse::Button const button) const { return mIsMouseReleased[button]; };
	bool isMouseHeld(sf::Mouse::Button const button) const { return mIsMouseHeld[button]; };
	bool isMouseMoved() const { return mIsMouseMoved; };
	// mouse location information
private:
	sf::Vector2f mousePosition{ sf::Mouse::getPosition(mAppWindow) };
	sf::Vector2f oldMousePosition{ 0.f, 0.f };
	sf::Vector2f mouseMovement{ 0.f, 0.f };
public:
	sf::Vector2f getMousePos() { return mousePosition; };
	sf::Vector2f getMouseMovement() { return mouseMovement; };

	// Tick Count
private:
	unsigned long long mTickCount{ 0 };
public:
	long long get_tickCount() { return mTickCount; };


	////////
	//////// FUNCTIONS
public:
	static AppWindow & instance();

	void start_frame();
	void end_frame();

	//// Pure Private
private:
	AppWindow(); // private constructor
	void reset_flags();
	void handle_events();
};

