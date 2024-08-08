#ifndef MONTE_CARLO_HPP_INCLUDED
#define MONTE_CARLO_HPP_INCLUDED

/*
This function implements a Monte-Carlo method to approximate the expectation of a function in the form of a function template.
*/
template <class Statistic, class RandomVariable, class Measurement, class RNG>
	void MonteCarlo(Statistic & , RandomVariable & , const Measurement & , RNG & , long unsigned int );

#include <iostream>
#include <vector>
#include <random>

template <typename Statistic, typename RandomVariable, typename Measurement, typename RNG>
    void MonteCarlo(Statistic & result, RandomVariable & X,const Measurement & f, RNG & G, long unsigned int n){
        for(int i = 0; i < n; i++){
            result += f(X(G)); // There's no need to store 𝑛 random variables if we're going to discard them afterward.
        }
        result /= double(n);
    };
/*
The function should simulate n random variables with the distribution given by 𝑋. using the generator G, apply the function f to these random variables, 
    and update res according to the previous formula.
*/

#endif