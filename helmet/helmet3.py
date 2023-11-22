import socket
import time
import subprocess
import os
host = '192.168.42.166'
port = 5000
message = "04 01 004 3 l l"
while(True):
    dat = message
    client_socket = socket.socket()
    client_socket.connect((host,port))
    client_socket.send(dat.encode())
    time.sleep(5)
    print("Data Sent");
