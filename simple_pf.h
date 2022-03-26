//
// Created by comoer on 2022/3/25.
//

#ifndef PRATICAL_FILTER_SIMPLE_PF_H
#define PRATICAL_FILTER_SIMPLE_PF_H
#include "particle_filter.h"
#include <Eigen/Dense>
/*int n,const Matrix<double,6,6>& Q,double sigmar*/
class simple_particle_filter:public Particle_Filter<3,2,2>
{
private:
    Matrix<double,3,1> Q;
    double sigmar;

    void NormalNoise(VectorState &noise);
public:
    simple_particle_filter(int n,const VectorState& state0,const Matrix<double,3,1>& Q,double sigmar);
    virtual VectorState prediction_step(double deltat,const VectorInput &u);
    virtual VectorState update_step(const vector<VectorOb> &obs, const vector<Matrix<double,2,1>>& map_point);
};

#endif //PRATICAL_FILTER_SIMPLE_PF_H
