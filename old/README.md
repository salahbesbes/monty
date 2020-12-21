
# Monty Project


## How the program works

	* read from a file
		* each line is an instruction
		* get rid of a comment if found
		* each instruction must be trimmed
		* each instruction is strored in a struct
			struct {
				command;
				args;
				idxofline;
			}
		* check for the first instruction if it is queue else by
		default its stack
		* we compaire the command by a list of predefined built-in
		created if found we execute



if argc == 2
	read from a file
	for each line
		we parse the line into command and args
		we save it into struct global var
		check for command  if found 
		we execute instruction

