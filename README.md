# NetworkClock
Work of Secure Code in Prague courses.  
[You can read the subject here](SUBJECT.md)

## Setup and launch
If not already done, build applications by launching build script: 
> bash build.sh

After editing config files, you can launch server or client by executing those commands:
> bash server_app  
> bash client_app  

You'll obtain applications in bin folder, all of them follow ACLs 100, that means only the owner gets permission to only execute them. Configuration files are also in the bin folder aside from applications and all of them follow ACL 600, that means only the owner gets permissions to read and write them.

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
- ✓ I will ask you to return the main_settime application. I agree that it
is elegant to keep everything in the same file (although I don't quite
understand why you read the /proc/self/exe file to get its name),
butit's really not suitable for the purpose - we want the privileged
application to be as tiny as possible, and making it a part of the main
application goes directly against that goal. Basically, you are now not
satisfying the requirement for a minimal easy-to-check application. [-25
pt.]

>     server:
> 
>     You are reading the port from a configuration file. Your implementation
>     may or may not be correct, depending on your intentions. You should
>     explain where you want the configuration file located, what ACLs do you
>     expect to apply to it, and why is that in accord with your intentions
>     for the application. [-1 pt.]

- ✓ This is not about a code but about an explanation of your choice. I
still need it. [-1 pt.]

>     This is not correct:
>           FILE *file = malloc(sizeof(FILE));
>           if ((file = fopen(config_file_name, "r")) == NULL)
>     Malloc allocates some memory. Fopen also allocates some memory. As a
>     result, the malloc pointer gets overwritten by the fopen pointer and
>     you
>     leak memory.

Fixed.

>     This is not necessary:
>           char *buffer = malloc(sizeof(char) * LINE_BUFFER_SIZE);
>     Especially since you lie to the getline function by telling it that the
>     size of the buffer is zero.

- ✓ Changed to a incorrect version. Just char *buffer; is not sufficient for
the function to work. The application can crash here or even cause a
buffer overflow. [-1 pt.]

>     You cannot use strcmp here:
>                   // If key equal needed key
>                   if (strcmp(buffer_key, key) == 0)
>     because buffer_key is not a string. The code might work for you, but
>     that's a random behavior, not a reliable thing. [-1 pt.]

Fixed.

>     In the same way, value returned from get_value is not a string. What
>     makes a pointer a string in C? [-1 pt.]

- ✓ It's better now, but the value can still be a non-string. [-1 pt.]

>     You chose to use strftime for your date/time formatting needs. Is it
>     safe? Can we trust this function?
> 
>     strftime can fail, you never deal wiuth this possibility. [-1 pt.]

Fixed.

>     Where do you expect settime_app to be located? I suspect you
>     implemented
>     something else than what you intended. Even if the implementation
>     matches your intentions, you need to at least explain it - I think your
>     implementation is dangerous, it can easily lead to running an incorrect
>     file. (Focus on the first sentence here. Don't try to fix the problem
>     before you realize what the problem is! Chances are you will fix
>     something that is not relevant!) [-2 pt.]

- Will be relevant again once you return a standalone settime.

>     You shouldn't write functions like get_command or get_arg, where you
>     modify an output buffer without knowing the size of the buffer. This is
>     exactly what made C the dangerous language it is. At the very least,
>     you
>     need to provide an argument for the buffer size. Better, avoid writing
>     data into memory. After all, you don't need it - certainly not in
>     get_command. [-1 pt.]

Fixed.

>     Similarly to get_value, the result of get_command might not be a
>     string.
>     This needs to be fixed, too. (I am not deducting any point here, but
>     only because it's a part of the previous error. You must fix both
>     places.) (Interestingly enough, you handled this correctly in get_arg.)

Fixed.

>     The "Check if doesn't start with space, instead, throw an argument
>     length of 0" in get_arg does not actually adhere to the results of
>     get_command. In particular, you might be accessing an invalid memory.
>     [-1 pt.]

Fixed.

>     fgets can fail. We discussed this in detail during a tutorial. [-1 pt.]

Fixed.

>     Note that read() will read any characters, including \0.
> 
>     Note that read(1024) does not actually get you a result similar to
>     using
>     fgets() - it gets you whatever is available in the buffer now, but that
>     doesn't have to be a full input, even if the full input is shorter than
>     1024 bytes! When someone sends "Hello", the command can easily return
>     just "H" or "He", not the full message. One of the requirements for the
>     network part is that you properly implement connection control so that
>     you can be certain to get a full message and then process it, properly
>     splitting it if you get multiple messages. [-1 pt.]

- ✓ You fixed this specific problem, but in doing so created a buffer
overflow. [-2 pt.]

It would be more efficient (but also more complicated) to read the whole
buffer at a time and then deal with the borderline cases.

>     In neither of the applications did you implement the optional security
>     parts parts - you didn't discard unnecessary privileges and didn't make
>     sure that DEP is active. [-4 pt.]

- Your implementation is rather problematic, for several reasons: [-4 pt.]

    - You are not actually trying to enable DEP - you are verifying that the
CPU supports it and if it doesn't, you exit the application. But the
support for NX doesn't mean that it is actually enabled and terminating
the application if it isn't is perhaps too strict. It would be better if
you did your best to enable DEP but then enable anyway.

    - Same for privileges - don't quit just because privileges can't be
dropped. What if the application is already setup to use minimal
privileges, which really is just "change the time"? Your current
implementation would quit the application, forcing the user to actually
increase the privileges above the required minimum. It's quite possible
the user would just decide to run as root to be certain that the
application will run, which is the opposite of what we want. Just like
with DEP, you should do your best to remove the privileges but allow to
continue regardless.

    - I will need some explanation how drop_privilegies actually achieves
the stated goal. It seems to me that it doesn't, but maybe I am
overlooking something. But I don't think I am - after all, if you had
dropped the privileges, then enable_settime_capability wouldn't work
anymore because you can't enable a dropped privilege.

    - Once you return the standalone settime, you will need to implement
these features for it, too.

