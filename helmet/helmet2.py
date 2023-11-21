import socket
import time
import subprocess
import os
host = '192.168.128.168'
port = 5000
message = " 10 200 2 l l"
count = 10;
while(True):
    dat = str(count)+message
    client_socket = socket.socket()
    client_socket.connect((host,port))
    client_socket.send(dat.encode())
    count+=1
    time.sleep(5)
    print("Data Sent");
