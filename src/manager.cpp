#include "manager.hpp"
#include "password.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace ks
{
    Manager::Manager(){}

    Manager::Manager(const std::string& path):m_path(path){}

    std::ostream& operator<<(std::ostream& os, const Manager& m)
    {
        os << m.m_path << "\n";

        return os;
    }

    void Manager::setPath(const std::string& path)
    {
        if(path.length()>0)
        {
            m_path = path;
        }
        else
        {
            throw std::invalid_argument("Path can not be empty");
        }
    }

    std::string Manager::getPath() const
    {
        return m_path;
    }
}