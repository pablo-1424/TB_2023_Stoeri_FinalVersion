Important files :
        Folder core/inc
                main.h : Main file, goToSleep function, timFunc function, and defines concerning the accelerometer and the water detection
                bma400func.h : Functions for the accelerometer
        
        Folder core/inc/it_sdk
                config.h : Configuration of the SDK
                configLoRaWan.h : LoRa configuration with SDK
                
        Folder core/src
                main.c : Main file, goToSleep function, and timFunc function
                project_main.c : LoRa send and Init
                bma400func.c : Functions for the accelerometer
                
        Folder stm32-it-sdk/src/stm32l_sdk
                gpio_wrapper.c : EXTI Pin12 callback
                
        Folder stm32-it-sdk/src/stm32l_sdk/timer
                timer.c : TIM6 callback
                
        
        
        