/*******************************************************************************
  GPIO PLIB

  Company:
    Microchip Technology Inc.

  File Name:
    plib_gpio.h

  Summary:
    GPIO PLIB Header File

  Description:
    This library provides an interface to control and interact with Parallel
    Input/Output controller (GPIO) module.

*******************************************************************************/

/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#ifndef PLIB_GPIO_H
#define PLIB_GPIO_H

#include <device.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data types and constants
// *****************************************************************************
// *****************************************************************************


/*** Macros for SEGf pin ***/
#define SEGf_Set()               (LATESET = (1<<5))
#define SEGf_Clear()             (LATECLR = (1<<5))
#define SEGf_Toggle()            (LATEINV= (1<<5))
#define SEGf_OutputEnable()      (TRISECLR = (1<<5))
#define SEGf_InputEnable()       (TRISESET = (1<<5))
#define SEGf_Get()               ((PORTE >> 5) & 0x1)
#define SEGf_PIN                  GPIO_PIN_RE5

/*** Macros for SEGg pin ***/
#define SEGg_Set()               (LATESET = (1<<6))
#define SEGg_Clear()             (LATECLR = (1<<6))
#define SEGg_Toggle()            (LATEINV= (1<<6))
#define SEGg_OutputEnable()      (TRISECLR = (1<<6))
#define SEGg_InputEnable()       (TRISESET = (1<<6))
#define SEGg_Get()               ((PORTE >> 6) & 0x1)
#define SEGg_PIN                  GPIO_PIN_RE6

/*** Macros for L1 pin ***/
#define L1_Set()               (LATASET = (1<<0))
#define L1_Clear()             (LATACLR = (1<<0))
#define L1_Toggle()            (LATAINV= (1<<0))
#define L1_OutputEnable()      (TRISACLR = (1<<0))
#define L1_InputEnable()       (TRISASET = (1<<0))
#define L1_Get()               ((PORTA >> 0) & 0x1)
#define L1_PIN                  GPIO_PIN_RA0

/*** Macros for termistor pin ***/
#define termistor_Get()               ((PORTB >> 1) & 0x1)
#define termistor_PIN                  GPIO_PIN_RB1

/*** Macros for L2 pin ***/
#define L2_Set()               (LATASET = (1<<1))
#define L2_Clear()             (LATACLR = (1<<1))
#define L2_Toggle()            (LATAINV= (1<<1))
#define L2_OutputEnable()      (TRISACLR = (1<<1))
#define L2_InputEnable()       (TRISASET = (1<<1))
#define L2_Get()               ((PORTA >> 1) & 0x1)
#define L2_PIN                  GPIO_PIN_RA1

/*** Macros for L3 pin ***/
#define L3_Set()               (LATASET = (1<<2))
#define L3_Clear()             (LATACLR = (1<<2))
#define L3_Toggle()            (LATAINV= (1<<2))
#define L3_OutputEnable()      (TRISACLR = (1<<2))
#define L3_InputEnable()       (TRISASET = (1<<2))
#define L3_Get()               ((PORTA >> 2) & 0x1)
#define L3_PIN                  GPIO_PIN_RA2

/*** Macros for L4 pin ***/
#define L4_Set()               (LATASET = (1<<3))
#define L4_Clear()             (LATACLR = (1<<3))
#define L4_Toggle()            (LATAINV= (1<<3))
#define L4_OutputEnable()      (TRISACLR = (1<<3))
#define L4_InputEnable()       (TRISASET = (1<<3))
#define L4_Get()               ((PORTA >> 3) & 0x1)
#define L4_PIN                  GPIO_PIN_RA3

/*** Macros for L5 pin ***/
#define L5_Set()               (LATASET = (1<<4))
#define L5_Clear()             (LATACLR = (1<<4))
#define L5_Toggle()            (LATAINV= (1<<4))
#define L5_OutputEnable()      (TRISACLR = (1<<4))
#define L5_InputEnable()       (TRISASET = (1<<4))
#define L5_Get()               ((PORTA >> 4) & 0x1)
#define L5_PIN                  GPIO_PIN_RA4

/*** Macros for L6 pin ***/
#define L6_Set()               (LATASET = (1<<5))
#define L6_Clear()             (LATACLR = (1<<5))
#define L6_Toggle()            (LATAINV= (1<<5))
#define L6_OutputEnable()      (TRISACLR = (1<<5))
#define L6_InputEnable()       (TRISASET = (1<<5))
#define L6_Get()               ((PORTA >> 5) & 0x1)
#define L6_PIN                  GPIO_PIN_RA5

