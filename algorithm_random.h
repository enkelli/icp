/*
 * @file algorithm_random.h
 * @author Plaskon Pavol, xplask00@stud.fit.vutbr.cz
 * @author Postolka Matej, xposto02@stud.fit.vutbr.cz
 *
 * @brief Super Artificial Intelligence.
 */
 
#include "algorithm.h"

/*
 * @brief Computer algorithm playing Othello game.
 */
class AlgorithmRandom: public Algorithm
{
    public:
        virtual Table::Coords step(const Table &table) const override;
};
