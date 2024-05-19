# Echo server

import socket

HOST = "127.0.0.1"
PORT = 6969

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()

    print(f"Server listening on {HOST}:{PORT}")

    while True:
        conn, addr = s.accept()
        with conn:
            print(f"Connected by {addr}")

            while True:
                data = conn.recv(1024)
                if not data:
                    break
                print(f"Received {data.decode()!r} from {addr}")
                if data == b'bye':
                    conn.sendall(b'')  # close connection
                    conn.close()
                    break
                conn.sendall(b"Echo: " + data)

        if conn.fileno() == -1:
            print(f"Connection with {addr} closed")
