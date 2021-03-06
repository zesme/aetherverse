#include "../include/catch.hpp"
#include "../src/Utilities.hpp"

TEST_CASE("Test J-Type instructions", "[step][J-type]") {
    Emulator* vm;

    SECTION("j") {
        WORD program[1];
        program[0] = Utilities::J_instruction(2, 0b10); // j 2
        program[1] = Utilities::R_instruction(0, 1, 1, 2, 0, 32); // add r1, r1, r2
        program[2] = Utilities::R_instruction(0, 1, 1, 3, 0, 32); // add r1, r1, r3

        vm = new Emulator(128, program, 3);
        vm->set_register(1, 8);
        vm->set_register(2, 5);
        vm->set_register(3, 10);

        SECTION("functions as expected") {
            REQUIRE(vm->step() == 0);
            REQUIRE(vm->step() == 0);
            REQUIRE(vm->get_register(1) == 18);
        }
    }

    SECTION("jal") {
        WORD program[1];
        program[0] = Utilities::J_instruction(3, 0b10); // jal 2
        program[1] = Utilities::R_instruction(0, 1, 1, 2, 0, 32); // add r1, r1, r2
        program[2] = Utilities::R_instruction(0, 1, 1, 3, 0, 32); // add r1, r1, r3

        vm = new Emulator(128, program, 3);
        vm->set_register(1, 8);
        vm->set_register(2, 5);
        vm->set_register(3, 10);

        SECTION("functions as expected") {
            REQUIRE(vm->step() == 0);
            REQUIRE(vm->step() == 0);
            REQUIRE(vm->get_register(1) == 18);
            REQUIRE(vm->get_register(31) == 4);
        }
    }
}
