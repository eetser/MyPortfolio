#include "stdio.h"
#include "String.h"
#include "malloc.h"
#include "ctype.h"
#include "time.h"
#include "stdlib.h"
#include "errno.h"
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"
#pragma warning ( disable : 4996 )

// Functions
void PrintObjects(HeaderA* pStruct2);
Object5* CreateObj(char* id, int c);
int InsertNewObject(HeaderA** pStruct2, char* pNewID, int NewCode);
bool IsLetters(char* id);
bool LowerAfterFirst(char* id);
int InputCompatibility(char* id);
Object5* RemoveExistingObject(HeaderA** pStruct2, char* pExistingID);
Node* CreateBinaryTree(HeaderA* pStruct2);
Stack* Push(Stack* pStack, void* pObj);
Stack* Pop(Stack* pStack, void** pObj);
void TreeTraversal(Node* pTree);
bool DoesCodeExist(HeaderA* pStruct2, unsigned long int c);
Node* DeleteTreeNode(Node* pTree, unsigned long int Code);

int main()
{
	// Kirjutage lähtestruktuuri genereeriv lause. See on:
	// a) Struct1 puhul:
	// ObjectO **pStruct = (ObjectO **)GetStruct1(O, N);
	//
	// b) Struct2 puhul:
	// HeaderA *pStruct = GetStruct2(O, N);
	//
	// c) Struct3 puhul:
	// HeaderB *pStruct = GetStruct3(O, N);
	//
	// d) Struct4 puhul:
	// HeaderC *pStruct = GetStruct4(O, N);
	//
	// e) Struct5 puhul:
	// HeaderA **pStruct = GetStruct5(O, N);
	//
	// f) Struct6 puhul:
	// HeaderA *pStruct = GetStruct6(O, N);
	//
	// g) Struct7 puhul:
	// HeaderD *pStruct = GetStruct7(O, N);
	//
	// O asemel kirjutage juhendaja poolt antud objekti indeks.
	// N asemel kirjutage juhendaja poolt antud objektide arv3.
	// N ei ole kunagi 0
	//
	int objectType = 5;
	int numOfObjects = 10;
	const char* id[] = { "Dx", "Db", "Dz", "Dk", "Aa", "Wu",
		"Wa", "Zw", "Za", "wk", "Wa", "WW", "W8", "W_" };
	int codes[] = { 0001, 0010, 0011, 0100, 0101, 0110, 0111, 1000, 1001,
	1010, 1011, 1100, 1101, 1110 };
	//unsigned long int Code = 316985719;	// root node, if N = 35
	//unsigned long int Code = 123665430;	// has only right child, if N = 35
	//unsigned long int Code = 258186307;	// root node, if N = 10
	//unsigned long int Code = 36666300;	// has only right child, if N = 10
	//unsigned long int Code = 1234;		// doesn't exist
	//unsigned long int Code = 197775800;	// has no child, if N = 10
	unsigned long int Code = 145409657;		// has both children, if N = 10


	HeaderA* pStruct = GetStruct2(objectType, numOfObjects);

	PrintObjects(pStruct);

	for (int i = 0; i < 14; i++)
	{
		if (InsertNewObject(&pStruct, (char*)id[i], codes[i]) != 0)
			printf("Lisati objekt %s\n", id[i]);
		else
			printf("Viga lisamisel\n");
	}


	Object5* remObj;
	PrintObjects(pStruct);
	for (int i = 0; i < 14; i++)
	{
		remObj = RemoveExistingObject(&pStruct, (char*)id[i]);
		if (remObj != NULL)
		{
			printf("Eemaldati objekt %s\n", id[i]);
		}
		else
			printf("Viga eemaldamisel\n");
	}

	printf("\n");
	PrintObjects(pStruct);

	// Puuga seotud funktsioonid
	printf("PUUGA SEOTUD FUNKTSIOONID:\n");

	Node* root = CreateBinaryTree(pStruct);
	TreeTraversal(root);

	if (DoesCodeExist(pStruct, Code) == 1)
	{
		printf("Eemaldati objekt koodiga %lu.\n", Code);
		root = DeleteTreeNode(root, Code);
		TreeTraversal(root);
	}
	else
	{
		printf("Kood %lu ei eksisteeri selles puus\n\n", Code);
	}



	free(remObj);

	return 0;
}

