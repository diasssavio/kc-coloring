#ifndef TYPEDEF_HPP_
#define TYPEDEF_HPP_

// SYSTEM LIBRARIES
#include <ilcplex/ilocplex.h>
#include <ilcplex/ilocplexi.h>
#include <vector>
#include <utility>

#define MAX_DOUBLE 1e+75

#define EPSILON 1e-6

///// CONCERT
typedef IloArray<IloNumVarArray> IloNumVarArray2;
typedef IloArray<IloNumVarArray2> IloNumVarArray3;
typedef IloArray<IloNumVarArray3> IloNumVarArray4;
typedef IloArray<IloNumVarArray4> IloNumVarArray5;

typedef IloArray<IloNumArray2> IloNumArray3;
typedef IloArray<IloNumArray3> IloNumArray4;

typedef IloArray<IloFloatVarArray> IloFloatVarArray2;
typedef IloArray<IloFloatVarArray2> IloFloatVarArray3;
typedef IloArray<IloFloatVarArray3> IloFloatVarArray4;

typedef IloArray<IloBoolVarArray> IloBoolVarArray2;
typedef IloArray<IloBoolVarArray2> IloBoolVarArray3;
typedef IloArray<IloBoolVarArray3> IloBoolVarArray4;

//typedef IloArray<IntegerFeasibilityStatus> IntegerFeasibilityArray;
//typedef IloArray<ControlCallbackl::IntegerFeasibilityArray> IntegerFeasibilityArray2;

typedef std::vector<int>::iterator VecIntIT;
typedef std::vector<int>::const_iterator VecIntCIT;
typedef std::vector<int> VecInt;

typedef std::pair < int, int > edge;

#endif /* TYPEDEF_HPP_ */
