/*!
 * @file        readme.txt
 *
 * @brief       This file is routine instruction
 *
 * @version     V1.0.2
 *
 * @date        2023-03-31
 *
 * @attention
 *
 *  Copyright (C) 2023 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */


&par Example Description

This example describes how to configure the SysTick to generate a time base equal to 1 ms.


&par Hardware Description

J2 and J3 Should be shorted.
using LED2(PB5).
using LED3(PB4).


&par Software Description

After Initialization, LED2 and LED3 will toggle interval 1ms.


&par Directory contents

  - SysTick/SysTick/Source/apm32f00x_int.c      Interrupt handlers
  - SysTick/SysTick/Source/main.c               Main program


&par Hardware and Software environment

  - This example runs on APM32F003 MINI Devices.
