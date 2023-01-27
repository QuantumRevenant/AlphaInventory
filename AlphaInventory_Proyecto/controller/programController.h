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
    bool isSeller = false;
    bool isAdmin = false;
    string sesionKey;

public:
    programController();
    ~programController();
    void closeSesion();
    void openSesion(string, bool, bool);
    bool getActiveSesion();
    bool getIsSeller();
    bool getIsAdmin();
    string getSesionKey();
};

programController::programController()
{
    activeSesion = false;
    isSeller = false;
    isAdmin = false;
    sesionKey = "null-000";
}
programController::~programController() {}
void programController::closeSesion()
{
    activeSesion = false;
    isSeller = false;
    isAdmin = false;
    sesionKey = "null-000";
}
void programController::openSesion(string key, bool isSeller = false, bool isAdmin = false)
{
    activeSesion = true;
    this->isSeller = isSeller;
    this->isAdmin = isAdmin;
    sesionKey = key;
}
bool programController::getActiveSesion()
{
    return activeSesion;
}
bool programController::getIsSeller()
{
    return isSeller;
}
bool programController::getIsAdmin()
{
    return isAdmin;
}

#endif