/*** Macros for SEG1 pin ***/
#define SEG1_Set()               (LATDSET = (1<<0))
#define SEG1_Clear()             (LATDCLR = (1<<0))
#define SEG1_Toggle()            (LATDINV= (1<<0))
#define SEG1_OutputEnable()      (TRISDCLR = (1<<0))
#define SEG1_InputEnable()       (TRISDSET = (1<<0))
#define SEG1_Get()               ((PORTD >> 0) & 0x1)
#define SEG1_PIN                  GPIO_PIN_RD0

/*** Macros for SEG2 pin ***/
#define SEG2_Set()               (LATDSET = (1<<1))
#define SEG2_Clear()             (LATDCLR = (1<<1))
#define SEG2_Toggle()            (LATDINV= (1<<1))
#define SEG2_OutputEnable()      (TRISDCLR = (1<<1))
#define SEG2_InputEnable()       (TRISDSET = (1<<1))
#define SEG2_Get()               ((PORTD >> 1) & 0x1)
#define SEG2_PIN                  GPIO_PIN_RD1

/*** Macros for SEG3 pin ***/
#define SEG3_Set()               (LATDSET = (1<<2))
#define SEG3_Clear()             (LATDCLR = (1<<2))
#define SEG3_Toggle()            (LATDINV= (1<<2))
#define SEG3_OutputEnable()      (TRISDCLR = (1<<2))
#define SEG3_InputEnable()       (TRISDSET = (1<<2))
#define SEG3_Get()               ((PORTD >> 2) & 0x1)
#define SEG3_PIN                  GPIO_PIN_RD2

/*** Macros for SEG4 pin ***/
#define SEG4_Set()               (LATDSET = (1<<3))
#define SEG4_Clear()             (LATDCLR = (1<<3))
#define SEG4_Toggle()            (LATDINV= (1<<3))
#define SEG4_OutputEnable()      (TRISDCLR = (1<<3))
#define SEG4_InputEnable()       (TRISDSET = (1<<3))
#define SEG4_Get()               ((PORTD >> 3) & 0x1)
#define SEG4_PIN                  GPIO_PIN_RD3

/*** Macros for aquecedor pin ***/
#define aquecedor_Set()               (LATDSET = (1<<4))
#define aquecedor_Clear()             (LATDCLR = (1<<4))
#define aquecedor_Toggle()            (LATDINV= (1<<4))
#define aquecedor_OutputEnable()      (TRISDCLR = (1<<4))
#define aquecedor_InputEnable()       (TRISDSET = (1<<4))
#define aquecedor_Get()               ((PORTD >> 4) & 0x1)
#define aquecedor_PIN                  GPIO_PIN_RD4

/*** Macros for L7 pin ***/
#define L7_Set()               (LATASET = (1<<6))
#define L7_Clear()             (LATACLR = (1<<6))
#define L7_Toggle()            (LATAINV= (1<<6))
#define L7_OutputEnable()      (TRISACLR = (1<<6))
#define L7_InputEnable()       (TRISASET = (1<<6))
#define L7_Get()               ((PORTA >> 6) & 0x1)
#define L7_PIN                  GPIO_PIN_RA6

/*** Macros for L8 pin ***/
#define L8_Set()               (LATASET = (1<<7))
#define L8_Clear()             (LATACLR = (1<<7))
#define L8_Toggle()            (LATAINV= (1<<7))
#define L8_OutputEnable()      (TRISACLR = (1<<7))
#define L8_InputEnable()       (TRISASET = (1<<7))
#define L8_Get()               ((PORTA >> 7) & 0x1)
#define L8_PIN                  GPIO_PIN_RA7

/*** Macros for SEGa pin ***/
#define SEGa_Set()               (LATESET = (1<<0))
#define SEGa_Clear()             (LATECLR = (1<<0))
#define SEGa_Toggle()            (LATEINV= (1<<0))
#define SEGa_OutputEnable()      (TRISECLR = (1<<0))
#define SEGa_InputEnable()       (TRISESET = (1<<0))
#define SEGa_Get()               ((PORTE >> 0) & 0x1)
#define SEGa_PIN                  GPIO_PIN_RE0

/*** Macros for SEGb pin ***/
#define SEGb_Set()               (LATESET = (1<<1))
#define SEGb_Clear()             (LATECLR = (1<<1))
#define SEGb_Toggle()            (LATEINV= (1<<1))
#define SEGb_OutputEnable()      (TRISECLR = (1<<1))
#define SEGb_InputEnable()       (TRISESET = (1<<1))
#define SEGb_Get()               ((PORTE >> 1) & 0x1)
#define SEGb_PIN                  GPIO_PIN_RE1

