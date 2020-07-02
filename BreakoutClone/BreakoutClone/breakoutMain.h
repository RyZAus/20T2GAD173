#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Brick
{
public:
	sf::RectangleShape bShape;
	sf::Color bColour;
	sf::Vector2f bSize;
	sf::Vector2f bPos;
};

class Ball 
{
//public to  use on other sheets
public:
	void Bounce(int dir, sf::RectangleShape obj, sf::CircleShape ball) 
	{
		//int direction controlls what surface we hit, what direction do we need to travel.
		//int x determines exactly where the ball hit
		//where is the centre of the object and where is the centre of the ball
		int x = (obj.getPosition().x + obj.getSize().x / 2) - (ball.getPosition().x + ball.getRadius());
		//switch to use cases for the direction
		switch (dir)
		{
		case 0:
			if (x > 0) 
			{
				//when the ball hits right side
				ballVelocity.y = -ballVelocity.y;
				ballVelocity.x += 1;
			}
			else
			{
				//when the ball hits left side
				ballVelocity.y = -ballVelocity.y;
				ballVelocity.x -= 1;
			}
			break;
		case 1:
			//when the ball hits top or bottom horizontally flip
			ballVelocity.x = -ballVelocity.x;
			break;
		}
	}
	//setting our shapes, velocity, and colour
	sf::CircleShape ballShape;
	sf::Vector2f ballStartPos;
	sf::Vector2f ballVelocity;
	float ballRadius = 10.f;
};

class Paddle
{
//public to  use on other sheets
public:
	void UpdatePosition(float dir)
	{
		//move in a direction by speed 
		pShape.setPosition(dir * speed, pShape.getPosition().y);
	}
	//setting our shapes, speed, and colour
	sf::RectangleShape pShape;
	float speed = 10.f;
	sf::Vector2f pSize;
	sf::Color pColour;
};

class Game
{
//public to  use on other sheets
public:
	//functions to run the game
	bool Start();
	int Update();
	//setting stuff here so it cant be changed initially on startup
	sf::RenderWindow window;
	sf::RectangleShape top;
	sf::RectangleShape left;
	sf::RectangleShape right;
	sf::RectangleShape bottom;
	float windowWidth = 1000;
	float windowHeight = 600;
	int score = 0;
	int lives = 3;
	sf::Font font;
	sf::Text scoreText;
	sf::Text livesText;
	//stores it in memory
	sf::SoundBuffer paddleSB;
	sf::SoundBuffer wallSB;
	sf::SoundBuffer brickSB;
	//used for calling from the sound buffer
	sf::Sound sound;
};