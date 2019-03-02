import socket

s = socket.socket()         
 
s.bind(('0.0.0.0', 49000 ))
s.listen(0)                 
 
try:
    while True:
    
        client, addr = s.accept()
    
        while True:
            content = client.recv(32)
    
            if len(content) ==0:
                break
    
            else:
                print(content)
    
        client.close()
        
except KeyboardInterrupt:
    print("bye bye!")
    s.close()