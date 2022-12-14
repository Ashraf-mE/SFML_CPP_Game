///// Game: The Shot //////

//__ Please provide the absolute paths rather than relative paths __//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Vector>
#include <iostream>

using namespace sf;
using namespace std;

int rep = 0;
int ext = 0;
int maxLevels = 8;
int score = 0;
int allClose = 0;

int main()
{
	// Front Page:
	RenderWindow window(VideoMode(600, 700), "The Shot", Style::Default);
	window.setFramerateLimit(60);

	// Sounds: //////////////////////////
	// Bullet Sound:
	SoundBuffer bulletSoundbuffer;
	bulletSoundbuffer.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/laser.wav");
	Sound bulletSound;
	bulletSound.setBuffer(bulletSoundbuffer);
	bulletSound.setVolume(15.f);

	// Game opening sound:
	SoundBuffer gameMusicbuffer;
	gameMusicbuffer.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/gameMusic.wav");
	Sound gameMusic;
	gameMusic.setBuffer(gameMusicbuffer);
	gameMusic.setVolume(15.f);

	// Texts and Textures: //////////////////////////
	// Font and Text:
	Font font;
	font.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/PixellettersFull.ttf"); // For Game Over
	Font font2;
	font2.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/Dosis-Light.ttf"); // For score and HP

	// Front page Texture:
	Texture frontPageTexture;
	Sprite frontPage;
	frontPageTexture.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/frontPage.png");
	frontPage.setTexture(frontPageTexture);
	frontPage.setScale(Vector2f(0.56f, 0.4f));

	Texture endpageTexture;
	Sprite endpage;
	endpageTexture.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/endCover.png");
	endpage.setTexture(endpageTexture);
	endpage.setScale(Vector2f(0.56f, 0.65f));

	// Player Texture:
	Texture playerTexture;
	Sprite player;
	playerTexture.loadFromFile("C:/Users/mohammad asfraf/myproject/src/Textures/ship.png");
	player.setTexture(playerTexture);
	player.setScale(Vector2f(0.08f, 0.08f));
	player.setPosition(window.getSize().x / 2 - player.getScale().x, window.getSize().y - player.getScale().y - 90);
	Vector2f playerCenter;

	// Enemy Texture:
	Texture enemyTexture;
	Sprite enemy;
	enemyTexture.loadFromFile("src/Textures/enemy.png");
	enemy.setTexture(enemyTexture);
	enemy.setScale(Vector2f(0.04f, 0.04f));
	vector<Sprite> enemies;
	Vector2f enemyCenter;

	// Bullet:
	//Player Bullets:
	RectangleShape playerBullet;
	playerBullet.setSize(Vector2f(5.f, 5.f));
	playerBullet.setFillColor(Color::Cyan);
	vector<RectangleShape> playerBullets;

	//Enemy Bullets:
	RectangleShape enemBullet;
	enemBullet.setSize(Vector2f(5.f, 8.f));
	enemBullet.setFillColor(Color::Red);
	vector<RectangleShape> enemBullets;

	// HP:
	RectangleShape hpBar;
	hpBar.setFillColor(Color::Yellow);
	hpBar.setPosition(45, 10);
	hpBar.setOutlineThickness(1);
	hpBar.setOutlineColor(Color::Green);

	// HP text:
	Text text;
	text.setFont(font2);
	text.setCharacterSize(20);
	text.setFillColor(Color::Green);
	text.setStyle(Text::Bold);
	text.setPosition(6, 6);
	text.setString("HP:");

	// Level text:
	Text level;
	level.setFont(font2);
	level.setCharacterSize(20);
	level.setFillColor(Color::Magenta);
	level.setStyle(Text::Bold);
	level.setPosition(window.getSize().x / 2 - 30, 6);

	// Score text:
	Text count;
	count.setFont(font2);
	count.setCharacterSize(20);
	count.setFillColor(Color::Cyan);
	count.setStyle(Text::Bold);
	count.setPosition(480, 6);

	// Game Over text:
	Text Over;
	Over.setFont(font);
	Over.setCharacterSize(50);
	Over.setFillColor(Color::Magenta);
	Over.setStyle(Text::Bold);
	Over.setPosition(200, 350);

	// End Page Score:
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(70);
	scoreText.setFillColor(Color::Yellow);
	scoreText.setStyle(Text::Italic | Text::Bold);
	scoreText.setPosition(485, 342);

	// Front Page window:
	while (window.isOpen())
	{
		Event R;
		while (window.pollEvent(R))
		{
			if (R.type == R.Closed || Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				allClose = 1;
			}

			if (Keyboard::isKeyPressed(Keyboard::Enter))
			{
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(frontPage);
		// frontpageMusic.play();
		window.display();
	}

	if (allClose == 0) // When frontPage is not closed
	{
		gameMusic.play(); // Sound for game opening
		gameMusic.setLoop(true);
		while (rep < maxLevels)
		{
			//Initiate:
			RenderWindow window(VideoMode(600, 700), "The Shot", Style::Default);
			window.setFramerateLimit(60);
			float bulletRate = 0;
			float hp = 10;
			int lenPos = 0;
			int depPos = 40;
			int enemCount = 0;
			int enemFinish = 0;
			int rows = 1;
			int bulletGap = 15;
			level.setString("Level: " + to_string(rep + 1));

			// Upgrades:
			if (rep >= 5) // After 5th level
			{
				hp = 15;
				bulletGap = 8;
			}

			while (window.isOpen())
			{
				Event event;
				while (window.pollEvent(event))
				{
					if (event.type == event.Closed || Keyboard::isKeyPressed(Keyboard::Enter))
					{
						window.close();
						ext = 1;
						break;
					}
				}

				if (hp > 0)
				{
					// Updates:

					// Player Updates:
					if (Keyboard::isKeyPressed(Keyboard::A) && player.getPosition().x >= 0)
						player.move(-5.f, 0.f);
					if (Keyboard::isKeyPressed(Keyboard::D) && player.getPosition().x <= window.getSize().x - 60.f)
						player.move(5.f, 0.f);
					if (Keyboard::isKeyPressed(Keyboard::W) && player.getPosition().y >= 0)
						player.move(0.f, -5.f);
					if (Keyboard::isKeyPressed(Keyboard::S) && player.getPosition().y <= window.getSize().y - 80.f)
						player.move(0.f, 5.f);

					playerCenter = Vector2f(player.getPosition().x + player.getScale().x + 25, player.getPosition().y + player.getScale().y);

					// Enemy Updates:

					while (rows < 2 + rep)
					{
						while (lenPos < (int)window.getSize().x * rows)
						{
							enemy.setPosition(lenPos - (int)window.getSize().x * (rows - 1), depPos); // Block element of array || (rand() % window.getSize().x - 50, 0)
							enemies.push_back(Sprite(enemy));
							lenPos += 60;
							enemCount++;
						}
						depPos += 50;
						rows++;
					}

					for (size_t i = 0; i < enemies.size(); i++) // Functions performed by the array vector
					{
						if (enemies[i].getPosition().y > window.getSize().y)
							enemies.erase(enemies.begin() + i);
					}

					//Bullet Updates:
					if (bulletRate <= bulletGap)
						bulletRate++;

					if (bulletRate >= bulletGap)
					{
						// Enemy Bullets:
						for (size_t i = rand() % 10; i < enemies.size(); i = i + rand() % 20) // For every enemy (rand() % (b - a) + a)
						{
							enemBullet.setPosition(enemies[i].getPosition().x + 30, enemies[i].getPosition().y + 30);
							enemBullets.push_back(RectangleShape(enemBullet));
						}

						//Player Bullets:
						if (Mouse::isButtonPressed(Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space))
						{
							bulletSound.play();
							playerBullet.setPosition(playerCenter);
							playerBullets.push_back(RectangleShape(playerBullet));
						}
						bulletRate = 0;
					}

					for (size_t i = 0; i < enemBullets.size(); i++)
					{
						enemBullets[i].move(0, 8.f);
						if (enemBullets[i].getPosition().y > window.getSize().y)
						{
							enemBullets.erase(enemBullets.begin() + i);
						}
					}

					for (size_t i = 0; i < playerBullets.size(); i++)
					{
						playerBullets[i].move(0, -13.f);
						if (playerBullets[i].getPosition().y < 0)
							playerBullets.erase(playerBullets.begin() + i);
					}

					// Collision Detection:
					for (size_t i = 0; i < playerBullets.size(); i++) // Player bullets and enemies collisions
					{
						for (size_t j = 0; j < enemies.size(); j++)
						{
							if (enemies[j].getGlobalBounds().intersects(playerBullets[i].getGlobalBounds()))
							{
								enemFinish++;
								score++;
								enemies.erase(enemies.begin() + j);
								playerBullets.erase(playerBullets.begin() + i);
								break;
							}
						}
					}

					for (size_t i = 0; i < enemies.size(); i++) // Player and enemies collisions
					{
						if (enemies[i].getGlobalBounds().intersects(player.getGlobalBounds()))
						{
							enemFinish++;
							hp--;
							score++;
							enemies.erase(enemies.begin() + i);
						}
					}

					for (size_t i = 0; i < enemBullets.size(); i++) // Player and enemy bullets collision
					{
						if (enemBullets[i].getGlobalBounds().intersects(player.getGlobalBounds()))
						{
							hp--;
							enemBullets.erase(enemBullets.begin() + i);
						}
					}

					// hpBar size:
					hpBar.setSize(Vector2f((float)hp * 10.f, 20.f));
					count.setString("Score:" + to_string(score)); // In the game
					scoreText.setString(to_string(score));		  // For the end page

					if (hp <= 0)
					{
						bulletSound.stop();
					}
				}

				if (hp <= 0)
				{
					Over.setString("GAME OVER");
				}

				if (enemFinish == enemCount)
				{
					rep++;
					break;
					// window.close();
				}

				//Render:
				window.clear();
				window.draw(player);
				window.draw(hpBar);
				window.draw(level);
				window.draw(text);
				window.draw(count);
				window.draw(Over);

				for (size_t i = 0; i < enemies.size(); i++)
				{
					window.draw(enemies[i]);
				}

				for (size_t i = 0; i < playerBullets.size(); i++)
				{
					window.draw(playerBullets[i]);
				}

				for (size_t i = 0; i < enemBullets.size(); i++)
				{
					window.draw(enemBullets[i]);
				}

				window.display();

				// End Screen:
				if (ext == 1) // When the game screen is over
				{
					gameMusic.stop();
					RenderWindow window(VideoMode(600, 700), "The Shot", Style::Default);
					window.setFramerateLimit(60);

					while (window.isOpen())
					{
						Event S;
						while (window.pollEvent(S))
						{
							if (S.type == S.Closed || Keyboard::isKeyPressed(Keyboard::Escape))
							{
								window.close();
							}
						}
						window.clear();
						window.draw(endpage);
						window.draw(scoreText);
						// endpageMusic.play();
						window.display();
					}
				}
			}

			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
				break;
			}
			if (ext == 1)
			{
				break;
			}
		}
	}

	cout << "You fought well!" << endl
		 << "Your Score: " << score << endl;

	return 0;
}