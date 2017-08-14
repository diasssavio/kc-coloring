//============================================================================
// Name        : callbacks.h
// Author      : Sávio S. Dias
// E-mail      : diasssavio@gmail.com
// Institution : Universidade Federal do Rio de Janeiro
// Description : Callbacks class interface
//============================================================================

#ifndef SRC_CALLBACKS_H_
#define SRC_CALLBACKS_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <ilcplex/ilocplex.h>

#include "FWChrono.h"
#include "instance.h"
#include "model.h"
#include "typedef.hpp"

// Callback to gather information in every node of optimization
class mipinfo_callback : public IloCplex::MIPInfoCallbackI {
private:
  FWChrono& timer;

  // Linear Relaxation Objective Value & Time against
  IloNum* linear_obj;
  double* linear_time;

public:
  IloCplex::CallbackI* duplicateCallback() const {
    return new (getEnv()) mipinfo_callback(*this);
  }

  mipinfo_callback(IloEnv env, FWChrono& _timer, IloNum* _linear_obj, double* _linear_time) : IloCplex::MIPInfoCallbackI(env), timer(_timer), linear_obj(_linear_obj), linear_time(_linear_time) {}

  void main();

};

// Cut callback for cut set constraints, i.e. applied in relaxed solutions
// class hao_cutsetcallback : public IloCplex::UserCutCallbackI {
// private:
//   IloNumVarArray3& x;
//   instance& cars;
//   ofstream& _file;
//
//   unsigned n_cuts;
//   double sep_time;
//
// public:
//   IloCplex::CallbackI* duplicateCallback() const {
//     return new (getEnv()) hao_cutsetcallback(*this);
//   }
//
//   hao_cutsetcallback(IloEnv env, IloNumVarArray3& _x, instance& _cars, ofstream& file) : IloCplex::UserCutCallbackI(env), x(_x), cars(_cars), _file(file) {
//     n_cuts = 0;
//     sep_time = 0.0;
//   }
//
//   void main();
//
//   inline unsigned get_n_cuts() { return n_cuts; }
//   inline double get_sep_time() { return sep_time; }
//
// };

// Lazy callback for cut set constraints, i.e. applied in integer solutions
// class hao_cutsetcallback2 : public IloCplex::LazyConstraintCallbackI {
// private:
//   IloNumVarArray3& x;
//   instance& cars;
//   ofstream& _file;
//
//   unsigned n_cuts;
//   double sep_time;
//
// public:
//   IloCplex::CallbackI* duplicateCallback() const {
//     return new (getEnv()) hao_cutsetcallback2(*this);
//   }
//
//   hao_cutsetcallback2(IloEnv env, IloNumVarArray3& _x, instance& _cars, ofstream& file) : IloCplex::LazyConstraintCallbackI(env), x(_x), cars(_cars), _file(file) {
//     n_cuts = 0;
//     sep_time = 0.0;
//   }
//
//   void main();
//
//   inline unsigned get_n_cuts() { return n_cuts; }
//   inline double get_sep_time() { return sep_time; }
//
// };

#endif /* SRC_CALLBACKS_H_ */
