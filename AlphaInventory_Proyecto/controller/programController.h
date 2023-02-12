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
    int sesionKey;

public:
    programController();
    ~programController();
    void closeSesion();
    void openSesion(int, bool, bool);
    bool getActiveSesion();
    bool getIsSupervisor();
    bool getIsAdmin();
    int getSesionKey();
};

programController::programController()
{
    activeSesion = false;
    isSupervisor = false;
    isAdmin = false;
    sesionKey = -1;
}
programController::~programController() {}

void programController::closeSesion()
{
    activeSesion = false;
    isSupervisor = false;
    isAdmin = false;
    sesionKey = -1;
}
void programController::openSesion(int key, bool isSupervisor = false, bool isAdmin = false)
{
    activeSesion = true;
    this->isSupervisor = isSupervisor;
    this->isAdmin = isAdmin;
    sesionKey = key;
}

bool programController::getActiveSesion() { return activeSesion; }
bool programController::getIsSupervisor() { return isSupervisor; }
bool programController::getIsAdmin() { return isAdmin; }
int programController::getSesionKey() { return sesionKey; }
#endif