#include "Client.h"

// Client::Client(); //do we need constructor/destructor?

// Client::~Client();

const int MAX_CHARS_PER_INSTRUCTION = 2; //make these hash defined?
const char* const DELIMITER_SPACE = " ";
const char* const DELIMITER_COMMA = ",";

ifstream openFiles(string filename) {
	size_t i = filename.rfind('.', filename.length());

	ifstream infile(filename);
	if (infile.fail()) {
		cerr << "Error opening file " << filename <<endl;
		exit(EXIT_FAILURE);
	}

	if (i == string::npos || filename.substr(i, 
		filename.length()-i) != ".mis") {
        cerr << "Incorrect input file. Please provide a .mis file" << endl;
        exit(EXIT_FAILURE);
    }

	string basefile(basename(const_cast<char*> (filename.c_str())));

    char* out = strdup((basefile.substr(0, basefile.length()-3) + "out").c_str());
    outfile.open(out);
    if (!outfile.is_open()) {
        cerr << "Error opening outfile";
        exit(EXIT_FAILURE);
    }

    char* err = strdup((basefile.substr(0, basefile.length()-3) + "err").c_str());
    errfile.open(err);
    if (!errfile.is_open()) {
    	cerr << "Error opening errfile";
    	exit(EXIT_FAILURE);
    }

    return infile;
}

void parse_file(ifstream & input_file) {
	// check if file input is valid
	if (!input_file.good()) {
		errfile << "error: file cannot be found" << endl;
		return;
	}

	String LINE;
	vector<string> lines;

	//read each line of input file
	while(!input_file.eof()) {
		
		getline(input_file, LINE);	// read line into memory
		lines.push_back(LINE);

		cout << LINE << endl;	//FOR TESTING
	}

	lines.push_back("STOP"); //can replace with something else as stop message

	return lines;
}

void transmit(vector<string> in, TCPSocket sock) { //need to check number of bytes written out adn compare to length of string trying to be sent
	int status;

	for (int i = 0; i < in.length; ++i)
	{
		string testing = in[i];
		int size = testing.length();
		char packet[size+sizeof(int)];

		memcpy(packet, &size, sizeof(size));

		for (int i = 0; i < size; ++i)
		{
			packet[3+i] = testing[i];
		}
		status = writeToSocket (packet, strlen(packet));

		if (status == -1)
			exit(1);
	}
}

void receive(std::vector<string> buffer, TCPSocket* sock) {
	char length[sizeof(int)];
	int bytesRead

	do {
		string info;
		bytesRead = sock.readFromSocket(length, sizeof(int));
		if(bytesRead == -1)
		{
			perror("Error reading from socket");
			exit(1);
		}
		else
		{
			while(bytesRead < 4) //make sure we read the whole int - need to figure out how to not overwrite length every time
			{
				bytesRead = bytesRead - sock.readFromSocket(length, bytesRead); //need to change this so length isnt overwritten every time
			}
		}

		//getting length of message
		int intLength = *((int*) length);
		char buff[intLength];
		bytesRead = sock.readFromSocket(buff, intLength)

		if(bytesRead == -1)
		{
			perror("Error reading from socket");
			exit(1);
		}

		while (bytesRead != intLength)
		{
			bytesRead = sock.readFromSocket(buff, intLength-bytesRead);
		}

		//grabbing from sizeof(int) offset to end of message
		for (int i = 3; i < intLength+3; ++i)
		{
			info += buff[i];
		}

		buffer.push_back(info);
		//wipe buffers at end?
	}

	while(bytesRead != -1 || info != "STOP");
}

void write() {
	for (int i = 0; i < outBuffer.length; ++i)
	{
		outfile << outBuffer[i] << endl;
	}

	for (int i = 0; i < errorBuffer.length; ++i)
	{
		errfile << errorBuffer[i] << endl;
	}
}

int main(int argc, char const *argv[])
{
	ifstream input_file;
	input_file = openFiles(argv[1]);

	if ( argc != 3) { // Check on the number of arguments and exit if incorrect
		printf ("Usage: ./client <.mis file> <server-address>\n");
		exit(1);
	}

	TCPSocket socket(argv[2], 9999); //port # will always be 9999

	input = parse_file(input_file);

	transmit(input, socket);

	receive(outBuffer, socket); //receives until gets to stop message
	receive(errorBuffer, socket); //need to figure out how messages come in (ie if all at once or if its separated)

	write();

	return 0;
}


// Client example

	// if ( argc != 2) { // Check on the number of arguments and exit if incorrect
	//	printf ("Usage: ./client <server-address>\n");
	//	exit(1);
	// }

	// int sock; // Socket handler
	// struct sockaddr_in serverAddr; // Server address
	// socklen_t sin_size = sizeof(struct sockaddr_in); // get size of server address

	// // Try to create a socket and print an error message and exit if failed
	// if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	// 	perror("Error Creating Socket");
	// 	exit(1);
	// }

	// memset((char *) &serverAddr, 0,sizeof(serverAddr)); // initialize the server address data structure
	// serverAddr.sin_family = AF_INET; // Set up the communication family
	// serverAddr.sin_port = htons(9999); //set the port of the server
	// struct hostent *server = gethostbyname(argv[1]); // convert the host name into a network host structure
	
	// if ( server == NULL ) 
	// 	terminate_with_error("Broken",sock); // if failed terminate with an error message

	// // copy Server address data into server address structure
	// memcpy((char *)&serverAddr.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
	// memset(&(serverAddr.sin_zero), 0, 8); // Zero out the rest of the address structure
	
	// // try to connect to the server and exit with an error message if failed
	// if (connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) == -1 ) 
	// 	terminate_with_error("Broken",sock);
	
	// send(sock,"Hello CMPS 108",strlen("Hello CMPS 109"),0); // Send a message to the server.
	// close(sock);// Close the socket.
