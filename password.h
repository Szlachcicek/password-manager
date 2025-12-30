#pragma once

#include <string> ///< Library to use string
#include <ctime> ///< Library to read current time.

namespace ks{

    /**
    * Basic class to store only password and URL of website. Class automaticly adds time of creation and unique ID
    */
    class Password{
    protected:
        std::string m_password; ///< Encrypted password
        std::string m_url; ///< Address to website
        std::time_t m_creationDate; ///< Date of creation
        unsigned int m_id; ///< Unique identifier

    public:
        /**
        * Default constructor
        */
        Password();

        /**
        * Constructor for generating password
        *
        * @param url    string with link to site
        */
        Password(std::string url);

        /**
        * Constructor for saving password
        *
        * @param pass   string with password to encrypt
        * @param url    string with link to site
        */
        Password(std::string pass, std::string url);

        virtual ~Password();
    };

}