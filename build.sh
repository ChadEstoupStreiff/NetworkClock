sudo apt-get install libcap-dev 

echo "Building server application"
gcc -o bin/server_app src/main_server.c src/core/config.c src/core/security.c src/server/time.c src/server/server.c src/server/console.c  -lcap

echo "Building client application"
gcc -o bin/client_app src/main_client.c src/core/config.c src/core/security.c -lcap

echo "Building settime application"
gcc -o bin/settime_app src/main_settime.c src/core/security.c -lcap

echo "Setting permissions"
sudo setcap 'cap_sys_time=ep' bin/settime_app

chmod 100 bin/server_app
chmod 100 bin/client_app
chmod 100 bin/settime_app
chmod 600 bin/client.config
chmod 600 bin/server.config