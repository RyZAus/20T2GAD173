#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
///Declare all of our int's
int windowX = 1000; //initial window width
int windowY = 600; //initial window height
int speed = 10; //how fast we move
int main()
{
	///shape stuff
	sf::Vector2f rectSize = sf::Vector2f(150.f, 50.f); //size of our paddle in pixel size
	sf::Vector2f rectPos = sf::Vector2f((windowX / 2) - (rectSize.x / 2), (windowY / 1.5f) - (rectSize.y / 2)); //center our paddle
	sf::Color rectColour = sf::Color(255, 255, 0, 255); //sets our colour r/g/b/a
	//Defining the window, name, and frame rate
	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Breakout Clone"); //give our window a name and perameters by default
	window.setFramerateLimit(60); //stop our window from running 500 fps
	//Setting all of our paddle settings
	sf::RectangleShape paddle(rectSize); //Our paddle object
	paddle.setFillColor(rectColour); //set colour of paddle
	paddle.setPosition(rectPos); //set position of paddle
	///ball stuff
	sf::CircleShape ball(10.f); //create ball shape
	ball.setFillColor(sf::Color::Cyan); //colour set
	sf::Vector2f velocity = sf::Vector2f(0.f, 0.f); //setup velocity
	velocity.x = rand() % 10; //generate a number between 1 and 10 to make x random initially
	velocity.y = -5; //move up by default
	//move starting pos of the ball up by the height of the paddle
	ball.setPosition(sf::Vector2f(rectPos.x, rectPos.y - rectSize.y));	
	//code to run when the window is open
	///border stuff
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;
	//sets position to vector2f aka co-ordinates and x, y
	top.setSize(sf::Vector2f(windowX, 1));
	top.setPosition(sf::Vector2f(0, 0));
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowX, 1));
	bottom.setPosition(sf::Vector2f(0, windowY - 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(windowX, 1));
	left.setPosition(sf::Vector2f(0, 0));
	left.setFillColor(sf::Color::Black);
	right.setSize(sf::Vector2f(windowX, 1));
	right.setPosition(sf::Vector2f(windowX - 1, 0));
	right.setFillColor(sf::Color::Black);
	//run this when the window is open
	while (window.isOpen()) //IF YOU WANT TO SHRINK CODE USE THIS PLUS
	{
		//check if left is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			//move rectangle left by decreasing
			rectPos.x -= speed;
			if (rectPos.x <= 0) 
			{
				rectPos.x = 0;
			}
			//set the rectangle position for return
			paddle.setPosition(rectPos);
		}
		//check if right is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			//move rectangle right by increasing
			rectPos.x += speed;
			if (rectPos.x >= windowX - rectSize.x)
			{
				rectPos.x = windowX - rectSize.x;
			}
			//set the rectangle position for return
			paddle.setPosition(rectPos);
		}
		if (top.getGlobalBounds().intersects(ball.getGlobalBounds())) 
		{
			//did we hit the top?
			velocity.y = -velocity.y;

		}
		if (bottom.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did we hit the bottom?
			velocity.y = -velocity.y;
		}
		if (left.getGlobalBounds().intersects(ball.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did we hit the side?
			velocity.x = -velocity.x;
		}
		if (paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
		{
			//did we hit the bottom?
			velocity.y = -velocity.y;
		}
		ball.move(velocity); //move ball around
		//pollevent is our window updating event
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			//if window closes identify
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//clear our window, and redraw everything
		window.clear();
		window.draw(paddle);
		window.draw(ball);
		window.display();
	}
	return 0;
}