# WebAuthTng2

Device server to provide basic web authorization and check access permissions.
(MySQL database needed).

Set property MailAgentDevice if you will use Tango device with mail-agent for sending email.

### Installation

You need installed Tango

```sh
$ git clone [git-repo-url] 
```

You have to use the definition of defines DBUSER and DBPASS in Makefile

```
CXXFLAGS_USR+= -DDBUSER="\"user_of_database\"" -DDBPASS="\"user_pass\""
```

In Visual Studio 

```
Configuration Properties // C/C++ // Preprocessor // Preprocessor Definitions // DBUSER="user_of_database";DBPASS="user_pass"
```

For IP, you can use a simple  regular expression '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}'
For device_name, you can use a simple  regular expression '.*/.*/.*/.*'