#include <array>
#include <iostream>
#include <boost/numeric/odeint.hpp>

using namespace std;
using namespace boost::numeric::odeint;

using state_type = array<double, 3>;

void lorenz_param(const state_type& x, state_type& dxdt, double t,
                  double sigma, double R, double b) {
    dxdt[0] = sigma*(x[1] - x[0]);
    dxdt[1] = R*x[0] - x[1] - x[0]*x[2];
    dxdt[2] = -b*x[2] + x[0]*x[1];
}

void write_lorenz(const state_type& x, const double t) {
    cout << t << '\t' << x[0] << '\t' << x[1] << '\t' << x[2]
         << endl;
}

int main() {
    const double sigma = 10.0;
    const double R = 28.0;
    const double b = 8.0/3.0;
    using namespace std::placeholders;
    auto lorenz = bind(lorenz_param, _1, _2, _3, sigma, R, b);
    state_type x = { 10.0, 1.0, 1.0 }; // initial conditions
    integrate(lorenz, x, 0.0, 25.0, 0.1, write_lorenz );
    return 0;
}