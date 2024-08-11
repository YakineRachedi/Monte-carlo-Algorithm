#ifndef ISING_HPP_INCLUDED
#define ISING_HPP_INCLUDED

#include <random>
#include <cmath>

class Ising1D{
    protected :
        std::vector<int> spin;
        double beta;
        double h;
        std::uniform_int_distribution<int> random_index;
    public :
        Ising1D(unsigned int N, double beta, double h) : spin(N,1), beta(beta), h(h), random_index(0,N-1) {}
        // The spins can be initialized to -1 or 1 to simplify things 
        template <typename RNG> const std::vector<int> & operator() (RNG & G);
        /* The bare minimum required to be callable as the second argument in MonteCarlo */
        // Getter
        const std::vector<int> & state() const {return spin;}
        // In the accessor, I used `const &` because the object is very large, 
        // so to avoid it being copied (for performance reasons and to manage memory efficiently)
};

template <class RNG>
    const std::vector<int> & Ising1D::operator() (RNG & G){
        unsigned int k = random_index(G);
        double p;
        if(k == 0){ // at the left side
            p = exp(-2.*beta*(spin[k+1])*spin[k]-2*h*spin[k]);
        }
        else if(k == spin.size() - 1) { // at the right side
            p = exp(-2.*beta*(spin[k-1])*spin[k]-2*h*spin[k]);
        }
        else{ // in the middle
            p = exp(-2.*beta*(spin[k-1]+spin[k+1])*spin[k]-2.*h*spin[k]);
        }
        // Calculating minimum now :
        if(p > 1.){
            p = 1.;
        }
        std::bernoulli_distribution Up(p);
        if(Up(G)){
            spin[k] = -spin[k];
        }
        return spin;
    }



#endif