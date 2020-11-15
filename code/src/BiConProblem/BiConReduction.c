
#include "BiConReduction.h"
#include "Z3Tools.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


Z3_ast getVariableIsIthTranslator(Z3_context ctx, int node, int number){
    char name[40];
    snprintf(name,40,"[%d,%d]",node,number);
    return mk_bool_var(ctx,name);
}

Z3_ast getVariableParent(Z3_context ctx, int child, int parent){
    char name[40];
    snprintf(name,40,"p_[%d,%d]",child,parent);
    return mk_bool_var(ctx,name);
}

Z3_ast getVariableLevelInSpanningTree(Z3_context ctx, int level, int component){
    char name[40];
    snprintf(name,40,"l_[%d,%d]",component,level);
    return mk_bool_var(ctx,name);
}

Z3_ast BiConReduction(Z3_context ctx, BiConGraph biGraph, int size){
    char name[40];
    //int x[biGraph.graph.numNodes][biGraph.graph.numNodes];  
    for (int u = 0 ; u<biGraph.graph.numNodes; u++){
        for(int i = 0 ; i<size ; i++){
            snprintf(name,40,"x_[%d,%d]", u, i);
            Z3_ast x =  mk_bool_var(ctx,name);
            printf("Variable %s created.\n",Z3_ast_to_string(ctx,x));
        }
    }

    for (int u = 0 ; u<biGraph.graph.numNodes; u++){
        for (int u = 0 ; u<biGraph.graph.numNodes; u++){
            
        }
    }

    return Z3_mk_true(ctx); 
}

void getTranslatorSetFromModel(Z3_context ctx, Z3_model model, BiConGraph *graph, int size){
    if(model==NULL || graph == NULL){
        fprintf(stderr,"getTranslatorSetFromModel : invalid graph or model\n");
    }
    // TODO
    // valueOfVarInModel(ctx,model,variable);
    return;
}

