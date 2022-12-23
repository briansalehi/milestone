#include <practice.hpp>
#include <reference.hpp>
#include <resource.hpp>

using namespace flashback;

practice::practice()
{
}

practice::practice(practice const&)
{
}

practice::practice(practice&&)
{
}

practice& practice::operator=(practice const&)
{
    return *this;
}

practice& practice::operator=(practice&&)
{
    return *this;
}

std::string practice::question() const
{
    return std::string{};
}

void practice::question(std::string const&)
{
}

void practice::question(std::string&&)
{
}

std::string practice::answer() const
{
    return std::string{};
}

void practice::answer(std::string const&)
{
}

void practice::answer(std::string&&)
{
}

std::vector<reference> practice::references() const
{
    return std::vector<reference>{};
}

void practice::add_reference(reference const&)
{
}

void practice::add_reference(reference&&)
{
}

std::vector<resource> practice::resoruces() const
{
    return std::vector<resource>{};
}

void practice::add_resource(resource const&)
{
}

void practice::add_resource(resource&&)
{
}

bool practice::operator==(practice const&)
{
    return false;
}
