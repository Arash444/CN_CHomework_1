#include "cmdHandler.hpp"

CmdHandler::CmdHandler() 
{

}

std::string CmdHandler::runCommand(std::string input, std::vector<User*> users;) 
{
	//splitting command
	stringstream ss(input);
    vector<string> command;
    while (getline(ss, s, ' ')) {
 
        // store token string in the vector
        command.push_back(s);
    }

    if (strcmp(command[0], "signin"))
    {
    	User* user;
    	if (command.size() != 3 )
    	{
    		return "Error 430: Invalid username or password.";
    	}
    	else
    	{
    		for(int i=0;i<users.size(), i++)
    		{
    			user = users[i]->checkInfo(command[1], command[2])
    			if(user != NULL)
    			{
    				
    			}
    		}
    	}
    }
}