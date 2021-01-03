#include "user_interface.h"
#include <ctime>

// Initialize UI
user_interface::user_interface(sf::RenderWindow* window, unsigned int screenWidth, unsigned int screenHeight, sf::Font* font)
{
	// Window
	_win = window;

	// Toolbar
    	_toolbar.setSize(sf::Vector2f(screenWidth, screenHeight / 10));
   	 _toolbar.setFillColor(sf::Color(150, 150, 150, 100));
    
	// Sorting
	_exit = false;
	_default_speed = 101;
	_animation_speed = _default_speed;

    	// Base for bars
    	_base.setPosition(screenWidth / 20, screenHeight - screenHeight / 10);
    	_base.setSize(sf::Vector2f(screenWidth - (screenWidth / 20), screenHeight / 80));

	// Initialize bars
	resetBars();

	// Button attributes
	float btnHeight = _toolbar.getGlobalBounds().height / 2;
	float btnWidth = btnHeight * 3;

	// Font
	this->_font = *font;

	// Controls
	_controls.setFont(this->_font);
	_controls.setFillColor(sf::Color::White);
	_controls.setCharacterSize(btnHeight / 2);
	_controls.setString("Press UP to increase sort speed     |     Press DOWN to decrease sort speed     |     Press ESC to stop sorting");
	_controls.setPosition(screenWidth / 2 - _controls.getGlobalBounds().width / 2, _base.getPosition().y + btnHeight / 4);

	// Current speed
	_curr_speed.setFont(this->_font);
	_curr_speed.setFillColor(sf::Color::White);
	_curr_speed.setCharacterSize(btnHeight / 2);
	_curr_speed.setString("Current Speed (1-10): 8");
	_curr_speed.setPosition(screenWidth / 2 - _curr_speed.getGlobalBounds().width / 2, _base.getPosition().y + btnHeight);
    
    	// Reset button
	_buttonList["RESET"] = new Button
		((screenWidth / 5 - btnWidth / 2), btnHeight / 2,
		btnWidth, btnHeight, "RESET", btnHeight / 1.5, this->_font,
		sf::Color(200, 0, 0, 255), sf::Color(150, 0, 0, 255), sf::Color(200, 50, 50, 255));

    	// Bubble Sort Button
	_buttonList["BUBBLE"] = new Button
		(2 * (screenWidth / 5 - btnWidth / 2), btnHeight / 2,
		btnWidth, btnHeight, "Bubble", btnHeight / 1.5, this->_font,
		sf::Color(0, 100, 0, 255), sf::Color(100, 200, 100, 255), sf::Color(0, 200, 0, 255));

    	// Insertion Sort Button
	_buttonList["INSERTION"] = new Button
		(3 * (screenWidth / 5 - btnWidth / 2), btnHeight / 2,
		btnWidth, btnHeight, "Insertion", btnHeight / 1.5, this->_font,
		sf::Color(0, 100, 0, 255), sf::Color(100, 200, 100, 255), sf::Color(0, 200, 0, 255));

    	// Merge Sort Button
	_buttonList["MERGE"] = new Button
		(4 * (screenWidth / 5 - btnWidth / 2), btnHeight / 2,
		btnWidth, btnHeight, "Merge", btnHeight / 1.5, this->_font,
		sf::Color(0, 100, 0, 255), sf::Color(100, 200, 100, 255), sf::Color(0, 200, 0, 255));

    	// Selection Sort Button
	_buttonList["SELECTION"] = new Button
		(5 * (screenWidth / 5 - btnWidth / 2), btnHeight / 2,
		btnWidth, btnHeight, "Selection", btnHeight / 1.5, this->_font,
		sf::Color(0, 100, 0, 255), sf::Color(100, 200, 100, 255), sf::Color(0, 200, 0, 255));
}

// Checks if buttons are clicked
void user_interface::checkButtonClick(sf::Vector2f mousePos, sf::RenderWindow* win)
{
	for (auto& it : _buttonList)
		it.second->checkClick(mousePos);

	if (_buttonList["RESET"]->isPressed())
        	resetBars();
    
    	if (_buttonList["BUBBLE"]->isPressed())
        	bubbleSort();
	
    	if (_buttonList["INSERTION"]->isPressed())
        	insertionSort();
	
    	if (_buttonList["MERGE"]->isPressed())
		mergeSort();
	
    	if (_buttonList["SELECTION"]->isPressed())
		selectionSort();
}

