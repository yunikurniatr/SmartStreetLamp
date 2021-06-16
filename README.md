# Sistem Monitoring Penerangan Lampu Jalan secara Otomatis dengan Sensor Cahaya menggunakan Nodered

## Nama Kelompok :
1. Dina Lisuardi (1941723004)
2. Yuni Kurnia Taramita (1941723002)


## nodemcu + MQTT + LDR sensor

## Library yang digunakan 
> #include <ESP8266WiFi.h> 

> #include <PubSubClient.h>
## Lampu yang tedaftar
> lamp1

> lamp2

> lamp3

## Perintah untuk on/off lampu 1-3 
> mosquitto_pub -h ec2-3-86-238-120.compute-1.amazonaws.com -t "street_lamp" -u jti -P password -m "<nama_lampu/perintah>"
## Contoh
> mosquitto_pub -h ec2-3-86-238-120.compute-1.amazonaws.com -t "street_lamp" -u jti -P password -m "lamp1/on>"

## Perintah untuk menampilkan nilai dari sensor

> mosquitto_sub -h ec2-3-86-238-120.compute-1.amazonaws.com -t "topic" -u jti -P password

## untuk menampilkan request untuk on/off lampu
> mosquitto_sub -h ec2-3-86-238-120.compute-1.amazonaws.com -t "street_lamp" -u jti -P password


