gcc -o server_app src/main_server.c src/core/config.c src/server/time.c src/server/server.c src/server/console.c
gcc -o client_app src/main_client.c src/core/config.c
gcc -o admin_app src/main_admin.c