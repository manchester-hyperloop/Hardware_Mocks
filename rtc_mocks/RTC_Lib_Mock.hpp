//
//  RTC_Lib_Mock.hpp
//  Hyperloop Door_Unit
//
//  Created by Harry O'Brien on 17/11/2020.
//

#ifndef mocks_rtc_mocks_RTC_Lib_Mock_hpp
#define mocks_rtc_mocks_RTC_Lib_Mock_hpp

class DateTime
{
public:
    enum timestampOpt
    {
        TIMESTAMP_FULL, //!< `YYYY-MM-DDThh:mm:ss`
        TIMESTAMP_TIME, //!< `hh:mm:ss`
        TIMESTAMP_DATE  //!< `YYYY-MM-DD`
    };

    std::string timestamp(timestampOpt opt)
    {
        switch (opt)
        {
        case TIMESTAMP_FULL:
            return "2020-11-18T12.47.39";
        case TIMESTAMP_TIME:
            return "12:47:39";
        case TIMESTAMP_DATE:
            return "2020-11-18";

        default:
            return "2020-11-18T12.47.39";
        }
    }
};

class RTC_DS1307
{
public:
    inline static bool canInitialise;

    static void setup_mock()
    {
        canInitialise = true;
    }

    bool begin()
    {
        return true;
    }

    DateTime now()
    {
        return DateTime();
    }
};

#endif /* mocks_rtc_mocks_RTC_Lib_Mock_hpp */