;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

    MODULE  ?cstartup

    ;; Forward declaration of sections.
    SECTION CSTACK:DATA:NOROOT(3) ;; 8 bytes alignment

    SECTION .intvec:CODE:NOROOT(2);; 4 bytes alignment

    EXTERN  SystemInit	
    EXTERN  __iar_program_start
    EXTERN  HardFault_Handler    
    PUBLIC  __vector_table

    DATA
__vector_table
    DCD     sfe(CSTACK)
    DCD     __iar_program_start

    DCD     NMI_Handler
    DCD     HardFault_Handler
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     0
    DCD     SVC_Handler
    DCD     0
    DCD     0
    DCD     PendSV_Handler
    DCD     SysTick_Handler

    ; External Interrupts
    DCD     BOD_IRQHandler              ;  0: Brownout low voltage detected interrupt                 
    DCD     WDT_IRQHandler              ;  1: Watch Dog Timer interrupt                              
    DCD     Default_Handler             ;  2: Reserved               
    DCD     USCI1_IRQHandler            ;  3: USCI1 interrupt               
    DCD     GPIO_IRQHandler             ;  4: External interrupt from GPA ~ GPD pins     
    DCD     EPWM_IRQHandler          	;  5: EPWM interrupt     
    DCD     BRAKE0_IRQHandler           ;  6: EPWM brake interrupt from PWM0 or PWM_BRAKE pin                                 
    DCD     BRAKE1_IRQHandler           ;  7: EPWM brake interrupt from PWM1                                 
    DCD     BPWM0_IRQHandler            ;  8: BPWM0 interrupt                                      
    DCD     BPWM1_IRQHandler            ;  9: BPWM1 interrupt                                      
    DCD     Default_Handler         	; 10: Reserved                                      
    DCD     USCI2_IRQHandler            ; 11: USCI2 interrupt                                      
    DCD     Default_Handler             ; 12: Reserved                                       
    DCD     Default_Handler             ; 13: Reserved                                        
    DCD     Default_Handler             ; 14: Reserved                                         
    DCD     ECAP_IRQHandler             ; 15: Enhanced Input Capture interrupt                                         
    DCD     CCAP_IRQHandler             ; 16: Continues Input Capture interrupt                                         
    DCD     Default_Handler             ; 17: Reserved                                         
    DCD     Default_Handler             ; 18: Reserved                                         
    DCD     GDMA0_IRQHandler            ; 19: GDMA_CH0 interrupt                                         
    DCD     GDMA1_IRQHandler            ; 20: GDMA_CH1 interrupt                                        
    DCD     HIRCTRIM_IRQHandler         ; 21: HIRC TRIM interrupt                                         
    DCD     TMR0_IRQHandler             ; 22: Timer 0 interrupt 
    DCD     TMR1_IRQHandler             ; 23: Timer 1 interrupt                                
    DCD     TMR2_IRQHandler             ; 24: Timer 2 interrupt                                         
    DCD     Default_Handler             ; 25: Reserved          
    DCD     ACMP_IRQHandler             ; 26: Analog Comparator 0 or Comparator 1 interrupt  
    DCD     Default_Handler             ; 27: Reserved
    DCD     PWRWU_IRQHandler            ; 28: Chip wake-up from Power-down state interrupt
    DCD     ADC0_IRQHandler             ; 29: ADC0 interrupt                                          
    DCD     ADC1_IRQHandler             ; 30: ADC1 interrupt
    DCD     Default_Handler             ; 31: Reserved                               

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
    THUMB
    PUBWEAK Reset_Handler   
    SECTION .text:CODE:REORDER:NOROOT(2)       ; 4 bytes alignment
Reset_Handler
        LDR     R0, =0x50000100
        ; Unlock Register                
        LDR     R1, =0x59
        STR     R1, [R0]
        LDR     R1, =0x16
        STR     R1, [R0]
        LDR     R1, =0x88
        STR     R1, [R0]
        
        ; Init POR
        LDR     R2, =0x50000024
        LDR     R1, =0x00005AA5
        STR     R1, [R2]
        
        ; Lock register
        MOVS    R1, #0
        STR     R1, [R0]                

        LDR      R0, =SystemInit
        BLX      R0
        LDR      R0, =__iar_program_start
        BX       R0

    PUBWEAK NMI_Handler       
    PUBWEAK SVC_Handler       
    PUBWEAK PendSV_Handler    
    PUBWEAK SysTick_Handler   
    PUBWEAK BOD_IRQHandler   
    PUBWEAK WDT_IRQHandler   
    PUBWEAK USCI1_IRQHandler 
    PUBWEAK GPIO_IRQHandler  
    PUBWEAK EPWM_IRQHandler
    PUBWEAK BRAKE0_IRQHandler 
    PUBWEAK BRAKE1_IRQHandler 
    PUBWEAK BPWM0_IRQHandler 
    PUBWEAK BPWM1_IRQHandler 
    PUBWEAK USCI2_IRQHandler
    PUBWEAK ECAP_IRQHandler
    PUBWEAK CCAP_IRQHandler
    PUBWEAK GDMA0_IRQHandler 
    PUBWEAK GDMA1_IRQHandler 
    PUBWEAK HIRCTRIM_IRQHandler 
    PUBWEAK TMR0_IRQHandler 
    PUBWEAK TMR1_IRQHandler
    PUBWEAK TMR2_IRQHandler
    PUBWEAK ACMP_IRQHandler 
    PUBWEAK PWRWU_IRQHandler 
    PUBWEAK ADC0_IRQHandler
    PUBWEAK ADC1_IRQHandler  
    SECTION .text:CODE:REORDER:NOROOT(2)
NMI_Handler       
SVC_Handler       
PendSV_Handler    
SysTick_Handler   
BOD_IRQHandler   
WDT_IRQHandler   
USCI1_IRQHandler 
GPIO_IRQHandler  
EPWM_IRQHandler 
BRAKE0_IRQHandler  
BRAKE1_IRQHandler  
BPWM0_IRQHandler  
BPWM1_IRQHandler  
USCI2_IRQHandler
ECAP_IRQHandler 
CCAP_IRQHandler
GDMA0_IRQHandler 
GDMA1_IRQHandler  
HIRCTRIM_IRQHandler  
TMR0_IRQHandler  
TMR1_IRQHandler  
TMR2_IRQHandler
ACMP_IRQHandler  
PWRWU_IRQHandler  
ADC0_IRQHandler  
ADC1_IRQHandler 
Default_Handler          
    B Default_Handler         

    
    END

