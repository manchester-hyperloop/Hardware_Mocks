//
//  SdFat.h
//  Dynamic_Pod_Control_Unit
//
//  Created by Harry O'Brien on 17/11/2020.
//

#ifndef mocks_sd_mock_SdFat_h
#define mocks_sd_mock_SdFat_h

#include <stdint.h>
#include <string>
#include "../Arduino_Mock/Arduino_Mock.hpp"

#define FILE_WRITE 0

// Log file.
class File
{

public:
    static bool file_is_open;
    std::string lastMessage = "";

    void setup_mock()
    {
        file_is_open = true;
    }

    void close()
    {
        file_is_open = false;
    }

    explicit operator bool()
    {
        return File::file_is_open;
    }

    void print(String message)
    {
        lastMessage = message.getString();
    }

    void println(String message)
    {
        lastMessage = message.getString() + "\n";
    }

    void flush()
    {
    }

    std::string &getLastMessage()
    {
        return lastMessage;
    }
};

class SdFat
{
    uint8_t cs_pin = -1;
    std::string dir_path = "";
    std::string log_path = "";
    int fileArgs = -1;

public:
    static bool canInitialise;

    void setup_mock()
    {
        canInitialise = true;
    }

    bool begin(uint8_t _cs_pin)
    {
        cs_pin = _cs_pin;

        return canInitialise;
    }

    void mkdir(std::string directory_name)
    {
        dir_path += directory_name;
    }

    void mkdir(char *directory_name)
    {
        dir_path += directory_name;
    }

    File open(std::string _log_path, int args)
    {
        log_path = _log_path;
        fileArgs = args;

        return File();
    }

    File open(String _log_path, int args)
    {
        log_path = _log_path.getString();
        fileArgs = args;

        return File();
    }

    uint8_t get_cs_pin()
    {
        return cs_pin;
    }
};

#endif /* mocks_sd_mock_SdFat_h */
