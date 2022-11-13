/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TextConst
*/

#ifndef LANGUAGES_HPP_
#define LANGUAGES_HPP_

#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

/*!
 *  \addtogroup LanguageManagement
 *  @{
 */

inline std::map<std::string, std::string> dict_path = {};

inline std::map<std::string, std::string> dictionnary_language = {};

/**
 * @brief prepare the different languages and load the wanted language
 *
 * @param ac : arguments of the main (number of arguments)
 * @param av : arguments of the main (arguments)
 */
void prepare_language(int ac, char const * const av[]);

/**
 * @brief load the wanted language
 *
 * @param lang : language to load (en, fr, ...)
 */
void load_language(std::string lang);

/**
 * @brief display the dictionnary of the language
 *
 */
void display_dict(void);


#endif /* !LANGUAGES_HPP_ */
