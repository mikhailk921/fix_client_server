# FIX client-server

Implementation of FIX server and client based on the latest master Quickfix library.

## = Build =

To build the project, run the following command:
```bash
mkdir "<project_folder>/build"
cd "<project_folder>/build"
cmake ..
make install
```

As a result of the installation, a `<project_folder>/bin/` folder will be created in the project folder.
This folder will contain two folders `<project_folder>/bin/server/` and `<project_folder>/bin/client/`.

### Server

The server processes input messages, performs authentication (Logon processing) and responds to client test requests using a new test request.

The `<project_folder>/bin/server/` folder contains the `server` executable file, the quickfix library, the configuration file and the FIX44 specification.

To start the server run the following command:
```bash
cd "<project_folder>/bin/server"
LD_LIBRARY_PATH=./ ./server
```

If you need to use a specific configuration file, then the executable file has an optional parameter - the path to the configuration file.
For this, run the following command:

```bash
cd "<project_folder>/bin/server"
LD_LIBRARY_PATH=./ ./server <path_to_config_file>
```

The server contains a logger. Logging is performed for each message and the result is saved in the `server/logs` folder.

### Client

The client connects to the server and performs Logon using the login and password.
After successfully connecting to the server and passing authentication, the client generates a test request and sends it to the server.

The `<project_folder>/bin/client/` folder contains the `client` executable file, the quickfix library, the configuration file and the FIX44 specification.

To start the server run the following command:
```bash
cd "<project_folder>/bin/client"
LD_LIBRARY_PATH=./ ./client
```

If you need to use a specific configuration file, then the executable file has an optional parameter - the path to the configuration file.
For this, run the following command:

```bash
cd "<project_folder>/bin/client"
LD_LIBRARY_PATH=./ ./client <path_to_config_file>
```

### Quickfix

The project uses the latest master version of the quickfix library.
The project uses the pre-built quickfix library. For build, gcc compiler version 9.4.0 was used. The library files are located in: `<project_folder>/thirdparty/quickfix`
