/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:24:28 by jleray            #+#    #+#             */
/*   Updated: 2026/11/25 09:24:31 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <iostream>
#include "./Message.hpp"

Message	tokenize(std::string raw);
std::vector<Message>	parseBuffer(int clientFd, std::string& buffer);

#endif
