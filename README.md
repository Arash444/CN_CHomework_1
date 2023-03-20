# CN_CHomeworks_1
Arash Shahin 810199442
Bardia Khalafi 810199414

Server: The commands, calculations and responses are in this section. 

Server.cpp handles the interface between the client and the server. If they're not logged in, they can sign in and sign up. if they are logged in, they have 10 commands they can choose from, which can lead to various errors if the client doesn't use with care. 

Rooms.cpp handles various commands relating to our rooms.

Date.cpp handles server's date, but does not handle client dates.

User.cpp handles the user info and functions

Json Reader reads our json files at the begining, and updates them in the end

Client: The clients communicate with the server with this folder. 

When we first boot up the server, we will take the date and store it in our date class. Then once clients want to connect, we conenct them using sockets and then send and recieve messages from our server  through them. The client first either has to sign in or sign up. After doing so, they have 10 commands they can use.
