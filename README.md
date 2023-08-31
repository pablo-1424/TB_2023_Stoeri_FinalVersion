# TB_2023_Stoeri_Public

## Information about the project

The goal of the project is to implement a system wich can detect if water is flowing and calculating for how long through a pipe. The amount of time of the water flow is then transmitted to TTN using the LoRa protocol.

A python script is able to store the received amount of time in a mySQL database from where two different graphs can be done.

## Used material

Chip : Murata CMWX1ZZABZ-091

Sensor : Bosch BMA400

DevKit with the Murata chip : B-L072Z-LRWAN1

DevKit with the sensor : SparkFun Triple Axis Accelerometer Breakout - BMA400

## Used software

IT-SDK from disk91 : https://github.com/disk91/stm32-it-sdk

## Content of the repository

### Folder 01_Report :

Contains the report of the thesis

### Folder 02_Code :

#### Folder EmbeddedSystem :

* Folder TB_noLoRa : Contains a functionnal code without the LoRa transmission
    
* Folder TB_Stoeri_FinalCode : Contains the final code including the LoRa transmission
  
#### Folder PythonScript :
  
* Folder SerialToGraph : Contains a code to make graphs with UART data
    
* Folder toFromSQL : Contains all the steps from TTN to dashboards threw a mySQL database

### Folder 03_Electronics :

  Contains the schematics of the PCB that has been made and wich is now used

### Folder 04_Mecanics :

  Contains all the CAD files of hardware used for this specific thesis
