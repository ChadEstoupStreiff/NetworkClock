sudo apt-get install libcap-dev 

echo "Building server application"
gcc -o server_app src/main_server.c src/core/config.c src/core/security.c src/server/time.c src/server/server.c src/server/console.c  -lcap

echo "Building client application"
gcc -o client_app src/main_client.c src/core/config.c src/core/security.c -lcap

echo "Setting permissions"
sudo setcap cap_setpcap+ep server_app
sudo setcap cap_setpcap+ep client_app

chmod 100 server_app
chmod 100 client_app