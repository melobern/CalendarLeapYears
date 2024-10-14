/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calendar.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:07:06 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/14 13:12:40 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Colors.hpp"
#include "../includes/Calendar.hpp"

const int Calendar::_daysInMonth[13] = {0, 31, 28, 31, 30, 31, 30,
                                           31, 31, 30, 31, 30, 31};

Calendar::Calendar(void) {
    return;
}

Calendar::Calendar(const Calendar &src) {
    *this = src;
    return;
}

Calendar& Calendar::operator=(Calendar const &src) {
    static_cast<void>(src);
    return (*this);
}

Calendar::~Calendar() {
    return;
}

bool Calendar::isLeap(const int year) {
  if (year == 0) {
    std::cerr << RED "Error: year 0 doesn't exist." RESET << std::endl;
    return (false);
  }

  int abs_year = std::abs(year);

  if (((abs_year % 4 == 0) && (abs_year % 100 != 0)) || (abs_year % 400 == 0)) {
    return (true);
  }
  return (false);
}

void Calendar::add_days_to_date(int mm, int dd, int yy, int daysLeftToAdd) {
  int daysLeftInMonth = this->_daysInMonth[mm]-dd;

  if (daysLeftToAdd < daysLeftInMonth) {
    dd += daysLeftToAdd;
  } else {
    while (daysLeftToAdd > daysLeftInMonth) {
      if (mm == 12) {
        ++yy;
        mm = 0;
      }
      if (mm == 2 && isLeap(yy))
        ++daysLeftInMonth;
      ++mm;
      daysLeftToAdd -= daysLeftInMonth;
      daysLeftInMonth = this->_daysInMonth[mm];
    }
    dd = daysLeftToAdd;
  }
  std::cout << "The new date is " << dd << " " << mm << " " << yy << std::endl;
}

bool Calendar::dateIsWrong(const int dd, const int mm, const int yy) {
  if (yy == 0) {
    std::cerr << RED "Error: year 0 doesn't exist." RESET << std::endl;
  } else if (dd <= 0 || dd > 31) {
    std::cerr << RED "Day must be between 0 and 31. You gave : " << dd;
    std::cerr <<  RESET << std::endl;
  } else if (mm <= 0 || mm > 12) {
    std::cerr << RED "Month must be between 0 and 12. You gave : " << mm;
    std::cerr << "You gave :" << mm << RESET << std::endl;
    std::cerr << RESET << std::endl;
  } else if (mm != 2 && mm > 0 && mm < 13 && dd > this->_daysInMonth[mm]) {
    std::cerr << RED "Error: this month contains only 30 days. ";
    std::cerr << "You gave :" << dd << RESET << std::endl;
  } else if (mm == 2 && dd > 28 && !isLeap(yy)) {
    std::cerr << RED "Error: February contains only 28 days on non-leap years.";
    std::cerr << "You gave " << dd << RESET << std::endl;
  } else if (mm == 2 && dd > 29) {
    std::cerr << RED "Error: February contains only 29 days on leap years.";
    std::cerr << "You gave " << dd << RESET << std::endl;
  } else {
    return (false);
  }
  return (true);
}

void Calendar::printLeapYears(const int min, const int max) {
    int yearFounds = 0;

    for (int x = min; x <= max; x++) {
      if (x != 0 && isLeap(x)) {
        yearFounds++;
        std::cout << x << "\t";
        if (yearFounds % 11 == 0)
          std::cout << std::endl;
        }
    }
    std::cout << CYAN "Leap years found : " RESET;
    std::cout << YELLOW << yearFounds << RESET << std::endl;
}

