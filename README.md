# OPIN AC Control

[![License](https://img.shields.io/badge/license-Apache%202-blue.svg)](https://www.apache.org/licenses/LICENSE-2.0)

![AC Control](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/ACControl.png)

## Table of Contents
For User
- [Introduction](#introduction)
- [Features](#features)
- [Components and Interface](#components-and-interface)
- [User Guide](#user-guide)

For Developer
- [Installation](#installation)
- [MQTT Topics](#mqtt-topics)
- [Limitations](#limitations)
- [Future Development](#future-development)

Additional Information
- [OPIN Smart Home Devices](#opin-smart-home-devices)
- [Further Information](#further-information)

 ---
 ---

# For User
## Introduction
The OPIN AC Control is an innovative solution designed to enhance the comfort and convenience of managing air conditioning systems in homes and offices. Integrated with the [OPIN Gateway](https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public), this device allows users to control their AC units remotely through the OPIN mobile app.

With the OPIN AC Control, users can easily turn their air conditioning units on or off, adjust temperature settings, manage swing and fan settings, and benefit from the auto-off feature for energy savings—all from anywhere, providing flexibility and control over their indoor environment. The device is compatible with various AC models, as it forwards received IR data to and from the gateway, ensuring up-to-date control across all devices.

The OPIN AC Control features real-time monitoring of room temperature and humidity, enabling users to maintain a comfortable atmosphere in their spaces. Additionally, notifications regarding system status ensure that users are always informed of their AC's performance and settings.

For developers, the OPIN AC Control utilizes the MQTT protocol for seamless communication, enabling easy integration with other smart devices within the OPIN ecosystem. With its user-friendly interface, reliable performance, energy-saving features, and advanced functionalities, the OPIN AC Control is the perfect solution for modern living.

## Features
The OPIN AC Control offers a range of features to make managing air conditioners more convenient and efficient:
1. **Remote Control via Mobile App**:  
   Control your air conditioner from anywhere using the OPIN mobile app. Adjust temperature, change fan speed, and control swing settings with ease.
2. **Real-Time Room Monitoring**:  
   Equipped with a BME280 sensor, the device provides real-time monitoring of room temperature and humidity, giving you insights to optimize your indoor comfort.
3. **Eco-Friendly Power Source**:  
   Powered by a rechargeable 18650 battery, the device is both eco-friendly and cost-effective. With up to 18 hours of battery life on a single charge, the device ensures continuous operation without the need for disposable batteries.
4. **Auto-Off Feature**:  
   The OPIN AC Control supports an auto-off function, automatically turning off the air conditioner after a specified period of inactivity, reducing energy consumption and saving costs.
5. **Sync with Original Remote**:  
   Capable of reading IR data from the original remote control, the OPIN AC Control can update settings in the mobile app, ensuring that all configurations are synced with the user's preferences.
6. **Battery and Charging Monitoring**:  
   The device features LED indicators for charging and full-charge status, ensuring you always know when it’s time to recharge.
7. **Seamless Integration**:  
    Utilizes the MQTT protocol for smooth communication with the OPIN ecosystem, allowing for easy integration with other smart devices.

## Components and Interface
The following components are used in the OPIN AC Control. The numbers correspond to the labels in the [cover image](#opin-ac-control):
1. [**ESP32 Devkit V1**](<https://olddocs.zerynth.com/r2.3.3/official/board.zerynth.doit_esp32/docs/index.html>)  
   The microcontroller responsible for managing the device's operations and communication via MQTT. It processes signals from the IR transmitter and receiver to control the AC unit.
2. **IR Transmitter**  
   This component sends infrared signals to the AC unit, allowing remote control of its functions, such as temperature settings, fan speed, and swing direction.
3. **IR Receiver**  
   The IR receiver captures signals from the original remote control, allowing the OPIN AC Control to send temperature settings, fan speed, and swing direction data to the app, ensuring that the information is synchronized and up to date.
4. **LED**  
   The device features an LED that indicates the Wi-Fi connection status, helping users verify whether the device is connected to the network.
5. **Button**  
   A button is provided for initiating the Wi-Fi configuration process, allowing users to connect the device to their network. This button can also be used to reset the Wi-Fi connection.
6. **J5019 Charging Module**  
   The J5019 charging module features a Micro USB input terminal, allowing direct connection to a phone charger for recharging lithium batteries. It supports charging and discharging protection for various lithium batteries, including 18650 and polymer batteries with a nominal voltage of 3.6V to 3.7V.
7. **BME280 Sensor**  
   This sensor measures temperature and humidity levels in the room, providing real-time data to users through the mobile app.
8. **18650 Battery Flat Top Holder**  
   A holder for the rechargeable 18650 battery flat top, ensuring safe and secure placement within the device.
9. **Charging Port**  
   This port allows users to recharge the built-in 18650 battery, ensuring continuous operation.
10. **On/Off Switch**  
    A switch that enables users to manually power the device on or off as needed.
11. **MAX17048**  
    A battery fuel gauge that monitors the battery level and provides information about the remaining power, enhancing the user experience.
12. **Device Holder**  
   The device holder is designed to resemble the original remote control, providing a familiar and ergonomic grip. It securely houses all components of the OPIN AC Control, ensuring stability and a clean aesthetic while facilitating easy handling and operation.

## User Guide
This section provides step-by-step instructions on how to set up and use the OPIN kWh Meter effectively.
### 1. Initial Setup
   - **Insert the Battery**: Place a 18650 battery flat top into the battery holder. Ensure it is oriented correctly, following the polarity markings.
   - **Power On the Device**: Use the on/off switch to power on the OPIN AC Control.
   - **Position the OPIN AC Control**:  
     Mount or place the OPIN AC Control near the AC unit for optimal IR communication. The device should have a clear line of sight to the AC unit.
     ![Installation Position](<https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/installation.png>)  

### 2. LED Indicator
1. **Solid**: The device is connected to the network.
2. **Blinking continuously**: The device is not connected to a network or in the process of connecting.
3. **Off**: The device is either not powered or in WiFi configuration mode.

### 3. WiFi Configuration
#### Add WiFi Configuration
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready to connect to a network.  
   ![Button1](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the AC Control SSID `OPIN-ACControl-[device_id]`. Your device should automatically redirect you to the WiFi configuration interface (captive portal).
      > **Tips**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select something like `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - Once inside the configuration interface, select `Configure WiFi`. Choose your home WiFi SSID from the list, enter the password, and click `Save`. (Refer to the provided images for detailed guidance.)  
   ![Configure WiFi](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/configure_wifi.png)

3. **Confirm Connection**  
   - After the connection is established, the LED will turn solid, indicating that the AC Control is successfully connected to your WiFi network.

#### Reset WiFi Configuration
1. **Initiate Reset**  
   - Press and hold the button for at least two seconds. The LED will blink three times (indicating reset) followed by two blinks (entering WiFi configuration mode), signaling that the WiFi settings have been reset. This action will erase all previously saved WiFi configurations.  
   ![Button2](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/button2.gif)

2. **Reconnect to the Network**  
   - After resetting the WiFi, follow step [2 "Connect to the Network"](#add-WiFi-configuration) from the **Add WiFi Configuration** section to reconnect the AC Control to your WiFi.

#### Check IP Address of the AC Control
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready for network configuration.  
   ![Button1](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the AC Control SSID `OPIN-ACControl-[device_id]`, and your device will be redirected to the WiFi configuration interface (captive portal).  
      > **Tip**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - The IP address of the AC Control will be shown in the connected WiFi details box. (Refer to the provided image for reference.)  
   ![Check IP](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/check_ip.jpeg)

3. **Exit Configuration Mode**  
   - After checking the IP address, select `Exit` to complete the configuration process. The LED will turn solid, indicating that the AC Control is successfully connected to your WiFi network.

### 4. Connect AC Control to OPIN Mobile App
1. **Add New Device**  
   - Open the OPIN mobile app and click the `Add New Device` option.  
   - Select `AC Control` from the list of devices.  
   - Enter the `Device ID` and `IP Address` of the AC Control.   
   - Click `Submit`.  
   > **Note**: Ensure that the `Device ID` and `IP Address` are accurate to avoid issues during the device setup.

2. **Control the AC Unit**
   - **Use the Original IR Remote Control**: Point your original AC remote at the AC unit and OPIN AC Control to set and send the current temperature settings, fan speed, and swing direction. The device will sync this information with the mobile app.  
   ![Configure WiFi](https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/original_remote.png)  
   - **Adjust Settings via Mobile App**: Use the OPIN mobile app to control your AC settings remotely, including turning the unit on or off and adjusting temperature preferences.  
   - **Auto Off Feature**: The OPIN AC Control also supports an `Auto Off` feature, which automatically turns off the AC unit when no person is detected in the room, helping save energy. You can enable and manage this feature through the OPIN mobile app. For more details, refer to the [Auto Off feature documentation](https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public#auto-off-feature).

4. **Monitoring Room Conditions**
   - **View Real-Time Data**: The OPIN AC Control provides real-time monitoring of room temperature and humidity via the app, allowing users to stay informed about their indoor environment.

5. **Charging Instructions**
   - **Connect the Charging Module**:    
     Use a Micro USB cable to connect the J5019 charging module to a power source (like a phone charger) to charge the 18650 lithium battery. While charging, the LED indicator will show **red**.  
     ![Charging LED Indicator](<https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/charging.jpeg>)  
   - **Charging Duration**: Charging typically takes 4 hours. Check the battery indicator to monitor the charging status.  
   - **Fully Charged Indicator**:  
     Once the battery is fully charged, the LED indicator will turn **green**.  
     ![Fully Charged LED Indicator](<https://github.com/OPIN-Smart-Home/ACControl/blob/main/asset/charged.jpeg>)  
   - **Battery Life**: The 18650 battery usually lasts for about 18 hours of continuous operation. Ensure to recharge it regularly to maintain functionality.

### 5. Troubleshooting
1. **Device Not Connecting to Wi-Fi**
   - **Check Wi-Fi Credentials**: Ensure that the correct Wi-Fi credentials (SSID and password) are entered during the setup.
   - **Proximity to Router**: Make sure the kWh Meter is within the range of your Wi-Fi router. Try moving it closer to the router for better signal strength.
   - **Reboot the Device**: Restart the OPIN AC Control by toggling the on/off switch.

2. **App Not Displaying Data**
   - **Check Device ID and IP Address**: Ensure that the correct Device ID and IP address are entered in the app. Incorrect entries can prevent data from being displayed.

---
---

# For Developer
This section provides guidelines for developers looking to contribute to the OPIN Smart Home system. It's recommended to pay attention on [For User](#for-user) section.
## Installation
### Prerequisites
Before you begin, ensure you have the following installed on your development environment:
- **Arduino IDE** for uploading the firmware to the ESP32.
- **ESP32 Board Package** for Arduino IDE. For Arduino IDE, you can install it by going to **File > Preferences > Additional Board Manager URLs** and adding `https://dl.espressif.com/dl/package_esp32_index.json`. Then, navigate to **Tools > Board > Board Manager** and search for "ESP32".
- **Required Libraries**:
  - **WiFi**: For WiFi connectivity.
  - **Wire**: Provides communication over I2C between the microcontroller and sensors.
  - [**IRremoteESP8266** by David Conran, et al.](<https://github.com/crankyoldgit/IRremoteESP8266>) version `2.8.6`
    - **IRac**: For controlling and interacting with the air conditioning system via infrared signals.
    - **IRsend**: Sends IR signals to the AC unit for control.
    - **IRrecv**: Receives IR signals from the original AC remote.
  - [**PicoMQTT** by Michał Leśniewski](<https://github.com/mlesniew/PicoMQTT>) version `0.3.8` : To enable the ESP32 to function as an MQTT broker/server.
  - [**WiFiManager** by tzapu](<https://github.com/tzapu/WiFiManager>) version `2.0.17`: For handling WiFi connections and configurations.
  - [**Adafruit BME280** by Adafruit](<https://github.com/adafruit/Adafruit_BME280_Library>) version `2.2.2`: For monitoring room temperature and humidity.
  - [**Adafruit MAX1704X** by Adafruit](<https://github.com/adafruit/Adafruit_MAX1704X>) version `1.0.3`: For monitoring battery status.

### Clone the Repository
To get started with the project, clone the repository to your local machine:
```bash
git clone https://github.com/OPIN-Smart-Home/ACControl.git
```

## MQTT Topics
The OPIN AC Control communicates with the OPIN Gateway using the following MQTT topics:
- **Remote to User (r2u)**:  
  `opin/ACControl_[device_id]/r2u`  
  This topic is used to send IR data captured from the original AC remote control back to the user. It ensures that the AC settings, such as temperature, fan speed, and swing direction, are up-to-date in the OPIN mobile app.
- **Device to User (d2u)**:  
  `opin/ACControl_[device_id]/d2u`  
  The topic for sending device status, such as the current room temperature, humidity, and battery level, to the user via the OPIN mobile app.
- **User to Device (u2d)**:  
  `opin/ACControl_[device_id]/u2d`  
  This topic is used for sending control commands from the user to the OPIN AC Control, allowing users to adjust the AC settings like turning it on/off, setting the temperature, or adjusting the fan speed and swing direction.
- **Device SSID**:  
  `OPIN-ACControl-[device_id]`  
  This SSID is used when connecting the OPIN AC Control to Wi-Fi during the initial configuration process.
> **Note**: Each AC control device must have a unique `device_id`. This prevents conflicts when multiple devices are connected within the OPIN ecosystem.

## Limitations
While the OPIN AC Control offers a range of convenient features for controlling air conditioners, it does have certain limitations that users should be aware of:
1. **Limited Battery Life**:  
   The 18650 rechargeable battery provides up to 18 hours of operation on a full charge. Users may need to recharge the device daily if used extensively. Additionally, battery performance may degrade over time, reducing operational hours between charges.
2. **Dependent on Line of Sight**:  
   Since the OPIN AC Control uses IR signals to communicate with the air conditioner, it requires a clear line of sight between the device and the AC unit. Obstructions may cause the signal to fail, preventing remote control of the AC.
3. **Wi-Fi Configuration Required**:  
   The device must be connected to the same local Wi-Fi network as the OPIN Gateway. If the device is moved to a different network, Wi-Fi configuration needs to be reset and reconfigured through the app.
4. **Manual Battery Charging**:  
   The device does not feature automatic charging capabilities. Users must manually plug the device into a power source via the charging port when the battery is low.

## Future Development
The OPIN AC Control is designed to evolve with user needs and technological advancements. Several improvements and new features are planned for future releases to enhance functionality and user experience:
1. **Longer Battery Life**:  
   Efforts are being made to improve the efficiency of the device’s power consumption. Future iterations may include the use of more advanced battery technology or power-saving features to extend operational hours beyond the current 18-hour limit.
2. **Voice Assistant Integration**:  
   The OPIN AC Control is expected to integrate with popular voice assistants such as Google Assistant and Amazon Alexa. This would enable users to control their AC units using voice commands, adding another layer of convenience to the smart home experience.
3. **Room Temperature and Humidity-Based Automation**:  
   In the future, the device could be programmed to automatically adjust the AC settings based on room temperature and humidity, creating a more comfortable and energy-efficient environment.

---
---

# Additional Information
## OPIN Smart Home Devices
Other devices:
- [OPIN Smart Gateway](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public>)
- [OPIN Smart Lamp](<https://github.com/OPIN-Smart-Home/SmartLamp>)
- [OPIN Smart kWh Meter](<https://github.com/OPIN-Smart-Home/kWhMeter>)
- [OPIN Smart Door Lock](<https://github.com/OPIN-Smart-Home/DoorLock>)

## Further Information
For further information, please feel free to contact me at:
- **Email**: [anisahfarah28@gmail.com](mailto:anisahfarah28@gmail.com)
- **LinkedIn**: [Anisah Farah Fadhilah](https://www.linkedin.com/in/anisahfarahfadhilah)
