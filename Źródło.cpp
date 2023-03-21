#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

using namespace sf;

int main()
{
	const signed szerokosc_okna = 800;
	const signed wysokosc_okna = 800;
	sf::RenderWindow window(sf::VideoMode(szerokosc_okna, wysokosc_okna), "test");
	window.setFramerateLimit(120);
	sf::Event e;
	float dt;
	sf::Clock dt_clock;
	
	const float grid = 50.f;

	//Gracz
	sf::RectangleShape gracz;
	gracz.setSize(sf::Vector2f(grid, grid));
	gracz.setPosition(400, 400);


	const float szybkoscRuchu = 100.f;
	sf::Vector2f Velocity;
	while (window.isOpen())
	{
		dt = dt_clock.restart().asSeconds();

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		window.draw(gracz);
		window.display();


		Velocity.y = 2.f;
		Velocity.x = 0.f;	
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Velocity.x += -szybkoscRuchu * dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Velocity.x += szybkoscRuchu * dt;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			Velocity.y += -szybkoscRuchu *2*Velocity.y* dt;
		}
		gracz.move(Velocity);

		//Kolizja Z Ekranem
		//Lewo
		if (gracz.getPosition().x < 0.f) //pobiera pozycje, 0.f to krawedz ekranu z lewej
		{
			gracz.setPosition(0.f, gracz.getPosition().y); // ustawia pozycje x na krawedz ekranu, a pozycje y zostawia tak jak byla.
		}
		//Gora
		if (gracz.getPosition().y < 0.f)
		{
			gracz.setPosition(gracz.getPosition().x, 0.f); // Analogicznie do kolizji z lewą strona ekranu
		}
		//Right
		if (gracz.getPosition().x + gracz.getGlobalBounds().width > szerokosc_okna) //pobieramy pozycje X gracza i dodajemy do niej jego wielkosc, tzw bound, porownujemy do wielkosci okna 
		{
			gracz.setPosition(szerokosc_okna - gracz.getGlobalBounds().width, gracz.getPosition().y);
		}
		//Down
		if (gracz.getPosition().y + gracz.getGlobalBounds().height > wysokosc_okna)
		{
			gracz.setPosition(gracz.getPosition().x, wysokosc_okna - gracz.getGlobalBounds().height);
		}
	}
}
