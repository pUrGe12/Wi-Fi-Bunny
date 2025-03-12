// Discover the target AP: identify the MAC address, SSID (network name), and channel of the AP you want to target

// Craft and send deauthentication frames: Using the captured MAC address of the target AP, create deauthentication frames and send them to the AP. The frames should contain the broadcast address to target all clients connected to the AP.

// Persist disconnection: send deauthentication frames at regular intervals

// A typical deauthentication frame includes the following components:
// Frame Control: Indicates the type (management) and subtype (deauthentication).
// Duration: Specifies the duration for which the frame is valid.
// Receiver Address: The MAC address of the target device being deauthenticated.
// Source Address: The MAC address of the access point (AP) sending the deauth frame.
// BSSID: The MAC address of the AP.
// Reason Code: A two-byte field indicating why the device is being disconnected, such as "unspecified reason" or "previous authentication no longer valid."


// BSSID: This is the MAC address of the access point (AP) that the ESP32 is targeting. It uniquely identifies the AP within a Basic Service Set (BSS). When performing a deauthentication attack, you would specify the BSSID of the AP from which you want to disconnect clients.
// Source Address: This refers to the MAC address of the device sending the deauthentication frame. In an attack scenario, if the ESP32 is replicating a deauth frame from a specific AP, the Source Address in that frame would typically be set to match the BSSID of that AP. This makes it appear as though the deauth request is coming from the legitimate AP.

#include "WiFi.h"

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected.
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");
}

void loop() {
  Serial.println("Scan start");

  int n = WiFi.scanNetworks();
  Serial.println("Scan done");
  if (n == 0) {
    Serial.println("No networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    Serial.println("Nr | SSID                             | RSSI | CH | Encryption       | BSSID");
    for (int i = 0; i < n; ++i) {
      Serial.printf("%2d", i + 1);
      Serial.print(" | ");
      Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      Serial.print(" | ");
      Serial.printf("%4ld", WiFi.RSSI(i));
      Serial.print(" | ");
      Serial.printf("%2ld", WiFi.channel(i));
      Serial.print(" | ");
      
      switch (WiFi.encryptionType(i)) {
        case WIFI_AUTH_OPEN:            Serial.print("open"); break;
        case WIFI_AUTH_WEP:             Serial.print("WEP"); break;
        case WIFI_AUTH_WPA_PSK:         Serial.print("WPA"); break;
        case WIFI_AUTH_WPA2_PSK:        Serial.print("WPA2"); break;
        case WIFI_AUTH_WPA_WPA2_PSK:    Serial.print("WPA+WPA2"); break;
        case WIFI_AUTH_WPA2_ENTERPRISE: Serial.print("WPA2-EAP"); break;
        case WIFI_AUTH_WPA3_PSK:        Serial.print("WPA3"); break;
        case WIFI_AUTH_WPA2_WPA3_PSK:   Serial.print("WPA2+WPA3"); break;
        case WIFI_AUTH_WAPI_PSK:        Serial.print("WAPI"); break;
        default:                        Serial.print("unknown");
      }
      
      // Printing BSSID
      Serial.print(" | ");
      uint8_t bssid[6];
      WiFi.BSSID(i, bssid);
      for (int j = 0; j < 6; j++) {
        if (j < 5) {
          Serial.printf("%02X:", bssid[j]);
        } else {
          Serial.printf("%02X", bssid[j]);
        }
      }
      
      Serial.println();
      delay(10);
    }
  }
  
  Serial.println("");

  WiFi.scanDelete();

  delay(5000);
}

