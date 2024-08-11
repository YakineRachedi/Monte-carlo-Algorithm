#include "monte_carlo.hpp"
#include "monte_carlo.cpp"
#include "chi_squared.hpp"
#include "markov2states.hpp"
#include "Ising.hpp"
#include "pi.hpp"
#include <iostream>
#include <fstream>
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


    // Histogram of the Normal Distribution : 
    double a = -3;
    double b = 3;
    double nb_of_boxes = 50;
    normal_distribution<double> N(0.,1.);
    Histogram H(a,b,nb_of_boxes);
    MonteCarlo(H,N,[](double x){return x;},G,nb_samples);
    cout << "Histogram of the Standard Normal Distribution for " << nb_of_boxes << " boxes : "<< H << "\n";
    ofstream file("Normal_dist.dat");
    file << H;
    file.close();

    // Histogram of the Chi2 Distribution for example k = 3 and k = 6 :
    a = 0.;
    b = 10.;
    Chi2_distribution<double,3> Chi2_3;
    Histogram H_chi2_3(a,b,nb_of_boxes);
    file.open("Chi2_first_example.dat");
    MonteCarlo(H_chi2_3,Chi2_3,[](double x){return x;},G,nb_samples);
    file << H_chi2_3;
    file.close();

    Chi2_distribution<double,6> Chi2_6;
    Histogram H_chi2_6(a,b,nb_of_boxes);
    file.open("Chi2_second_example.dat");
    MonteCarlo(H_chi2_6,Chi2_6,[](double x){return x;},G,nb_samples);
    file << H_chi2_6;
    file.close();

    cout << "-----------------------------------\n";
    cout << "***********************************\n";
    cout << "-----------------------------------\n";
    // Two-state Markov Chain
    /* We vary a and b and display the associated invariant measures in a file
    * in the form of a matrix where the coefficient (i,j) corresponds to pi(a_i,b_j)
    */

    double aa = 2. / 3.;
    double bb = 1. / 2.;
    Markov2states Mc2states(1,aa,bb);
    Stat2states stat_mc;
    MonteCarlo(stat_mc,Mc2states,[](auto x){return x;},G,nb_samples);
    cout << "Estimation of the invariant measure by ergodic theorem:\n";    
    cout << "\tpi(1): " << stat_mc.frequency_of_visits(1) << "\n";
    cout << "\tpi(2): " << stat_mc.frequency_of_visits(2) << "\n";
    cout << "-----------------------------------\n";

    // Estimation of the global average of all spins for N = 1000 as β and h are fixed.
    auto measure_function = [](const std::vector<int>& spins) {
    double sum = 0.0;
    for (int spin : spins) {
        sum += spin;
    }
    return sum / spins.size();};
    Ising1D ising(100, 1.0, 0.5);
    double result = 0.0;
    MonteCarlo(result, ising, measure_function, G, 10000);
    cout << "Estimated result: " << result << std::endl;
    cout << "-----------------------------------\n";
    
    // Estimation of the average value of x500 for N = 1000 as β and h vary.

    unsigned N0 = 1000;
    auto x500 = [](const std::vector<int> & v) {return v[499];};
    cout << "Ising model: some values according to beta and h:\n";
    ofstream output("Ising_model.dat");
    for(double beta = 0.; beta < 2.; beta += 0.4){
        for(double h = 0.; h < 1.; h += 0.2){
            Ising1D Ising(N0,beta,h);
            double m = 0.;
            MonteCarlo(m,Ising,x500,G,nb_samples);
            cout << "\ttheta = " << beta << "\th = " << h << "\taverage of x_500 = " << m << "\n";
            output << "\t" << beta << "\t" << h << "\t" << m << "\n";
        }
    }
    output.close();
    cout << "-----------------------------------\n";

    return 0;
}