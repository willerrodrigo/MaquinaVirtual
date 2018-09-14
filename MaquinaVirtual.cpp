/*
Detalhes do set de instrução

	Tamanho das instruções: 16 bits
	
	Código das intruções:
	
		ADD: 	000  	OR:   010		LOAD: 	100
		MULT: 	001 	AND:  011		STORE:  101
		 

	Instruções Tipo 1: 
	
		- Utilizado para operações aritméticas (soma e multiplicação)
	     
             MSB                                      LSB
		   
		(Tipo instr.) (End. Reg 1) (End. Reg 2) (End Reg Dest.)
          
           3 bits        4 bits        4 bits       5 bits
           
		   
         - Exemplo: 0b0000000000100010 >>> |000|0000|0001|00010
         
         	 	Realiza a soma (000 >> tipo da instrução) do registro 0 (0000 
 	 	 	 >> end. Reg 1) com o registro 1 (0001 >> end. Reg 2) e salva o resultado
 	 	 	 em registro 2 (00010 >> end. Reg Dest.)	 	 
 	 	 	 
 	 	 	 
    Instruções Tipo 2:
    
     	 - Utlizado para operações de LOAD e STORE
     	 
     	       MSB                        LSB
     	 
     	 (Tipo instr.) (End Reg) (End Memória de dados)

		    3 bits       4 bits        9 bits
		    
   	   - Exemplo: 0b1000000000010010 >>> |100|0000|000010000
         
         	 	Realiza o LOAD (100 >> tipo da instrução) do endereço de 
			memória 8 (00001000 >> end. Memória) para o registro 0 
			(0000 >> end. Reg )
 	 	 	 
*/

#include <iostream>

using namespace std;



// Memoria de programa            
unsigned int ProgMemory[] = {
								//LOAD 
								0b1000000000000000,
								0b1000001000000001,
								
	   	   	   	   	   	   	   	//ADD e MULT
								0b0000000000100010,
								0b0010000000100011,
								
								//STORE
								0b1010000000000011,
								
								//OU e E
								0b0100000100000100,
								0b0110001001100101
								};
// Memoria de dados
unsigned int DataMemory[] = { 2, 3, 0, 0, 0, 0, 0, 0};

									
// Registradores
unsigned int PC;
unsigned int Instr;
unsigned int InstrType;
unsigned int RegSourceA;
unsigned int RegSourceB;
unsigned int RegDest;
unsigned int RegAddrMemory;
unsigned int Reg[10];

// Prototipos
void decode(void);
void execute(void);

int main()
{
	unsigned char i;
	
	// Inicializacao dos registros
	PC = 0;
	for(i = 0; i < 10; i++)
	{
		Reg[i] = 0;
	}
	
	while(PC < 7)
	{
		Instr = ProgMemory[PC]; // busca da instrução
		PC = PC + 1;
		decode();    // decodificação
		execute();
	}

    return 0;       
}


void decode(void)
{
	InstrType = Instr >> 13;
	
	if(InstrType == 0 || InstrType == 1 || InstrType == 2 || InstrType == 3)
	{
		// Soma , Multiplicação , E e OU
		RegSourceA = Instr >> 9;
		RegSourceA = RegSourceA & 0b0000000000001111;
		RegSourceB = Instr >> 5;
		RegSourceB = RegSourceB & 0b0000000000001111;
		RegDest = Instr & 0b0000000000011111;	
	}
	else if(InstrType == 4)
	{
		// Load
		RegDest = Instr >> 9;
		RegDest = RegDest & 0b0000000000001111; 
		RegAddrMemory = Instr & 0b0000000111111111;
	}
	else if(InstrType == 5)
	{
		// Store
		RegSourceA = Instr >> 9;
		RegSourceA = RegSourceA & 0b0000000000001111; 
		RegAddrMemory = Instr & 0b0000000111111111;
	}
}

void execute(void)
{
	if(InstrType == 0)
	{
		// Soma
		Reg[RegDest] = Reg[RegSourceA] + Reg[RegSourceB];
	}
	else if(InstrType == 1)
	{
		// Multiplica
		Reg[RegDest] = Reg[RegSourceA] * Reg[RegSourceB];
	}
	else if (InstrType == 2){
		//OU
		Reg[RegDest] = Reg[RegSourceA] | Reg[RegSourceB];
	}
	else if (InstrType == 3){
		//E
		Reg[RegDest] = Reg[RegSourceA] & Reg[RegSourceB];
	}
	else if(InstrType == 4)
	{
		// Load
		Reg[RegDest] = DataMemory[RegAddrMemory];
	}
	else if(InstrType == 5)
	{
		// Store
		DataMemory[RegAddrMemory] = Reg[RegSourceA];
	}
}



