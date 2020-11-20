//
//  Mode_Test_Mock.cpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef mocks_Mode_Mode_Test_Mock_hpp
#define mocks_Mode_Mode_Test_Mock_hpp

#include "Core/Mode/Mode.hpp"
#include "Core/SystemController.hpp"

namespace Core
{
    namespace Mode
    {
        /**
         * Defines the behaviour of the system when in Test
         */
        class ModeTest : public Mode
        {
            bool initialised;
            int timesExecuted;

        public:
            /**
             * Defines the behaviour of the system when in Test
             */
            ModeTest(Core::SystemController *sysCtrl) : Mode(sysCtrl),
                                                        initialised(false),
                                                        timesExecuted(0)
            {
            }

            ~ModeTest()
            {
            }

            bool init()
            {
                initialised = true;
                return true;
            }

            bool run()
            {
                timesExecuted++;
                return true;
            }

            /**
             * Gets the name of the mode as a string
             */
            ModeType type()
            {
                return ModeType::TEST;
            }

            bool wasInitialised()
            {
                return initialised;
            }

            bool wasExecuted()
            {
                return timesExecuted > 0;
            }

            int getTimesExecuted()
            {
                return timesExecuted;
            }

            void transitionToNextTestMock()
            {
                sysCtrl->shouldTransitionToMode(ModeType::TEST);
            }
        };
    } // namespace Mode
} // namespace Core

#endif /* mocks_Mode_Mode_Test_Mock_hpp */