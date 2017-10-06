// In this quiz you'll implement the global kinematic model.
#include <math.h>
#include <iostream>
#include "Eigen-3.3/Eigen/Core"

//
// Helper functions
//
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

const double Lf = 2;

// TODO: Implement the global kinematic model.
// Return the next state.
//
// NOTE: state is [x, y, psi, v]
// NOTE: actuators is [delta, a]
Eigen::VectorXd globalKinematic(Eigen::VectorXd state,
                                Eigen::VectorXd actuators, double dt) {
  Eigen::VectorXd next_state(state.size());
  next_state[0] = state[0] + state[3] * cos(state[2]) * dt;
  next_state[1] = state[1] + state[3] * sin(state[2]) * dt;
  next_state[2] = state[2] + (state[3] / Lf) * actuators[0] * dt;
  next_state[3] = state[3] + actuators[1] * dt;

  return next_state;
}

int main() {
  // [x, y, psi, v]
  Eigen::VectorXd state(4);
  // [delta, v]
  Eigen::VectorXd actuators(2);

  state << 0, 0, deg2rad(45), 1;
  actuators << deg2rad(5), 1;

  // should be [0.212132, 0.212132, 0.798488, 1.3]
  auto next_state = globalKinematic(state, actuators, 0.3);

  std::cout << next_state << std::endl;
}
/** State Equations - Simplified model
* x​t+1 = x​t + v​t​​ ∗ cos(ψ​t) ∗ dt
* yt+1 = yt + vt ∗ sin(ψt) ∗ dt
* ψt+1 = ψt + ((vt / Lf) * δ ∗ dt)
* v​t+1​ = vt + at ∗ dt
*/
