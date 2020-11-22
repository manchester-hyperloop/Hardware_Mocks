//
//  Fake_Duino.hpp
//  Hyperloop Door_Unit
//
//  Created by Harry O'Brien on 17/11/2020.
//

#ifndef Mocks_Fake_Duino_h
#define Mocks_Fake_Duino_h

#include <stdint.h>
#include <map>
#include <utility>
#include <iostream>
#include <string.h>
#include <sstream>

#define HIGH 0x1
#define LOW 0x0

#define OUTPUT 0x0
#define INPUT 0x1
#define INPUT_PULLUP 0x2

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define constrain(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))
#define round(x) ((x) >= 0 ? (long)((x) + 0.5) : (long)((x)-0.5))
#define radians(deg) ((deg)*DEG_TO_RAD)
#define degrees(rad) ((rad)*RAD_TO_DEG)
#define sq(x) ((x) * (x))

// Setup and loop stubs
static void setup();
static void loop();

static unsigned long micros(void)
{
    return 1000;
}

namespace patch
{
    template <typename T>
    std::string to_string(const T &n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
} // namespace patch

class String
{
    std::string str;

public:
    std::string &getString()
    {
        return str;
    }

    std::string::size_type length() const
    {
        return str.length();
    }

    template <typename T>
    String(T param)
    {
        str = patch::to_string(param);
    }

    String(std::string _str)
    {
        str = _str;
    }

    String &replace(char find, char replace)
    {
        if (str.empty())
            return *this;
        for (std::string::size_type i = 0; i < str.size(); i++)
        {
            if (str[i] == find)
                str[i] = replace;
        }

        return *this;
    }

    String &operator+=(String s)
    {
        str += s.getString();
        return *this;
    }

    String operator+(String s)
    {
        return String(str + s.getString());
    }

    const char *c_str()
    {
        return str.c_str();
    }
};

class SerialCommunication
{
    unsigned int baudRate = 0;

public:
    /*
I've gotten bored of trying to make this work...
Implemented templated empty print function
    void print(std::string output)
    {
        std::cerr << output << std::flush;
    }

    void println(std::string output)
    {
        print(output + "\n");
    }

    void print(String output)
    {
        std::cerr << output.getString() << std::flush;
    }

    void println(String output)
    {
        print(output.getString() + "/n");
    }

    template <typename T>
    void print(T val)
    {
        print(patch::to_string(param));
    }

    template <typename T>
    void println(T val)
    {
        print(patch::to_string(param) + "/n");
    }
    */

    template <typename T>
    void print(T val) {}

    template <typename T>
    void println(T val) {}

    bool begin(unsigned int _baudRate)
    {
        baudRate = _baudRate;
        return true;
    }

    explicit operator bool() const
    {
        return true;
    }
};

static SerialCommunication Serial;

#define F

enum IO_State
{
    IO_UNDEFINED = -1, // (undefined behaviour)
    IO_HIGH = 0,
    IO_LOW = 1
};

enum PinMode
{
    PIN_UNDEFINED = -1,
    PIN_OUTPUT,
    PIN_INPUT,
    PIN_INPUT_PULLUP
};

class IO_Mock
{
    IO_State state = IO_UNDEFINED;
    PinMode mode = PIN_UNDEFINED;

    uint8_t pin = -1;

public:
    IO_Mock() {}

    IO_Mock(PinMode pinMode)
        : mode(pinMode)
    {
    }

    IO_Mock(uint8_t _pin, PinMode pinMode)
        : pin(_pin), mode(pinMode)
    {
    }

    void setHigh()
    {
        state = IO_HIGH;
    }

    void setLow()
    {
        state = IO_LOW;
    }

    IO_State getState() const
    {
        return state;
    }
};

static std::map<uint8_t, IO_Mock> initialisedPins;

static void digitalWrite(uint8_t pin, uint8_t state)
{
    try
    {
        IO_Mock &mock = initialisedPins[pin];
        if (state == 0x01)
        {
            mock.setHigh();
        }
        else
        {
            mock.setLow();
        }
    }
    catch (...)
    {
        std::cerr << "Pin " << pin << " not initialised yet!" << std::endl;
    }
}

static bool digitalRead(uint8_t pin)
{
    try
    {
        IO_Mock mock = initialisedPins[pin];
        return (mock.getState() == IO_State::IO_HIGH ? 1 : 0);
    }
    catch (...)
    {
        std::cerr << "Pin " << pin << " not initialised yet!" << std::endl;
    }

    return 0;
}

static void pinMode(uint8_t pin, uint8_t mode)
{
    IO_Mock mock(pin, (PinMode)mode);

    if ((PinMode)mode == PinMode::PIN_INPUT_PULLUP)
    {
        mock.setHigh();
    }

    initialisedPins.insert(std::pair<uint8_t, IO_Mock>(pin, mock));
}

#endif /* Fake_Duino_h */
