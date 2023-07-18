# NetworkClock
Work of Secure Code in Prague courses.  
[You can read the subject here](SUBJECT.md)

## Setup and launch
If not already done, build applications by launching build script:
> bash build.sh

After editing config files, you can launch server or client by executing those commands:
> bash server_app  
> bash client_app  

## Objectives
- In order to be eligible for any points, the application must, at the very least, work locally for the interactive user: The non-network user must be able to request the time in a format specified by him, and must be able to set the system time. The application must run with the privileges of a regular user, any high privileged tasks must be done through a separate application which will be executed with elevated privileges.  
    - Make sure the application isn’t vulnerable to buffer overflow, format string abuse, malformed input, etc.
    - Create a list of privileged functions that the application needs and propose their separation into a new process.
    - The privileged process must be properly launched with administrative privileges.
    - The privileged process must only perform the barest minimum of work and then terminate, in order to minimize the attack surface. In particular, it is not acceptable to run any new process from TS – functions such as system, fork, exec, ShellExecute and similar are prohibited.
    - Note: The local part must be completely separated from the network. It is not sufficient to verify that a network user uses a local IP address!
    For completing all of these requirements you will get up to [15 points].
- In both applications, give up all privileges you don’t need; explain why you need any privileges you kept. [2 points]
- In both applications, subscribe to DEP (in case the operating system is configured in the "OptIn" mode), or provide a reliable documentation that shows that you don’t need to do that. [2 points]
- ✓ The application should allow remote users to connect and request the current date/time. [1 point]
- ✓ The remote users may not set the time, but they may specify a format string for the display of the current time. [3 points]
- ✓ Within one connection, the user should be able to ask for multiple formats. [1 point]
- ✓ TCP port used by the server part will be configured through a configuration file or a registry key. Explain your choice of location, including the ACLs for it. [1 point]
- Any security issues found will decrease the final score.
## Server application  
Command line inputs and server are separated in two threads.  

