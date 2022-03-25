//
// Created by comoer on 2022/3/25.
//

#ifndef PRATICAL_FILTER_SIMPLE_PF_H
#define PRATICAL_FILTER_SIMPLE_PF_H
#include "particle_filter.h"
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/core/eigen.hpp>
/*int n,const Matrix<double,6,6>& Q,double sigmar*/
class simple_particle_filter:public Particle_Filter<6,2,1>
{
private:
    Matrix<double,6,6> Q;
    double sigmar;

    void NormalNoise(VectorState &noise);
public:

    simple_particle_filter(int n,const Matrix<double,6,6>& Q,double sigmar);
    virtual VectorState prediction_step(double deltat);
    virtual VectorState update_step(const vector<VectorOb> &obs) override;
};

#endif //PRATICAL_FILTER_SIMPLE_PF_H
