#pragma once

#include "password.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace ks{

    /**
    * Class to manage writing and reading files for class Password
    */
    class Manager{
    private:
        std::string m_path; ///< Path to file with encrypted data
    public:
        /**
        * Default constructor
        */
        Manager();

        /**
        * Parametric constructor to set path
        *
        * @param path string with path to encrypted file
        */
        Manager(const std::string& path);

        /**
        * Function to export encrypted data to class Password
        *
        * @param database vector of objects from class Password. Calls Password::encryption to save string to file
        */
        void exporting(const std::vector<Password>& database);

        /**
        * Function to import encrypted data
        *
        * @return vector of Password 
        */
        std::vector<Password> importing();

        /**
        * Operator <<
        *
        * Allows to print class information on screen (std::cout)
        */
        friend std::ostream& operator<<(std::ostream& os, const Manager& m);

        /**
        * Function to set path
        *
        * Allows to set path
        *
        * @param path need to be path to encrypted file
        */
        void setPath(const std::string& path);

        /**
        * Function to get path
        *
        * @return path
        */
        std::string getPath() const;
        };

}