### Commands
In command line you have this commands:
- time [format]: will display current time, if format is specified will adapt to format, see [regex date formatting](#regex-date-formatting) to know how to use.  
- settime <time>: will set time based on format "YYYY-MM-DD HH:MM:SS".  

On server socket you can connect and send the format you need, the server will answer with current time formated.  

### Config
Edit server.config with parameters you need.  
```
# Server port
PORT 8080
# Max number of similtaneous clients
MCLI 100
```

## Client application
### Command
You can type in every format you need and the server will answer current time formated. see [regex date formatting](#regex-date-formatting) to know how to use.  
Sending "time", "get" or "default" will return default time formating of server.    
### Config
Edit server.config with parameters you need. 
```
# Server address
ADDR 127.0.0.1
# Server port
PORT 8081
```
## regex date formatting

| Specifier | Meaning | Example |
|-|-|-|
| %% | The % character. | % |
| %a | National abbreviated weekday name | Mon |
| %A | National full weekday name | Monday |
| %b | National abbreviated month name | Sep |
| %B | National full month name | September |
| %c | National representation of date and time | Mon Sep 22 12:50:32 2011 |
| %C | The Century number (00-99) | 19 |
| %d | Day of the month, zero-padded (01-31) | 22 |
| %D | Short MM/DD/YY date, equivalent to %m/%d/%y | 07/30/09 |
| %e | Day of the month, space-padded ( 1-31) | 22 |
| %F | Short YYYY-MM-DD date, equivalent to %Y-%m-%d | 2011-09-22 |
| %g | Week-based year, last two digits (00-99) | 16 |
| %G | Week-based year, with century | 2016 |
| %h | The same as %b. | Sep |
| %H | Hour in 24h format (00-23) | 16 |
| %I | Hour in 12h format (01-12) | 08 |
| %j | Day of the year (001-366) | 145 |
| %m | Month as a decimal number (01-12) | 08 |
| %M | Minute (00-59) | 52 |
| %n | Newline character ('\n') | |
| %p | AM or PM designation | AM |
| %r | 12-hour clock time | 02:55:02 PM |
| %R | 24-hour HH:MM time, equivalent to %H:%M | 12:44 |
| %S | Second (00-61) | 06 |
| %s | Unix time; the number of seconds since the Unix epoch | 1455803239 |
| %t | Horizontal-tab character ('\t') | |
| %T | ISO 8601 time format (HH:MM:SS) | 18:25:34 |
| %u | ISO 8601 weekday as number with Monday as 1 (1-7) | 6 |
| %U | Week number with the first Sunday as the first day | 30 |
| | of week one (00-53) | |
| %V | ISO 8601 week number (00-53) | 12 |
| %w | Weekday as a decimal number with Sunday as 0 (0-6) | 5 |
| %W | Week number with the first Monday as the first day | 50 |
| | of week one (00-53) | |
| %x | National date representation | 05/28/11 |
| %X | National time representation | 12:22:02 |
| %y | Year, last two digits (00-99) | 11 |
| %Y | Year | 2016 |
| %z | The time zone offset from UTC | +0100 |
| %Z | Timezone name or abbreviation | CEST |


## Comments:
### settime:

- ✓ As discussed during the lecture, it's generally a very bad idea to
verify that a user is root. After all, you don't need root privileges,
the only reason you are making that test is because root usually has the
privileges that you need - but a non-root user can have them too and by
requiring root you are violating the least privilege principle. Remove
the check. [-2 pt.]

- ✓ You shouldn't print out detailed error messages. They won't help the
user because the user won't see them (or, if they see them, they won't
understand them). They won't help the developer because the developer
already made sure the application is correct (we specifically made the
application as simple as possible to achieve this goal). The only one
who can benefit from the messages is the attacker, and why should we
help them? [-1 pt.]

### server:

- You are reading the port from a configuration file. Your implementation
may or may not be correct, depending on your intentions. You should
explain where you want the configuration file located, what ACLs do you
expect to apply to it, and why is that in accord with your intentions
for the application. [-1 pt.]

- ✓ This is not correct:
     FILE *file = malloc(sizeof(FILE));
     if ((file = fopen(config_file_name, "r")) == NULL)
Malloc allocates some memory. Fopen also allocates some memory. As a
result, the malloc pointer gets overwritten by the fopen pointer and you
leak memory.

- ✓ This is not necessary:
     char *buffer = malloc(sizeof(char) * LINE_BUFFER_SIZE);
Especially since you lie to the getline function by telling it that the
size of the buffer is zero.

- ✓ You cannot use strcmp here:
             // If key equal needed key
             if (strcmp(buffer_key, key) == 0)
because buffer_key is not a string. The code might work for you, but
that's a random behavior, not a reliable thing. [-1 pt.]

- ✓ In the same way, value returned from get_value is not a string. What
makes a pointer a string in C? [-1 pt.]

- ✓ You chose to use strftime for your date/time formatting needs. Is it
safe? Can we trust this function?

- ✓ strftime can fail, you never deal wiuth this possibility. [-1 pt.]

- You shouldn't use a potentially dangerous function like sprintf. Your
buffer might be big enough to hold the values, but it's still a poor
practice. Keep in mind that the size of the buffer is a macro, someone
might easily change in the future without realizing the consequences of
that.

- Where do you expect settime_app to be located? I suspect you implemented
something else than what you intended. Even if the implementation
matches your intentions, you need to at least explain it - I think your
implementation is dangerous, it can easily lead to running an incorrect
file. (Focus on the first sentence here. Don't try to fix the problem
before you realize what the problem is! Chances are you will fix
something that is not relevant!) [-2 pt.]

- You shouldn't write functions like get_command or get_arg, where you
modify an output buffer without knowing the size of the buffer. This is
exactly what made C the dangerous language it is. At the very least, you
need to provide an argument for the buffer size. Better, avoid writing
data into memory. After all, you don't need it - certainly not in
get_command. [-1 pt.]

- ✓ Similarly to get_value, the result of get_command might not be a string.
This needs to be fixed, too. (I am not deducting any point here, but
only because it's a part of the previous error. You must fix both
places.) (Interestingly enough, you handled this correctly in get_arg.)

- The "Check if doesn't start with space, instead, throw an argument
length of 0" in get_arg does not actually adhere to the results of
get_command. In particular, you might be accessing an invalid memory.
[-1 pt.]

- fgets can fail. We discussed this in detail during a tutorial. [-1 pt.]

Note that read() will read any characters, including \0.

- Note that read(1024) does not actually get you a result similar to using
fgets() - it gets you whatever is available in the buffer now, but that
doesn't have to be a full input, even if the full input is shorter than
1024 bytes! When someone sends "Hello", the command can easily return
just "H" or "He", not the full message. One of the requirements for the
network part is that you properly implement connection control so that
you can be certain to get a full message and then process it, properly
splitting it if you get multiple messages. [-1 pt.]

- In neither of the applications did you implement the optional security
parts parts - you didn't discard unnecessary privileges and didn't make
sure that DEP is active. [-4 pt.]