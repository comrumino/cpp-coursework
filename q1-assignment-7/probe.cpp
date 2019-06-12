#include "probe.h"
#include <iostream>

Probe::Probe(const std::string _target_class) : target_class(_target_class) {}

unsigned int Probe::get_ctor_calls() const { return ctor_calls; }

unsigned int Probe::get_dtor_calls() const { return dtor_calls; }

unsigned int Probe::get_inst_count() const { return ctor_calls - dtor_calls; }

void Probe::inc_ctor() { ctor_calls += 1; }

void Probe::inc_dtor() {
    dtor_calls += 1;
    if (dtor_calls > ctor_calls) {
        throw 1; // If this happens then throw an error to indicate Probe is being misused
    }
}

std::ostream &operator<<(std::ostream &os, const Probe &probe) {
    os << "target_cls: " << probe.target_class << std::endl;
    os << "ctor_calls: " << probe.ctor_calls << std::endl;
    os << "dtor_calls: " << probe.dtor_calls << std::endl;
    os << "inst_count: " << probe.get_inst_count() << std::endl;
    return os;
}

Probe Overhead::probe("overhead");

Overhead::Overhead() { probe.inc_ctor(); }

Overhead::~Overhead() { probe.inc_dtor(); }
