# idf_component_register(SRCS "ble_helper/bluedroid_gatts.c" "ble_helper/nimble_gatts.c"
#                     "ble_helper/ble_api.c"
#                     INCLUDE_DIRS "." "./ble_helper/include/"
#                     # Embed the server root certificate into the final binary
#                     EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem)


idf_component_register(SRCS "main.c" "OTA_helper/OTA_CONFIG.c" "feed_control_helper/feed_control.c"
                    "RS_485_helper/rs_485.c" "i2c_helper/i2c_control.c" 
                    INCLUDE_DIRS "." "./OTA_helper/include/" "./RS_485_helper/include/" "./feed_control_helper/include/"  "./i2c_helper/include/"
                                        # Embed the server root certificate into the final binary
                    EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem)