/*** Macros for SEGc pin ***/
#define SEGc_Set()               (LATESET = (1<<2))
#define SEGc_Clear()             (LATECLR = (1<<2))
#define SEGc_Toggle()            (LATEINV= (1<<2))
#define SEGc_OutputEnable()      (TRISECLR = (1<<2))
#define SEGc_InputEnable()       (TRISESET = (1<<2))
#define SEGc_Get()               ((PORTE >> 2) & 0x1)
#define SEGc_PIN                  GPIO_PIN_RE2

/*** Macros for SEGd pin ***/
#define SEGd_Set()               (LATESET = (1<<3))
#define SEGd_Clear()             (LATECLR = (1<<3))
#define SEGd_Toggle()            (LATEINV= (1<<3))
#define SEGd_OutputEnable()      (TRISECLR = (1<<3))
#define SEGd_InputEnable()       (TRISESET = (1<<3))
#define SEGd_Get()               ((PORTE >> 3) & 0x1)
#define SEGd_PIN                  GPIO_PIN_RE3

/*** Macros for SEGe pin ***/
#define SEGe_Set()               (LATESET = (1<<4))
#define SEGe_Clear()             (LATECLR = (1<<4))
#define SEGe_Toggle()            (LATEINV= (1<<4))
#define SEGe_OutputEnable()      (TRISECLR = (1<<4))
#define SEGe_InputEnable()       (TRISESET = (1<<4))
#define SEGe_Get()               ((PORTE >> 4) & 0x1)
#define SEGe_PIN                  GPIO_PIN_RE4


// *****************************************************************************
/* GPIO Port

  Summary:
    Identifies the available GPIO Ports.

  Description:
    This enumeration identifies the available GPIO Ports.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all ports are available on all devices.  Refer to the specific
    device data sheet to determine which ports are supported.
*/

typedef enum
{
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4,
    GPIO_PORT_F = 5,
    GPIO_PORT_G = 6,
} GPIO_PORT;

// *****************************************************************************
/* GPIO Port Pins

  Summary:
    Identifies the available GPIO port pins.

  Description:
    This enumeration identifies the available GPIO port pins.

  Remarks:
    The caller should not rely on the specific numbers assigned to any of
    these values as they may change from one processor to the next.

    Not all pins are available on all devices.  Refer to the specific
    device data sheet to determine which pins are supported.
*/

typedef enum
{
    GPIO_PIN_RA0 = 0,
    GPIO_PIN_RA1 = 1,
    GPIO_PIN_RA2 = 2,
    GPIO_PIN_RA3 = 3,
    GPIO_PIN_RA4 = 4,
    GPIO_PIN_RA5 = 5,
    GPIO_PIN_RA6 = 6,
    GPIO_PIN_RA7 = 7,
    GPIO_PIN_RA9 = 9,
    GPIO_PIN_RA10 = 10,
    GPIO_PIN_RA14 = 14,
    GPIO_PIN_RA15 = 15,
    GPIO_PIN_RB0 = 16,
    GPIO_PIN_RB1 = 17,
    GPIO_PIN_RB2 = 18,
    GPIO_PIN_RB3 = 19,
    GPIO_PIN_RB4 = 20,
    GPIO_PIN_RB5 = 21,
    GPIO_PIN_RB6 = 22,
    GPIO_PIN_RB7 = 23,
    GPIO_PIN_RB8 = 24,
    GPIO_PIN_RB9 = 25,
    GPIO_PIN_RB10 = 26,
    GPIO_PIN_RB11 = 27,
    GPIO_PIN_RB12 = 28,
    GPIO_PIN_RB13 = 29,
    GPIO_PIN_RB14 = 30,
    GPIO_PIN_RB15 = 31,
    GPIO_PIN_RC1 = 33,
    GPIO_PIN_RC2 = 34,
    GPIO_PIN_RC3 = 35,
    GPIO_PIN_RC4 = 36,
    GPIO_PIN_RC12 = 44,
    GPIO_PIN_RC13 = 45,
    GPIO_PIN_RC14 = 46,
    GPIO_PIN_RC15 = 47,
    GPIO_PIN_RD0 = 48,
    GPIO_PIN_RD1 = 49,
    GPIO_PIN_RD2 = 50,
    GPIO_PIN_RD3 = 51,
    GPIO_PIN_RD4 = 52,
    GPIO_PIN_RD5 = 53,
    GPIO_PIN_RD6 = 54,
    GPIO_PIN_RD7 = 55,
    GPIO_PIN_RD8 = 56,
    GPIO_PIN_RD9 = 57,
    GPIO_PIN_RD10 = 58,
    GPIO_PIN_RD11 = 59,
    GPIO_PIN_RD12 = 60,
    GPIO_PIN_RD13 = 61,
    GPIO_PIN_RD14 = 62,
    GPIO_PIN_RD15 = 63,
    GPIO_PIN_RE0 = 64,
    GPIO_PIN_RE1 = 65,
    GPIO_PIN_RE2 = 66,
    GPIO_PIN_RE3 = 67,
    GPIO_PIN_RE4 = 68,
    GPIO_PIN_RE5 = 69,
    GPIO_PIN_RE6 = 70,
    GPIO_PIN_RE7 = 71,
    GPIO_PIN_RE8 = 72,
    GPIO_PIN_RE9 = 73,
    GPIO_PIN_RF0 = 80,
    GPIO_PIN_RF1 = 81,
    GPIO_PIN_RF2 = 82,
    GPIO_PIN_RF3 = 83,
    GPIO_PIN_RF4 = 84,
    GPIO_PIN_RF5 = 85,
    GPIO_PIN_RF8 = 88,
    GPIO_PIN_RF12 = 92,
    GPIO_PIN_RF13 = 93,
    GPIO_PIN_RG0 = 96,
    GPIO_PIN_RG1 = 97,
    GPIO_PIN_RG2 = 98,
    GPIO_PIN_RG3 = 99,
    GPIO_PIN_RG6 = 102,
    GPIO_PIN_RG7 = 103,
    GPIO_PIN_RG8 = 104,
    GPIO_PIN_RG9 = 105,
    GPIO_PIN_RG12 = 108,
    GPIO_PIN_RG13 = 109,
    GPIO_PIN_RG14 = 110,
    GPIO_PIN_RG15 = 111,

    /* This element should not be used in any of the GPIO APIs.
       It will be used by other modules or application to denote that none of the GPIO Pin is used */
    GPIO_PIN_NONE = -1

} GPIO_PIN;

