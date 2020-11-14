/**
 * @file BiConResolution.h
 * @author Vincent Penelle (vincent.penelle@u-bordeaux.fr)
 * @brief  Algorithms to solve directly the BiCon problem
 * @version 
 * @date 2020-10-22
 * 
 * @copyright Creative Commons.
 * 
 */

#ifndef COCA_BICONRESOLUTION_H
#define COCA_BICONRESOLUTION_H

#include "BiConGraph.h"

/**
 * @brief Brute Force Algorithm. If there is a result, the solution will be stored in graph.translator. If no solution, graph won't be modified.
 * 
 * @param graph An instance of the problem.
 * @return true if there is a solution.
 * @return false if there is no solution.
 * 
 * @pre graph must be valid.
 */
bool BruteForceBiCon(BiConGraph *graph);

/**
 * @brief Test if a node is in a list of nodes.
 * 
 * @param graph A graph.
 * @param liste_sommets a list of nodes .
 * @param sommet a node .
 * @param n size of list_sommets .
 * @return bool True if the node s is in liste_sommets else false.
 * @pre @p graph must be a valid graph.
 */
bool s_in_cc(BiConGraph *graph, int *liste_sommets, int sommet, int size);

/**
 * @brief Test if there is a node which is the best to add a translator and return the index of this node. 
 * 
 * @param graph A graph.
 * @return int An int corresponding to the most optimal node to which a translator must be added, -1 if no solution founded.
 * @pre @p graph must be a valid graph.
 */
int max_cc(BiConGraph *graph);

/**
 * @brief Greedy algorithm. If there is a result, the solution will be stored in graph.translator. If no solution, graph won't be modified.
 * 
 * @param graph An instance of the problem.
 * @return true if there is a solution.
 * @return false if there is no solution.
 * 
 * @pre graph must be valid.
 */
bool GreedyBiCon(BiConGraph *graph);

#endif