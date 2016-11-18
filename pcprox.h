#pragma once

using namespace std;

class Pcprox {
public:
    Pcprox();
    bool connect();
    void disconnect();
    string get_card_id();
    int get_last_lib_err();
private:
    bool is_connected;
    unsigned int number_of_devices;

    int try_to_connect();
    string try_get_card_id(unsigned int bytes, BYTE buf[36]);
};