# Summer_Training_2024
# Certification 
![C programming, data structure and algorithms from diploma](https://github.com/user-attachments/assets/4d66b4db-e894-46ca-80fd-f44390e22c55)
# Learning Outcomes 
During this diploma I studied these topics:
  1) Advanced C programing, data structure and algorithms. 
     - These certificates were obtained from Hacker Rank: (https://www.hackerrank.com/certificates/a6e63e1eb7bc)
  2) Microcontroller interfacing: many device drivers have been written for PIC18F family like: GPIO, interrupt handling, ADC, EEPROM, UART, I2C and SPI.
       * These projects have been implemented during this part:
         - Traffic Control  : In this project multiple modules have been used like: LED, and Seven segment .
         - Joystick wheelchair  : In this project multiple modules have been used like: LCD, Bush button, L298 and external Interrupt .
         - EUSART using receiver and transmitter : In this project two modules have been used like: EUSART, and LED .
         - Autonomous driving of a 2 wheel car : In this project multiple modules have been used like: LCD, Buzzer, L298, and ultrasonic sensor.
         - Security system password check : In this project multiple modules have been used like: LCD, Buzzer, LED, and Keypad .
         - Simple calculator : In this project two modules have been used like: LCD, and two types of Keypad .
         - Smart Home System: Multiple microcontrollers communicate over the I2C protocol. In this project multiple modules have been used like: 24C02C, TC74, L298, and DS1307.
    # PIC18F4620-Driver
    ## Driver for PIC18F4620 with many projects. 
    ## For more information : [https://rightful-hawk-670.notion.site/microcontroller-38c62297c2804bcc8aa5715c66834b3b?pvs=4](url)
    ## Layers
      ### 1) __MCAL layer__
           a) Device config
           b) MCAL_STD_Types ( standard types )
           c) STD_Libraries  ( standard libraries )
           d) Compiler
           e) GPIO
             * hal_GPIO
           f) Interrupt
             * MCAL_External_Interrupt
             * MCAL_Internal_Interrupt
             * MCAL_Interrupt_Manager
             * MCAL_Interrupt_Config ( in header file )
           g) Timer
             * HAL_Timer0
         
    -------------------------------------------------------------------------------------------------------------------------
      ### 2) __ECU layer__
           a) ECU_Layer_Initialization : is used to initialize ECU modules instead of initialize it in application layer (readability).
           b) Button
             * Button
             * Button_config ( in header file )
           c) CHAR_LCD
             * hal_GPIO
             * hal_GPIO_config ( in header file )
           d) DC_Motor
             * DC_Motor
             * DC_Motor_Config ( in header file )
           e) Keypad
             * Keypad
             * Keypad_Config ( in header file )
           f) Seven Segment
             * Seven_Segment
             * Seven_Segment_Config ( in header file )
           g) Relay
             * Relay
             * Relay_Config
           h) LED
             * LED
             * LED_config
           i) Buzzer
             * Buzzer
             * Buzzer_config
    ------------------------------------------------------------------------------------------------------------------------
     ### 3) __Application Layer__
           a) applicaion ( in header file )
    ------------------------------------------------------------------------------------------------------------------------
      ### 4) Project 
           a) Traffic Control ( is an aaplication.c ) 
           b) Password security system ( is an aaplication.c )
           c) Joystick wheelchair  ( is an aaplication.c )
           d) Autonomus Car  ( is an aaplication.c )
           e) Interface EUSART Transmit and receive  ( is an aaplication.c )
           f) Calculator  ( is an aaplication.c )
           g) Smart home  ( is an aaplication.c ) 
         
    ------------------------------------------------------------------------------------------------------------------------
