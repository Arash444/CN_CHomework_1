# CN_CHomeworks_1
Arash Shahin 810199442
Bardia Khalafi 810199414

Server: The commands, calculations and responses are in this section. 

Server.cpp handles the interface between the client and the server. If they're not logged in, they can sign in and sign up. if they are logged in, they have 10 commands they can choose from, which can lead to various errors if the client doesn't use with care. 

Rooms.cpp handles various commands relating to our rooms.

Date.cpp handles server's date, but does not handle client dates. Our date is a long long type as we hold the number of days passed since 0/0/0000 so we can easily compare dats

User.cpp handles the user info and functions

Json Reader reads our json files at the begining, and updates them in the end

Client: The clients communicate with the server with this folder. 

When we first boot up the server, we will take the date and store it in our date class. Then once clients want to connect, we conenct them using sockets and then send and recieve messages from our server  through them. The client first either has to sign in or sign up. After doing so, they have 10 commands they can use.

The first and second one merely printing the user's (or all user's) information. The third one is printing all room's information. Only admins can view every username and room. The fourth one is booking. We have to ask for the room number and number of reservations, and check if it'd go over the max capacity, if the format is correct and if the user can afford it. Cancelling is similar. We ask for the room number and number of cancelations, and we have to check if the format is correct, if the room exists at all, and if the reservation for the room exists or we aren't cancelling more than we have. Leaving is the same except we don't cget money back like cancelling and we have  all the beds. We can edit our information which are the passwords and phone numbers and address if we have them, and we can logout whenever we want to. The admin can also add remove and modify rooms. We have a function called pass day, that causes users to check in and checkout. 

