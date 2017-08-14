//============================================================================
// Name        : model.cpp
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal do Rio de Janeiro
// Description : Model class implementation
//============================================================================

#include "../include/model.h"

model::model(IloEnv _env, instance& _in_graph) : IloModel(_env), in_graph(_in_graph) {
	init();
	add_obj();
	add_const();
}

model::~model() { }

void model::init(){
	int n = in_graph.get_n();
	int m = in_graph.get_m();
	int R = in_graph.get_R();

	x = IloNumVarArray2(getEnv(), n);
	for(int v = 0; v < n; v++) {
		x[v] = IloNumVarArray(getEnv(), R);
		for(int j = 0; j < R; j++) {
			x[v][j] = IloNumVar(getEnv(), 0, 1, ILOINT);
			stringstream x_name;
			x_name << "x(" << v << ")(" << j << ")";
			x[v][j].setName(x_name.str().c_str());
			add(x[v][j]);
		}
	}

	y = IloNumVarArray2(getEnv(), m);
	for(int e = 0; e < m; e++) {
		y[e] = IloNumVarArray(getEnv(), R);
		for(int j = 0; j < R; j++) {
			y[e][j] = IloNumVar(getEnv(), 0, 1, ILOINT);
			stringstream y_name;
			y_name << "y(" << e << ")(" << j << ")";
			y[e][j].setName(y_name.str().c_str());
			add(y[e][j]);
		}
	}

	w = IloNumVarArray(getEnv(), R);
	for(int j = 0; j < R; j++) {
		w[j] = IloNumVar(getEnv(), 0, 1, ILOINT);
		stringstream w_name;
		w_name << "w(" << j << ")";
		w[j].setName(w_name.str().c_str());
		add(w[j]);
	}
}

void model::add_const(){
	int n = in_graph.get_n();
	int m = in_graph.get_m();
	int k = in_graph.get_k();
	int c = in_graph.get_c();
	int R = in_graph.get_R();

	vector < edge > edges = in_graph.get_edges();

	IloEnv env = getEnv();

	// Constraint (2):
	for(int v = 0; v < n; v++) {
		IloExpr expr(env);
		for(int j = 0; j < R; j++)
			expr += x[v][j];
		IloConstraint c2 = (expr == k);
		stringstream c2_name;
		c2_name << "Cons2(" << v << ")";
		c2.setName(c2_name.str().c_str());
		add(c2);
	}

	// Constraint (3):
	for(int e = 0; e < m; e++) {
		IloExpr expr(env);
		for(int j = 0; j < R; j++)
			expr += y[e][j];
		IloConstraint c3 = (expr <= c);
		stringstream c3_name;
		c3_name << "Cons3(" << e << ")";
		c3.setName(c3_name.str().c_str());
		add(c3);
	}

	// Constraint (4):
	for(int e = 0; e < m; e++) {
		int u = edges[e].first;
		int v = edges[e].second;
		for(int j = 0; j < R; j++) {
			IloConstraint c4 = (x[u][j] + x[v][j] - y[e][j] <= 1);
			stringstream c4_name;
			c4_name << "Cons4(" << e << ")(" << j << ")";
			c4.setName(c4_name.str().c_str());
			add(c4);
		}
	}

	// Constraint (5):
	for(int v = 0; v < n; v++)
		for(int j = 0; j < R; j++) {
			IloConstraint c5 = (x[v][j] <= w[j]);
			stringstream c5_name;
			c5_name << "Cons5(" << v << ")(" << j << ")";
			c5.setName(c5_name.str().c_str());
			add(c5);
		}

	// Constraint (6):
	for(int j = 0; j < R - 1; j++) {
		IloConstraint c6 = (w[j] <= w[j + 1]);
		stringstream c6_name;
		c6_name << "Cons6(" << j << ")";
		c6.setName(c6_name.str().c_str());
		add(c6);
	}
}

void model::add_obj() {
	int R = in_graph.get_R();

	// Creating OF expression
	IloExpr expr(getEnv());
	for(int j = 0; j < R; j++)
		expr += w[j];

	// Adding objective function
	add(IloMinimize(getEnv(), expr));
}
