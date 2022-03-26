//
// Created by comoer on 2022/3/25.
//
#include "simple_pf.h"
#include <cmath>
#include <assert.h>
#define V(x,i) x(i,0)
simple_particle_filter::simple_particle_filter(int n,const VectorState& state0,const Matrix<double,3,1>& Q,double sigmar):
Particle_Filter<3, 2, 2>(n,state0),Q(Q),sigmar(sigmar){}
void simple_particle_filter::NormalNoise(simple_particle_filter::VectorState &noise)
{
    normal_distribution<double> g1(0,V(Q,0)),g2(0,V(Q,1)),g3(0,V(Q,2));
    V(noise,0) = g1(_e);
    V(noise,1) = g2(_e);
    V(noise,2) = g3(_e);
}
simple_particle_filter::VectorState simple_particle_filter::prediction_step(double deltat,const VectorInput &u)
{
    _resample();
    for(Particle& p:*particles)
    {
        VectorState x0=p.state;
        V(p.state,0) = V(x0,0)+V(u,0)*deltat*cos(V(p.state,2));
        V(p.state,1) = V(x0,1)+V(u,0)*deltat*sin(V(p.state,2));
        V(p.state,2) = V(x0,2)+V(u,1)*deltat;
        /* add normal noise*/
        NormalNoise(x0);
        p.state += x0;
    }
    return _expectation();
}
simple_particle_filter::VectorState simple_particle_filter::update_step(const vector<VectorOb> &obs,
                                                                        const vector<Matrix<double,2,1>>& map_point)
{
    if(obs.empty())return _expectation();
    assert(obs.size()==map_point.size());
    for(Particle& p:*particles)
    {
        double pr=1.;
        for(int i=0;i<obs.size();++i)
        {
            const Matrix<double,2,1>& mp = map_point[i];
            VectorOb y_estimated;
            double dx = V(mp,0)-V(p.state,0);
            double dy = V(mp,1)-V(p.state,1);
            V(y_estimated,0) = std::sqrt(dx*dx+dy*dy);
            V(y_estimated,1) = std::atan2(dy,dx)-V(p.state,2);
            VectorOb delta = obs[i]-y_estimated;
            pr*=exp(-V((delta.transpose()*delta),0)/(2.*sigmar*sigmar));
        }
        p.weight = pr;
    }
    _normalize();
    return _expectation();
}
