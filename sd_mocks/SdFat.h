//
//  SdFat.h
//  Dynamic_Pod_Control_Unit
//
//  Created by Harry O'Brien on 17/11/2020.
//

#ifndef mocks_sd_mock_SdFat_h
#define mocks_sd_mock_SdFat_h

#include <stdint.h>
#include <string.h>

#define FILE_WRITE 0

// Log file.
struct File
{
    bool file_is_open = true;
    std::string lastMessage = "";

    void close()
    {
        file_is_open = false;
    }

    explicit operator bool() const
    {
        return file_is_open;
    }

    void print(std::string message)
    {
        lastMessage = message;
    }
};

class SdFat
{
    uint8_t cs_pin = -1;
    std::string dir_path = "";
    std::string log_path = "";
    int fileArgs = -1;

public:
    bool begin(uint8_t _cs_pin)
    {
        cs_pin = _cs_pin;

        return true;
    }

    void mkdir(std::string directory_name)
    {
        dir_path += directory_name;
    }

    File open(std::string _log_path, int args)
    {
        log_path = _log_path;
        fileArgs = args;

        return File();
    }

    uint8_t get_cs_pin()
    {
        return cs_pin;
    }
};

#endif /* mocks_sd_mock_SdFat_h */
