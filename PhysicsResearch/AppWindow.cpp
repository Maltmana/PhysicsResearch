#include "stdafx.h"
#include "AppWindow.h"
// STD

// SFML

// ENTT

// ME SAFE

// ME UNSAFE


//////////////////////////////////////////////////////////////////////////////////////////////////// >8)
//////////////////////////////////////////////////////////////////////////////////////////////////// AppWindow
//////////////////////////////////////////////////////////////////////////////////////////////////// >8)

////////////////////////////////////////>~
////////// Data
////////////////////////////////////////>~

////////// Static
#ifdef DEBUG
static bool frameStarted{ false };
#endif // DEBUG


////////////////////////////////////////>~
////////// Constructors
////////////////////////////////////////>~

////////// Ctor
AppWindow::AppWindow()
{
	mEnteredText.reserve(512); // might aswell reserve some.
}
////////// Dtor

////////// Copy

////////// Move

////////////////////////////////////////>~
////////// Functions
////////////////////////////////////////>~

////////// Public
AppWindow & AppWindow::instance()
{
	static AppWindow instance; // Guaranteed to be destroyed. Instantiated on first use.
	return instance;
}

void AppWindow::start_frame()
{
#ifdef DEBUG
	assert(!frameStarted);
	frameStarted = true;
#endif // DEBUG
	mTickCount++;
	handle_events();
	mAppWindow.clear();
}

void AppWindow::end_frame()
{
#ifdef DEBUG
	assert(frameStarted);
	frameStarted = false;
#endif // DEBUG

	mAppWindow.display();
}

////////// Private
void AppWindow::reset_flags()
{
	// reset text entered
	mEnteredText.clear();
	// reset key and mouse flags
	mIsKeyPressed.reset();
	mIsKeyReleased.reset();
	mIsMousePressed.reset();
	mIsMouseReleased.reset();
	mIsMouseMoved = false;
	mouseMovement = { 0.f,0.f };
}

void AppWindow::handle_events()
{
	// all important reseting of the flags.
	reset_flags();
	mouseMovement = { 0.0f, 0.0f };

	sf::Event event;
	// process all events
	// NOTE that some of these events get sent multiple times per frame, like mouse moved. 
	// That is why mouse move accumulates the mouse movements of the entire frame with +=.
	while (mAppWindow.pollEvent(event))
	{
		switch (event.type)
		{
			// Window events
		case sf::Event::EventType::Closed: // Close window
		{
			mAppWindow.close();
		}
		break;
		case sf::Event::EventType::Resized: // shows you more stuff if you resize window.
		{
			sf::FloatRect visibleArea{ 0.f,0.f,static_cast<float>(event.size.width), static_cast<float>(event.size.height) };
			mAppWindow.setView(sf::View(visibleArea));
		}
		break;
		// Keyboard events
		case sf::Event::EventType::KeyPressed: // set isKeyPressed flag and isKeyHeld flag.
		{
			if (event.key.code <= (int)mIsKeyPressed.size()) // bug : capslock bug
			{
				mIsKeyPressed[event.key.code] = true;
				mIsKeyHeld[event.key.code] = true;
			}

		}
		break;
		case sf::Event::EventType::KeyReleased: // set isKeyReleased flag and unset isKeyHeld flag.
		{
			if (event.key.code <= (int)mIsKeyPressed.size()) // bug : capslock bug
			{
				mIsKeyReleased[event.key.code] = true;
				mIsKeyHeld[event.key.code] = false;
			}
		}
		break;
		case sf::Event::EventType::TextEntered: // Puts all text entered that frame into nice little string.
		{
			auto unichar = event.text.unicode;


			// change silly text.
			//if (unichar == '\r')
			//{
			//	unichar = '\n';
			//}
			// get rid of garbage text.
			if (unichar != '\b' && unichar != '\r')
			{
				mEnteredText += static_cast<char>(unichar);
			}

		}
		break;
		// Mouse events
		case sf::Event::EventType::MouseButtonPressed: // set isMouseReleased flag and unset isKeyHeld flag.
		{
			mIsMousePressed[event.mouseButton.button] = true;
			mIsMouseHeld[event.mouseButton.button] = true;
		}
		break;
		case sf::Event::EventType::MouseButtonReleased: // set isMouseReleased flag and unset isKeyHeld flag.
		{
			mIsMouseReleased[event.mouseButton.button] = true;
			mIsMouseHeld[event.mouseButton.button] = false;

		}
		break;
		case sf::Event::EventType::MouseMoved:
		{
			mIsMouseMoved = true;
			oldMousePosition = mousePosition;
			mousePosition = { static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) };
			mouseMovement += mousePosition - oldMousePosition; // accumulates movement through whole frame.
		}
		break;
		case sf::Event::EventType::MouseLeft:
		{
		}
		break;
		// Focus events
		case sf::Event::EventType::LostFocus: // reset all the isKeyHeld flags.
		{
			mIsKeyHeld.reset();
			mIsMouseHeld.reset();
			mIsMouseReleased = true; // HMMM TODO WTF ?  Do i want the mouse to release when I leave screen?
		}
		break;
		default:
			break;
		}
	}
}
////////////////////////////////////////>~
////////// Operators
////////////////////////////////////////>~

