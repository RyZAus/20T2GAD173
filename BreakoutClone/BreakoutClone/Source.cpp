#include <conio.h>
#include "breakoutMain.h"
int main()
{
	//failsafe
	Game myGame;
	if (!myGame.Start())
	{
		//something failed in the game so it will push an error code
		return EXIT_FAILURE;
	}
	return myGame.Update();
}
//define Brick as brick
Brick brick;
//make 31 of Bricks called brick
std::vector<Brick> Bricks(31, Brick(brick));
bool Game::Start() //only happens on start
{
	//load the sound buffers from header and pull our audio files
	paddleSB.loadFromFile("SFX/paddlebounce.wav");
	wallSB.loadFromFile("SFX/wallbounce.wav");
	brickSB.loadFromFile("SFX/blockbounce.wav");
	//load font from the header file
	font.loadFromFile("arial.ttf");
	//setting all our text up for lives and score
	scoreText.setFont(font);
	livesText.setFont(font);
	scoreText.setPosition(0, windowHeight - 50);
	livesText.setPosition(windowWidth - 100, windowHeight - 50);
	scoreText.setCharacterSize(24);
	livesText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	livesText.setFillColor(sf::Color::White);
	//create our window and set the frame rate limit
	sf::VideoMode vMode(windowWidth, windowHeight);
	window.create(vMode, "breakouttt");
	window.setFramerateLimit(60);
	//setup the previously made bricks
	srand(time(NULL));
	for (int i = 0; i < 31; i++)
	{
		Bricks[i].bShape.setSize(sf::Vector2f(100, 50));
		//bottom row colour randomness and position set
		if (i <= 10)
		{
			Bricks[i].bShape.setFillColor(sf::Color(rand() % 35 + 180, 0, 0, 255));
			Bricks[i].bShape.setPosition(100 * i, 0);
		}
		//top row colour randomness and position set
		else if (i > 20)
		{
			Bricks[i].bShape.setFillColor(sf::Color(0, rand() % 35 + 180, 0, 255));
			Bricks[i].bShape.setPosition(100 * (i-21), 100);
		}
		//middle row colour randomness and position set
		else if (i > 10)
		{
			Bricks[i].bShape.setFillColor(sf::Color(0, 0, rand() % 35 + 180, 255));
			Bricks[i].bShape.setPosition(100 * (i - 11), 50);
		}
	}
	//setup borders
	//sets position to vector2f aka co-ordinates and x, y
	top.setSize(sf::Vector2f(windowWidth, 1));
	top.setPosition(sf::Vector2f(0, 0));
	top.setFillColor(sf::Color::Black);
	bottom.setSize(sf::Vector2f(windowWidth, 1));
	bottom.setPosition(sf::Vector2f(0, windowHeight - 1));
	bottom.setFillColor(sf::Color::Black);
	left.setSize(sf::Vector2f(1, windowHeight));
	left.setPosition(sf::Vector2f(0, 0));
	left.setFillColor(sf::Color::Black);
	right.setSize(sf::Vector2f(1, windowHeight));
	right.setPosition(sf::Vector2f(windowWidth - 1, 0));
	right.setFillColor(sf::Color::Black);
	return true;
}
int Game::Update() //updates every frame
{
	//setup paddle
	Paddle paddle;
	paddle.pShape.setSize(sf::Vector2f(120.f, 15.f));
	paddle.pShape.setFillColor(sf::Color::Yellow);
	paddle.pShape.setPosition(windowHeight - (windowHeight / 5), windowWidth / 2);
	//setup ball
	Ball ball;
	ball.ballShape.setRadius(ball.ballRadius);
	ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
	ball.ballShape.setFillColor(sf::Color::Cyan);
	ball.ballVelocity.x = rand() % 10;
	ball.ballVelocity.y = -5;
	//run this when the window is open
	while (window.isOpen()) //IF YOU WANT TO SHRINK CODE USE THIS PLUS
	{
		//Using mouse to move paddle
		//detect mouse inside screen
		if (sf::Mouse::getPosition(window).x > paddle.pShape.getSize().x / 2 && sf::Mouse::getPosition(window).x < window.getSize().x - paddle.pShape.getSize().x / 2)
		{
			paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x / 2, paddle.pShape.getPosition().y);
		}
		//move ball
		ball.ballShape.move(ball.ballVelocity);
		if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds())) 
		{
			//did we hit the top?
			ball.Bounce(0, top, ball.ballShape);
			sound.setBuffer(wallSB);
			sound.play();
		}
		if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			//did we hit the bottom?
			//original code
			//ball.Bounce(0, top, ball.ballShape);
			//new edit
			ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
			ball.ballVelocity.x = rand() % 10;
			ball.ballVelocity.y = -5;
			lives -= 1;
			if (lives == 0)
			{
				//game over
				return 1;
			}
		}
		if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) || right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			//did we hit the side?
			ball.Bounce(1, left, ball.ballShape);
			sound.setBuffer(wallSB);
			sound.play();
		}
		if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			//did we hit the paddle?
			ball.Bounce(0, paddle.pShape, ball.ballShape);
			sound.setBuffer(paddleSB);
			sound.play();
		}
		//collision with bricks
		for (int i = 0; i < Bricks.size(); i++)
		{
			if (Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
			{
				ball.Bounce(0, Bricks[i].bShape, ball.ballShape);
				Bricks[i].bShape.setPosition(1200, 0);
				score += 1;
				//original code has too drastic increase
				//ball.ballVelocity = ball.ballVelocity * 1.03f;
				//New code to decrease gradual speed increase to stop the ball breaking boundarys
				ball.ballVelocity = ball.ballVelocity * 1.005f;
				if (score == 30)
				{
					return 1;
				}
				sound.setBuffer(brickSB);
				sound.play();
			}
		}
		//pollevent is our window updating event
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			//if window closes identify
			if (event.type == sf::Event::Closed)
				window.close();
		}
		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
		//clear our window, and redraw everything
		window.clear();
		//draw our bricks
		for (int i = 0; i < Bricks.size(); i++)
		{
			window.draw(Bricks[i].bShape);
		}
		//draw our text such as score and lives
		window.draw(scoreText);
		window.draw(livesText);
		//draw our paddle and ball
		window.draw(paddle.pShape);
		window.draw(ball.ballShape);
		//display all drawed
		window.display();
	}
	return 0;
}