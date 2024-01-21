Work done by Enora Latour, Raphaël Ruelle and Saïd Ider.

# ESP32 meteo measurement with BME280 captors and ThingsBoard project

-  - [Introduction](#introduction)
   - [Prerequisites](#prerequisites)
   - [1) Wiring](#1-wiring)
   - [2) Install required libraries](#2-install-required-libraries)
   - [3) Modify environment variables](#3-modify-environment-variables)
   - [4) Create connection from ESP32 to the ThingsBoard](#4-create-connection-from-esp32-to-the-thingsboard)
   - [5) Upload and deploy](#5-upload-and-deploy)
   - [6) Display and processing of data](#6-display-and-processing-of-data)
   - [Demonstration](#demonstration)

## Introduction

The goal of this project is to build a meteo station with a BME280 captor connected to an ESP32. The ESP32 then sends the values to a ThingsBoard who's goal is to collect, process and display the values of multiple ESP32.

## Prerequisites

To make this project work, you'll need :

- ESP32 board

- BME280 captor

- ThingsBoard

- WiFi connection to internet (or local if the thingboard is self hosted) that the ESP32 can reach

- Wiring (cables, breadboard, ...)

- Arduino IDE (or other equivalent) to install libraries, adapt and upload the code to the ESP32

To make multiple meteo captors, you'll need multiple ESP32s and BME280 captors. All will be connected to your unique ThingsBoard.

## 1\) Wiring

To connect the BME280 captor to the ESP32, you'll need to wire each of the captor's pins to the corresponding ESP32's as follows :

- SCL to pin 18

- SDO to pin 19

- SDA to pin 23

- CSB to pin 5

- VCC to 3v3 pin

- GND to GND pin

## 2\) Install required libraries

The required dependencies are :

- WiFi.h

- ThingsBoard.h

- PubSubClient.h

- ESPping.h

- SPI.h

- Adafruit_BME280.h

- Adafruit_Sensor.h

So in Arduino IDE, go to **Sketch** then **include library**, **Manage libraries** and install all the following :

- PubSubClient

- ESPping

- Adafruit BME280 (this library will install all the necessary dependencies)

## 3\) Modify environment variables

On the ENVIRONMENT VARIABLES section from the `meteo_measurement_esp32_to_thingsboard.ino` code, change the WiFi and ThingsBoard parameters as needed.

An exemple of connection to thingsboard.cloud ThingsBoard is given on the next section to complete the TOKEN and DEVICE_ID fields.

## 4\) Create connection from ESP32 to the ThingsBoard

Here is how to connect the ThingsBoard to collect the data from the ESP32 :

1) Connect and login to https://thingsboard.cloud/login

2) Go to **Entites** and select **devices**

3) Click on the "**+**" (add device) and select **Add New Device**

4) Enter the name of your device, then click on **Add** and then click on **close**

5) To get the credentials, click on **device** then click either on : **Copy device ID** to get the DEVICE_ID value, or **Copy access token** to get the TOKEN value

6) Modify the DEVICE_ID and TOKEN values in your ENVIRONMENT VARIABLES from the `meteo_measurement_esp32_to_thingsboard.ino` code accordingly.

You can verify if the ThingsBoard get the values by clicking on the device and then **Latest telemetry**. If values change or are displayed correctly, your connection is good !

## 5\) Upload and deploy

Once you have finished correctly the previous steps, you can upload the code to your ESP32 and find a way to supply energy to the plateform to make it autonomous. 

If you need multiple meteo captors, just follow the same steps from the beginning with the others ESP32s and BME280 sensors. 

You can have as much captors as needed in the same ThingsBoard who will collect, process and display the values of each meteo captor.

## 6\) Display and processing of data

To display the data from all the meteo captors on the ThingsBoard do this steps :

1) Connect and login to https://thingsboard.cloud/login

2) Go to **Dashboards**

3) Click on "**+**" (add dashboard), then **Create new dashboard** (or go to one already created)

4) Fill with the name and description you want to use then **Add**

5) From here you can **add new widgets** by clicking on the button

6) Select a widget of your liking that can support your data (for example data then value card)

7) Click on **device** and select the device you want to display the values. Then on **data key** remove the current parameter by clicking on the **cross**. Click again on **data key** and select the data type you want to display and click on **Add**.

8) Don't forget to **save** you dashboard

If you want process (min, max, average...) your data from a device do this steps :

1) Do the previous steps until step 6.

2) Click on **device** and select the device you want to display the values. 

3) Then on **data key** remove the current parameter by clicking on the **cross**. Click again on **data key** and select the data type you want to display. Select the processing you want to use for your data by selecting it from the aggregation menu. You can also enable delta calculation from a time period and results with the options below.

4) Click on **Save**

5) Finally click on **Add**.

## Demonstration

We deployed our work and here are the results.

Wiring :

<img src="https://cdn.discordapp.com/attachments/1171788299967398019/1197695171253510144/IMG_0913.jpg?ex=65bc338c&is=65a9be8c&hm=ab878926ad36fe1cb1b6b8d144367dd71c72a64319e6f81a7de81ed2b7197ac2&" title="" alt="" width="396">

<img title="" src="https://cdn.discordapp.com/attachments/1171788299967398019/1197695171828138055/IMG_0914.jpg?ex=65bc338d&is=65a9be8d&hm=69a35e7ddf7cfd4333fa79016ab3f9642dcbf7035ee6e2e9ca2545b54fe228f5&" alt="" width="391">

All the devices and ThingsBoard working simultaneously :

<img src="file:///C:/Users/diasr/Desktop/OSEF%20WOULA/Snapchat-1489786848.jpg" title="" alt="Snapchat-1489786848.jpg" width="625">

And here is an example of dashboard with results at two different moments :

<img title="" src="https://cdn.discordapp.com/attachments/1171788299967398019/1197694200888696982/image.png?ex=65bc32a5&is=65a9bda5&hm=a4945115d913539f5923cccad927b6fe8ea14dcf7bf2f08b92a4f1f615d4908a&" alt="" width="619">

<img src="https://cdn.discordapp.com/attachments/1171788299967398019/1197694321722404894/image.png?ex=65bc32c2&is=65a9bdc2&hm=c90aa0a32a45b9aeb413c0a74d386ac75f04deed0470c89272c52eeca7e97f0a&" title="" alt="" width="621">
