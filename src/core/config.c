#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_BUFFER_SIZE 256
#define KEY_LENGTH 4

FILE *open_file(char *config_file_name)
{
    FILE *file = malloc(sizeof(FILE));
    char buffer[LINE_BUFFER_SIZE];

    if ((file = fopen(config_file_name, "r")) == NULL)
    {
        fprintf(stderr, "[ERROR] Failed to open config file\n!");
        exit(EXIT_FAILURE);
    }

    return file;
}

void close_file(FILE *file)
{
    fclose(file);
}

char *get_value(char *file_path, char *key)
{
    FILE *file = open_file(file_path);
    size_t len = 0;
    int line_length = 0;
    char *buffer = malloc(sizeof(char) * LINE_BUFFER_SIZE);

    do
    {
        line_length = getline(&buffer, &len, file);
        if (line_length > 0 && buffer[0] != '#')
        {
            char buffer_key[KEY_LENGTH];
            for (int i = 0; i < KEY_LENGTH; i++)
                buffer_key[i] = buffer[i];

            if (strcmp(buffer_key, key) == 0)
            {
                char *value = malloc(sizeof(char) * (LINE_BUFFER_SIZE - KEY_LENGTH - 1));
                for (int i = KEY_LENGTH + 1; i < LINE_BUFFER_SIZE; i++)
                {
                    if (buffer[i] == '\n' || buffer[i] == '\0')
                        break;
                    value[i - KEY_LENGTH - 1] = buffer[i];
                }
                close_file(file);
                return value;
            }
        }
    } while (line_length > 0);

    close_file(file);
    return "0";
}

int get_config_int_value(char *file_path, char *key)
{
    return atoi(get_value(file_path, key));
}
char *get_config_str_value(char *file_path, char *key)
{
    return get_value(file_path, key);
}