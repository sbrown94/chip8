// Chip-8 Emulator in C

class chip8 {

	public:
		chip8();
		~chip8();
		
		bool drawFlag;
		void cycle();
		void load();

		unsigned short gfx[64 * 32];	// Display
		unsigned char key[16];			// Input

	private:
		unsigned short opcode;
		unsigned char mem[4096];

		unsigned char V[16];			// General purpose registers
		unsigned short I;				// Index register
		unsigned short pc;				// Program counter
		
		unsigned char delay_timer;
		unsigned char sound_timer;

		unsigned short stack[16];		
		unsigned short sp;				// Stack pointer

		void init();

}
