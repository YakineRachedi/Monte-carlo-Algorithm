#ifndef MCMC_HPP_INCLUDED
#define MCMC_HPP_INCLUDED

#include <random>

class Markov2states{
    protected :
        int x;
        std::bernoulli_distribution Ua;
        std::bernoulli_distribution Ub;
    public :
        Markov2states(int x0 = 1, double a0 = 0.5, double b0 = 0.5) : x(x0), Ua(a0), Ub(b0) {}
        template <typename RNG> int operator() (RNG &); 
        // int because it takes the value 1 or 2 according to the previous mathematical model and should not be const because x evolves.
};

template <typename RNG> 
    int Markov2states::operator() (RNG & G) {
        x == 1 ? (Ua(G) ? x = 2 : x = 1) : (Ub(G) ? x = 1 : x = 2);
        return x; 
}

class Stat2states{
    protected :
        long unsigned visit1;
        long unsigned visit2;
        long unsigned normalization;
        /* The idea behind normalization is to perform the final division by n for the means 
        * only at the time of accessing, not before. This is partly imposed by the fact that all variables
        * are integers, so only integer division is available. On the other hand, this is an advantage
        * because there are no rounding errors in integers, so all rounding occurs at the last moment.
        */
    public :
        Stat2states() : visit1(0), visit2(0), normalization(1) {} // constructor by default
        void operator += (int x) { x==1 ? visit1++ : visit2++ ;}
        void operator /= (long unsigned n) {normalization *= n;}
        /* All the prototypes are actually imposed by the fact that Stat2states 
        * can be used as the first argument in MonteCarlo: it necessarily requires += and /= with the appropriate arguments.
        */
       double frequency_of_visits(int x) const {
        return x == 1 ? double(visit1) / double(normalization) : double(visit2) / double(normalization);
       } // Getter
};
#endif