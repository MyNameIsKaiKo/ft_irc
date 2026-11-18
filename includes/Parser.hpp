/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:24:28 by jleray            #+#    #+#             */
/*   Updated: 2026/11/18 15:55:26 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_CPP
#define HEADER_CPP

#include <string>
#include "./Message.hpp"

Message	tokenize(std::string raw);
void	parseBuffer(std::string& buffer);

#endif
