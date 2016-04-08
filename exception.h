/**
 * Course ICP @ FIT VUT Brno, 2016
 * ICP 2016 Project - Othello
 *
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief A representation of Othello table.
 * @file exception.h
 *
 * Unless otherwise stated, all code is licensed under a
 * GNU General Public License v2.0
 *
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

/**
 * @brief Base class for all C-types errors.
 */
class OthelloError: public std::runtime_error
{
	public:
		using std::runtime_error::runtime_error;
};

#endif
