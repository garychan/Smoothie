/*
      This file is part of Smoothie (http://smoothieware.org/). The motion control part is heavily based on Grbl (https://github.com/simen/grbl).
      Smoothie is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
      Smoothie is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
      You should have received a copy of the GNU General Public License along with Smoothie. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef STEPPER_H
#define STEPPER_H
#include "libs/Module.h"
#include "libs/Kernel.h"
#include "Planner.h"
#include "Block.h"

#define microseconds_per_step_pulse_checksum        CHECKSUM("microseconds_per_step_pulse")
#define acceleration_ticks_per_second_checksum      CHECKSUM("acceleration_ticks_per_second")
#define minimum_steps_per_minute_checksum           CHECKSUM("minimum_steps_per_minute")
#define base_stepping_frequency_checksum            CHECKSUM("base_stepping_frequency")
#define alpha_step_pin_checksum                     CHECKSUM("alpha_step_pin")
#define beta_step_pin_checksum                      CHECKSUM("beta_step_pin")
#define gamma_step_pin_checksum                     CHECKSUM("gamma_step_pin")
#define alpha_dir_pin_checksum                      CHECKSUM("alpha_dir_pin")
#define beta_dir_pin_checksum                       CHECKSUM("beta_dir_pin")
#define gamma_dir_pin_checksum                      CHECKSUM("gamma_dir_pin")
#define alpha_en_pin_checksum                       CHECKSUM("alpha_en_pin")
#define beta_en_pin_checksum                        CHECKSUM("beta_en_pin")
#define gamma_en_pin_checksum                       CHECKSUM("gamma_en_pin")


class Stepper : public Module {
    public:
        Stepper();
        void on_module_loaded();
        void on_config_reload(void* argument);
        void on_block_begin(void* argument);
        void on_block_end(void* argument);
        void on_gcode_execute(void* argument);
        void on_play(void* argument);
        void on_pause(void* argument);
        uint32_t main_interrupt(uint32_t dummy);
        void trapezoid_generator_reset();
        void set_step_events_per_minute(double steps_per_minute);
        uint32_t trapezoid_generator_tick(uint32_t dummy);
        uint32_t stepper_motor_finished_move(uint32_t dummy);
        int config_step_timer( int cycles );
        void turn_enable_pins_on();
        void turn_enable_pins_off();
        uint32_t synchronize_acceleration(uint32_t dummy);

        Block* current_block;
        int counters[3];
        int stepped[3];
        int offsets[3];
        float counter_alpha;
        float counter_beta;
        float counter_gamma;
        //int step_events_completed;
        unsigned int out_bits;
        double trapezoid_adjusted_rate;
        int trapezoid_tick_cycle_counter;
        int cycles_per_step_event;
        bool trapezoid_generator_busy;
        int microseconds_per_step_pulse;
        int acceleration_ticks_per_second;
        unsigned int minimum_steps_per_minute;
        int base_stepping_frequency;
        unsigned short step_bits[3];
        int counter_increment;
        bool paused;
        bool force_speed_update;
        bool enable_pins_status;
        Hook* acceleration_tick_hook;

        StepperMotor* main_stepper;

};




#endif
