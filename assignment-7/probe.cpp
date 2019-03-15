/*
 *  Author: James Stronz
 *  Course: C++PROG 711 - 2019
 *  Assignment: 7.1 Probe
 *  Problem Statement:
 *   + Define a probe that can be inserted into a class as a test coverage device. The probe keeps track of the
 *     number of instances of the class that currently exist and how many have been created since the program was
 *     started. The probe is to respond with appropriate tracking information when the class instance containing
 *     the probe is queried. It will be necessary to figure out the best way to present the query. Demonstrate your
 *     probe on a class with multiple instances. Note: the data and function members of the probe cannot be static.
 *     The probe itself must be declared static in the probed class.
 *   + Overload the ostream operator to support printing of information of the class Probe.
 *   + Use the delete keyword to delete the copy constructor and assignment operator for the probe. (see Section 13.1.6 in Lippman)
 */
#include "probe.h"
#include <iostream>

Probe::Probe(const std::string _target_class)
    :target_class(_target_class)
{
}

unsigned int Probe::get_ctor_calls() const {
    return ctor_calls;
}

unsigned int Probe::get_dtor_calls() const {
    return dtor_calls;
}

unsigned int Probe::get_inst_count() const {
    return ctor_calls - dtor_calls;
}

void Probe::inc_ctor() {
    ctor_calls += 1;
}

void Probe::inc_dtor() {
    dtor_calls += 1;
    if (dtor_calls > ctor_calls) {
        throw 1;  // If this happens then throw an error to indicate Probe is being misused
    }
}

std::ostream& operator<<(std::ostream& os, const Probe& probe) {
    os << "target_cls: " << probe.target_class << std::endl;
    os << "ctor_calls: " << probe.ctor_calls << std::endl;
    os << "dtor_calls: " << probe.dtor_calls << std::endl;
    os << "inst_count: " << probe.get_inst_count() << std::endl;
    return os;
}

Probe Overhead::probe("overhead");

Overhead::Overhead() {
    probe.inc_ctor();
}

Overhead::~Overhead() {
    probe.inc_dtor();
}
