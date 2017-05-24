extern “C” int connect_to_server(char server_add[15], int port );
extern “C” int send_to_server (char message[6]);
extern “C” int receive_from_server (char message[6]);
 
void openGate(){
 
    //Setup variable to store password
    char pass[6];  
    //Connect to gate
    connect_to_server(“130.195.6.196”, 1024);
    send_to_server(“please”); //ask for password
    //Receive password
    receive_from_server(pass);
    //Send Password back to gate
    send_to_server(pass);
 
}
