//
// Created by dargouder on 12/3/17.
//

#pragma once

#include <pybind11/pybind11.h>
#include "Sampler.h"

namespace py = pybind11;

PYBIND11_MODULE(PyGeometry, m)
{
    py::class_<Solstice::Point2i>(m, "Point2i")
        .def(py::init<>())
        .def(py::init<const int, const int>());
}
