#pragma once

#include "password.hpp"
#include <string>
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <sstream>

namespace ks
{
    class PasswordCM : public Password
    {
        friend class Manager;

    private:
        static unsigned int m_idCounter; ///< Counter for unique identifier for classes

    protected:
        std::string m_login; ///< Login or email to website

    public:
        /**
        * @brief Default constructor
        * 
        * Setting only time of creation
        */
        PasswordCM();
        
        /**
         * @brief Constructor for generating password
         * 
         * Setting time of creation, URL of website, client number and generating password
         * 
         * @param url string with link to site
         * @param login string with login or email to site
         */
        PasswordCM(const std::string& url, const std::string& login);

        /**
         * @brief Constructor for saving password
         * 
         * Setting time of creation, URL of website, client number and password
         * 
         * @param url string with link to site
         * @param login string with login or email to site
         * @param password string with password to encrypt
         */
        PasswordCM(const std::string& url, const std::string& login, const std::string& password);

        /**
        * @brief Function for encrypting password
        *
        * @return formatted all data ready to save in .txt file 
        */
        std::string encryption() const override;

        /**
        * @brief Function for decrytping password
        *
        * @return data to class
        */
        void decryption(const std::string& data) override;

        /**
        * @brief Operator ==
        *
        * @return bool true or false if objects are identicall (m_url, m_password, m_login)
        */
        bool operator==(const PasswordCM& other) const;
        
        /**
        * @brief Operator <<
        *
        * Allows to print class information on screen (std::cout)
        * 
        * @return id, password, url, login/email, creation date (even when empty)
        */
        friend std::ostream& operator<<(std::ostream& os, const PasswordCM& p);

        /**
        * @brief Function to set new login/email
        *
        * Allows to change login/email
        *
        * @param login need to be login or email
        */
        void setLogin(const std::string& login);
        
        /**
        * @brief Function to get login
        *
        * @return client login
        */
        std::string getLogin() const;
    };
}