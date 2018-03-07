#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>


//testU01 for RNG verification
//portaudio for audio capture



enum padValues {moduleLength = 18, moduleCount = 10000};
char modifiedBase64Alpha[64] = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.";
struct padFile{

	int outgoingPointer; 
	int outgoingEnd; 
	int incomingPointer; 
	int incomingEnd; 
	char* outgoing; 
	char* incoming; 
} padFile;


void fillModules(int m, int n, char * modules) // this is a placeholder RNG function
{ // arguments should be replaced with enums
	srand(time(NULL));   
	for (int i = 0; i < n; i++)
	{
		for (int c = 0; c < m; c++)
		{
			modules[(moduleLength * i)+c] = (unsigned char)(rand() % 256);
		}

	}

}


void padFile_init(struct padFile * p ){
	p -> outgoingPointer = 0;
	p -> outgoingEnd =  moduleCount; 
	p -> incomingPointer = 0; // incoming pointer changes so this is only applicable when initializing.
	p -> incomingEnd =   moduleCount;

}

void savePadFile(FILE * file, struct  padFile *  padStruct)//probably gonna want to format overhaul this
{
	

	fprintf(file,"%i\n%i\n%i\n%i\n ", padStruct -> outgoingPointer, padStruct->outgoingEnd, padStruct-> incomingPointer, padStruct-> incomingEnd);


	fprintf(file,"%c", 's');
	
	int counter = 0;
	while (counter < moduleLength*moduleCount)
	{
		fputc((int)padStruct -> outgoing[counter],file);
		counter++;
	}


	counter = 0;
	while (counter < moduleLength*moduleCount)
	{
		fputc( (int)padStruct -> incoming[counter],file);
		counter++;
	}

}


char getSymbol(char  val)
{
	return modifiedBase64Alpha[val];
}

int getVal(char c)
{
	int val = 0;

	for(int i = 0 ; i < 64; i++)
	{
		if (modifiedBase64Alpha[i] == c)
		{
			val = i;
		}
	}
	return val;
}

void encodeChunk(char * chunk, char * output) // encodes a three-byte chunk to modified base64 
{


	int chunkVals[4];
	chunkVals[0]=  getVal(chunk[0]);
	chunkVals[1]= getVal(chunk[1]);
	chunkVals[2]= getVal(chunk[2]);
	chunkVals[3]= getVal(chunk[3]);

	output[0] = ((unsigned char)chunkVals[0] << 2)  |  ((unsigned char)chunkVals[1] >> 4);
	output[1] = ((unsigned char)chunkVals[1] << 4) | ((unsigned char)chunkVals[2] >> 2);
	output[2] = ((unsigned char)chunkVals[2] << 6) | ((unsigned char)chunkVals[3]);

}

void decodeChunk(char * chunk, char * output)
{
	output[0] = getSymbol((unsigned char)chunk[0] >> 2);
	output[1] = getSymbol(((unsigned char)((unsigned char)chunk[0] <<6) >>2)| (unsigned char)chunk[1]>>4);
	output[2] = getSymbol(((unsigned char)((unsigned char)chunk[1] << 4) >> 2 )| (unsigned char)chunk[2]>>6);
	output[3] = getSymbol((unsigned char)((unsigned char)chunk[2] << 2) >> 2);

}

void decodeMessage(char * message, char * output)
{


	for (int i = 0; i < moduleLength/3; i++ )
	{
		decodeChunk(&message[3*i], &output[4*i]);

	}
	output[(moduleLength/3)*4]='\0';

}




void encodeMessage(char * message, char * output)
{
	for (int i = 0; i < moduleLength/3; i++ )
	{
		encodeChunk(&message[4*i], &output[3*i]);
	}

}

void printModules(int m, int n, char *  modules)
{


	for (int i = 0; i < m; i++)
	{
		for (int c = 0; c < n; c++)
		{
			printf("%c",modules[(moduleLength * i ) + c]);
		}
		printf("\n");
	}


}

void exportPads()
{
	char *  modules1 = (char * ) malloc( moduleLength * moduleCount);
	char *  modules2 = (char * ) malloc (moduleLength * moduleCount);
	fillModules(moduleLength,moduleCount,modules1);
	fillModules(moduleLength, moduleCount,modules2);

	struct padFile * p1 = malloc(sizeof(padFile));
	struct padFile *  p2 = malloc(sizeof(padFile));

	padFile_init(p1);
	padFile_init(p2);



	p1 -> incoming = modules1; 
	p2 -> incoming = modules2;

	p1 -> outgoing = modules2;
	p2 -> outgoing = modules1;


	FILE *fp1  = fopen("padgroup1.pad", "w+");
	FILE *fp2  = fopen("padgroup2.pad", "w+");

	savePadFile(fp1,p1);
	savePadFile(fp2,p2);
	free(p1);
	free(p2);
	fclose(fp1);
	fclose(fp2);

}


