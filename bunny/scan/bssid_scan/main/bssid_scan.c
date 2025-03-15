#include <string.h>
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

static const char *TAG = "SCAN";
#define TARGET_SSID ""                  // Have to enter the target SSID here

void wifi_scan_and_print_mac() {
    ESP_LOGI(TAG, "Starting WiFi scan to find MAC address of target SSID");

    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };

    esp_err_t scan_result = esp_wifi_scan_start(&scan_config, true);
    if (scan_result != ESP_OK) {
        ESP_LOGE(TAG, "Scan start failed: %s", esp_err_to_name(scan_result));
        return;
    }

    uint16_t ap_count = 0;
    esp_err_t ap_num_result = esp_wifi_scan_get_ap_num(&ap_count);
    if (ap_num_result != ESP_OK) {
        ESP_LOGE(TAG, "Get AP number failed: %s", esp_err_to_name(ap_num_result));
        return;
    }

    ESP_LOGI(TAG, "Found %d access points", ap_count);

    wifi_ap_record_t *ap_records = malloc(sizeof(wifi_ap_record_t) * ap_count);
    esp_err_t ap_records_result = esp_wifi_scan_get_ap_records(&ap_count, ap_records);
    if (ap_records_result != ESP_OK) {
        ESP_LOGE(TAG, "Get AP records failed: %s", esp_err_to_name(ap_records_result));
        free(ap_records);
        return;
    }

    bool target_found = false;
    for (int i = 0; i < ap_count; i++) {
        ESP_LOGI(TAG, "Found AP: %s", ap_records[i].ssid);
        if (strcmp((char*)ap_records[i].ssid, TARGET_SSID) == 0) {
            ESP_LOGI(TAG, "Target SSID '%s' found with BSSID: %02X:%02X:%02X:%02X:%02X:%02X",
                     TARGET_SSID,
                     ap_records[i].bssid[0], ap_records[i].bssid[1],
                     ap_records[i].bssid[2], ap_records[i].bssid[3],
                     ap_records[i].bssid[4], ap_records[i].bssid[5]);
            target_found = true;
            break;
        }
    }

    if (!target_found) {
        ESP_LOGE(TAG, "Target SSID '%s' not found", TARGET_SSID);
    }

    free(ap_records);
}

void app_main() {
    ESP_LOGI(TAG, "Starting!");

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));
    ESP_ERROR_CHECK(esp_wifi_start());

    wifi_scan_and_print_mac();
}
