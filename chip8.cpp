#include "chip8.h"

chip8::chip8()
{
}

chip8::~chip8()
{
}

void chip8::init()
{
	pc = 0x200;			// Start address
	opcode = 0;
	I = 0;
	sp = 0;
	
	// Clear screen
	for (int i = ; i < 2048; i++)
		gfx[i] = 0;
		
	// Clear stack and registers
	for (int i = 0; i < 16; i++)
		stack[i] = key[i] = V[i] = 0;
	
	// Clear memory	
	for (int i = 0; i < 4096; i++)
		mem[i] = 0;
		
	// Load font
	for (int i = 0; i < 80; i++)
		mem[i] = font[i];
		
	delay_timer = 0;
	sound_timer = 0;
	
	drawFlag = true;
	
	srand (time(NULL));
}

void chip8::cycle()
{
	// Get opcode 
	opcode = mem[pc] << 8 | mem[pc + 1];
	
	switch(opcode & 0xF000) // Get first digit of hex
	{
		case 0x0000:
			switch (opcode)
			{
				case 0x00E0: // Clear screen
					for (int i = 0; i < 2048; i++)
						gfx[i] = 0;
					drawFlag = true;
					pc += 2;
				break;
					
				case 0x00EE: // Return from subroutine
					sp--; // decrement stack pointer
					pc = stack[sp] + 2; // put return address back into the program counter and increment
				break;
				
				default:
					printf("ERROR opcode invalid");
			}	
			
		case 0x1000: // 0x1NNN Jump to NNN
			pc = opcode & 0x0FFF;
		break;
		
		case 0x2000: 				// 0x2NNN Call subroutine at NNN
			stack[sp] = pc; 		// store current location in the stack
			sp++ 					// incrememnt stack pointer
			pc = opcode & 0x0FFF; 	// go to address
		break;
		
		case 0x3XNN: // Skip next instruction if Vx = NN
			if (V[(opcode & 0x0F00) >> 8] == (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
				
		case 0x4XNN: // Skip next instruction if Vx != NN
			if (V[(opcode & 0x0F00) >> 8] != (opcode & 0x00FF))
				pc += 4;
			else
				pc += 2;
	}
}
















