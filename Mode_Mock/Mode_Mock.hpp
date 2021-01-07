//
//  Mode_Mock.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef mocks_Mode_Mode_Mock_hpp
#define mocks_Mode_Mode_Mock_hpp

#include "../../include/Core/Mode/Mode.hpp"
#include "../../include/Core/SystemController.hpp"

namespace Core
{
    namespace Mode
    {
        /**
         * Defines the behaviour of the system when in Test
         */
        class ModeTest : public Mode
        {
            int timesExecuted;
            bool initialised;

        public:
            /**
             * Defines the behaviour of the system when in Test
             */
            ModeTest(Core::SystemController *sysCtrl) : Mode(sysCtrl),
                                                        timesExecuted(0)
            {
            }

            ~ModeTest()
            {
            }

            bool init()
            {
                // only initialise if allowed
                initialised = (mayInitialise ? true : false);
                return initialised;
            }

            bool run()
            {
                timesExecuted++;
                return true;
            }

            /**
             * Gets the name of the mode
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

            static bool mayInitialise;
        };
    } // namespace Mode
} // namespace Core

#endif /* mocks_Mode_Mode_Mock_hpp */