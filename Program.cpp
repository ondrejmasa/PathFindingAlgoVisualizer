#include "Program.h"


void Program::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(gbl::SCREEN::WIDTH, gbl::SCREEN::HEIGHT)), "Game 3", sf::Style::Close | sf::Style::Titlebar);
	this->window->setVerticalSyncEnabled(true);
}

void Program::pollEvents()
{
	while (const std::optional event = this->window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			this->window->close();

		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				this->window->close();
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
			{
				this->restart();
			}

			else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
			{
				if (this->BFSFinished)
				{
					startAgain();
				}
				else
				{
					this->BFSStart = not this->BFSStart;
				}
			}
		}
	}
}

void Program::updateMapWalls()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) or sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		if (!this->isMouseDown)
		{
			this->mouseCoordStart = this->getCellCoords(sf::Mouse::getPosition(*this->window));
			this->isMouseDown = true;
		}
	}
	else
	{
		this->isMouseDown = false;
	}

	if (this->isMouseDown)
	{
		sf::Vector2i mouseCoord = this->getCellCoords(sf::Mouse::getPosition(*this->window));
		unsigned char dx = std::abs(mouseCoordStart.x - mouseCoord.x);
		unsigned char dy = std::abs(mouseCoordStart.y - mouseCoord.y);

		char sx = gbl::sign(mouseCoord.x - mouseCoordStart.x);
		char sy = gbl::sign(mouseCoord.y - mouseCoordStart.y);

		char err = dx - dy;

		sf::Vector2i c = mouseCoordStart;
		while (true)
		{
			if (c.x >= 0 and c.x < gbl::MAP::ROWS and c.y >= 0 and c.y < gbl::MAP::COLUMNS)
			{
				gbl::MAP::Cell& cell = this->map.getCellAtCoords(c);
				if (c != this->map.startPos and c != this->map.finishPos)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						if (cell != gbl::MAP::Cell::Wall)
						{
							if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
							{
								this->map.startPos = c;
							}
							else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::F))
							{
								this->map.finishPos = c;
							}
							else
							{
								cell = gbl::MAP::Cell::Wall;
							}
						}
					}
					else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
					{
						cell = gbl::MAP::Cell::Empty;
					}
					mapUpdated = true;
				}
			}
			if (c == mouseCoord)
				break;
			int e2 = 2 * err;
			if (e2 > -dy)
			{
				err -= dy;
				c.x += sx;
			}
			if (e2 < dx)
			{
				err += dx;
				c.y += sy;
			}

		}
		this->mouseCoordStart = mouseCoord;
	}
}

void Program::restart()
{
	this->map.clearGrid();
	this->BFSStart = false;
	this->BFSFinished = false;
	this->mapUpdated = true;
}

void Program::startAgain()
{
	BfsRestart(this->BFSQueue, this->map.startPos, this->map.finishPos, this->map.grid, this->BFSPrevPos, this->pathLength);
	this->mapUpdated = false;
	this->BFSFinished = false;
}

sf::Vector2i Program::getCellCoords(sf::Vector2i pos)
{
	return sf::Vector2i((pos.y - gbl::MAP::MARGIN) / (gbl::MAP::CELL_SIZE + gbl::MAP::GAP),
						(pos.x - gbl::MAP::MARGIN) / (gbl::MAP::CELL_SIZE + gbl::MAP::GAP));
}

void Program::initText()
{
	if (!this->font.openFromFile("fonts/Minecraft.ttf"))
	{
		std::cout << "ERROR in loading font \n";
	}
	this->pathLenText.emplace(sf::Text(this->font, "TEST", 16u));
	this->pathLenText->setOrigin(sf::Vector2f(0.f, 4.f));
	this->pathLenText->setPosition(sf::Vector2f(2*gbl::MAP::MARGIN + gbl::MAP::COLUMNS * (gbl::MAP::CELL_SIZE + gbl::MAP::GAP), gbl::MAP::MARGIN));
}

void Program::renderText(sf::RenderTarget* target)
{
	if (this->BFSFinished)
	{
		target->draw(*this->pathLenText);
	}
}

void Program::updateText()
{
	std::stringstream ss;
	ss << "Path length: " << this->pathLength;
	this->pathLenText->setString(ss.str());
}

void Program::initSounds()
{
	if (!soundBuffer.loadFromFile("sounds/beep.wav"))
	{
		std::cout << "ERROR in loading sound buffer";
	}
}

void Program::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

void Program::update()
{
	this->pollEvents();
	this->updateMapWalls();

	sf::Time dt = clock.restart();  // delta time (èas jednoho framu)
	timer += dt;
	frameCount++;

	if (timer.asSeconds() >= 1.0f)
	{
		fps = frameCount / timer.asSeconds();
		frameCount = 0;
		timer = sf::Time::Zero;

		//std::cout << "FPS: " << fps << std::endl;
	}

	if (BFSStart and not BFSFinished)
	{
		BFSFinished = bfsSearch(this->BFSQueue, this->map.startPos, this->map.finishPos, this->map.grid, this->BFSPrevPos, this->pathLength, this->beepSound);
	}
	if (this->mapUpdated)
	{
		startAgain();
	}

	this->updateText();
}

void Program::render()
{
	this->window->clear();

	this->map.drawGrid(*this->window);
	this->renderText(this->window);
	
	this->window->display();
}

Program::Program()
	: beepSound(soundBuffer)
{
	this->initWindow();
	this->initText();
	this->initSounds();
}

Program::~Program()
{
	delete this->window;
}
