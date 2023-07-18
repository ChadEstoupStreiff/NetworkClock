echo "Building server application"
gcc -o server_app src/main_server.c src/core/config.c src/core/security.c src/server/time.c src/server/server.c src/server/console.c

echo "Building client application"
gcc -o client_app src/main_client.c src/core/config.c src/core/security.c

echo "Building settime application"
gcc -o settime_app src/main_settime.c src/core/security.c

echo "Setting permissions"
chmod 100 server_app
chmod 100 client_app
chmod 100 settime_app