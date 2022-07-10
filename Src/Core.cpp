#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

void random_colour_picker(sf::CircleShape& elem);

void grower(std::vector<sf::CircleShape>& elem, unsigned int& skips, unsigned int& curr, float dt) // gets the current size of the shape and increase it by a rate
{ 
	float rate = 10.f; 
	float fadeRate = 0.005f;
	for (int i = 0; i < elem.size(); i++)
	{

		if (elem[i].getRadius() <= 350.f and elem[i].getFillColor().a >= 2)
		{
			elem[i].setRadius(elem[i].getRadius() + rate * dt);

			elem[i].setFillColor(sf::Color(elem[i].getFillColor().r, elem[i].getFillColor().g, elem[i].getFillColor().b, elem[i].getFillColor().a - fadeRate * dt));


		}
		else
		{
			skips++;
			curr--;
			auto itr = elem.begin() + i;
			elem.erase(itr);
		}


	}
}

int main()
{
	unsigned int skips = 0; // will store the count of circle which have reched the limit of growth
	unsigned int curr = 0;
	std::cout << "The app has started\n";
	srand(time_t(0));
	const short height = 800, width = 600;
	sf::RenderWindow win(sf::VideoMode(height, width), "Colours");
	sf::RenderWindow logs(sf::VideoMode(300, 200), "Logs");
	win.setFramerateLimit(30);

	sf::Vector3<int> what_color;
	std::vector<sf::CircleShape> objects; // a vector of the circles

	bool is_drawn = false;

	sf::CircleShape sh1;

	sf::Event events;
	sf::Event logs_event;

	sf::Vector2i df;

	sf::Font font;

	const std::string file = "Res/times.ttf";
	sf::Clock Clock;
	sf::Time dt;
	float seconds;
	font.loadFromFile(file);

	sf::Text count("", font, 15);
	sf::Text current("", font, 16);
	count.setPosition(5, count.getPosition().y);
	current.setPosition(5, 20);

	while (win.isOpen())
	{
		while (win.pollEvent(events) or logs.pollEvent(logs_event))
		{
			if (events.type == sf::Event::Closed)
			{
				win.close();
				std::cout << "Windows has been closed successfully\n";
				return EXIT_SUCCESS;

			}

		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{


			//df= sf::Mouse::getPosition(win); //Use this for accurate position i use the below cause i can see the circles better
			df = sf::Mouse::getPosition();
			sh1.setPosition(df.x, df.y);

			sf::Vector3i range(rand() % 255 + 1, rand() % 150 + 1, rand() % 105 + 1);
			sh1.setFillColor(sf::Color(range.x, range.y, range.z));

			sh1.setRadius(1.f); //set the initial radius of the circle

			objects.push_back(sh1); // pushing the new shape into the stack
			curr++;
		}

		dt = Clock.restart(); 
		seconds = dt.asSeconds();
		grower(objects, skips, curr, seconds); // grow,fade and remove the useless cirlces


		win.clear();

		for (int i = 0; i < objects.size(); i++)
		{
			win.draw(objects[i]);
		}

		win.display();


		count.setString("Total Processing: " + std::to_string(skips));
		current.setString("Currently Processing: " + std::to_string(curr));

		logs.clear();
		logs.draw(count);
		logs.draw(current);
		logs.display();



	}

	return EXIT_FAILURE;
}


void random_colour_picker(sf::CircleShape& elem) // returns a random colour 
{
	srand(time_t(NULL));
	sf::Vector3i range(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
	elem.setFillColor(sf::Color(range.x, range.y, range.z));

}