//
// Created by comoer on 2022/3/25.
//
#include "simple_pf.h"
#include <cmath>
#define V(x,i) x(i,0)
simple_particle_filter::simple_particle_filter(int n,const Matrix<double,6,6>& Q,double sigmar):
Particle_Filter<6, 2, 1>(n),Q(Q),sigmar(sigmar){}
void simple_particle_filter::NormalNoise(simple_particle_filter::VectorState &noise)
{
    cv::RNG r;
    cv::Mat out;
    cv::Mat mean = cv::Mat::zeros(6,1,CV_64F);
    cv::Mat Qr;
    cv::eigen2cv(Q,Qr);
    r.fill(out,cv::RNG::NORMAL,mean,Qr);
    cv::cv2eigen(out,noise);
}
simple_particle_filter::VectorState simple_particle_filter::prediction_step(double deltat)
{
    _resample();
    for(Particle& p:*particles)
    {
        VectorState x0=p.state;
        V(p.state,0) = V(x0,1)+V(x0,1)*deltat+0.5*V(x0,4)*deltat*deltat;
        V(p.state,1) = V(x0,1)+V(x0,4)*deltat;
        V(p.state,2) = V(x0,2)+V(x0,3)*deltat+0.5*V(x0,5)*deltat*deltat;
        V(p.state,3) = V(x0,3)+V(x0,5)*deltat;
        /* 4,5 is the same */
        /* add normal noise*/
//        NormalNoise(x0);
//        p.state += x0;
    }
    return _expectation();
}
simple_particle_filter::VectorState simple_particle_filter::update_step(const vector<VectorOb> &obs)
{
    for(Particle& p:*particles)
    {
        VectorOb y_estimated;
        V(y_estimated,0) = std::atan2(V(p.state,0),V(p.state,2));
        V(y_estimated,1) = std::sqrt(V(p.state,0)*V(p.state,0)+V(p.state,1)*V(p.state,1));
        double pr=1.;
        for(const VectorOb& ob:obs)
        {
            VectorOb dy;
            dy = ob-y_estimated;
            pr*=exp(-V((dy.transpose()*dy),0)/(2.*sigmar*sigmar))/(std::sqrt(2*M_PI)*sigmar);
        }
        p.weight = pr;
    }
    _normalize();
    return _expectation();
}
