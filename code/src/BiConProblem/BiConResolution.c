#include "BiConResolution.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX 10000

bool are_cc_connected(BiConGraph *graph, int *liste_sommets, int size)
{
    for (int i = 0; i < size; i = i + 1)
    {
        addTranslator(graph, liste_sommets[i]);
    }
    if (graph->numComponents != 1)
    {
        return false;
    }
    resetTranslator(graph);
    return true;
}

void solution(BiConGraph *graph, int *liste_translator, int nb_convertisseurs, int indice, int *list_sommets, int size, int *result, int *result_size)
{
    if (nb_convertisseurs > *result_size)
    {
        return;
    }
    //On commence par réinitialiser le graphe, et ajouter rajouter correctement les convertisseurs sur les sommets
    resetTranslator(graph);
    for (int i = 0; i < nb_convertisseurs; i++)
    {
        addTranslator(graph, liste_translator[i]);
    }

    if (graph->numComponents == 1 && nb_convertisseurs <= *result_size)
    {
        *result_size = nb_convertisseurs;
        for (int i = 0; i < *result_size; i++)
        {
            result[i] = liste_translator[i];
        }
        return;
    }

    if (graph->translators[list_sommets[indice]] == false)
    {
        addTranslator(graph, list_sommets[indice]);
        liste_translator[nb_convertisseurs] = list_sommets[indice];
        nb_convertisseurs++;
    }

    for (int i = indice + 1; i < size; i++)
    {
        solution(graph, liste_translator, nb_convertisseurs, i, list_sommets, size, result, result_size);
    }
}

//Algorithme brute force 
bool BruteForceBiCon(BiConGraph *graph)
{
    if (graph == NULL)
    {
        return false;
    }
    int nb_sommets = graph->graph.numNodes;
    int *liste_sommets = (int *)malloc(nb_sommets * sizeof(int));
    int size = 0;
    //On réalise un premier parcours pour récupérer les sommets hétérogènes
    for (int i = 0; i < nb_sommets; i++)
    {
        int decalage = i * nb_sommets;
        for (int j = decalage; j < j + nb_sommets; j++)
        {
            if (graph->heterogeneousEdges[j] == true)
            {
                liste_sommets[size] = i;
                size = size + 1;
                break;
            }
        }
    }

    if (are_cc_connected(graph, liste_sommets, size) == false)
    {
        return false;
    }
    int *liste_translator = (int *)malloc(nb_sommets * sizeof(int));
    int *result = (int *)malloc(nb_sommets * sizeof(int));
    int *result_size = (int *)malloc(sizeof(int));
    *result_size = MAX;
    for (int i = 0; i < size; i = i + 1)
    {

        solution(graph, liste_translator, 0, i, liste_sommets, size, result, result_size);
        if (*result_size == 1)
        {
            return true;
        }
    }

    resetTranslator(graph);
    for (int i = 0; i < *result_size; i++)
    {
        addTranslator(graph, result[i]);
    }
    free(liste_sommets);
    free(result);
    free(result_size);
    return true;
}

bool s_in_cc(BiConGraph *graph, int *liste_sommets, int sommet, int size)
{
    if(graph == NULL){
        fprintf(stderr,"Invalid graph given\n");
    }
    for (int i = 0; i < size; i++)
    {
        if (areInSameComponent(*graph, liste_sommets[i], sommet))
        {
            return true;
        }
    }
    return false;
}

int max_cc(BiConGraph *graph) 
{
    if (graph == NULL)
    {
        return -1;
    }
    
    int nmax = 0;
    int s_max = -1;
    int cc[graph->graph.numNodes];

    for (int i = 0; i < graph->graph.numNodes; i++)
    {
        cc[0] = i;
        int size = 1;
        int n = 0;

        int j = i * graph->graph.numNodes; // Get the neighbors of the node i
        for (int k = j; k < j + graph->graph.numNodes; k++) 
        {
            if (graph->heterogeneousEdges[k])
            {
                int s = k % graph->graph.numNodes;
                if (!s_in_cc(graph, cc, s, size))
                {
                    cc[size] = s;
                    size = size + 1;
                    n++;
                }
            }
        }
        if (n > nmax){
            nmax = n;
            s_max = i;
        }
    }
    return s_max;
}

bool GreedyBiCon(BiConGraph *graph)
{
    if (graph == NULL)
    {
        fprintf(stderr,"Invalid graph given\n");
        return false;
    }

    while (graph->numComponents != 1) 
    {
        int s_max = max_cc(graph);
        if (s_max!=-1){
           addTranslator(graph, s_max);
        }
        else{
            return false;
        }
    }
    return true;
}