void PrintObjects(HeaderA* pStruct2)
{
	int i = 0;

	for (HeaderA* p = pStruct2; p; p = p->pNext)
	{
		Object5* pObj5 = (Object5*)p->pObject;

		for (Object5* d = pObj5; d; d = d->pNext)
		{
			printf("%2d) %s %lu %02d-%02d-%04d\n", i + 1, d->pID, d->Code, d->pDate1->Day, d->pDate1->Month, d->pDate1->Year);
			i++;
		}
	}
	printf("\n\n");
}

Object5* CreateObj(char* id, int c)
{
	time_t kp;
	Object5* pNew = (Object5*)malloc(sizeof(Object5));
	pNew->pID = (char*)malloc(strlen(id) + 1);
	pNew->pID = strcpy(pNew->pID, id);
	pNew->Code = c;
	pNew->pNext = NULL;

	Date1* d = (Date1*)malloc(sizeof(Date1));
	int err = GetDate1(time_t(time(&kp)), d);

	// Kui funktsioon GetDate1 täitis oma ülesande, väljastab ta suuruse 1
	// Errori korral väljastatakse 0
	if (err != 1)
	{
		return NULL;
	}
	pNew->pDate1 = d;

	return pNew;
}

bool IsLetters(char* id)
{
	for (int i = 1; id[i] != '/0'; i++)
	{
		if (!isalpha(id[i]))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool LowerAfterFirst(char* id)
{
	for (int i = 1; id[i] != '/0'; i++)
	{
		if (isupper(id[i]))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return true;
}
int InputCompatibility(char* id)
{
	if (!IsLetters(id))
	{
		return 0;
	}
	if (!LowerAfterFirst(id))
	{
		return 0;
	}
	if (!isupper(id[0]))
	{
		return 0;
	}
}
int InsertNewObject(HeaderA** pStruct2, char* pNewID, int NewCode)
{
	//int i;
	// Kontrollin, et sisend poleks tühi
	if (pStruct2 == NULL || pNewID == NULL || NewCode < 0)
		return 0;

	if (InputCompatibility(pNewID) == 0)
	{
		return 0;
	}

	int cnt = 0;
	HeaderA* p = *pStruct2;

	// Kontrollin, et struktuur oleks tühi
	if (p == NULL)
	{
		// Loon uue HeaderA tyypi siduja
		p = (HeaderA*)malloc(sizeof(HeaderA));
		p->cBegin = pNewID[0];
		p->pObject = NULL;
		p->pNext = NULL;
		*pStruct2 = p;
	}

	// Otsin õige koha, kuhu lisada uus objekt
	while (p)
	{
		// Tähele vastav siduja eksisteerib
		if (p->cBegin == pNewID[0])
		{
			Object5* pObj5 = (Object5*)p->pObject;

			// Kontrollin, kas uus ID juba eksisteerib
			while (pObj5)
			{
				// Kontrollin, kas selline ID juba eksisteerib
				if (strcmp(pObj5->pID, pNewID) == 0)
				{
					return 0;
				}
				pObj5 = pObj5->pNext;
			}
			// Kui ID ei eksisteerinud, lisan uue
			Object5* pNew = CreateObj(pNewID, NewCode);
			// Kontrollin, kas sai luua
			if (pNew == NULL) {
				return 0;
			}
			// Lisan viimaseks
			pNew->pNext = (Object5*)p->pObject;
			p->pObject = pNew;
			return 1;
		}
		// Kui tähele vastavat sidujat ei eksisteeri, lisan selle
		else if ((p->pNext == NULL) || (p->pNext->cBegin > pNewID[0]))
		{
			HeaderA* NewLetter = (HeaderA*)malloc(sizeof(HeaderA));
			NewLetter->cBegin = pNewID[0];
			NewLetter->pObject = NULL; // objekte selles sidujas veel ei eksisteeri
			NewLetter->pNext = NULL;
			if (cnt == 0)
			{
				HeaderA* temp = *pStruct2;
				*pStruct2 = NewLetter;
				NewLetter->pNext = temp;
			}
			else
			{
				NewLetter->pNext = p->pNext;
				p->pNext = NewLetter;
			}
			p = NewLetter;
		}
		else
		{
			p = p->pNext;
		}
		cnt++;
	}
	return 0;
}

Object5* RemoveExistingObject(HeaderA** pStruct2, char* pExistingID)
{
	Object5* pReturn = NULL; //Eemaldatud objekti kustutada ei tohi. Väljundsuuruseks on viit eemaldatud objektile.
	// Kontrollime et sisendid poleks tühjad
	if (pStruct2 == NULL || pExistingID == NULL)
		return pReturn;
	// Kontrollin, et eemaldatava objekt ID oleks sobiv (esimene täht peab olema suur)
	if (!isupper(pExistingID[0]))
		return pReturn;

	// Muutujate deklaratsioon
	HeaderA* p = *pStruct2;
	HeaderA* pPre = NULL;
	Object5* obj = NULL;



	// Otsi siduja ja objekt
		// Kas varasem objekt on samas listis -> jah -> eemalda objekt
		//									  -> ei -> kas pNext == NULL -> jah -> eemalda siduja 
		// Kui ei leidnud -> väljasta pReturn 
	while (p != NULL)
	{
		// Kui siduja on olemas
		if (p->cBegin == pExistingID[0])
		{
			obj = (Object5*)p->pObject;
			Object5* preObj = (Object5*)p->pObject;
			preObj = NULL;
			// Käib sidujas olevad objektid läbi
			while (obj != NULL)
			{
				// Kontrollin, kas sellise ID-ga objekt eksisteerib
				if (strcmp(pExistingID, obj->pID) == 0)
				{
					pReturn = obj;
					// Kui on ainuke objekt listis
					if (preObj == NULL && p->pObject == obj && obj->pNext == NULL)
					{
						// Vastav siduja on keskel/lõpus
						if (pPre != NULL)
						{
							// Eemaldan vastava siduja
							pPre->pNext = p->pNext;
						}
						// Vastav siduja on ahelloendi alguses
						else if (p->pNext != NULL)
						{
							*pStruct2 = p->pNext;
						}
					}
					else if (preObj == NULL && p->pObject == obj && obj->pNext != NULL)
					{
						p->pObject = obj->pNext;
					}
					else
					{
						preObj->pNext = obj->pNext;
					}
					return pReturn;
				}
				// Kui sellise ID-ga objekti ei leitud, siis eelmisest objektist saab järgmine objekt
				preObj = obj;
				obj = obj->pNext;
			}
			// Objekti polnud sidujas
			return NULL;
		}
		// Sellist sidujat ei leitud
		pPre = p;
		p = p->pNext;
	}
	// Kui töö ei õnnestunud, tagastan NULLi (funkts. algul pReturn == NULL)
	return pReturn;
}

Node* CreateBinaryTree(HeaderA* pStruct2)
{
	// Initialize root to NULL
	Node* root = NULL;

	for (HeaderA* p = pStruct2; p; p = p->pNext)
	{
		Object5* pObj = (Object5*)p->pObject; // Use the current header's object pointer
		for (Object5* d = pObj; d; d = d->pNext)
		{
			// Allocate memory for a new node
			Node* temp = (Node*)malloc(sizeof(Node));
			if (!temp)
			{
				printf("Memory allocation failed.\n");
				exit(EXIT_FAILURE); // Handle memory allocation failure
			}

			temp->pObject = d;
			temp->pLeft = NULL;
			temp->pRight = NULL;

			unsigned long int key = d->Code;

			Node* ptr = root;
			Node* parent = NULL;

			// Find the correct position for the new node in the binary tree
			while (ptr != NULL)
			{
				parent = ptr;
				if (key < ((Object5*)ptr->pObject)->Code)
					ptr = ptr->pLeft;
				else if (key > ((Object5*)ptr->pObject)->Code)
					ptr = ptr->pRight;
				else
				{
					printf("Object with this code is already added to the tree.\n");
					free(temp); // Free the allocated memory before returning
					return root;
				}
			}

			// Update the parent's pointer to the new node
			if (parent == NULL)
				root = temp;
			else if (key < ((Object5*)parent->pObject)->Code)
				parent->pLeft = temp;
			else
				parent->pRight = temp;
		}
	}

	return root;
}

Stack* Push(Stack* pStack, void* pObj)
{
	errno = 0;
	Stack* pNew;

	if (!pObj)
	{
		errno = EINVAL;
		return pStack;
	}

	pNew = (Stack*)malloc(sizeof(Stack));
	if (!pNew)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE); // Handle memory allocation failure
	}

	pNew->pObject = pObj;
	pNew->pNext = pStack;

	return pNew;
}

Stack* Pop(Stack* pStack, void** pObj)
{
	Stack* p;

	if (!pStack)
	{
		*pObj = NULL;
		return pStack;
	}

	*pObj = pStack->pObject;
	p = pStack->pNext;
	free(pStack);

	return p;
}


void TreeTraversal(Node* pTree)
{
	int i = 0;
	Stack* pStack = NULL;
	Node* ptr = pTree;

	if (ptr == NULL)
	{
		printf("Puu on tühi\n");
		return;
	}

	while (ptr != NULL || pStack != NULL)
	{
		while (ptr != NULL)
		{
			pStack = Push(pStack, ptr);
			ptr = ptr->pLeft;
		}

		if (pStack != NULL)
		{
			ptr = (Node*)pStack->pObject;
			pStack = Pop(pStack, (void**)&ptr);
			Object5* Obj = (Object5*)ptr->pObject;

			printf("%2d) %s %lu %02d-%02d-%04d\n", i + 1, Obj->pID, Obj->Code, Obj->pDate1->Day, Obj->pDate1->Month, Obj->pDate1->Year);
			i++;

			ptr = ptr->pRight;
		}
	}
	printf("\n");
}


bool DoesCodeExist(HeaderA* pStruct2, unsigned long int c)
{
	for (HeaderA* p = pStruct2; p; p = p->pNext)
	{
		Object5* pObj5 = (Object5*)p->pObject;

		for (Object5* d = pObj5; d; d = d->pNext)
		{
			if (d->Code == c)
				return true;
		}
	}
	return false;
}

Node* DeleteTreeNode(Node* pTree, unsigned long int Code) {
	Node* current = pTree;
	Node* parent = NULL;
	Node* child = pTree;

	// Find the node to be deleted
	while (current != NULL && ((Object5*)current->pObject)->Code != Code) {
		parent = current;
		if (Code < ((Object5*)current->pObject)->Code)
			current = current->pLeft;
		else
			current = current->pRight;
	}

	// Node has two children
	if (current->pLeft != NULL && current->pRight != NULL) {
		Node* successorParent = current;
		Node* successor = current->pRight;

		// Find the leftmost node in the right subtree
		while (successor->pLeft != NULL) {
			successorParent = successor;
			successor = successor->pLeft;
		}

		// Replace the data of the current node with the successor's data
		((Object5*)current->pObject)->Code = ((Object5*)successor->pObject)->Code;
		((Object5*)current->pObject)->pID = ((Object5*)successor->pObject)->pID;

		current = successor;
		parent = successorParent;
	}

	// Node has at most one child
	child = (current->pLeft != NULL) ? current->pLeft : current->pRight;

	// Root node case
	if (parent == NULL)
		pTree = child;
	else if (current == parent->pLeft)
		parent->pLeft = child;
	else
		parent->pRight = child;

	free(current);
	return pTree;
}





