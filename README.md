---

I’m currently working on a password manager as a personal project. The primary goal is to learn as much as possible through the process. While the project is still a work in progress, 
I’d like to share some details on how to run (or recompile) the code for this specific project.

### Key Notes About the Project:
1. Platform Dependency:  
   This application was developed specifically for Linux and will not run on other operating systems. The main reason for this is that I used the system() function to execute Linux command-line operations within the source code.
   (I now realize this is not a good practice and plan to address this in future updates.)

3. Dependencies:  
   The project uses the OpenSSL library for cryptography. To build the implementation object, you’ll need to run the following command:
   
		$ gcc -c passRepos_imple.c -lssl -lcrypto

   To link the implementation with the client, use this command:

     	$ gcc passRepos_client.o passRepos_imple.o -o client.out -lssl -lcrypto

4. Installing OpenSSL:  
   Ensure OpenSSL is installed on your system. For Manjaro (or other Arch-based distributions), you can install it using:

    	 $ sudo pacman -Syu openssl

   If you’re using a different Linux distribution, use your OS’s corresponding package manager to install OpenSSL. After it, verify that OpenSSL is correctly installed.

### Feedback Welcome:
If you have any suggestions for improving the code or the project, I’d be happy to hear them! Feel free to reach out to me at:

cibercianocode@gmail.com

---
