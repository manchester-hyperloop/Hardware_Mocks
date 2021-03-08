//
//  CAN_Mock.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 10/03/2021.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef mocks_CAN_CAN_Mock_hpp
#define mocks_CAN_CAN_Mock_hpp

class CAN
{
    int timesExecuted;
    bool initialised;

public:
    static bool mayInitialise;
};
#endif /* mocks_CAN_CAN_Mock_hpp */