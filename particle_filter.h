//
// Created by comoer on 2022/3/22.
//

#ifndef PRATICAL_FILTER_PARTICLE_FILTER_H
#define PRATICAL_FILTER_PARTICLE_FILTER_H

#include <Eigen/Core>
#include <iostream>
#include <memory>
#include <vector>
#include <random>

using namespace std;
using namespace Eigen;

/*M is the state dimension, N is the observation dimension, U is the input dimension*/
template <int M,int N,int U>
class Particle_Filter {
public:
    typedef Matrix<double,U,1> VectorInput;
    typedef Matrix<double,N,1> VectorOb;
    typedef Matrix<double,M,1> VectorState;
private:
    int Ns; /* the number of particles*/
protected:
    struct Particle{
        VectorState state;
        double weight;

        Particle(double w, VectorState s) :
                state(std::move(s)), weight(w){}
    };

    shared_ptr<vector<Particle>> particles;
    /* random generator */
    uniform_real_distribution<double> _generator;
    default_random_engine _e;

    void _normalize(double eps=1e-10);
    VectorState _expectation();
    void _resample();

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Particle_Filter(int n,const VectorState& state0);
    VectorState query(){return _expectation();};
    virtual VectorState prediction_step(double deltat, VectorInput u){return VectorState();}
    virtual VectorState update_step(const vector<VectorOb> &obs){return VectorState();}

};

template<int M, int N, int U>
Particle_Filter<M, N, U>::Particle_Filter(int n,const VectorState& state0) :
        Ns(n), particles(make_shared<vector<Particle>>()), _e(time(nullptr)), _generator(0, 1. / n) {
    // initial make all
    for (int i = 0; i < n; ++i) particles->emplace_back(1. / n,state0);
}

template<int M, int N, int U>
void Particle_Filter<M, N, U>::_resample() {
    /* implement the resample algorithm */
    double sp = _generator(_e); /* start point */
    double gap = 1. / Ns;
    shared_ptr<vector<Particle>> resampled_particles = make_shared<vector<Particle>>();
    double c_weight = 0;
    for (Particle &p:*particles) {
        c_weight += p.weight;
        p.weight = c_weight;
    }

    for (int i = 0, j = 0; i < Ns; ++i) {
        const Particle &p = particles->data()[j];
        if (p.weight > sp + i * gap){
            resampled_particles->push_back(p);
        }
        else resampled_particles->push_back(particles->data()[++j]);
    }
    particles = resampled_particles;

}

template<int M, int N, int U>
void Particle_Filter<M, N, U>::_normalize(double eps) {
    double weight_sum = 0.;
    for (Particle &p:*particles) {
        weight_sum += p.weight;
    }
    for (Particle &p:*particles) {
        p.weight /= (weight_sum + eps);
    }
}

template<int M, int N, int U>
typename Particle_Filter<M,N,U>::VectorState Particle_Filter<M, N, U>::_expectation() {
    VectorState result = VectorState::Zero();
    for(const Particle& p:*particles)
    {
        result += p.weight*p.state;
    }
    return result;
}


#endif //PRATICAL_FILTER_PARTICLE_FILTER_H
