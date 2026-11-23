#include "game.h"

#include <iostream>

int play_game(int max_value)
{
    // Используем текущее время в качестве начального значения для генератора случайных чисел
	static const bool is_seeded = []() {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		return true;
	}();


	const int random_value = std::rand() % max_value;

	int current_value = -1;     // Переменная для хранения текущей догадки игрока
	int attempt_counter = 0;	// Переменная для хранения количества попыток

	std::cout << "Enter your guess:" << std::endl;

	while (current_value != random_value)
	{
		std::cin >> current_value;

		// Защита от ввода букв вместо числа
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number:" << std::endl;
			current_value = -1; // Сбрасываем на случай, если при ошибке ввода std::cin записал 0
            continue;
        }

		// Очищаем остаток строки (если ввели что-то лишнее после числа)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
		if (current_value > random_value) 
		{
			std::cout << "less than " << current_value << std::endl;
		}
		else if (current_value < random_value) 
		{
			std::cout << "greater than " << current_value << std::endl;
		}
		++attempt_counter;
	}

	std::cout << "You win! Total attempts: " << attempt_counter << std::endl;
	return attempt_counter;
}
