/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * Conditionals_post.h
 * Defines that depend on configuration but are not editable.
 */

#ifndef CONDITIONALS_POST_H
#define CONDITIONALS_POST_H

  #if ENABLED(EMERGENCY_PARSER)
    #define EMERGENCY_PARSER_CAPABILITIES " EMERGENCY_CODES:M112,M410"
  #else
    #define EMERGENCY_PARSER_CAPABILITIES ""
  #endif

  /**
   * Set ENDSTOPPULLUPS for unused endstop switches
   */
  #if ENABLED(ENDSTOPPULLUPS)
    #if ENABLED(USE_XMAX_PLUG)
      #define ENDSTOPPULLUP_XMAX
    #endif
    #if ENABLED(USE_YMAX_PLUG)
      #define ENDSTOPPULLUP_YMAX
    #endif
    #if ENABLED(USE_ZMAX_PLUG)
      #define ENDSTOPPULLUP_ZMAX
    #endif
    #if ENABLED(USE_XMIN_PLUG)
      #define ENDSTOPPULLUP_XMIN
    #endif
    #if ENABLED(USE_YMIN_PLUG)
      #define ENDSTOPPULLUP_YMIN
    #endif
    #if ENABLED(USE_ZMIN_PLUG)
      #define ENDSTOPPULLUP_ZMIN
    #endif
    #if DISABLED(DISABLE_Z_MIN_PROBE_ENDSTOP)
      #define ENDSTOPPULLUP_ZMIN_PROBE
    #endif
  #endif

  /**
   * Axis lengths
   */
  #define X_MAX_LENGTH (X_MAX_POS - (X_MIN_POS))
  #define Y_MAX_LENGTH (Y_MAX_POS - (Y_MIN_POS))
  #define Z_MAX_LENGTH (Z_MAX_POS - (Z_MIN_POS))

  /**
   * CoreXY and CoreXZ
   */
  #if ENABLED(COREXY)
    #define CORE_AXIS_1 A_AXIS // XY from A + B
    #define CORE_AXIS_2 B_AXIS
    #define NORMAL_AXIS Z_AXIS
  #elif ENABLED(COREXZ)
    #define CORE_AXIS_1 A_AXIS // XZ from A + C
    #define CORE_AXIS_2 C_AXIS
    #define NORMAL_AXIS Y_AXIS
  #elif ENABLED(COREYZ)
    #define CORE_AXIS_1 B_AXIS // YZ from B + C
    #define CORE_AXIS_2 C_AXIS
    #define NORMAL_AXIS X_AXIS
  #endif

  /**
   * Set the home position based on settings or manual overrides
   */
  #ifdef MANUAL_X_HOME_POS
    #define X_HOME_POS MANUAL_X_HOME_POS
  #elif ENABLED(BED_CENTER_AT_0_0)
      #define X_HOME_POS ((X_MAX_LENGTH) * (X_HOME_DIR) * 0.5)
  #else
      #define X_HOME_POS (X_HOME_DIR < 0 ? X_MIN_POS : X_MAX_POS)
  #endif

  #ifdef MANUAL_Y_HOME_POS
    #define Y_HOME_POS MANUAL_Y_HOME_POS
  #elif ENABLED(BED_CENTER_AT_0_0)
      #define Y_HOME_POS ((Y_MAX_LENGTH) * (Y_HOME_DIR) * 0.5)
  #else
      #define Y_HOME_POS (Y_HOME_DIR < 0 ? Y_MIN_POS : Y_MAX_POS)
  #endif

  #ifdef MANUAL_Z_HOME_POS
    #define Z_HOME_POS MANUAL_Z_HOME_POS
  #else
    #define Z_HOME_POS (Z_HOME_DIR < 0 ? Z_MIN_POS : Z_MAX_POS)
  #endif

  /**
   * Host keep alive
   */
  #ifndef DEFAULT_KEEPALIVE_INTERVAL
    #define DEFAULT_KEEPALIVE_INTERVAL 2
  #endif

  /**
   * MAX_STEP_FREQUENCY differs for TOSHIBA
   */
  #if ENABLED(CONFIG_STEPPERS_TOSHIBA)
    #define MAX_STEP_FREQUENCY 10000 // Max step frequency for Toshiba Stepper Controllers
  #else
    #define MAX_STEP_FREQUENCY 40000 // Max step frequency for Ultimaker (5000 pps / half step)
  #endif

  // MS1 MS2 Stepper Driver Microstepping mode table
  #define MICROSTEP1 LOW,LOW
  #define MICROSTEP2 HIGH,LOW
  #define MICROSTEP4 LOW,HIGH
  #define MICROSTEP8 HIGH,HIGH
  #define MICROSTEP16 HIGH,HIGH

  #if ENABLED(ULTIPANEL) && DISABLED(ELB_FULL_GRAPHIC_CONTROLLER)
    #undef SD_DETECT_INVERTED
  #endif

  /**
   * Set defaults for missing (newer) options
   */
  #ifndef DISABLE_INACTIVE_X
    #define DISABLE_INACTIVE_X DISABLE_X
  #endif
  #ifndef DISABLE_INACTIVE_Y
    #define DISABLE_INACTIVE_Y DISABLE_Y
  #endif
  #ifndef DISABLE_INACTIVE_Z
    #define DISABLE_INACTIVE_Z DISABLE_Z
  #endif

  // Power Signal Control Definitions
  // By default use ATX definition
  #ifndef POWER_SUPPLY
    #define POWER_SUPPLY 1
  #endif
  #if (POWER_SUPPLY == 1)     // 1 = ATX
    #define PS_ON_AWAKE  LOW
    #define PS_ON_ASLEEP HIGH
  #elif (POWER_SUPPLY == 2)   // 2 = X-Box 360 203W
    #define PS_ON_AWAKE  HIGH
    #define PS_ON_ASLEEP LOW
  #endif
  #define HAS_POWER_SWITCH (POWER_SUPPLY > 0 && PIN_EXISTS(PS_ON))

  /**
   * ARRAY_BY_EXTRUDERS based on EXTRUDERS
   */
  #define ARRAY_BY_EXTRUDERS(args...) ARRAY_N(EXTRUDERS, args)
  #define ARRAY_BY_EXTRUDERS1(v1) ARRAY_BY_EXTRUDERS(v1, v1, v1, v1, v1, v1)

  /**
   * Z_DUAL_ENDSTOPS endstop reassignment
   */
  #if ENABLED(Z_DUAL_ENDSTOPS)
    #define _XMIN_ 100
    #define _YMIN_ 200
    #define _ZMIN_ 300
    #define _XMAX_ 101
    #define _YMAX_ 201
    #define _ZMAX_ 301
    #if Z2_USE_ENDSTOP == _XMAX_
      #define Z2_MAX_ENDSTOP_INVERTING X_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN X_MAX_PIN
      #undef USE_XMAX_PLUG
    #elif Z2_USE_ENDSTOP == _YMAX_
      #define Z2_MAX_ENDSTOP_INVERTING Y_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Y_MAX_PIN
      #undef USE_YMAX_PLUG
    #elif Z2_USE_ENDSTOP == _ZMAX_
      #define Z2_MAX_ENDSTOP_INVERTING Z_MAX_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Z_MAX_PIN
      #undef USE_ZMAX_PLUG
    #elif Z2_USE_ENDSTOP == _XMIN_
      #define Z2_MAX_ENDSTOP_INVERTING X_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN X_MIN_PIN
      #undef USE_XMIN_PLUG
    #elif Z2_USE_ENDSTOP == _YMIN_
      #define Z2_MAX_ENDSTOP_INVERTING Y_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Y_MIN_PIN
      #undef USE_YMIN_PLUG
    #elif Z2_USE_ENDSTOP == _ZMIN_
      #define Z2_MAX_ENDSTOP_INVERTING Z_MIN_ENDSTOP_INVERTING
      #define Z2_MAX_PIN Z_MIN_PIN
      #undef USE_ZMIN_PLUG
    #else
      #define Z2_MAX_ENDSTOP_INVERTING false
    #endif
  #endif

  /**
   * Shorthand for pin tests, used wherever needed
   */
  #define HAS_SERVOS (defined(NUM_SERVOS) && NUM_SERVOS > 0)
  #define HAS_SERVO_0 (PIN_EXISTS(SERVO0))
  #define HAS_SERVO_1 (PIN_EXISTS(SERVO1))
  #define HAS_SERVO_2 (PIN_EXISTS(SERVO2))
  #define HAS_SERVO_3 (PIN_EXISTS(SERVO3))
  #define HAS_HOME (PIN_EXISTS(HOME))
  #define HAS_KILL (PIN_EXISTS(KILL))
  #define HAS_SUICIDE (PIN_EXISTS(SUICIDE))
  #define HAS_PHOTOGRAPH (PIN_EXISTS(PHOTOGRAPH))
  #define HAS_X_MIN (PIN_EXISTS(X_MIN))
  #define HAS_X_MAX (PIN_EXISTS(X_MAX))
  #define HAS_Y_MIN (PIN_EXISTS(Y_MIN))
  #define HAS_Y_MAX (PIN_EXISTS(Y_MAX))
  #define HAS_Z_MIN (PIN_EXISTS(Z_MIN))
  #define HAS_Z_MAX (PIN_EXISTS(Z_MAX))
  #define HAS_Z2_MIN (PIN_EXISTS(Z2_MIN))
  #define HAS_Z2_MAX (PIN_EXISTS(Z2_MAX))
  #define HAS_Z_MIN_PROBE_PIN (PIN_EXISTS(Z_MIN_PROBE))
  #define HAS_SOLENOID_1 (PIN_EXISTS(SOL1))
  #define HAS_SOLENOID_2 (PIN_EXISTS(SOL2))
  #define HAS_SOLENOID_3 (PIN_EXISTS(SOL3))
  #define HAS_MICROSTEPS (PIN_EXISTS(X_MS1))
  #define HAS_MICROSTEPS_E0 (PIN_EXISTS(E0_MS1))
  #define HAS_MICROSTEPS_E1 (PIN_EXISTS(E1_MS1))
  #define HAS_MICROSTEPS_E2 (PIN_EXISTS(E2_MS1))
  #define HAS_STEPPER_RESET (PIN_EXISTS(STEPPER_RESET))
  #define HAS_X_ENABLE (PIN_EXISTS(X_ENABLE))
  #define HAS_X2_ENABLE (PIN_EXISTS(X2_ENABLE))
  #define HAS_Y_ENABLE (PIN_EXISTS(Y_ENABLE))
  #define HAS_Y2_ENABLE (PIN_EXISTS(Y2_ENABLE))
  #define HAS_Z_ENABLE (PIN_EXISTS(Z_ENABLE))
  #define HAS_Z2_ENABLE (PIN_EXISTS(Z2_ENABLE))
  #define HAS_X_DIR (PIN_EXISTS(X_DIR))
  #define HAS_X2_DIR (PIN_EXISTS(X2_DIR))
  #define HAS_Y_DIR (PIN_EXISTS(Y_DIR))
  #define HAS_Y2_DIR (PIN_EXISTS(Y2_DIR))
  #define HAS_Z_DIR (PIN_EXISTS(Z_DIR))
  #define HAS_Z2_DIR (PIN_EXISTS(Z2_DIR))
  #define HAS_X_STEP (PIN_EXISTS(X_STEP))
  #define HAS_X2_STEP (PIN_EXISTS(X2_STEP))
  #define HAS_Y_STEP (PIN_EXISTS(Y_STEP))
  #define HAS_Y2_STEP (PIN_EXISTS(Y2_STEP))
  #define HAS_Z_STEP (PIN_EXISTS(Z_STEP))
  #define HAS_Z2_STEP (PIN_EXISTS(Z2_STEP))
  #define HAS_DIGIPOTSS (PIN_EXISTS(DIGIPOTSS))
  #define HAS_BUZZER (PIN_EXISTS(BEEPER) || ENABLED(LCD_USE_I2C_BUZZER))

  #define HAS_MOTOR_CURRENT_PWM (PIN_EXISTS(MOTOR_CURRENT_PWM_XY) || PIN_EXISTS(MOTOR_CURRENT_PWM_Z))

  /**
   * Servos and probes
   */

  #if HAS_SERVOS
    #ifndef Z_ENDSTOP_SERVO_NR
      #define Z_ENDSTOP_SERVO_NR -1
    #endif
  #endif

  /**
   * Buzzer/Speaker
   */
  #if ENABLED(LCD_USE_I2C_BUZZER)
    #ifndef LCD_FEEDBACK_FREQUENCY_HZ
      #define LCD_FEEDBACK_FREQUENCY_HZ 1000
    #endif
    #ifndef LCD_FEEDBACK_FREQUENCY_DURATION_MS
      #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 100
    #endif
  #elif PIN_EXISTS(BEEPER)
    #ifndef LCD_FEEDBACK_FREQUENCY_HZ
      #define LCD_FEEDBACK_FREQUENCY_HZ 5000
    #endif
    #ifndef LCD_FEEDBACK_FREQUENCY_DURATION_MS
      #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
    #endif
  #else
    #ifndef LCD_FEEDBACK_FREQUENCY_DURATION_MS
      #define LCD_FEEDBACK_FREQUENCY_DURATION_MS 2
    #endif
  #endif

  /**
   * Z_HOMING_HEIGHT
   */
  #ifndef Z_HOMING_HEIGHT
    #define Z_HOMING_HEIGHT 0
  #endif

#endif // CONDITIONALS_POST_H
