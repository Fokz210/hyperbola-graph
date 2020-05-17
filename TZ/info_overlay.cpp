#include "info_overlay.h"

#define COLUMN_SIZE 220.f

info_overlay::info_overlay (sf::Font font, float window_width, float window_height, std::vector <model *> & models) :
	rectangular_window (sf::RectangleShape ()),
	m_window_height (window_height),
	m_window_width (window_width),
	buffer (""),
	m_info_blocks (),
	gap_x (30.f),
	gap_y (30.f),
	m_left_column (),
	m_right_column (),
	m_left_separator (),
	m_right_separator (),
	m_models (models),
	m_font (font),
	m_reload_button_ptr (nullptr),
	m_next_button_ptr (nullptr),
	left (gap_x, window_height - gap_y - 140, 220 - 2 * gap_x, 20, sf::Color (235, 122, 40), sf::Color (25, 118, 194), 0.f),
	right (window_width - 220 + gap_x, window_height - gap_y - 140, 220 - 2 * gap_x, 20, sf::Color (235, 122, 40), sf::Color (25, 118, 194), 0.f)
{
}

info_overlay::~info_overlay ()
{
	for (auto && el : m_info_blocks)
		if (el)
			delete el;

	for (auto && el : m_models)
		if (el)
			delete el;

	delete m_reload_button_ptr;
	delete m_next_button_ptr;
}

void info_overlay::init (window_manager & manager)
{
	m_models[0] = new model (manager, m_window_width, m_window_height);
	m_models[0]->init (100, 100, 2.f);

	m_models[1] = new model (manager, m_window_width, m_window_height);
	m_models[1]->init (100, 100, 2.f);
	m_models[1]->hide ();

	right.hide ();

	manager.add_window (&left);
	manager.add_window (&right);

	auto lambda1 = [&] ()
	{
		m_models[1]->show ();
		m_models[0]->lock ();
		right.show ();
	};

	sf::RectangleShape button_shape;

	text_button <decltype (lambda1)> * button1 = new text_button <decltype (lambda1)> (gap_x, m_window_height - 100 - gap_y - 10 , 220 - 2 * gap_x, 50, sf::Color (235, 122, 40), sf::Color (25, 118, 194), "Next iteration", m_font, lambda1);
	manager.add_window (button1);

	m_next_button_ptr = button1;

	auto lambda2 = [&]()
	{
		m_models[0]->show ();
		m_models[1]->hide ();

		right.hide ();

		left.reset ();
		right.reset ();

		m_models[0]->reset (100, 100);
		m_models[1]->reset (100, 100);
	};

	text_button <decltype (lambda2)> * button2 = new text_button <decltype (lambda2)> (gap_x, m_window_height - 50 - gap_y, 220 - 2 * gap_x, 50, sf::Color (235, 122, 40), sf::Color (25, 118, 194), "Reset", m_font, lambda2);
	manager.add_window (button2);

	m_reload_button_ptr = button2;

	m_info_blocks.push_back (new info_block (*m_models[0], m_font));
	m_info_blocks.push_back (nullptr);

	m_info_blocks[1] = new info_block (*m_models[1], m_font);
	m_info_blocks[1]->set_position (sf::Vector2f (m_window_width - gap_x - 155, gap_y));
	m_info_blocks[1]->set_title ("Iteration #2");

	m_right_column.setSize (sf::Vector2f (COLUMN_SIZE, m_window_height));
	m_right_column.setPosition (sf::Vector2f (m_window_width - COLUMN_SIZE, 0.f));
	m_right_column.setFillColor (sf::Color (245, 245, 245));

	m_left_column = m_right_column;
	m_left_column.setPosition (0.f, 0.f);

	m_left_separator.setSize (sf::Vector2f (1.f, m_window_height));
	m_left_separator.setFillColor (sf::Color (125, 125, 125));
	m_left_separator.setPosition (sf::Vector2f (COLUMN_SIZE - 1.f, 0));

	m_right_separator = m_left_separator;
	m_left_separator.setPosition (m_window_width - COLUMN_SIZE, 0);

	m_info_blocks[0]->set_position (sf::Vector2f (gap_x, gap_y));
	m_info_blocks[0]->set_title ("Iteration #1");

	
}

void info_overlay::update ()
{
	m_models[0]->set_scale ((left.get_value () + 0.25) * 4);
	m_models[1]->set_scale ((right.get_value () + 0.25) * 4);

	m_info_blocks[0]->update ();

	if (m_info_blocks[1])
		m_info_blocks[1]->update ();
}

void info_overlay::draw (sf::RenderTarget& window)
{
	window.draw (m_left_column);
	window.draw (m_right_column);
	window.draw (m_left_separator);
	window.draw (m_right_separator);

	m_info_blocks[0]->draw (window);

	if (!m_models[1]->m_hidden)
		m_info_blocks[1]->draw (window);
}

void info_overlay::update_resolution  (float window_width, float window_height)
{
	m_window_height = window_height;
	m_window_width = window_width;

	m_right_column.setSize (sf::Vector2f (COLUMN_SIZE, m_window_height));
	m_right_column.setPosition (sf::Vector2f (m_window_width - COLUMN_SIZE, 0.f));

	m_left_column = m_right_column;
	m_left_column.setPosition (0.f, 0.f);

	m_left_separator.setSize (sf::Vector2f (1.f, m_window_height));
	m_left_separator.setPosition (sf::Vector2f (COLUMN_SIZE - 1.f, 0));

	m_right_separator = m_left_separator;
	m_left_separator.setPosition (m_window_width - COLUMN_SIZE, 0);

	m_reload_button_ptr->set_position (sf::Vector2f(gap_x, m_window_height - 50 - gap_y));
	m_next_button_ptr->set_position (sf::Vector2f(gap_x, m_window_height - 100 - 10 - gap_y));

	m_info_blocks[0]->set_position (sf::Vector2f (gap_x, gap_y)); 
	m_info_blocks[1]->set_position (sf::Vector2f (m_window_width - gap_x - 155, gap_y));

	left.set_position (sf::Vector2f (gap_x, window_height - gap_y - 140));
	right.set_position (sf::Vector2f (window_width + gap_x, window_height - gap_y - 140));
}