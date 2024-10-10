/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 09:29:57 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/09 22:06:47 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Colors.hpp"
#include "../includes/Calendar.hpp"
#include "../includes/BitcoinExchange.hpp"

#include <cstdlib>
#include <utility>

static void calendarTests(int ac, char **av) {
  Calendar calendar;

  if (ac == 3) {
    int minYY = std::atoi(av[1]);
    int maxYY = std::atoi(av[2]);
    if (minYY > maxYY)
      std::swap(maxYY, minYY);
    calendar.printLeapYears(minYY, maxYY);
    return;
  }

  if (ac == 5) {
    int day = std::atoi(av[1]);
    int month = std::atoi(av[2]);
    int year = std::atoi(av[3]);
    int add = std::atoi(av[4]);
    if (calendar.dateIsWrong(day, month, year))
      return;
    calendar.add_days_to_date(month, day, year, add);
  }
}

int main(int ac, char **av) {
  if (ac == 1 || (ac == 2 && std::string(av[1]) == "-h")) {
    std::cout << "- Calcul the value of the bitcoins possessed at a certain date :" << std::endl;
    std::cout << "Usage : ./btc [filename]" << std::endl;
    std::cout << "- Add an amount of days to a date to know the future date :" << std::endl;
    std::cout << "Usage : ./btc [day] [month] [year] [days to add]" << std::endl;
    std::cout << "- Print every leap year between two date :" << std::endl;
    std::cout << "Usage : ./btc [min year] [max year]" << std::endl;
    return (0);
  }

  calendarTests(ac, av);
  
  if (ac != 2) {
      // std::cerr << RED "Error: wrong number of arguments" RESET << std::endl;
      // std::cerr << "Usage : ./btc [filename]" << std::endl;
      return (0);
  }

  const std::string s1 = av[1];

  if (s1.empty()) {
      std::cerr << RED "Error: s1 or s2 is empty" RESET << std::endl;
      return (1);
  }
  BitcoinExchange file(s1);
  file.searchBitcoinValue();

  return (0);
}

