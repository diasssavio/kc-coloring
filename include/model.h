//============================================================================
// Name        : model.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal do Rio de Janeiro
// Description : Model class interface
//============================================================================

#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <sstream>
#include <ilcplex/ilocplex.h>

#include "instance.h"
#include "typedef.hpp"

class model: public IloModel {
private:
	void init(); // Initialize all variables for problem
	void add_const(); // Add constraints to model
	void add_obj(); // Add objective function to model

public:
	model(IloEnv, instance&);
	virtual ~model();

	// Instance
	instance& in_graph;

	// Variables
	// Vertices colors
	IloNumVarArray2 x;

	// Edges sharing colors
	IloNumVarArray2 y;

	// Colors used
	IloNumVarArray w;
};

#endif /* SRC_MODEL_H_ */
