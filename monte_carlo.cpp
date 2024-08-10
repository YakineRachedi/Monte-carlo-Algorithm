// Compilation of the code for the methods or operators of the class.


#include "monte_carlo.hpp"
#include <algorithm>

void Histogram::operator+=(double x){
    if( (x < upper_bound) && (x > lower_bound) ){
        unsigned k = std::floor((x - lower_bound) / box_width);
        Sample[k] += 1.; 
    }
    return;
}

void Histogram::operator/=(double k){
    std::transform(Sample.begin(),Sample.end(),Sample.begin(),[&](const double & x) {return x / k;});
    return;
}

std::ostream & operator<< (std::ostream & output,const Histogram & H){
    for(unsigned int i = 0; i < H.Sample.size(); i++){
        output << H.lower_bound + H.box_width * 0.5 + i * H.box_width << "\t" << H.Sample[i] << "\n";
    }
    return output;
}