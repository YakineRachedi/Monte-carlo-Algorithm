#include "monte_carlo.hpp"
#include "pi.hpp"
#include <iostream>
#include <ctime>
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

    return 0;
}