/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Languages
*/

#include "Languages.hpp"
#include "Globals.hpp"

void prepare_language(int ac, char const * const av[])
{
    nlohmann::json load_json;
    std::ifstream load_path("../assets/lang/load.json");
    load_json = nlohmann::json::parse(load_path);
    for (auto &it : load_json.items())
            dict_path[it.key()] = it.value();
    std::string lang = "en";
    for (int i = 0; i < ac; i++) {
        if (std::string(av[i]) == "-l") {
            if (i + 1 < ac) {
                lang = av[i + 1];
            }
        }
    }
    load_language(lang);
}

void load_language(std::string lang)
{
    std::ifstream file(dict_path[lang]);
    nlohmann::json file_json;
    if (!file.good())
        file = std::ifstream(dict_path["en"]);
    file_json = nlohmann::json::parse(file);
    Globals::font.loadFromFile(file_json["font"]);
    for (auto &it : file_json["dictionnary"].items())
            dictionnary_language[it.key()] = it.value();
}

void display_dict(void)
{
    for (auto &it : dictionnary_language) {
        std::cout << it.first << " : " << it.second << std::endl;
    }
}