// Randomizes bars
void user_interface::resetBars()
{
    	srand(time(NULL));
    	this->_bars.clear();

	_bars_size = 48;
	_space_btw_bars = _base.getGlobalBounds().height / 2;
	_bar_width = (_base.getGlobalBounds().width / _bars_size) - _space_btw_bars;
    
	_bars_min_x = _base.getPosition().x;
	_bars_max_x = _bars_min_x + _base.getGlobalBounds().width;
    
	_bars_min_y = _toolbar.getGlobalBounds().height;
	_bars_max_y = _base.getPosition().y;
    
    	for (unsigned short i = 0; i < _bars_size; i++)
    	{
		unsigned short x = _bars_min_x + i * (_bar_width + _space_btw_bars);
		unsigned short y = rand() % _bars_size + 1;
		y = _bars_max_y - y * (_bars_max_y / _bars_min_y);

		sf::RectangleShape temp;
		temp.setPosition(sf::Vector2f(x, y));
		temp.setSize(sf::Vector2f(_bar_width, _bars_max_y - y));
		temp.setFillColor(sf::Color::Blue);
        
        	this->_bars.push_back(temp);
    	}
}

// Display everything on screen
void user_interface::render(std::vector<sf::RectangleShape>* left, std::vector<sf::RectangleShape>* right)
{
	// Clear window
	_win->clear(sf::Color::Black);

	// Display toolbar
	_win->draw(_toolbar);

	// Display buttons
	for (auto& it : _buttonList)
		it.second->render(_win);

    	// Display bars
	for (auto& it : _bars)
		_win->draw(it);

    	// Display controls and speed
	_win->draw(_controls);
	_win->draw(_curr_speed);

	// Delay
	sf::sleep(_time);

	// Event handling
	detect_input(_win);
	
	// Update display
	_win->display();
}

user_interface::~user_interface()
{
	for (auto& it : _buttonList)
		delete it.second;
}

// Event handling
void user_interface::detect_input(sf::RenderWindow* win)
{
	sf::Event event;
	while (win->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			win->close();
			break;
		}
		case sf::Event::KeyReleased:
		{
			// Increase sort speed
			if (event.key.code == sf::Keyboard::Up)
			{
				if (_animation_speed > 1)
					_animation_speed -= 50;
				setAnimationSpeed(_animation_speed);
			}
			// Decrease sort speed
			else if (event.key.code == sf::Keyboard::Down)
			{
				if (_animation_speed < 451)
					_animation_speed += 50;
				setAnimationSpeed(_animation_speed);
			}
			// Exit sorting
			else if (event.key.code == sf::Keyboard::Escape)
			{
				_exit = true;
			}

			break;
		}
		default:
			break;
		}
	}
}

// Set animation speed
void user_interface::setAnimationSpeed(unsigned short num)
{
	_time = sf::milliseconds(num);
	std::string temp = "Current Speed (1-10): " + std::to_string(10 - num / 50);
	_curr_speed.setString(temp);
}

// Swaps locations of two bars
void user_interface::swap(sf::RectangleShape* a, sf::RectangleShape* b)
{
	float temp_y = a->getPosition().y;
	float temp_height = a->getGlobalBounds().height;
	sf::Color temp_color = a->getFillColor();

	a->setPosition(sf::Vector2f(a->getPosition().x, b->getPosition().y));
	a->setSize(sf::Vector2f(a->getGlobalBounds().width, b->getGlobalBounds().height));
	a->setFillColor(b->getFillColor());

	b->setPosition(sf::Vector2f(b->getPosition().x, temp_y));
	b->setSize(sf::Vector2f(b->getGlobalBounds().width, temp_height));
	b->setFillColor(temp_color);
}


// SORTING ALGORITHMS

// ALL COLOR CHANGES ARE FOR ANIMATION PURPOSES TO DEPICT SHIFTS AND SUCCESSFUL SORTING

