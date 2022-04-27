/*
 * File:   Log.h
 * Author: Imad Anis <imad.anis@neumann.ai>
 *
 */
#pragma once

#include <iostream>

//Uncomment to enable DEBUG MODE
//#define DEBUGMODE //To be defined by configuration 

//Log Levels ENUM
enum class TYPE_LOG {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    NONE
};

//Struct log used to configure the log
struct LOG_CONFIG_DEF {
    bool headers = false; //show log headers
    TYPE_LOG level = TYPE_LOG::WARN; //log level 
};
extern LOG_CONFIG_DEF LOG_CFG; //Log configuration

//LOG CLASS
class LOG {
public:

    LOG() {} //empty constructor 
    
    LOG(TYPE_LOG type) { //constuctor with log type
        msglevel = type;

        //If configuration enable header show header from type 
        if (LOG_CFG.headers) {
            operator << ("[" + getLabel(type) + "] \n"); // call the operator
        }
    }
    ~LOG() {
        //check if opened and add closing line 
        if (opened) {
            std::cout << std::endl;
        }
        opened = false;
    }

    //Template operator function to support all types
    template<class T>
    LOG& operator<<(const T& msg) {
        //Check for log level
        if (msglevel >= LOG_CFG.level) {
            std::cout << msg;
            opened = true; //flag log as opened 
        }
        return *this;
    }
private:

    bool opened = false; //flag
    TYPE_LOG msglevel = TYPE_LOG::DEBUG; //default message level 

    //get log label message
    inline std::string getLabel(TYPE_LOG type) {
        std::string label;
        switch (type) {
            case TYPE_LOG::DEBUG: label = "DEBUG"; break;
            case TYPE_LOG::INFO:  label = "INFO"; break;
            case TYPE_LOG::WARN:  label = "WARN"; break;
            case TYPE_LOG::ERROR: label = "ERROR"; break;
        }
        return label;
    }
};

