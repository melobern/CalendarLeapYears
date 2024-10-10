/* Copyright 2024 <mbernard>************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Calendar.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbernard <mbernard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:07:06 by mbernard          #+#    #+#             */
/*   Updated: 2024/10/09 21:55:32 by mbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_CALENDAR_HPP_
#define INCLUDES_CALENDAR_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <map>
#include <climits>
#include "../includes/Colors.hpp"

class Calendar {
 private:
  static const int                       _daysInMonth[13];

  Calendar &operator=(const Calendar &src);
  Calendar(const Calendar &src);


 public:
  Calendar(void);
  ~Calendar(void);

  bool        isLeap(const int year);
  bool        dateIsWrong(const int dd, const int mm, const int yy);
  void        printLeapYears(const int min, const int max);
  void        add_days_to_date(int mm, int dd, int yy, int days_left_to_add);
};

#endif  // INCLUDES_CALENDAR_HPP_
