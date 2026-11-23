#include "high_scores.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

static const std::string HIGH_SCORES_FILENAME = "high_scores.txt";

// Внутренняя функция загрузки таблицы рекордов из файла в std::map
static std::map<std::string, int> load_scores()
{
    std::map<std::string, int> scores;
    std::ifstream in_file{HIGH_SCORES_FILENAME};

    if (!in_file.is_open())
    {
        // Файла ещё может не существовать (первый запуск) — возвращаем пустую таблицу
        return scores;
    }

    std::string username;
    int high_score = 0;
    while (in_file >> username >> high_score)
    {
        // Если в файле вдруг были дубликаты, оставляем лучший (минимальный) результат
        std::map<std::string, int>::iterator it = scores.find(username);
        if (it == scores.end() || high_score < it->second)
        {
            scores[username] = high_score;
        }
    }

    return scores;
}

void save_high_score(const std::string& user_name, int attempts_count)
{
    // Загружаем текущие рекорды в память
    std::map<std::string, int> scores = load_scores();

    // Проверяем, нужно ли обновлять запись для текущего игрока
    std::map<std::string, int>::iterator it = scores.find(user_name);
    if (it != scores.end() && attempts_count >= it->second)
    {
        // Игрок уже есть в таблице, и его новый результат не лучше старого — выходим
        return;
    }

    // Обновляем или добавляем новый лучший результат
    scores[user_name] = attempts_count;

    // Перезаписываем файл актуальной таблицей
    std::ofstream out_file{HIGH_SCORES_FILENAME};
    if (!out_file.is_open())
    {
        std::cout << "Error: failed to open file for write: " << HIGH_SCORES_FILENAME << "!" << std::endl;
        return;
    }

    for (const auto& entry : scores)
    {
        out_file << entry.first << ' ' << entry.second << '\n';
    }
}

void print_high_scores()
{
    std::ifstream in_file{HIGH_SCORES_FILENAME};
    if (!in_file.is_open())
    {
        std::cout << "High scores table is empty yet (file '" << HIGH_SCORES_FILENAME << "' not found)." << std::endl;
        return;
    }

    std::cout << "High scores table:" << std::endl;

    std::string username;
    int high_score = 0;
    while (in_file >> username >> high_score)
    {
        // Выводим информацию на экран (разделяя табуляцией \t)
        std::cout << username << '\t' << high_score << std::endl;
    }
}