// Bubble sort
void user_interface::bubbleSort()
{
	setAnimationSpeed(_default_speed);
	_exit = false;

	bool swapped = false;
	do {
		swapped = false;
		for (std::vector<sf::RectangleShape>::iterator it = _bars.begin(); it != _bars.end(); ++it)
		{
			if (it != _bars.end() - 1)
			{
				it->setFillColor(sf::Color::Red);
				(it + 1)->setFillColor(sf::Color::Red);
				render();

				if ((*it).getGlobalBounds().height > (*(it + 1)).getGlobalBounds().height)
				{
					// Swapping bars
					swap(&(*it), &(*(it + 1)));
					render();
					swapped = true;
				}

				it->setFillColor(sf::Color::Blue);
				(it + 1)->setFillColor(sf::Color::Blue);
				render();
			}
			if (_exit)
				break;
		}
	} while (swapped && !_exit);
	setAnimationSpeed(0);
}

// Insertion sort
void user_interface::insertionSort()
{
	setAnimationSpeed(_default_speed);
	_exit = false;

	for (std::vector<sf::RectangleShape>::iterator it = _bars.begin(); it != _bars.end() && !_exit; ++it)
	{
		if (it != _bars.begin())
		{
			// Current bar
			it->setFillColor(sf::Color::Red);
			render();

			// Bar left of current bar
			(it - 1)->setFillColor(sf::Color::Yellow);
			render();

			if (it->getGlobalBounds().height < (it - 1)->getGlobalBounds().height)
			{
				unsigned short temp_y = it->getPosition().y;
				unsigned short temp_height = it->getGlobalBounds().height;

				for (std::vector<sf::RectangleShape>::iterator it2 = it; it2 != _bars.begin() && !_exit; --it2)
				{
					if (it2->getGlobalBounds().height < (it2 - 1)->getGlobalBounds().height)
					{
						if (it != it2)
						{
							it2->setFillColor(sf::Color::Red);
							(it2 - 1)->setFillColor(sf::Color::Yellow);
							render();
						}
						// Swapping bars
						swap(&(*it2), &(*(it2 - 1)));

						render();

						if (it2 - 1 == _bars.begin())
						{
							it2->setFillColor(sf::Color::Blue);
							render();

							(it2 - 1)->setFillColor(sf::Color::Green);
							render();

							(it2 - 1)->setFillColor(sf::Color::Blue);
							render();
						}
						else
						{
							it2->setFillColor(sf::Color::Blue);
							render();
						}
					}
					else
					{
						it2->setFillColor(sf::Color::Red);
						(it2 - 1)->setFillColor(sf::Color::Yellow);
						render();

						(it2 - 1)->setFillColor(sf::Color::Blue);
						render();

						it2->setFillColor(sf::Color::Green);
						render();

						it2->setFillColor(sf::Color::Blue);
						render();

						break;
					}
				}
			}
			else
			{
				(it - 1)->setFillColor(sf::Color::Blue);
				render();

				it->setFillColor(sf::Color::Green);
				render();

				it->setFillColor(sf::Color::Blue);
				render();
			}

		}
	}
	// Setting all bars to blue if exiting sort
	if (_exit)
		for (auto& it : _bars)
			it.setFillColor(sf::Color::Blue);
	setAnimationSpeed(0);
}

