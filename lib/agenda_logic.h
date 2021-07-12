/*	Proyecto Davinia | agenda_logic.h
	En este archivo se ha programado la l�gica que hace que se agreguen nuevos
contactos y que se puedan visualizar.
*/

void	listContactsFunc(void), // Visualiza todos los contactos en la DB
		addContactFunc(void); // Agrega nuevos contactos en la DB

//Visualiza los contactos almacenados en "ficheros/contacts_db.txt"
void listContactsFunc(){
	/*Kenneth Lola | Proyecto Davinia | Julio 08, 2021 | listContactsFunc()
	DESCRIPCION DE VARIABLES
	------------------------
	fp		>> base de datos de contactos
	c		>> Caracter que almacena cada caracter de la base de datos
	EOF		>> final del fichero
	N		>> Cantidad de productos a ingresar
	*/
	
	FILE *fp;
	char c;
	
	fp=fopen("ficheros/contacts_db.txt", "r");
	
	if(fp==NULL){
		printf("\n No se ha podido abrir el fichero");
		exit(1);
	}
	
	clearScreen();
	printf("ID\tNombre         Apellido       Edad      Tel�fono    Fecha de nacimiento\n");
	printf("~~\t~~~~~~         ~~~~~~~~       ~~~~      ~~~~~~~~    ~~~~~~~~~~~~~~~~~~~\n");

	
	c=fgetc(fp);
	while(c!=EOF){
		printf("%c", c);
		c=fgetc(fp);
	}
	
	fclose(fp);
	printf("\n");
	
	puts("Presiona una tecla para continuar...");
	
	getchar();
	getchar();
	clearScreen();
}

// Agrega nuevos contactos a la DB "ficheros/contacts_db.txt"
void addContactFunc(void) {
	/*Jeremy Fonseca | Proyecto Davinia | Julio 07, 2021 | addContactFunc()
	DESCRIPCI�N DE VARIABLES
	------------------------
	contactDBFile			>> Fichero con la DB de los contactos
	contactsNumberFile		>> Fichero con la cantidad total de contactos
	i						>> Contador
	N						>> Cantidad de productos a ingresar
	cant					>> Cantidad de contactos
	contactID				>> Identificacion de cada contacto
	contactsNumber			>> Numero de productos en DB
	*/
	
	// Estructuras
	typedef struct Birthday {
		int d, m, y;
	} Birthday;
	
	struct Contact {
		char name[20], lastname[20], address[50], contactID[2];
		long int number;
		short int age;
		Birthday birthday;
	} Contact;
	
	FILE *contactDBFile, *contactsNumberFile;
	short int i, N, rsult;
	int contactsNumber;
	
	// Abrir ficheros a editar
	contactDBFile = fopen("ficheros/contacts_db.txt", "a+");
	contactsNumberFile = fopen("ficheros/contacts_number.txt", "r");
	
	fscanf(contactsNumberFile, "%i", &contactsNumber); // Obtener la cantidad total de productos en la DB
	
	clearScreen();
	printf("(Cantidad de contactos: %i/100.)\n", (contactsNumber - 1));
	printf("Contactos a ingresar: ");
	scanf("%hi", &N);
	
	// Verificar el n�mero ingresado
	rsult = (N < 0 || N >= 100);
	if (rsult) {
		clearScreen();
		printf("Error: (%hi) Car�cter o n�mero ilegal.\n", N);
		exit(EXIT_SUCCESS);
	}
	
	for (i = 1; i <= N; i++) {
		clearScreen();
		printf("Contacto [%i]\n", i);
		
		// Agrega un '0' si la cantidad de productos en DB es de 1 digito
		if (contactsNumber < 10) {
			Contact.contactID[0] = '0';
			Contact.contactID[1] = contactsNumber; // Numero de un digito
			// Imprimir el contactID del producto en la DB
			fprintf(contactDBFile, "%c", Contact.contactID[0]);
			fprintf(contactDBFile, "%i", Contact.contactID[1]);
		} else {
			*Contact.contactID = contactsNumber;
			// Imprimir el contactID del producto en la DB
			fprintf(contactDBFile, "%i", *Contact.contactID);
		}
		++contactsNumber;
		
		fclose(contactsNumberFile);
		contactsNumberFile = fopen("ficheros/contacts_number.txt", "w"); // Abriril it_cant.txt en modo escritura
		fprintf(contactsNumberFile, "%i", contactsNumber); // Actualiza la cantidad de contactos en la DB
		fclose(contactsNumberFile);
		
		fputc('\t', contactDBFile);
		
		// Peticion de los datos de los contactos
		// Nombre
		printf("Nombre: ");
		scanf("%s", Contact.name);
		fprintf(contactDBFile, "%-15s", Contact.name);
		
		// Apellido
		printf("Apellido: ");
		scanf("%s", Contact.lastname);
		fprintf(contactDBFile, "%-15s", Contact.lastname);
		
		do {
			// Edad
			printf("Edad: ");
			scanf("%hi", &Contact.age);
			fprintf(contactDBFile, "%-10hi", Contact.age);
			
			if (Contact.age <= 10 || Contact.age >= 100) printf("Error: Edad incorrecta.\n");
		} while(Contact.age <= 10 || Contact.age >= 100);
		
		// Telefono
		printf("Telefono: ");
		scanf("%li", &Contact.number);
		fprintf(contactDBFile, "%-12li", Contact.number);
		
		// Fecha de nacimiento
		printf("Fecha de nacimiento (N�meros)\n");
		printf("D�a: "); scanf("%i", &Contact.birthday.d);
		printf("Mes: "); scanf("%i", &Contact.birthday.m);
		printf("A�o: "); scanf("%i", &Contact.birthday.y);
		
		fprintf(contactDBFile, "%i", Contact.birthday.d);
		fputc('/', contactDBFile);
		fprintf(contactDBFile, "%i", Contact.birthday.m);
		fputc('/', contactDBFile);
		fprintf(contactDBFile, "%i", Contact.birthday.y);
		fputc('/', contactDBFile);
		
		fputc('\n', contactDBFile); // Salto de linea
	}
	fclose(contactDBFile);
	return;
}
