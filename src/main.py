response = "<html><head><title>Open the fucking door</title><meta name='viewport' content='width=device-width, initial-scale=1'><link rel='icon' href='data:,'><style>html {font-family: Helvetica;display:inline-block;margin: 0px auto;text-align: center;background-color: black;}h1 {color: white;padding: 2vh;}p {font-size: 1.5rem;}.button {display: inline-block;background-color: green;border: none;border-radius: 4px;color: white;padding: 16px 40px;text-decoration: none;font-size: 30px;margin: 2px;cursor: pointer;}</style></head><body><h1>Open the door!</h1><p><a href='/?open=yes'><button class='button'>OPEN</button></a></p></body></html>"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

while True:
    conn, addr = s.accept()
    print('Got a connection from' + str(addr))

    request = conn.recv(1024)
    request = str(request)
    print('Content =' + request)

    isopen = request.find('/?open=yes')

    if isopen != -1:
        print('Opening the door...')
        switch.value(1)
        sleep(5)
        switch.value(0)

    conn.send('HTTP/1.1 200 OK\n')
    conn.send('Content-Type: text/html\n')
    conn.send('Connection: close\n\n')
    conn.sendall(response)
    conn.close()
