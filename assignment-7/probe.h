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
#pragma once
#include <string>
#include <iostream>

class Probe
{
public:
    Probe() = delete;  // Don't allow default constructor require that target_class id is initialized
    Probe(const std::string target_class);
    Probe(const Probe& rhs) = delete;
    Probe& operator=(const Probe& rhs) = delete;
    std::ostream& operator<<(std::ostream& os);
    unsigned int get_ctor_calls() const;
    unsigned int get_dtor_calls() const;
    unsigned int get_inst_count() const;
    void inc_ctor();
    void inc_dtor();

    // global function is friend of class, so can access private
    friend std::ostream& operator<<(std::ostream& os, const Probe& probe);


private:
    const std::string target_class;  // Id of class which is being probed
    unsigned int ctor_calls = 0;
    unsigned int dtor_calls = 0;
};

class Overhead
{
    public:
        Overhead();
        ~Overhead();
        static Probe probe;
};
