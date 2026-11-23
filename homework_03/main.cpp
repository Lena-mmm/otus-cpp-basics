#include "game.h"
#include "high_scores.h"

#include <iostream>
#include <limits>
#include <string>

// Очищает остаток текущей строки во входном потоке (защита от лишних слов и ошибок ввода)
void clear_input_line()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Выводит меню команд с отображением текущих настроек сессии
void print_menu(const std::string& player_name, int max_value)
{
    std::cout << "\n========================================\n";
    std::cout << "Player: " << player_name << " | Range: [0 .. " << max_value << ")\n";
    std::cout << "Available commands:\n";
    std::cout << "  play         - start a new game\n";
    std::cout << "  max <number> - set upper limit (e.g., max 50)\n";
    std::cout << "  name <name>  - change player name (e.g., name Bob)\n";
    std::cout << "  table        - show high scores table\n";
    std::cout << "  help         - show this menu\n";
    std::cout << "  exit         - quit the game\n";
    std::cout << "========================================\n\n";
}

int main()
{
    int max_value = 100;
    std::string player_name;

    std::cout << "Welcome to 'Guess the Number'!\n";
    std::cout << "Enter your name (one word): ";
    std::cin >> player_name;
    clear_input_line();

    print_menu(player_name, max_value);

    std::string command;
    while (true)
    {
        std::cout << "\n> ";
        if (!(std::cin >> command))
        {
            break; // Выход при закрытии потока ввода (например, Ctrl+Z / Ctrl+D)
        }

        if (command == "play")
        {
            clear_input_line();
            int attempts = play_game(max_value);
            if (attempts > 0)
            {
                save_high_score(player_name, attempts);
                print_high_scores();
            }
            print_menu(player_name, max_value);
        }
        else if (command == "max")
        {
            int new_max = 0;
            std::cin >> new_max;

            if (std::cin.fail() || new_max <= 0)
            {
                std::cout << "Error: please enter a positive integer (e.g., max 50).\n";
            }
            else
            {
                max_value = new_max;
                std::cout << "Upper limit updated to " << max_value << ".\n";
            }
            clear_input_line();
        }
        else if (command == "name")
        {
            std::string new_name;
            std::cin >> new_name;

            if (std::cin.fail() || new_name.empty())
            {
                std::cout << "Error: please enter a valid name (one word).\n";
            } 
            else
            {
                player_name = new_name;
                std::cout << "Player name changed to " << player_name << ".\n";
            }
            clear_input_line();
        }
        else if (command == "table")
        {
            clear_input_line();
            print_high_scores();
        }
        else if (command == "help")
        {
            clear_input_line();
            print_menu(player_name, max_value);
        }
        else if (command == "exit")
        {
            std::cout << "Goodbye, " << player_name << "!\n";
            break;
        }
        else
        {
            std::cout << "Unknown command '" << command << "'. Type 'help' to see available commands.\n";
            clear_input_line();
        }
    }

    return 0;
}