int main(int argc, char *argv[])
{

	printf("Implementation: A Hardware and Operating-System Agnostic Approach to Secure HyperText Communication\n" );

	char input;
	int  terminationFlag = 1;
	while (terminationFlag != 0)
	{
		input = 'n';
		printf("Please select an option:\n a. select padgroup \n b. export padgroups\n c.terminate\n");

		while(input != 'a' && input != 'b' &&  input != 'c')
		{		
			fscanf(stdin, "%c", &input);
		}


		char filePath[100] = {""};


		switch (input){


			case 'a' :  
				printf("%s\n", "Please input file path:");
				fscanf(stdin , "%s", filePath);


				FILE *fp;
				fp =fopen(filePath, "r");
				if(!fp) break;  
				char outgoingPointerTemp[18];
				char outgoingEndTemp[18];
				char incomingPointerTemp[18];
				char incomingEndTemp[18];
				struct padFile * pad  = malloc(sizeof(padFile));
				char * pads = malloc(2 * moduleLength * moduleCount * sizeof(char));
				pad -> outgoing = pads;
				pad -> incoming = &pads[moduleLength * moduleCount * sizeof(char)];		
				fscanf(fp,"%s\n%s\n%s\n%s\n", outgoingPointerTemp,outgoingEndTemp,incomingPointerTemp,incomingEndTemp);
				int buf;
				int counter = 0;
				int startFlag = 0;
				while ((buf = fgetc(fp)) != EOF)
				{
					if(startFlag)
					{

						pads[counter] =(char) buf;
						counter++;
					}
					if(buf == 's')
					{
						startFlag = 1;
					}
				}

				pad -> outgoingPointer = atoi(outgoingPointerTemp);
				pad -> outgoingEnd = atoi(outgoingEndTemp);
				pad -> incomingPointer = atoi(incomingPointerTemp);
				pad -> incomingEnd = atoi(incomingEndTemp);


				int messageFlag = 1;
				while(messageFlag)
				{
					printf("you may send %i more messages and recieve %i more messages\n", pad -> outgoingEnd - pad -> outgoingPointer, pad -> incomingEnd - pad -> incomingPointer);



					input = 'n';
					printf("Please select an option:\n a. send message \n b. recieve message\n c.terminate\n");

					while(input != 'a' && input != 'b' &&  input != 'c')
					{		
						fscanf(stdin, "%c", &input);
					}
					char message[25] = {""};
					char encoded[18] ={""};
					char prepared[25]= {""};
					char *entropy;
					switch(input) {

						case 'a' :
							if(pad->outgoingPointer < pad->outgoingEnd)
							{
								printf("Please input your message\n");


								int c;
								while ((c = getchar()) != '\n' && c != EOF);

								fgets (message, 25, stdin);
								encodeMessage(message, encoded);



								entropy = pad ->outgoing +((moduleLength * (pad -> outgoingPointer)));					

								for(int i = 0; i < moduleLength; i++)
								{
									encoded[i] = encoded[i] ^ entropy[i];


									entropy[i] = 0;
								}
								decodeMessage(encoded, prepared);
								printf("The encrypted message is: %s\n",prepared);
								pad -> outgoingPointer += 1;
							}
							break;

						case 'b' :

							if(pad->incomingPointer < pad->incomingEnd)
							{
								printf("%s\n","Please input your message");


								int c;
								while ((c = getchar()) != '\n' && c != EOF);

								fgets (message, 25, stdin);
								encodeMessage(message, encoded);



								entropy = pad ->incoming +((moduleLength * (pad -> incomingPointer)));					


								for(int i = 0; i < moduleLength; i++)
								{
									encoded[i] = encoded[i] ^ entropy[i];



									entropy[i] = 0;
								}
								decodeMessage(encoded, prepared);
								printf("%s%s\n","The decrypted message is: ",prepared);
								pad -> incomingPointer += 1;
							}




							break;

						case 'c' :
							fclose(fp);
							fp = fopen(filePath, "w+");
							savePadFile(fp,pad);
							free(pads);
							fclose(fp);


							messageFlag = 0;
							break;

					}


				}



				break;

			case 'b' : 
				
							
				
				
				exportPads(); // may add settings for module count at a later date


				break;


			case 'c' :
				terminationFlag = 0;
				break;

		}



	}




	return 0;
} 
