# Business Analysis V2
**Advanced Version of Business Management and Analysis tool using C (2nd semester project)**

Description: This is a simple Business Management Tool made using basic C language which uses functions and data types like structures to create a simple systwm which can add/remove customers, keep list of product inventory, calculate overall profit/loss of the business based on inventory and customer purchases and even provide financial statements. Comments has also been added into each header (.h) and each source code (.c) file for every code snippet to make code easily readable and understandable in case this program is replicated.

**How to implement the program:**
Download the Business Analysis folder and make sure your task.json and launch.json folders on vscode have their contents intact.
Before opening in VSCode, first go to file location, open Business Analysis folder and go to data folder. Then delete the file "data.txt". Make sure you do this otherwise program will have implementation issues. Afterwards go back to Business Analysis folder, then right click and select open with code as shown below:

![image](https://github.com/user-attachments/assets/17f99368-e39b-47b5-91c0-ea70cd06059f)


Now, to run this in vscode, create a new terminal and when the terminal opens, choose command prompt as the type of terminal from the terminal window as indicated in the image below:

![image](https://github.com/user-attachments/assets/0f376007-9382-404e-b236-8b9824111481)

Then enter this code to compile the C program: 

gcc -o bin\bams src\main.c src\billing.c src\customer.c src\financial.c src\product.c src\trend_analysis.c src\utils.c src\globals.c -Iinclude -Wall -Wextra

and then run the program by typing this:

bin\bams

this should run the program and open this interface

![image](https://github.com/user-attachments/assets/f2bb3327-4d8c-428c-957c-d12cfbee4040)

Afterwards you can press enter and you will come across this menu

![image](https://github.com/user-attachments/assets/7f4e70aa-4617-454a-96d6-985cec1bd2c9)

From here the user can input different numbers to access the given menus.
Follow comments in each file to understand the code better if needed.



