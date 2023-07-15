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
- settime <time>: will set time.  

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


