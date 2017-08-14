//============================================================================
// Name        : main.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal do Rio de Janeiro
// Description : Main program file
//============================================================================

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <ilcplex/ilocplex.h>

#include "../include/instance.h"
#include "../include/model.h"
#include "../include/callbacks.h"
#include "../include/typedef.hpp"
#include "../include/FWChrono.h"

using namespace std;

template<typename T>
T string_to(const string& s){
	istringstream i(s);
	T x;
	if (!(i >> x)) return 0;
	return x;
}

template<typename T>
string to_string2(const T& t){
  stringstream ss;
  if(!(ss << t)) return "";
  return ss.str();
}

ILOSTLBEGIN

int main(int argc, char* args[]){
	instance in_graph;
  int n, m, k, c;

  if(argc >= 2 && args[1][0] != '2') {
  	in_graph.read_data();
  	n = in_graph.get_n();
		m = in_graph.get_m();
		k = in_graph.get_k();
    c = in_graph.get_c();
  }

	// Initializing cplex environment
	IloEnv env;

  ofstream _file;
  IloNum linear_obj = 0.0;
  double linear_time = 0.0;
  FWChrono timer;
  timer.start();
	try {
		model mod(env, in_graph);

		_file.open("cutset.txt", ios::trunc);

		IloCplex cplex(mod);
		cplex.setParam(IloCplex::Threads, 1);
		// cplex.setParam(IloCplex::NodeLim, 0);
		cplex.setParam(IloCplex::Param::Preprocessing::Aggregator, 0);
		cplex.setParam(IloCplex::Param::Preprocessing::Presolve, 0);
		cplex.setParam(IloCplex::PreInd, 0);
		cplex.setParam(IloCplex::CutsFactor, 1);
		cplex.setParam(IloCplex::HeurFreq, -1);
    cplex.setParam(IloCplex::Param::TimeLimit, 3600);
		cplex.exportModel("test.lp");

    // cplex.use(IloCplex::Callback(new (env) hao_cutsetcallback(env, mod.x, in_graph, _file)));
    // cplex.use(IloCplex::Callback(new (env) hao_cutsetcallback2(env, mod.x, in_graph, _file)));
    cplex.use(IloCplex::Callback(new (env) mipinfo_callback(env, timer, &linear_obj, &linear_time)));

		cplex.solve();
    timer.stop();
    _file.close();

		// Printing solution
		printf("Objective value = %.2lf\n", cplex.getObjValue());
		printf("Number of integer solutions: %ld\n", cplex.getSolnPoolNsolns());
    printf("Number of nodes: %ld\n", cplex.getNnodes());
    printf("Linear Relaxation value = %lf (%lf)\n", linear_obj, linear_time);

    // Save the resulting data in a .csv file
		_file.open("results.csv", ios::app);
		if(_file.is_open()){
			_file.precision(3);
			_file << fixed << cplex.getBestObjValue() << ", ," << timer.getStopTime()	<< "," << linear_obj << "," << linear_time << ","
            << cplex.getSolnPoolNsolns() << "," << cplex.getNnodes() << endl;
			_file.close();
		}
	} catch(IloException& e) {
		cerr << "CONCERT EXCEPTION -- " << e << endl;
	}
	// Closing the environment
	env.end();

	return 0;
}
