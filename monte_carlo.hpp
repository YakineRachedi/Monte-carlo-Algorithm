#ifndef MONTE_CARLO_HPP_INCLUDED
#define MONTE_CARLO_HPP_INCLUDED
#include <iostream>
#include <random>
#include <vector>

class DoubleMeanVar;
class Histogram;
std::ostream & operator<<(std::ostream &, const Histogram &);
/*
This function implements a Monte-Carlo method to approximate the expectation of a function in the form of a function template.
*/
template <class Statistic, class RandomVariable, class Measurement, class RNG>
	void MonteCarlo(Statistic & , RandomVariable & , const Measurement & , RNG & , long unsigned int );

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



class DoubleMeanVar{
    protected :
        double m; // Mean
        double v; // Useful for the variance.
    public :
        DoubleMeanVar(double x = 0) : m(x), v(0.) {}
        double Get_mean() const {return this-> m;}
        double Get_var() const {return this-> v - m * m;}
        void operator +=(double x) {this-> m += x; this->v += x * x;}
        void operator /=(int n) {this-> m /= n; this-> v /= n;}
};


class Histogram{
    protected :
        std::vector<double> Sample;
        unsigned int nb_boxes; // number of the boxes
        double lower_bound; // Start of the interval
        double upper_bound; // End of the interval
        double box_width; // Size of a bin
    public :
        // A constructor that initializes a histogram with n bins over the interval [min_interval, max_interval]
        Histogram(double min_interval, double max_interval, unsigned int n) : lower_bound(min_interval), 
                    upper_bound(max_interval), nb_boxes(n), box_width(double(max_interval - min_interval) / nb_boxes), Sample(n,0) {}
        void operator += (double);
        void operator /= (double);
        friend std::ostream & operator<< (std::ostream & ,const Histogram &);
        
};

#endif