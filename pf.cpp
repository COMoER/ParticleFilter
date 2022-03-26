//
// Created by comoer on 2022/3/26.
//
#include "simple_pf.h"
#include <pybind11/stl.h>
#include "pybind11/pybind11.h"
#include <pybind11/eigen.h>


namespace py = pybind11;

PYBIND11_MODULE(simple_pf,m)
{
    m.doc() = "a simple particle filter";
    py::class_<Particle_Filter<3,2,2>>(m, "Particle_filter");
    py::class_<simple_particle_filter,Particle_Filter<3,2,2>>(m, "simple_particle_filter")
            .def(py::init<int,const simple_particle_filter::VectorState&,Matrix<double,3,1>,double>())
            .def("predict",&simple_particle_filter::prediction_step)
            /*const vector<VectorOb> &obs, const vector<Matrix<double,2,1>>& map_point*/
            .def("update",&simple_particle_filter::update_step,py::arg("obs"),py::arg("map_point"))
            .def("query",&simple_particle_filter::query);
}