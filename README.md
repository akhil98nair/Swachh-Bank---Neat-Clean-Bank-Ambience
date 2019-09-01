# Swachh-Bank---Neat-Clean-Bank-Ambience
 A centralized system to detect Branch Cleanliness &amp; Ambiance effectively. Since everyday several visitors visit bank for business and financial transactions it is very important to keep it neat and clean so as to ensure long lasting cleanliness and dust-free atmosphere that will attract more customers for sure.

Hardware Required:
  1. NodeMCU
  2. Ultrasonic Distance Sensor (hc-sr04)
  3. Gas Sensor (MQ135)
  4. Android Phone
  
Software Required:
  1. Arduino IDE (https://www.arduino.cc/en/main/software)
  2. Camlytics Tool (https://camlytics.com/download/latest)

Steps:
  1. Install Arduino IDE.
  2. Do connection with the above mentioned sensors as shown in the circuit diagram (https://github.com/akhil98nair/Swachh-Bank---Neat-Clean-Bank-Ambience/blob/master/cuircuit%20connection.PNG).
  3. Now open the microcontroller code in arduino IDE and add the mobile no of the cleaning person without the country code in the place of ADD_MOBILE_NO, add your wifi name in the place of YOUR_WIFI_NAME, add password of wifi in the place of YOUR_WIFI_PASSWORD.
  4. Then Upload the code into NodeMCU
  5. Install the apk given into the android phone of the cleaning authority.
  6. Once the above steps are completed download the camlytics tool from the above given link and install in to the cctv recording computer and select the entrance camera and select count object option after that calibirate the entrance and exit line according to the requirement. See our video (https://youtu.be/stlTmiFYLp4)
  
  