// Merge for merge sort
void user_interface::merge(std::vector<sf::RectangleShape>* bars_p, unsigned short l, unsigned short m, unsigned short r)
{
	unsigned short i, j, k;
	unsigned short n1 = m - l + 1;
	unsigned short n2 = r - m;

	// Temp vectors
	std::vector<sf::RectangleShape> left;
	std::vector<sf::RectangleShape> right;

	for (auto& it : _bars)
	{
		left.push_back(it);
		right.push_back(it);
	}

	// Copy data from bars_p to temp vectors
	for (i = 0; i < n1 && !_exit; i++)
	{
		left[i].setPosition((*bars_p)[l + i].getPosition());
		left[i].setSize((*bars_p)[l + i].getSize());
		left[i].setFillColor((*bars_p)[l + i].getFillColor());
	}
		
	for (j = 0; j < n2 && !_exit; j++)
	{
		right[j].setPosition((*bars_p)[m + 1 + j].getPosition());
		right[j].setSize((*bars_p)[m + 1 + j].getSize());
		right[j].setFillColor((*bars_p)[m + 1 + j].getFillColor());
	}

	// Merge the temp vectors back into bars_p
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2 && !_exit)
	{
		if (left[i].getGlobalBounds().height < right[j].getGlobalBounds().height)
		{
			swap(&(*bars_p)[k], &left[i]);
			i++;
		}
		else
		{
			swap(&(*bars_p)[k], &right[j]);
			j++;
		}
		render();
		k++;
	}

	// Copy the remaining elements of left vector
	while (i < n1 && !_exit)
	{
		swap(&(*bars_p)[k], &left[i]);
		i++;
		k++;
	}

	// Copy the remaining elements of right vector
	while (j < n2 && !_exit)
	{
		swap(&(*bars_p)[k], &right[j]);
		j++;
		k++;
	}
}

// Merge sort
void user_interface::mergeSort()
{
	_exit = false;
	setAnimationSpeed(_default_speed);
	
	unsigned short curr_size;  // Number of sub-vectors
	unsigned short left_start; // Starting index of left sub-vector
	unsigned short n = _bars.size(); // Number of bars 

	// Merge sub-vectors in bottom up manner
	// Continously divides sub-vectors by two until no more divisions can be made
	for (curr_size = 1; curr_size <= n - 1 && !_exit; curr_size = 2 * curr_size)
	{
		// Finding starting and ending points of sub-vectors
		for (left_start = 0; left_start < n - 1 && !_exit; left_start += 2 * curr_size)
		{
			// mid = ending point of left; mid + 1 = is starting point of right 
			unsigned short mid;
			if (left_start + curr_size - 1 < n - 1)
				mid = left_start + curr_size - 1;
			else
				mid = n - 1;

			unsigned short right_end;
			if (left_start + 2 * curr_size - 1 < n - 1)
				right_end = left_start + 2 * curr_size - 1;
			else
				right_end = n - 1;

			// Comparison animation
			unsigned short i = left_start;
			unsigned j = mid + 1;
			while (i <= mid && j <= right_end && !_exit)
			{
				_bars[i].setFillColor(sf::Color::Red);
				_bars[j].setFillColor(sf::Color::Red);
				render();

				_bars[i].setFillColor(sf::Color::Blue);
				_bars[j].setFillColor(sf::Color::Blue);
				render();
				i++;
				j++;
			}
			
			// Merge sub-vectors
			merge(&_bars, left_start, mid, right_end);
		}
	}
	setAnimationSpeed(0);
}

// Selection sort
void user_interface::selectionSort()
{
	setAnimationSpeed(_default_speed);
	_exit = false;

	unsigned short cur_min_y;
	unsigned short cur_min_height;
	std::vector<sf::RectangleShape>::iterator cur_min_pos;

	for (std::vector<sf::RectangleShape>::iterator it = _bars.begin(); it != _bars.end() && !_exit; ++it)
	{
		it->setFillColor(sf::Color::Red);
		render();

		cur_min_height = it->getGlobalBounds().height;
		cur_min_pos = it;

		// Finding smallest bar right of current bar
		for (std::vector<sf::RectangleShape>::iterator it2 = it + 1; it2 != _bars.end() && !_exit; ++it2)
		{
			it2->setFillColor(sf::Color::Yellow);
			render();

			if (cur_min_height > it2->getGlobalBounds().height)
			{
				if (cur_min_pos != it)
					cur_min_pos->setFillColor(sf::Color::Blue);

				cur_min_height = it2->getGlobalBounds().height;
				cur_min_pos = it2;

				it2->setFillColor(sf::Color::Magenta);
				render();
			}
			else
			{
				it2->setFillColor(sf::Color::Blue);
				render();
			}
		}

		// Swapping current bar with smallest bar
		swap(&(*it), &(*cur_min_pos));

		render();

		cur_min_pos->setFillColor(sf::Color::Blue);
		render();

		(*it).setFillColor(sf::Color::Green);
		render();

		(*it).setFillColor(sf::Color::Blue);
		render();
	}
	setAnimationSpeed(0);
}
