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
