/*******************************************************************************
 System Tasks File

  File Name:
    tasks.c

  Summary:
    This file contains source code necessary to maintain system's polled tasks.

  Description:
    This file contains source code necessary to maintain system's polled tasks.
    It implements the "SYS_Tasks" function that calls the individual "Tasks"
    functions for all polled MPLAB Harmony modules in the system.

  Remarks:
    This file requires access to the systemObjects global data structure that
    contains the object handles to all MPLAB Harmony module objects executing
    polled in the system.  These handles are passed into the individual module
    "Tasks" functions to identify the instance of the module to maintain.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
 * Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "configuration.h"
#include "definitions.h"
#include "queue.h"
#include "task.h"
#include "freertos.h"
#include "semphr.h"
#include "math.h"

#define SLAVE_ADDR          0x0A
#define NUM_BYTES           0x01
#define Aumenta__temperatura 01
#define Diminue_temperatura 02
#define Sem_comunicacao_arduino 03
#define Sem_comunicacao_computador 04
#define esperando_comunicacao 05
#define reseta_dados 06
#define mantem_temperatura 07
// *****************************************************************************
// *****************************************************************************
// Section: RTOS "Tasks" Routine
// *****************************************************************************
// *****************************************************************************
/* Handle for the TEMISTOR_Tasks. */
int status = esperando_comunicacao;
TaskHandle_t xTEMISTOR_Tasks;
xQueueHandle controle_entrada, Saida_dados, controle_aquecedor;
xSemaphoreHandle xMutex, xmutex2, xMutextemp;
portBASE_TYPE xStatus;
/* Handle for the ERRO_Tasks. */
TaskHandle_t xERRO_Tasks;

void _ERRO_Tasks(void *pvParameters) {
    /**************************************************************************/
    /* OS PINOS A SEREM CONECTADOS PARA EXIBIR ERRO NO DISPLAY DE 7 SEGMENTOS*/
    /*A-E0
      B-E1
      C-E2
      D-E3
      E-E4
      F-E5
      G-E6
     COM1-D0
     COM2-D1
     COM3-D2
     COM4-D3*/
    const int temp = 4;
    while (1) {
        ERRO_Tasks();
        //goto sai;
        /*letra E do display de 7 segmentos*/
        SEG1_Clear();
        SEGa_Clear();
        SEGf_Clear();
        SEGe_Clear();
        SEGg_Clear();
        SEGd_Clear();
        vTaskDelay(temp / portTICK_PERIOD_MS);
        SEG1_Set();
        /*letra R do display de 7 segmentos*/
        SEG2_Clear();
        SEGb_Clear();
        SEGc_Clear();
        SEGd_Set();
        vTaskDelay(temp / portTICK_PERIOD_MS);
        SEG2_Set();
        /*letra R do display de 7 segmentos*/
        SEG3_Clear();
        vTaskDelay(temp / portTICK_PERIOD_MS);
        SEG3_Set();
        /*letra O do display de 7 segmentos*/
        SEG4_Clear();
        SEGd_Clear();
        SEGg_Set();
        vTaskDelay(temp / portTICK_PERIOD_MS);
        SEG4_Set();
        /*limpa todas as saidas para o display*/
        vTaskDelay(temp / portTICK_PERIOD_MS);
        SEGa_Set();
        SEGb_Set();
        SEGc_Set();
        SEGd_Set();
        SEGe_Set();
        SEGf_Set();
        SEGg_Set();

        if (status == Aumenta__temperatura || status == Diminue_temperatura || status == reseta_dados || status == mantem_temperatura) {
            vTaskSuspend(xERRO_Tasks);
        }
        //sai:
        vTaskDelay(temp / portTICK_PERIOD_MS);
    }
}

