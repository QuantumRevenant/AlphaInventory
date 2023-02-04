#ifndef PROGRAMCONTROLLER_H
#define PROGRAMCONTROLLER_H

#include <iostream>
#include <string>

using namespace std;

/*

*/

class programController
{
private:
    bool activeSesion = false;
    bool isSupervisor = false;
    bool isAdmin = false;
    string sesionKey;

public:
    programController();
    ~programController();
    void closeSesion();
    void openSesion(string, bool, bool);
    bool getActiveSesion();
    bool getIsSupervisor();
    bool getIsAdmin();
    string getSesionKey();
};

programController::programController()
{
    activeSesion = false;
    isSupervisor = false;
    isAdmin = false;
    sesionKey = "null-000";
}
programController::~programController() {}
void programController::closeSesion()
{
    activeSesion = false;
    isSupervisor = false;
    isAdmin = false;
    sesionKey = "null-000";
}
void programController::openSesion(string key, bool isSupervisor = false, bool isAdmin = false)
{
    activeSesion = true;
    this->isSupervisor = isSupervisor;
    this->isAdmin = isAdmin;
    sesionKey = key;
}
bool programController::getActiveSesion()
{
    return activeSesion;
}
bool programController::getIsSupervisor()
{
    return isSupervisor;
}
bool programController::getIsAdmin()
{
    return isAdmin;
}
string programController::getSesionKey()
{
    return sesionKey;
}
#endif