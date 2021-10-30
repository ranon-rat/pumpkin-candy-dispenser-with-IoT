#include <WiFi.h>
#include "esp_camera.h"
#include "esp_http_server.h"

#define PART_BOUNDARY "123456789000000000000987654321"
#define STREAM_CONTENT_TYPE "multipart/x-mixed-replace;boundary=" PART_BOUNDARY
#define STREAM_BOUNDARY "\r\n--" PART_BOUNDARY "\r\n"
#define STREAM_PART "Content-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n"

static esp_err_t streamHandler(httpd_req_t *req)
{

    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    size_t jpg_buf_len = 0;
    uint8_t *jpg_buf = NULL;
    char *part_buf[64];

    res = httpd_resp_set_type(req, STREAM_CONTENT_TYPE);
    if (res != ESP_OK)
    {
        return res;
    }

    while (true && res == ESP_OK)
    {
        fb = esp_camera_fb_get();
        if (!fb)
        {
            Serial.println("Camera capture failed");
            
            continue;
        }
     

            jpg_buf_len = fb->len;
            jpg_buf = fb->buf;
        
        size_t hlen = snprintf((char *)part_buf, 64, STREAM_PART, jpg_buf_len);
        const char *responses[3] = {
            (char *)part_buf, (char *)jpg_buf, STREAM_BOUNDARY};
        const size_t sizes_response[3] = {
            hlen, jpg_buf_len, strlen(STREAM_BOUNDARY)};

        for (int i = 0; i < 3 && res == ESP_OK; i++)
        {
            res = httpd_resp_send_chunk(req, responses[i], sizes_response[i]);
        }

        if (fb)
        {
            esp_camera_fb_return(fb);
            fb = NULL;
            jpg_buf = NULL;
        }
        else if (jpg_buf)
        {
            free(jpg_buf);
            jpg_buf = NULL;
        }

        //Serial.printf("MJPG: %uB\n", (uint32_t)(jpg_buf_len));
    }
    return res;
}