void _TEMISTOR_Tasks(void *pvParameters) {
    /*CONCTAR O TERMISTOR, OU OUTRO SENSOR ANALÓGICO, NO PINO:
     ADC1-PORTB B1*/
    // Parâmetros do termistor
    double t;
    double rt;
    double v;
    const double beta = 3600.0;
    const double r0 = 20000.0;
    const double t0 = 273.0;
    const double rx = r0 * exp(-beta / t0);

    const double vcc = 5.0;
    const double R = 20000.0;
    uint8_t dados = 30;
    uint32_t termo = 0;
    ADC_Enable();
    ADC_Initialize();
    while (1) {
        TEMISTOR_Tasks();
        ADC_SamplingStart();
        ADC_ConversionStart();
        vTaskDelay(100 / portTICK_PERIOD_MS);
        while (!ADC_ResultIsReady()) {
            vTaskDelay(1 / portTICK_PERIOD_MS);
        }
        termo = ADC_ResultGet(0); //ler dado analogico
        v = (vcc * termo) / (1024.0);
        rt = (vcc * R) / v - R;
        // Calcula a temperatura
        t = beta / log(rt / rx);
        dados = (uint8_t) t;


        xSemaphoreTake(xMutex, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
        xQueueSend(Saida_dados, &dados, 0);
        xSemaphoreGive(xMutex); // Libera o semaforo
        xSemaphoreTake(xMutextemp, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
        xQueueSend(controle_aquecedor, &dados, 0);
        xSemaphoreGive(xMutextemp);
        vTaskDelay(40 / portTICK_PERIOD_MS);
    }
}
/* Handle for the LEDS_Tasks. */
TaskHandle_t xLEDS_Tasks;

void _LEDS_Tasks(void *pvParameters) {
    while (1) {

        LEDS_Tasks();
        if (status == Sem_comunicacao_arduino || status == esperando_comunicacao || status == Sem_comunicacao_computador) {
            L1_Set();
            L2_Set();
            L3_Set();
            L4_Set();
            L5_Set();
            L6_Set();
            L7_Set();
            L8_Set();
            vTaskDelay(500 / portTICK_PERIOD_MS);
            L1_Clear();
            L2_Clear();
            L3_Clear();
            L4_Clear();
            L5_Clear();
            L6_Clear();
            L7_Clear();
            L8_Clear();
            vTaskDelay(500 / portTICK_PERIOD_MS);
        } else {

            L1_Toggle();
            L8_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L1_Toggle();
            L8_Toggle();
            L2_Toggle();
            L7_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L2_Toggle();
            L7_Toggle();
            L3_Toggle();
            L6_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L3_Toggle();
            L6_Toggle();
            L4_Toggle();
            L5_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L3_Toggle();
            L6_Toggle();
            L4_Toggle();
            L5_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L2_Toggle();
            L7_Toggle();
            L3_Toggle();
            L6_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L1_Toggle();
            L8_Toggle();
            L2_Toggle();
            L7_Toggle();
            vTaskDelay(120 / portTICK_PERIOD_MS);
            L1_Toggle();
            L8_Toggle();
        }

    }
}
/* Handle for the DADOS_Tasks. */
TaskHandle_t xDADOS_Tasks;

void _DADOS_Tasks(void *pvParameters) {
    /* OS PINOS PARA CONECTAR O I2C SAO */
    /* SDA-PORT A15
       SCL-PORT A14*/
    I2C1_Initialize();
    uint8_t dados = 30;
    bool conexao=true;
    while (1) {
        DADOS_Tasks();
        xSemaphoreTake(xMutex, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
        xStatus = xQueueReceive(Saida_dados, &dados, 0);
        xSemaphoreGive(xMutex); // Libera o semaforo
        if (xStatus == pdPASS) {
            if (!I2C1_Write(SLAVE_ADDR, &dados, NUM_BYTES)) {

            }
            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
        conexao=I2C1_Read(SLAVE_ADDR, &dados, NUM_BYTES);
        vTaskDelay(10 / portTICK_PERIOD_MS);
        if(!conexao){
            status=Sem_comunicacao_arduino;
        }
        xSemaphoreTake(xmutex2, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
        xQueueSend(controle_entrada, &dados, 0);
        xSemaphoreGive(xmutex2); // Libera o semaforo
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

TaskHandle_t xCONTROLAAQUECEDOR_Tasks;

void _CONTROLAAQUECEDOR_Tasks(void *pvParameters) {
    /*O PINO QUE CONTROLA O RELÉ QUE ACIONA O AQUECEDOR É
     "PORTD D4*/
    uint8_t dados, temperatura = 25, temp = 25;
    while (1) {
        CONTROLAAQUECEDOR_Tasks();
        xSemaphoreTake(xmutex2, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
        xStatus = xQueueReceive(controle_entrada, &dados, 0);
        xSemaphoreGive(xmutex2);
        if (xStatus == pdPASS) {
            status = dados;
        } else {
            status = Sem_comunicacao_arduino;
            temperatura = 25;
        }

        if (status == Sem_comunicacao_arduino || status == esperando_comunicacao || status == Sem_comunicacao_computador) {
            aquecedor_Clear();
            vTaskResume(xERRO_Tasks);

        } else {
            xSemaphoreTake(xMutextemp, portMAX_DELAY); /*semaforo para impedir que duas tesks acessar a mesma fila ao mesmo tempo*/
            xStatus = xQueueReceive(controle_aquecedor, &dados, 0);
            xSemaphoreGive(xMutextemp);
            if (xStatus != pdPASS) {

            } else {
                temperatura = dados;
            }
            if (status == reseta_dados) {
                temperatura = 25;
                temp = 25;
                status = mantem_temperatura;
            } else if (status == Aumenta__temperatura) {
                temp++;
                status = mantem_temperatura;
            } else if (status == Diminue_temperatura) {
                temp--;
                status = mantem_temperatura;
            }
            if (temperatura <= temp) {
                aquecedor_Set();
            } else {
                aquecedor_Clear();
            }
        }
        vTaskDelay(120 / portTICK_PERIOD_MS);
    }
}





// *****************************************************************************
// *****************************************************************************
// Section: System "Tasks" Routine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Remarks:
    See prototype in system/common/sys_module.h.
 */
void SYS_Tasks(void) {
    xMutex = xSemaphoreCreateMutex();
    xmutex2 = xSemaphoreCreateMutex();
    xMutextemp = xSemaphoreCreateMutex();
    controle_entrada = xQueueCreate(10, sizeof ( uint8_t));
    Saida_dados = xQueueCreate(10, sizeof ( uint8_t));
    controle_aquecedor = xQueueCreate(10, sizeof ( uint8_t));

    /* Create OS Thread for TEMISTOR_Tasks. */
    xTaskCreate((TaskFunction_t) _TEMISTOR_Tasks,
            "TEMISTOR_Tasks",
            1024,
            NULL,
            1,
            &xTEMISTOR_Tasks);

    /* Create OS Thread for LEDS_Tasks. */
    xTaskCreate((TaskFunction_t) _LEDS_Tasks,
            "LEDS_Tasks",
            1024,
            NULL,
            1,
            &xLEDS_Tasks);

    /* Create OS Thread for DADOS_Tasks. */
    xTaskCreate((TaskFunction_t) _DADOS_Tasks,
            "DADOS_Tasks",
            1024,
            NULL,
            1,
            &xDADOS_Tasks);

    /* Create OS Thread for CONTROLAAQUECEDOR_Tasks. */
    xTaskCreate((TaskFunction_t) _CONTROLAAQUECEDOR_Tasks,
            "CONTROLAAQUECEDOR_Tasks",
            1024,
            NULL,
            1,
            &xCONTROLAAQUECEDOR_Tasks);

    /* Create OS Thread for ERRO_Tasks. */
    xTaskCreate((TaskFunction_t) _ERRO_Tasks,
            "ERRO_Tasks",
            1024,
            NULL,
            1,
            &xERRO_Tasks);

    vTaskSuspend(xERRO_Tasks);


    /*  SEGb_Set();
      SEGc_Set();
      SEGd_Set();
      SEGe_Set();
      SEGf_Set();
      SEGg_Set();*/

    /* Start RTOS Scheduler. */

    /**********************************************************************
     * Create all Threads for APP Tasks before starting FreeRTOS Scheduler *
     ***********************************************************************/
    vTaskStartScheduler(); /* This function never returns. */

}

/*******************************************************************************
 End of File
 */

