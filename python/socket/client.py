# Echo client

import socket

# HOST = "192.168.8.102"
HOST = "127.0.0.1"
PORT = 6969

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))

    while True:
        message = input("Enter message: ")

        if message == "exit":
            break

        s.sendall(message.encode())

        data = s.recv(1024)

        if not data:
            print("Server closed connection")
            break

        print(f"Received {data.decode()!r}")
