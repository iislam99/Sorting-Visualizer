#pragma once
#include <vector>
#include "Button.h"

class user_interface
{
private:
	sf::RenderWindow* _win;
	sf::RectangleShape _toolbar;
	sf::RectangleShape _base;
	std::map<std::string, Button*> _buttonList;
	
	std::vector<sf::RectangleShape> _bars;
	unsigned short _bars_size;
	
	// Bar constraints
	unsigned short _bars_min_x;
	unsigned short _bars_max_x;
	unsigned short _bars_min_y;
	unsigned short _bars_max_y;

	unsigned short _bar_width;
	unsigned short _space_btw_bars;

	// Controls and current speed text
	sf::Font _font;
	sf::Text _controls;
	sf::Text _curr_speed;

	// Sorting attributes
	unsigned short _default_speed;
	unsigned short _animation_speed;
	sf::Time _time;
	bool _exit;

public:
	user_interface(sf::RenderWindow*, unsigned int, unsigned int, sf::Font*);
	void checkButtonClick(sf::Vector2f, sf::RenderWindow*);
	void resetBars();
	void render(std::vector<sf::RectangleShape>* left = nullptr, std::vector<sf::RectangleShape>* right = nullptr);
	~user_interface();

	// Sorting
	void detect_input(sf::RenderWindow* win);
	void setAnimationSpeed(unsigned short);
	void swap(sf::RectangleShape*, sf::RectangleShape*);

	void bubbleSort();
	void insertionSort();
	void merge(std::vector<sf::RectangleShape>*, unsigned short, unsigned short, unsigned short);
	void mergeSort();
	void selectionSort();
};