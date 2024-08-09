#include "monte_carlo.hpp"
#include "pi.hpp"
#include <iostream>
#include <ctime>
#include <utility>
#include <chrono>

using namespace std;
using timer = std::chrono::system_clock;


int main(){
    mt19937 G(time(nullptr));

    // Pi Approximation
    long unsigned int nb_samples = 1000000; // We can modify the value of n and choose whatever we want.
    double pi_approx;
    SquareInDisk A;
    auto f = [](double x){return 4*x;};

    auto start = timer::now();
    MonteCarlo(pi_approx, A, f,G, nb_samples);
    auto end = timer::now();
    chrono::duration<double> pi_approximation_time = end - start;
    /*****
     * `f` could also be:
     * - A global function defined outside of `main`:
     *   double fois4(double x) { return 4*x; }
     * 
     * - An object of a class (e.g., `Mult4`) that has
     *   an evaluation operator:
     *   class Mult4 {
     *      public:
     *          double operator()(double x) { return 4*x; }
     *   };
     *   ...
     *   Mult4 f;
     *   Note: The 4 could be replaced by `k` as a private field or
     *   template parameter...
     *   */

    cout << "Estimated value of Pi: " << pi_approx << "\n";    
    cout << "It takes " << pi_approximation_time.count() << " seconds " << "for " << nb_samples << " samples \n";
    cout << "\n-----------------------------------\n";

    // Printing in the terminal the 95% confidence interval for the value of π given by the previous simulation using the DoubleMeanVar class.
    DoubleMeanVar pi_mv;
    MonteCarlo(pi_mv,A,f,G,nb_samples); 
    // Confidence interval
    start = timer::now();
    cout << "Average value of Pi: " << pi_mv.Get_mean() 
        << " +/- " << 1.96 * sqrt(pi_mv.Get_var()) / sqrt(nb_samples) 
        << "\n-----------------------------------\n";
    end = timer::now();
    pi_approximation_time = end - start;
    cout << "It takes (using class DoubleMeanVar) " << pi_approximation_time.count() << " seconds " << "for " << nb_samples << " samples \n";
    cout << "\n-----------------------------------\n";

    DoubleMeanVar Integral_1;
    DoubleMeanVar Integral_2;

    std::exponential_distribution<double> X(1.);
    std::uniform_real_distribution<double> Y(1.,0.);

    MonteCarlo(Integral_1,Y,[](double x){return std::log(1 + x * x);},G,nb_samples);
    auto CoupleXY = [&](std::mt19937 & G) {return std::make_pair(X(G),Y(G));};
    auto Function_to_evaluate = [] (std::pair<double,double> point){
        double x = point.first;
        double y = point.second;
        return std::log(1 + x*y) * std::exp(-x);
    };

    MonteCarlo(Integral_2,CoupleXY,Function_to_evaluate,G,nb_samples);

    cout << "Estimation of the integral 1 : " << Integral_1.Get_mean() << "+/-" << 1.96*sqrt(Integral_1.Get_var())/sqrt(nb_samples) << "\n-----------------------------------\n";
    cout << "Estimation of the integral 2 : " << Integral_2.Get_mean() << " +/- " << 1.96*sqrt(Integral_2.Get_var())/sqrt(nb_samples) << "\n-----------------------------------\n";

    return 0;
}