typedef enum
{
  CN0_PIN = 1 << 0,
  CN1_PIN = 1 << 1,
  CN2_PIN = 1 << 2,
  CN3_PIN = 1 << 3,
  CN4_PIN = 1 << 4,
  CN5_PIN = 1 << 5,
  CN6_PIN = 1 << 6,
  CN7_PIN = 1 << 7,
  CN8_PIN = 1 << 8,
  CN9_PIN = 1 << 9,
  CN10_PIN = 1 << 10,
  CN11_PIN = 1 << 11,
  CN12_PIN = 1 << 12,
  CN13_PIN = 1 << 13,
  CN14_PIN = 1 << 14,
  CN15_PIN = 1 << 15,
  CN16_PIN = 1 << 16,
  CN17_PIN = 1 << 17,
  CN18_PIN = 1 << 18,
  CN19_PIN = 1 << 19,
  CN20_PIN = 1 << 20,
  CN21_PIN = 1 << 21,
}CN_PIN;


void GPIO_Initialize(void);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on multiple pins of a port
// *****************************************************************************
// *****************************************************************************

uint32_t GPIO_PortRead(GPIO_PORT port);

void GPIO_PortWrite(GPIO_PORT port, uint32_t mask, uint32_t value);

uint32_t GPIO_PortLatchRead ( GPIO_PORT port );

void GPIO_PortSet(GPIO_PORT port, uint32_t mask);

void GPIO_PortClear(GPIO_PORT port, uint32_t mask);

void GPIO_PortToggle(GPIO_PORT port, uint32_t mask);

void GPIO_PortInputEnable(GPIO_PORT port, uint32_t mask);

void GPIO_PortOutputEnable(GPIO_PORT port, uint32_t mask);

// *****************************************************************************
// *****************************************************************************
// Section: GPIO Functions which operates on one pin at a time
// *****************************************************************************
// *****************************************************************************

static inline void GPIO_PinWrite(GPIO_PIN pin, bool value)
{
    GPIO_PortWrite((GPIO_PORT)(pin>>4), (uint32_t)(0x1) << (pin & 0xF), (uint32_t)(value) << (pin & 0xF));
}

static inline bool GPIO_PinRead(GPIO_PIN pin)
{
    return (bool)(((GPIO_PortRead((GPIO_PORT)(pin>>4))) >> (pin & 0xF)) & 0x1);
}

static inline bool GPIO_PinLatchRead(GPIO_PIN pin)
{
    return (bool)((GPIO_PortLatchRead((GPIO_PORT)(pin>>4)) >> (pin & 0xF)) & 0x1);
}

static inline void GPIO_PinToggle(GPIO_PIN pin)
{
    GPIO_PortToggle((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinSet(GPIO_PIN pin)
{
    GPIO_PortSet((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinClear(GPIO_PIN pin)
{
    GPIO_PortClear((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinInputEnable(GPIO_PIN pin)
{
    GPIO_PortInputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}

static inline void GPIO_PinOutputEnable(GPIO_PIN pin)
{
    GPIO_PortOutputEnable((GPIO_PORT)(pin>>4), 0x1 << (pin & 0xF));
}


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END
#endif // PLIB_GPIO_H
