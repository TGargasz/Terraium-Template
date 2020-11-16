/*
    Name:       TerrariumTemplate.ino - An Arduino template for PedalPCB Terrarium 
    Created:	11/15/2020 10:30:38 AM
    Copyright (C) 2020  By: Tony Gargasz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation version 3.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see https://www.gnu.org/licenses
*/

/*




*/
// Includes
#include <DaisyDSP.h>
#include <DaisyDuino.h>


// Instantiate Daisy Seed hardware
DaisyHardware hw;
size_t num_channels;
float sample_rate;

// Indetify Switch pins
const int footSw1 = D25;
const int footSw2 = D26;
const int toglSw1 = D8;
const int toglSw2 = D9;
const int toglSw3 = D10;
const int toglSw4 = D11;

// Identify Led pins
const int led1 = D22;
const int led2 = D23;

// Idenify Knob pins
const int knob1 = A1;
const int knob2 = A2;
const int knob3 = A3;
const int knob4 = A4;
const int knob5 = A5;
const int knob6 = A6;

// Create vars for Knobs
float knob1val;
float knob2val;
float knob3val;
float knob4val;
float knob5val;
float knob6val;

// Create vars for non-blocking timer in loop()
unsigned long currentMillis;        // To set period to poll knobs and switches
unsigned long previousMillis = 0;   // Last time knobs and switches were polled
const long interval = 100;          // Interval at which to poll (milliseconds)

// Create vars for Examples
boolean footSw1_Enabled = true;
boolean footSw1_On = false;

void setup()
{
    // Setup Switches
    pinMode(footSw1, INPUT_PULLUP);
    pinMode(footSw2, INPUT_PULLUP);
    pinMode(toglSw1, INPUT_PULLUP);
    pinMode(toglSw2, INPUT_PULLUP);
    pinMode(toglSw3, INPUT_PULLUP);
    pinMode(toglSw4, INPUT_PULLUP);

    // Setup Leds
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    // Initialize Daisy Seed audio at 48kHz
    hw = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    num_channels = hw.num_channels;
    sample_rate = DAISY.get_samplerate();
}

void loop()
{
    // Poll the hardware. Poll period is 100 ms and can be adjusted with var: interval 
    currentMillis = millis();
    if (currentMillis - previousMillis >= interval)
    {
        // save the last poll time
        previousMillis = currentMillis;

        // ================== EXAMPLE - Footswitch and Led =====================
        // Footswitch is momentary so simulate a S/R latch
        if (digitalRead(footSw1))
        {
            if (footSw1_Enabled == true)
            {
                digitalWrite(led1, !(digitalRead(led1)));
                footSw1_Enabled = false;
            }
        }
        else
        {
            if (footSw1_Enabled == false)
            {
                footSw1_Enabled = true;
            }
        }
        if (digitalRead(led1) == HIGH)
        {
            footSw1_On = false; 
        }
        else
        {
            footSw1_On = true; 
        }

        // ================= EXAMPLE - Read Knobs (return range is 0 to 1023) =====================
        knob1val = analogRead(knob1);
        knob2val = analogRead(knob2);
    }
}
