#ifndef CHI_HPP_INCLUDED
#define CHI_HPP_INCLUDED
#include <random>

template <class REAL, int k> class Chi2_distribution;
/*
 * --- The REAL parameter corresponds to the choice 
 *     float/double/long double (to leave the decision to the user,
 *     similar to the std::***_distribution laws from <random>).
 * --- The integer parameter k is for the distribution. The benefit of passing 
 *     it as a template parameter is allowing the compiler to optimize the 
 *     for loop below.
 */


template <class REAL,int k> 
    class Chi2_distribution{
        private :
            std::normal_distribution<REAL> N;
        public :
            Chi2_distribution() : N(0.,1.) {};
            template <class RNG> REAL operator() (RNG & G); 
            // Operator() : Simulates k Gaussian random variables and returns a random variable following a Chi-squared distribution.
            /*
            * The advantage of having a method template inside the class template
            * is the ability to declare a variable of type Chi2_distribution WITHOUT 
            * HAVING TO immediately specify the type of generator: as many methods 
            * as there are generators used will be compiled for the same class.
            */
    };

template <class REAL,int k>
    template <class RNG> 
        REAL Chi2_distribution<REAL,k>::operator() (RNG & G){
            REAL s(0.);
            REAL x;
            for(int i = 0; i < k; i++){
                x = N(G);
                s += x * x;
                /*
                * Be careful not to replace the two lines with s += N(G) * N(G)
                * thinking it will simplify things !!! 
                */
            }
            return s;
    }


#endif