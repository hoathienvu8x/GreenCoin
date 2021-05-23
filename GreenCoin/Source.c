
#include "src/BlockChain/BlockChain.h"
#include "src/CommandLine/ExternalCommandLine.h"
#include "src/Network/Network.h"

#include <stdio.h>



int Demo() {

	srand(time(NULL));

	// Get ip
	printf("Please enter your ip: ");
	char buf[64] = { 0 };
	fgets(buf, sizeof(buf), stdin);
	unsigned long ip = inet_addr(buf);
	memcpy(LOCALHOST_IP, &ip, sizeof(ip));

	Load_Block_History_Path();

	Load_Domain_Parameters();

	Load_Local_Notary_Signing_Address();

	WSADATA * wsadata = NULL;
	SOCKET * socket = NULL;

	HANDLE server_thread = Network_Demo(wsadata, socket);

	uint64_t ind = 0;
	while (Block_Index_Exists(ind)) { ind++; }


	FILE* f;
	Open_Block_File(&f, ind - 1);
	if (f != NULL) {
		_Block* b;

		FILE* f;
		Open_Block_File(&f, ind - 1);
		char* block_buffer = (char*)malloc(sizeof(_Block));
		fseek(f, 4, SEEK_SET);
		fread(block_buffer, sizeof(_Block), 1, f);

		char* hash = Hash_SHA256(block_buffer, sizeof(_Block));


		b = Create_Block(ind, hash);

		fclose(f);
		free(hash);

		live_block = b;
	}
	else {
		Create_First_Block(wsadata, socket);
	}

	while (1) {
		Transaction_Demo_Spam(wsadata, socket);
	}
	//BlockChain_Demo();

	//Print_Demo_Keys();

	//Transaction_Demo();

	/*srand(time(NULL));

	uint p; BN_Init(&p);
	uint q; BN_Init(&q);

	uint_t N = 5;
	uint_t L = 31;

	//BN_Set_Value(q, 6071717768788351249);
	//DSA_Generate_P(p, q, L);

	char * q_file_path = "C:\\Users\\stein\\Desktop\\GreenCoin\\Globals\\q.hex";
	char * p_file_path = "C:\\Users\\stein\\Desktop\\GreenCoin\\Globals\\p.hex";

	FILE * fq;
	FILE * fp;
	fopen_s(&fq, q_file_path, "rb");
	fopen_s(&fp, p_file_path, "rb");

	char q_bin[20];
	char p_bin[128];

	fread(q_bin, sizeof(char), 20, fq);
	fread(p_bin, sizeof(char), 128, fp);

	fclose(fq);
	fclose(fp);

	BN_Import(q, q_bin, 20, BN_BIG_ENDIAN);
	BN_Import(p, p_bin, 128, BN_BIG_ENDIAN);


	uint G; BN_Init(&G);
	uint h; BN_Init(&h);
	BN_Set_Value(h, 2);

	DSA_Generate_G(G, p, q, h);

	DSA_Private_Key * priv_key = 0;
	DSA_Public_Key * pub_key = 0;

	DSA_Init_Private_Key(&priv_key);
	DSA_Init_Public_Key(&pub_key);

	DSA_Load_Private_Key(priv_key, p, q, G);
	DSA_Load_Public_Key(pub_key, p, q, G);

	DSA_Create_Keys(priv_key, pub_key);
	TRACE_DEBUG("  x:\r\n");
	TRACE_DEBUG_MPI("    ", (priv_key->x));
	TRACE_DEBUG("  y:\r\n");
	TRACE_DEBUG_MPI("    ", (pub_key->y));





	_Transaction transaction;
	transaction.Index = 0;
	memset(transaction.Reciever, 0, sizeof(_Wallet_Address));
	memcpy(transaction.Sender, pub_key->y->data, sizeof(_Wallet_Address));
	transaction.Value = 10;
	transaction.Fee = 0;

	char * transaction_info = (char*)malloc(sizeof(_Transaction) - sizeof(_Signature));
	memcpy(transaction_info, &transaction, sizeof(_Transaction) - sizeof(_Signature));

	//char * message = "abc";
	char * message_digest = Hash_SHA256(transaction_info, sizeof(_Transaction) - sizeof(_Signature));//"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

	printf("Hash: %s\n", message_digest);

	BN aaa; BN_Init_Stack(&aaa);
	BN_Import_Hex_String(&aaa, message_digest, 64, BN_BIG_ENDIAN);
	_Hash has;
	memcpy(has.Bytes, aaa.data, 8 * sizeof(uint32_t));
	Print_Hash(stderr, has.Bytes);

	DSA_Signature * signature = 0;
	DSA_Init_Signature(&signature);

	DSA_Generate_Signature(priv_key, message_digest, 256, signature);

	_Signature sig;
	memcpy((sig.r), signature->r->data, 5 * sizeof(uint_t));
	memcpy((sig.s), signature->s->data, 5 * sizeof(uint_t));

	memcpy(&(transaction.Signature), &sig, sizeof(_Signature));

	Transaction_Export_To_File("C:\\Users\\stein\\Desktop\\GreenCoin\\Globals\\Transaction_Test1.GCT", &transaction);

	DSA_Domain_Parameters params;
	params.G = priv_key->G;
	params.p = priv_key->p;
	params.q = priv_key->q;

	Print_Transaction(stderr, &params, &transaction);*/
}

int main_c(int argc, char ** argv) {

	if (argc > 1) { Execute_External_Commands(argc, argv); }
	
	
	
	else {
		Demo();
	}
	
	if (argc > 1) {
		printf("Press ENTER to close.\n");
		getchar();
	}
}