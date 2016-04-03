/*
 * @file algorithm.h
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Abstract class for algorithm implementing Othell player.
 */
 
#include "Table.h"

/*
 * @brief Abstract class for algorithm implementing Othell player.
 */
class Algorithm
{
    public:
        virtual Table::Coords step(const Table &table) const = 0;
};
