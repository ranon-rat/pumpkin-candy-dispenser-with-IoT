#include "WiFi.h"
#include "esp_http_server.h"
#include "static.h"
#include <ESP32Servo.h>
#include "streaming.h"
ESP32PWM pwm;
Servo dispenser;
static esp_err_t html_resp(httpd_req_t *req)
{

    httpd_resp_set_type(req, "text/html");
    esp_err_t res = httpd_resp_send(req, (const char *)index_html, index_html_len);

    return res;
}

static esp_err_t open_dispenser(httpd_req_t *req)
{

    dispenser.write(180);
    delay(500);
    dispenser.write(0);

    return httpd_resp_send(req, (const char *)"everything is okay", strlen("everything is okay"));
}
void startServer()

{

    ESP32PWM::timerCount[0] = 4;
    dispenser.attach(2);
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t stream_img_httpd = NULL;
    httpd_handle_t robot_control = NULL;

    config.server_port = 80;

    httpd_uri_t static_page = {
        .uri = "/",
        .method = HTTP_GET, //HTTP_GET
        .handler = html_resp,
        .user_ctx = NULL};
    httpd_uri_t open_uri = {
        .uri = "/open",
        .method = HTTP_GET, //HTTP_GET
        .handler = open_dispenser,
        .user_ctx = NULL};
    if (httpd_start(&robot_control, &config) == ESP_OK)
    {
        httpd_register_uri_handler(robot_control, &open_uri);
        httpd_register_uri_handler(robot_control, &static_page);
    }

    config.server_port++;
    config.ctrl_port++;
    httpd_uri_t img = {
        .uri = "/",
        .method = HTTP_GET, //HTTP_GET
        .handler = streamHandler,
        .user_ctx = NULL};

    //Serial.printf("Starting web server on port: '%d'\n", config.server_port);
    if (httpd_start(&stream_img_httpd, &config) == ESP_OK)
    {

        httpd_register_uri_handler(stream_img_httpd, &img);
    }
    //
}