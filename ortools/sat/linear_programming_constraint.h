// Copyright 2010-2014 Google
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef OR_TOOLS_SAT_LINEAR_PROGRAMMING_CONSTRAINT_H_
#define OR_TOOLS_SAT_LINEAR_PROGRAMMING_CONSTRAINT_H_

#include <limits>
#include <vector>

#include "ortools/glop/revised_simplex.h"
#include "ortools/lp_data/lp_data.h"
#include "ortools/sat/integer.h"
#include "ortools/sat/model.h"
#include "ortools/sat/sat_base.h"
#include "ortools/util/time_limit.h"

namespace operations_research {
namespace sat {

// A SAT constraint that enforces a set of linear inequality constraints on
// integer variables using an LP solver.
//
// The propagator uses glop's revised simplex for feasibility and propagation.
// It uses the Reduced Cost Strengthening technique, a classic in mixed integer
// programming, for instance see the thesis of Tobias Achterberg,
// "Constraint Integer Programming", sections 7.7 and 8.8, algorithm 7.11.
// http://nbn-resolving.de/urn:nbn:de:0297-zib-11129
// Feasibility propagation is done with this technique by setting total
// constraint violation as an objective, i.e. by dualizing all constraints.
// Per-constraint bounds propagation is NOT done by this constraint,
// it should be done by redundant constraints, as reduced cost propagation
// may miss some filtering.
//
// Workflow: create a LinearProgrammingConstraint instance, make linear
// inequality constraints, call RegisterWith() to finalize the set of linear
// constraints. A linear constraint a x + b y + c z <= k, with x y z
// IntegerVariables, can be created by calling:
// auto ct = lp->CreateNewConstraint(-std::numeric_limits<double>::infinity(),
//                                   k);
// lp->SetCoefficient(ct, x, a);
// lp->SetCoefficient(ct, y, b);
// lp->SetCoefficient(ct, z, c);
//
// Note that this constraint works with double floating-point numbers, so one
// could be worried that it may filter too much in case of precision issues.
// However, the underlying LP solver reports infeasibility only if the problem
// is still infeasible by relaxing the bounds by some small relative value.
// Thus the constraint will tend to filter less than it could, not the opposite.
//
// TODO(user): Work with scaled version of the model, maybe by using
// LPSolver instead of RevisedSimplex.
class LinearProgrammingConstraint : public PropagatorInterface {
 public:
  typedef glop::RowIndex ConstraintIndex;

  explicit LinearProgrammingConstraint(Model* model);

  // User API, see header description.
  ConstraintIndex CreateNewConstraint(double lb, double ub);

  // TODO(user): Allow Literals to appear in linear constraints.
  // TODO(user): Calling SetCoefficient() twice on the same
  // (constraint, variable) pair will overwrite coefficients where accumulating
  // them might be desired, this is a common mistake, change API.
  void SetCoefficient(ConstraintIndex ct, IntegerVariable ivar,
                      double coefficient);

  // Set the coefficient of the variable in the objective. Calling it twice will
  // overwrite the previous value.
  void SetObjectiveCoefficient(IntegerVariable ivar, double coeff);

  // The main objective variable should be equal to the linear sum of
  // the arguments passed to SetObjectiveCoefficient().
  void SetMainObjectiveVariable(IntegerVariable ivar) { objective_cp_ = ivar; }

  // PropagatorInterface API.
  bool Propagate() override;

  bool IncrementalPropagate(const std::vector<int>& watch_indices) override;

  void RegisterWith(GenericLiteralWatcher* watcher);

 private:
  // Generates a set of IntegerLiterals explaining why the best solution can not
  // be improved using reduced costs. This is used to generate explanations for
  // both infeasibility and bounds deductions.
  void FillReducedCostsReason();

  // Same as FillReducedCostReason() but for the case of a DUAL_UNBOUNDED
  // problem. This exploit the dual ray as a reason for the primal infeasiblity.
  void FillDualRayReason();

  // Fills the deductions vector with reduced cost deductions that can be made
  // from the current state of the LP solver. The given delta should be the
  // difference between the cp objective upper bound and lower bound given by
  // the lp.
  void ReducedCostStrengtheningDeductions(double cp_objective_delta);

  // Gets or creates an LP variable that mirrors a CP variable.
  // The variable should be a positive reference.
  glop::ColIndex GetOrCreateMirrorVariable(IntegerVariable positive_variable);

  // Returns the variable value on the same scale as the CP variable value.
  glop::Fractional GetVariableValueAtCpScale(glop::ColIndex var);

  // TODO(user): use solver's precision epsilon.
  static const double kEpsilon;

  // Underlying LP solver API.
  glop::LinearProgram lp_data_;
  glop::RevisedSimplex simplex_;

  // For the scaling.
  glop::SparseMatrixScaler scaler_;
  glop::Fractional lp_to_cp_objective_scale_;

  // violation_sum_ is used to simulate phase I of the simplex and be able to
  // do reduced cost strengthening on problem feasibility by using the sum of
  // constraint violations as an optimization objective.
  glop::ColIndex violation_sum_;
  ConstraintIndex violation_sum_constraint_;

  // Structures used for mirroring IntegerVariables inside the underlying LP
  // solver: integer_variables_[i] is mirrored by mirror_lp_variables_[i],
  // both are used in IncrementalPropagate() and Propagate() calls;
  // integer_variable_to_index_ is used to find which mirroring variable's
  // coefficient must be modified on SetCoefficient().
  std::unordered_map<IntegerVariable, int> integer_variable_to_index_;
  std::vector<IntegerVariable> integer_variables_;
  std::vector<glop::ColIndex> mirror_lp_variables_;

  // We need to remember what to optimize if an objective is given, because
  // then we will switch the objective between feasibility and optimization.
  bool objective_is_defined_ = false;
  IntegerVariable objective_cp_;
  std::vector<std::pair<glop::ColIndex, double>> objective_lp_;

  // Structures for propagators.
  IntegerTrail* integer_trail_;
  std::vector<IntegerLiteral> integer_reason_;
  std::vector<IntegerLiteral> deductions_;

  // Last solution found by a call to the underlying LP solver.
  // On IncrementalPropagate(), if the bound updates do not invalidate this
  // solution, Propagate() will not find domain reductions, no need to call it.
  std::vector<double> lp_solution_;

  // Linear constraints cannot be created or modified after this is registered.
  bool lp_constraint_is_registered_ = false;

  // Time limit (shared with, owned by the sat solver).
  TimeLimit* time_limit_;
};

}  // namespace sat
}  // namespace operations_research

#endif  // OR_TOOLS_SAT_LINEAR_PROGRAMMING_CONSTRAINT_H_
