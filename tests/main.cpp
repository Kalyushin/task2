#include "save_test.h"
#include "showupper_test.h"
#include "m_test.h"
#include "mlb_test.h"
#include "r1e_test.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
