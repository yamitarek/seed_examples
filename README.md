FM-Synthesizer project using the embedded audio platform daisy.

Requires the DaisySP (https://github.com/electro-smith/DaisySP) and the libDaisy (https://github.com/electro-smith/libDaisy) libraries as well as the DaisyToolchain (https://github.com/electro-smith/DaisyToolchain). 

0. Add folder to Daisy_Seed > DaisyExamples > seed. Otherwise you probably need to change the location of the libraries inside the makefile.

1. flash daisy seed by holding BOOT and pressing RESET

2. open folder in VS Code

3. launch VS command palette (press command + P on Mac)

4. type task build_all

5. type task build_and_program_dfu

Now you should hear sound.

If task build_all does not appear in your command palette that is probably becaus the task.json file is not present. YOu can just copy the hidden .vscode folder from the example projects in Daisy_Seed > DaisyExamples > seed

