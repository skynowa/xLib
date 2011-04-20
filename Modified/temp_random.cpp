#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <wincrypt.h>
//---------------------------------------------------------------------------
#include <wincrypt.h>
HCRYPTPROV g_hCrypt;
  
bool my_random_init();
void my_random_shutdown();
void get_random_bytes(int size,char* buf);
char get_random_byte();
int get_random_int();
//---------------------------------------------------------------------------
bool my_random_init() {
	//Init CryptoAPI for random generation
	if(!CryptAcquireContext(&g_hCrypt,NULL,NULL,PROV_RSA_FULL,CRYPT_VERIFYCONTEXT))  {
		std::cout << "CryptAcquireContext error" << std::endl;
		return false;
	}  else {
		return true;
	}
}
//---------------------------------------------------------------------------
void my_random_shutdown() {
	//Clean up CryptoAPI
	CryptReleaseContext(g_hCrypt,0);
}
//---------------------------------------------------------------------------
void get_random_bytes(int size, char* buf) {
	//Fill buf with random bytes ranging from 0x00 to 0xFF
	CryptGenRandom(g_hCrypt,size, (unsigned char*)buf);

	buf[size - 1] = '\0';
}  
//---------------------------------------------------------------------------
char get_random_byte() {
	//Return a single random byte from 0x00 to 0xFF
	char ret;
	get_random_bytes(sizeof(ret),&ret);
	
	return ret;
}  
//---------------------------------------------------------------------------
int get_random_int() {
	//Return a random integer from 0 to INT_MAX
	int ret;
	get_random_bytes(sizeof(ret), (char *)&ret);

	return ret;
}
//---------------------------------------------------------------------------
int main(int argc, char* argv[]) {


	for (int i = 0; i < 4; i ++) {
		char         szBuff[8];
		
		my_random_init();
		get_random_bytes(8, szBuff);
		std::cout << szBuff << std::endl;
		my_random_shutdown();
	}






	system("pause");

	return 0;
}
//---------------------------------------------------------------------------

