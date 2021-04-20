//
//  Mode_Mock.hpp
//  Hyperloop_Embedded
//
//  Created by Harry O'Brien on 15/10/2020.
//  Copyright © 2020 Hyperloop Manchester. All rights reserved.
//

#ifndef mocks_Mode_Mode_Mock_hpp
#define mocks_Mode_Mode_Mock_hpp

// NOTE(mikolaj): this define is here to allow intellisense to see the XXX_TEST
// values for statemasks and ids (they are compiled conditionally). it should
// be commented out for running tests to avoid a redefinition warning
//#define UNIT_TEST

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
            ModeTest() : timesExecuted(0)
            {
            }

            void setup(Core::SystemController *state) override
            {
                // only initialise if allowed
                initialised = mayInitialise;
            }

            MODE_ID tick(SystemController *state) override
            {
                if (!initialised)
                    return MODE_ID_PANIC;

                timesExecuted++;
                return MODE_FINALISE;
            }

            void teardown(Core::SystemController *state) override
            {

            }

            statemask_t get_statemask() const override
            {
                return MODE_STATEMASK_TEST;
            }

            bool wasInitialised() const
            {
                return initialised;
            }

            bool wasExecuted() const
            {
                return timesExecuted > 0;
            }

            int getTimesExecuted() const
            {
                return timesExecuted;
            }

            static bool mayInitialise;
        };
    }
}

#endif /* mocks_Mode_Mode_Mock_hpp */