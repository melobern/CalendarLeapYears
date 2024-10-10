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

#include <cstdlib>
#include <utility>
#include "../includes/Colors.hpp"
#include "../includes/Calendar.hpp"

static void printLeapYears(char **av) {
  Calendar calendar;
  int minYY = std::atoi(av[1]);
  int maxYY = std::atoi(av[2]);

  if (minYY > maxYY)
    std::swap(maxYY, minYY);
  calendar.printLeapYears(minYY, maxYY);
  return;
}

static void addDaysToDate(char **av) {
  Calendar calendar;
  int day = std::atoi(av[1]);
  int month = std::atoi(av[2]);
  int year = std::atoi(av[3]);
  int add = std::atoi(av[4]);

  if (calendar.dateIsWrong(day, month, year))
    return;
  calendar.add_days_to_date(month, day, year, add);
}

static void askIfIsLeapYear(char **av) {
  Calendar calendar;
  int year = std::atoi(av[1]);

  if (calendar.isLeap(year) && year != 0)
    std::cout << GREEN << year << " is a leap year." << RESET << std::endl;
  else
    std::cout << RED << year << " is not a leap year." << RESET << std::endl;
}

int main(int ac, char **av) {
  if ((ac != 3 && ac != 5)
       && (ac != 2  || (ac == 2 && std::string(av[1]) == "-h"))) {
    std::cout << "- Check if a year is leap :";
    std::cout << std::endl;
    std::cout << "Usage : ./cal [year]";
    std::cout << std::endl << std::endl;

    std::cout << "- Print every leap year between two date :";
    std::cout << std::endl;
    std::cout << "Usage : ./cal [min year] [max year]";
    std::cout << std::endl << std::endl;

    std::cout << "- Add an amount of days to a date to know the future date :";
    std::cout << std::endl;
    std::cout << "Usage : ./cal [day] [month] [year] [days to add]";
    std::cout << std::endl << std::endl;
    return (0);
  }

  if (ac == 2)
    askIfIsLeapYear(av);
  if (ac == 3)
    printLeapYears(av);
  if (ac == 5)
    addDaysToDate(av);
}
